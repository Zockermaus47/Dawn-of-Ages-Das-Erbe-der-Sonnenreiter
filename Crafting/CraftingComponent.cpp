#include "Crafting/CraftingComponent.h"
#include "Inventory/InventoryComponent.h"

UCraftingComponent::UCraftingComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    MaxCraftingSlots = 3;
    AvailableSlots = 3;
}

void UCraftingComponent::BeginPlay()
{
    Super::BeginPlay();
    ActiveCrafting.SetNum(MaxCraftingSlots);
    for (int32 i = 0; i < MaxCraftingSlots; i++)
    {
        ActiveCrafting[i].bIsCrafting = false;
        ActiveCrafting[i].SlotsRemaining = MaxCraftingSlots;
    }
}

void UCraftingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    UpdateCrafting(DeltaTime);
}

void UCraftingComponent::UpdateCrafting(float DeltaTime)
{
    for (int32 i = 0; i < ActiveCrafting.Num(); i++)
    {
        if (ActiveCrafting[i].bIsCrafting)
        {
            ActiveCrafting[i].CurrentTime += DeltaTime;
            
            const FCraftingRecipe* Recipe = GetRecipe(ActiveCrafting[i].RecipeID);
            if (Recipe && ActiveCrafting[i].CurrentTime >= Recipe->CraftingTime)
            {
                CompleteCrafting(i);
            }
        }
    }
}

const FCraftingRecipe* UCraftingComponent::GetRecipe(FName RecipeID) const
{
    for (const FCraftingRecipe& Recipe : KnownRecipes)
    {
        if (Recipe.RecipeID == RecipeID) return &Recipe;
    }
    return nullptr;
}

bool UCraftingComponent::HasMaterials(const FCraftingRecipe* Recipe) const
{
    if (!Recipe) return false;

    UInventoryComponent* Inventory = GetOwner()->FindComponentByClass<UInventoryComponent>();
    if (!Inventory) return false;

    for (int32 i = 0; i < Recipe->RequiredMaterials.Num(); i++)
    {
        FName Material = Recipe->RequiredMaterials[i];
        int32 RequiredQty = Recipe->RequiredQuantities[i];
        
        if (!Inventory->HasItem(Material, RequiredQty))
        {
            return false;
        }
    }
    return true;
}

void UCraftingComponent::ConsumeMaterials(const FCraftingRecipe* Recipe)
{
    if (!Recipe) return;

    UInventoryComponent* Inventory = GetOwner()->FindComponentByClass<UInventoryComponent>();
    if (!Inventory) return;

    for (int32 i = 0; i < Recipe->RequiredMaterials.Num(); i++)
    {
        FName Material = Recipe->RequiredMaterials[i];
        int32 RequiredQty = Recipe->RequiredQuantities[i];
        Inventory->RemoveItem(Material, RequiredQty);
    }
}

bool UCraftingComponent::CanCraft(FName RecipeID) const
{
    const FCraftingRecipe* Recipe = GetRecipe(RecipeID);
    if (!Recipe) return false;

    for (const FCraftingProgress& Progress : ActiveCrafting)
    {
        if (Progress.bIsCrafting && Progress.RecipeID == RecipeID)
        {
            return false;
        }
    }

    UInventoryComponent* Inventory = GetOwner()->FindComponentByClass<UInventoryComponent>();
    if (!Inventory) return false;

    return HasMaterials(Recipe);
}

bool UCraftingComponent::StartCrafting(FName RecipeID)
{
    const FCraftingRecipe* Recipe = GetRecipe(RecipeID);
    if (!Recipe)
    {
        UE_LOG(LogTemp, Warning, TEXT("Rezept nicht gefunden: %s"), *RecipeID.ToString());
        return false;
    }

    if (!HasMaterials(Recipe))
    {
        UE_LOG(LogTemp, Warning, TEXT("Nicht genug Materialien!"));
        return false;
    }

    int32 FreeSlot = -1;
    for (int32 i = 0; i < ActiveCrafting.Num(); i++)
    {
        if (!ActiveCrafting[i].bIsCrafting)
        {
            FreeSlot = i;
            break;
        }
    }

    if (FreeSlot == -1)
    {
        UE_LOG(LogTemp, Warning, TEXT("Keine freien Crafting-Slots!"));
        return false;
    }

    ConsumeMaterials(Recipe);

    ActiveCrafting[FreeSlot].RecipeID = RecipeID;
    ActiveCrafting[FreeSlot].CurrentTime = 0.0f;
    ActiveCrafting[FreeSlot].bIsCrafting = true;
    ActiveCrafting[FreeSlot].SlotsRemaining = MaxCraftingSlots;

    UE_LOG(LogTemp, Log, TEXT("Starte Crafting: %s"), *Recipe->RecipeName.ToString());
    return true;
}

void UCraftingComponent::CancelCrafting(int32 SlotIndex)
{
    if (SlotIndex < 0 || SlotIndex >= ActiveCrafting.Num()) return;
    
    ActiveCrafting[SlotIndex].bIsCrafting = false;
    ActiveCrafting[SlotIndex].CurrentTime = 0.0f;
    ActiveCrafting[SlotIndex].RecipeID = NAME_None;
}

bool UCraftingComponent::CompleteCrafting(int32 SlotIndex)
{
    if (SlotIndex < 0 || SlotIndex >= ActiveCrafting.Num()) return false;
    if (!ActiveCrafting[SlotIndex].bIsCrafting) return false;

    const FCraftingRecipe* Recipe = GetRecipe(ActiveCrafting[SlotIndex].RecipeID);
    if (!Recipe) return false;

    UInventoryComponent* Inventory = GetOwner()->FindComponentByClass<UInventoryComponent>();
    if (Inventory)
    {
        Inventory->AddItem(Recipe->OutputItemID, Recipe->OutputQuantity);
        UE_LOG(LogTemp, Log, TEXT("Crafting abgeschlossen: %s x%d"), *Recipe->OutputItemID.ToString(), Recipe->OutputQuantity);
    }

    ActiveCrafting[SlotIndex].bIsCrafting = false;
    ActiveCrafting[SlotIndex].CurrentTime = 0.0f;
    ActiveCrafting[SlotIndex].RecipeID = NAME_None;

    return true;
}

void UCraftingComponent::LearnRecipe(FCraftingRecipe Recipe)
{
    for (const FCraftingRecipe& Known : KnownRecipes)
    {
        if (Known.RecipeID == Recipe.RecipeID) return;
    }
    
    KnownRecipes.Add(Recipe);
    UE_LOG(LogTemp, Log, TEXT("Neues Rezept gelernt: %s"), *Recipe.RecipeName.ToString());
}

void UCraftingComponent::ClearRecipe(FName RecipeID)
{
    KnownRecipes.RemoveAll([RecipeID](const FCraftingRecipe& R) { return R.RecipeID == RecipeID; });
}

bool UCraftingComponent::HasLearnedRecipe(FName RecipeID) const
{
    for (const FCraftingRecipe& Recipe : KnownRecipes)
    {
        if (Recipe.RecipeID == RecipeID) return true;
    }
    return false;
}

TArray<FCraftingRecipe> UCraftingComponent::GetRecipesByCategory(ECraftingCategory Category) const
{
    TArray<FCraftingRecipe> Results;
    for (const FCraftingRecipe& Recipe : KnownRecipes)
    {
        if (Recipe.Category == Category) Results.Add(Recipe);
    }
    return Results;
}

TArray<FCraftingRecipe> UCraftingComponent::GetAvailableRecipes() const
{
    return KnownRecipes;
}

int32 UCraftingComponent::GetCraftingSlotCount() const
{
    return MaxCraftingSlots;
}
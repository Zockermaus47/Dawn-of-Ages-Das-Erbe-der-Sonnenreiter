#include "CraftingComponent.h"
#include "InventorySystemComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

UCraftingComponent::UCraftingComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UCraftingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bIsCrafting)
    {
        CraftingTimeRemaining -= DeltaTime;

        if (CraftingTimeRemaining <= 0.0f)
        {
            CompleteCrafting();
        }
    }
}

bool UCraftingComponent::HasRequiredItems(const FCraftingRecipe& Recipe) const
{
    return true;
}

void UCraftingComponent::ConsumeRequiredItems(const FCraftingRecipe& Recipe)
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    UInventorySystemComponent* Inventory = Owner->FindComponentByClass<UInventorySystemComponent>();
    if (!Inventory) return;

    for (const auto& ItemPair : Recipe.RequiredItems)
    {
        Inventory->RemoveItem(ItemPair.Key, ItemPair.Value);
    }
}

bool UCraftingComponent::CanCraft(FName RecipeID) const
{
    FCraftingRecipe Recipe = GetRecipe(RecipeID);
    if (Recipe.RecipeID == NAME_None) return false;

    if (Recipe.RequiredWorkbenchLevel > WorkbenchLevel && !bCanCraftAnywhere)
    {
        return false;
    }

    return true;
}

void UCraftingComponent::StartCrafting(FName RecipeID)
{
    if (bIsCrafting)
    {
        CancelCrafting();
    }

    FCraftingRecipe Recipe = GetRecipe(RecipeID);
    if (Recipe.RecipeID == NAME_None) return;

    if (!CanCraft(RecipeID)) return;

    ConsumeRequiredItems(Recipe);

    bIsCrafting = true;
    CurrentRecipeID = RecipeID;
    CraftingTimeTotal = Recipe.CraftingTime;
    CraftingTimeRemaining = Recipe.CraftingTime;

    OnCraftingStarted.Broadcast(RecipeID);
}

void UCraftingComponent::CancelCrafting()
{
    if (!bIsCrafting) return;

    FName CancelledRecipeID = CurrentRecipeID;
    
    bIsCrafting = false;
    CurrentRecipeID = NAME_None;
    CraftingTimeRemaining = 0.0f;
    CraftingTimeTotal = 0.0f;

    OnCraftingCancelled.Broadcast(CancelledRecipeID);
}

void UCraftingComponent::CompleteCrafting()
{
    if (!bIsCrafting) return;

    FCraftingRecipe Recipe = GetRecipe(CurrentRecipeID);
    FName CompletedRecipeID = CurrentRecipeID;

    bIsCrafting = false;
    CurrentRecipeID = NAME_None;
    CraftingTimeRemaining = 0.0f;
    CraftingTimeTotal = 0.0f;

    AActor* Owner = GetOwner();
    if (Owner)
    {
        UInventorySystemComponent* Inventory = Owner->FindComponentByClass<UInventorySystemComponent>();
        if (Inventory)
        {
            for (int32 i = 0; i < Recipe.ResultQuantity; i++)
            {
                Inventory->AddItem(Recipe.ResultItemID, 1);
            }
        }
    }

    OnCraftingCompleted.Broadcast(CompletedRecipeID, true);
}

TArray<FName> UCraftingComponent::GetAvailableRecipes() const
{
    TArray<FName> RecipeIDs;
    for (const FCraftingRecipe& Recipe : AvailableRecipes)
    {
        RecipeIDs.Add(Recipe.RecipeID);
    }
    return RecipeIDs;
}

TArray<FName> UCraftingComponent::GetCraftableRecipes() const
{
    TArray<FName> Craftable;
    for (const FCraftingRecipe& Recipe : AvailableRecipes)
    {
        if (CanCraft(Recipe.RecipeID))
        {
            Craftable.Add(Recipe.RecipeID);
        }
    }
    return Craftable;
}

FCraftingRecipe UCraftingComponent::GetRecipe(FName RecipeID) const
{
    for (const FCraftingRecipe& Recipe : AvailableRecipes)
    {
        if (Recipe.RecipeID == RecipeID)
        {
            return Recipe;
        }
    }
    return FCraftingRecipe();
}

void UCraftingComponent::AddRecipe(const FCraftingRecipe& Recipe)
{
    for (int32 i = 0; i < AvailableRecipes.Num(); i++)
    {
        if (AvailableRecipes[i].RecipeID == Recipe.RecipeID)
        {
            AvailableRecipes[i] = Recipe;
            return;
        }
    }
    AvailableRecipes.Add(Recipe);
}

void UCraftingComponent::RemoveRecipe(FName RecipeID)
{
    AvailableRecipes.RemoveAll([RecipeID](const FCraftingRecipe& Recipe) {
        return Recipe.RecipeID == RecipeID;
    });
}

float UCraftingComponent::GetCraftingProgress() const
{
    if (CraftingTimeTotal > 0.0f)
    {
        return 1.0f - (CraftingTimeRemaining / CraftingTimeTotal);
    }
    return 0.0f;
}
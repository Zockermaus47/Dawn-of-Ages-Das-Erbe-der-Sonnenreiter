#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Harvesting/ResourceTypes.h"
#include "CraftingComponent.generated.h"

UENUM(BlueprintType)
enum class ECraftingCategory : uint8
{
    Weapons UMETA(DisplayName = "Waffen"),
    Armor UMETA(DisplayName = "Rüstung"),
    Tools UMETA(DisplayName = "Werkzeuge"),
    Building UMETA(DisplayName = "Bauen"),
    Food UMETA(DisplayName = "Essen"),
    Alchemy UMETA(DisplayName = "Alchemie"),
    Metalwork UMETA(DisplayName = "Metallverarbeitung")
};

UENUM(BlueprintType)
enum class ECraftingStation : uint8
{
    None UMETA(DisplayName = "Keine"),
    Workbench UMETA(DisplayName = "Werkbank"),
    Forge UMETA(DisplayName = "Schmiede"),
    Cauldron UMETA(DisplayName = "Kessel"),
    Anvil UMETA(DisplayName = "Amboss"),
    Kiln UMETA(DisplayName = "Ofen"),
    Loom UMETA(DisplayName = "Webstuhl")
};

USTRUCT(BlueprintType)
struct FCraftingRecipe
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RecipeID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RecipeName = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECraftingCategory Category = ECraftingCategory::Tools;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECraftingStation RequiredStation = ECraftingStation::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CraftingTime = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 OutputQuantity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName OutputItemID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> RequiredMaterials;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> RequiredQuantities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEpoch RequiredEpoch = EEpoch::StoneAge;
};

USTRUCT(BlueprintType)
struct FCraftingProgress
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RecipeID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCrafting = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SlotsRemaining = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_DAWNOFAGES_API UCraftingComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UCraftingComponent();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
    int32 MaxCraftingSlots = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
    TArray<FCraftingRecipe> KnownRecipes;

    UPROPERTY(BlueprintReadOnly, Category = "Crafting")
    TArray<FCraftingProgress> ActiveCrafting;

    UPROPERTY(BlueprintReadOnly, Category = "Crafting")
    int32 AvailableSlots = 3;

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    bool CanCraft(FName RecipeID) const;

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    bool StartCrafting(FName RecipeID);

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    void CancelCrafting(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    bool CompleteCrafting(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    void LearnRecipe(FCraftingRecipe Recipe);

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    void ClearRecipe(FName RecipeID);

    UFUNCTION(BlueprintPure, Category = "Crafting")
    bool HasLearnedRecipe(FName RecipeID) const;

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    TArray<FCraftingRecipe> GetRecipesByCategory(ECraftingCategory Category) const;

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    TArray<FCraftingRecipe> GetAvailableRecipes() const;

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    int32 GetCraftingSlotCount() const;

private:
    void UpdateCrafting(float DeltaTime);
    const FCraftingRecipe* GetRecipe(FName RecipeID) const;
    bool HasMaterials(const FCraftingRecipe* Recipe) const;
    void ConsumeMaterials(const FCraftingRecipe* Recipe);
};
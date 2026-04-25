#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemData.h"
#include "CraftingComponent.generated.h"

USTRUCT(BlueprintType)
struct FCraftingRecipe
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RecipeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, int32> RequiredItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ResultItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ResultQuantity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CraftingTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredWorkbenchLevel = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> RequiredTags;

    FCraftingRecipe()
    {
        RecipeID = NAME_None;
        ResultQuantity = 1;
        CraftingTime = 0.0f;
        RequiredWorkbenchLevel = 0;
    }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCraftingStarted, FName, RecipeID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCraftingCompleted, FName, RecipeID, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCraftingCancelled, FName, RecipeID);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_SPIEL_API UCraftingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCraftingComponent();

    UFUNCTION(BlueprintCallable)
    bool CanCraft(FName RecipeID) const;

    UFUNCTION(BlueprintCallable)
    void StartCrafting(FName RecipeID);

    UFUNCTION(BlueprintCallable)
    void CancelCrafting();

    UFUNCTION(BlueprintCallable)
    void CompleteCrafting();

    UFUNCTION(BlueprintCallable)
    TArray<FName> GetAvailableRecipes() const;

    UFUNCTION(BlueprintCallable)
    TArray<FName> GetCraftableRecipes() const;

    UFUNCTION(BlueprintCallable)
    FCraftingRecipe GetRecipe(FName RecipeID) const;

    UFUNCTION(BlueprintCallable)
    void AddRecipe(const FCraftingRecipe& Recipe);

    UFUNCTION(BlueprintCallable)
    void RemoveRecipe(FName RecipeID);

    UFUNCTION(BlueprintPure)
    bool IsCrafting() const { return bIsCrafting; }

    UFUNCTION(BlueprintPure)
    float GetCraftingProgress() const;

    UFUNCTION(BlueprintPure)
    FName GetCurrentRecipeID() const { return CurrentRecipeID; }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
    TArray<FCraftingRecipe> AvailableRecipes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
    int32 WorkbenchLevel = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
    bool bCanCraftAnywhere = true;

    UPROPERTY(BlueprintAssignable)
    FOnCraftingStarted OnCraftingStarted;

    UPROPERTY(BlueprintAssignable)
    FOnCraftingCompleted OnCraftingCompleted;

    UPROPERTY(BlueprintAssignable)
    FOnCraftingCancelled OnCraftingCancelled;

protected:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY()
    bool bIsCrafting = false;

    UPROPERTY()
    FName CurrentRecipeID = NAME_None;

    UPROPERTY()
    float CraftingTimeRemaining = 0.0f;

    UPROPERTY()
    float CraftingTimeTotal = 0.0f;

    bool HasRequiredItems(const FCraftingRecipe& Recipe) const;
    void ConsumeRequiredItems(const FCraftingRecipe& Recipe);
};
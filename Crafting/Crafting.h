#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Crafting.generated.h"

UENUM(BlueprintType)
enum class ECraftStation : uint8
{
    None        UMETA(DisplayName = "None"),
    Hand        UMETA(DisplayName = "Hand"),
    Workbench   UMETA(DisplayName = "Workbench"),
    Anvil        UMETA(DisplayName = "Anvil"),
    Forge       UMETA(DisplayName = "Forge"),
    Kitchen     UMETA(DisplayName = "Kitchen"),
    Pot         UMETA(DisplayName = "Pot"),
    BrewingStand UMETA(DisplayName = "Brewing Stand"),
    Loom         UMETA(DisplayName = "Loom"),
    grindstone   UMETA(DisplayName = "Grindstone")
};

UENUM(BlueprintType)
enum class ECraftCategory : uint8
{
    None        UMETA(DisplayName = "None"),
    Weapon      UMETA(DisplayName = "Weapon"),
    Armor       UMETA(DisplayName = "Armor"),
    Tool        UMETA(DisplayName = "Tool"),
    Building    UMETA(DisplayName = "Building"),
    Food        UMETA(DisplayName = "Food"),
    Potion      UMETA(DisplayName = "Potion"),
    Drink       UMETA(DisplayName = "Drink"),
    Material    UMETA(DisplayName = "Material"),
    Clothing    UMETA(DisplayName = "Clothing"),
    Jewelry     UMETA(DisplayName = "Jewelry"),
    Music       UMETA(DisplayName = "Music")
};

USTRUCT(BlueprintType)
struct FCraftRecipe : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RecipeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ResultItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ResultQuantity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, int32> Ingredients;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECraftingStation Station = ECraftingStation::Hand;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECraftingCategory Category = ECraftingCategory::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CraftingTime = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperienceGained = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkillLevelRequired = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RequiredProfession;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAutoLearn = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MasteryLevelRequired = 0;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UCraftingSystem : public UObject
{
    GENERATED_BODY()

public:
    UCraftingSystem();

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    static bool CanCraft(FName RecipeID, const TMap<FName, int32>& Inventory);

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    static TMap<FName, int32> Craft(FName RecipeID, const TMap<FName, int32>& Inventory);

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    static TArray<FCraftingRecipe> GetRecipesByStation(ECraftingStation Station);

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    static TArray<FCraftingRecipe> GetRecipesByCategory(ECraftingCategory Category);

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    static TArray<FCraftingRecipe> GetAllRecipes();

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    static FCraftingRecipe GetRecipe(FName RecipeID);

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    static int32 GetCraftingTime(FName RecipeID);

    UFUNCTION(BlueprintCallable, Category = "Crafting")
    static bool HasRequiredProfession(FName RecipeID, const TArray<FName>& Professions);
};
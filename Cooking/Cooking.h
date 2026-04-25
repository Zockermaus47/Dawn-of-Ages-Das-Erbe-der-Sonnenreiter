#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Cooking.generated.h"

UENUM(BlueprintType)
enum class EFoodType : uint8
{
    None        UMETA(DisplayName = "None"),
    Meat        UMETA(DisplayName = "Meat"),
    Bread       UMETA(DisplayName = "Bread"),
    Soup        UMETA(DisplayName = "Soup"),
    Stew        UMETA(DisplayName = "Stew"),
    Roast       UMETA(DisplayName = "Roast"),
    Salad       UMETA(DisplayName = "Salad"),
    Pie         UMETA(DisplayName = "Pie"),
    Cake        UMETA(DisplayName = "Cake")
};

UENUM(BlueprintType)
enum class EDrinkType : uint8
{
    None        UMETA(DisplayName = "None"),
    Water       UMETA(DisplayName = "Water"),
    Beer        UMETA(DisplayName = "Beer"),
    Wine        UMETA(DisplayName = "Wine"),
    Mead        UMETA(DisplayName = "Mead"),
    Ale         UMETA(DisplayName = "Ale"),
    Juice       UMETA(DisplayName = "Juice"),
    Tea         UMETA(DisplayName = "Tea"),
    Coffee      UMETA(DisplayName = "Coffee")
};

USTRUCT(BlueprintType)
struct FCookingRecipe : public FTableRowBase
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
    int32 CookingTime = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperienceGained = 15;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkillLevelRequired = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 HungerRestore = 20;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ThirstRestore = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 HealthRestore = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ManaRestore = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAutoLearn = false;
};

USTRUCT(BlueprintType)
struct FBrewingRecipe : public FTableRowBase
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
    int32 BrewingTime = 30;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperienceGained = 25;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkillLevelRequired = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ThirstRestore = 30;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ManaRestore = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAutoLearn = false;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UCookingBrewingSystem : public UObject
{
    GENERATED_BODY()

public:
    UCookingBrewingSystem();

    UFUNCTION(BlueprintCallable, Category = "Cooking")
    static bool CanCook(FCookingRecipe Recipe, const TMap<FName, int32>& Inventory);

    UFUNCTION(BlueprintCallable, Category = "Cooking")
    static TMap<FName, int32> Cook(FCookingRecipe Recipe, const TMap<FName, int32>& Inventory);

    UFUNCTION(BlueprintCallable, Category = "Brewing")
    static bool CanBrew(FBrewingRecipe Recipe, const TMap<FName, int32>& Inventory);

    UFUNCTION(BlueprintCallable, Category = "Brewing")
    static TMap<FName, int32> Brew(FBrewingRecipe Recipe, const TMap<FName, int32>& Inventory);

    UFUNCTION(BlueprintCallable, Category = "Cooking")
    static TArray<FCookingRecipe> GetAllCookingRecipes();

    UFUNCTION(BlueprintCallable, Category = "Brewing")
    static TArray<FBrewingRecipe> GetAllBrewingRecipes();
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Alchemy.generated.h"

UENUM(BlueprintType)
enum class EPotionType : uint8
{
    Healing     UMETA(DisplayName = "Healing"),
    Mana       UMETA(DisplayName = "Mana"),
    Stamina    UMETA(DisplayName = "Stamina"),
    Strength  UMETA(DisplayName = "Strength"),
    Speed      UMETA(DisplayName = "Speed"),
    Invisibility UMETA(DisplayName = "Invisibility"),
    FireResistance UMETA(DisplayName = "Fire Resistance"),
    IceResistance UMETA(DisplayName = "Ice Resistance"),
    Poison     UMETA(DisplayName = "Poison"),
    Love       UMETA(DisplayName = "Love"),
    Luck       UMETA(DisplayName = "Luck"),
    NightVision UMETA(DisplayName = "Night Vision"),
    EagleEye   UMETA(DisplayName = "Eagle Eye")
};

USTRUCT(BlueprintType)
struct FPotionRecipe
{
    GENERATED_BODY()
    FName RecipeID;
    FText DisplayName;
    EPotionType Type;
    TArray<FName> Ingredients;
    int32 SkillRequired = 1;
    float Potency = 10.0f;
    float Duration = 60.0f;
    bool bHasAntidote = false;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UAlchemySystem : public UObject
{
    GENERATED_BODY()
public:
    static TArray<FPotionRecipe> GetKnownRecipes();
    static bool BrewPotion(FPotionRecipe Recipe, TArray<FName> Ingredients);
    static FPotionRecipe GetRecipe(FName RecipeID);
    static bool StudyRecipe(FPotionRecipe Recipe);
    static int32 GetAlchemySkill();
    static void LevelUpSkill(int32 Amount);
    static bool CanBrew(FPotionRecipe Recipe);
    static float GetPotionBonus(EPotionType Type);
    static void AddPotionToInventory(FPotionRecipe Potion);
    static bool HasRequiredIngredients(FPotionRecipe Recipe);
private:
    static TArray<FName> KnownRecipes;
    static int32 AlchemySkill;
};
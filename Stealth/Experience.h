#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Experience.generated.h"

UENUM(BlueprintType)
enum class EAttribute : uint8
{
    Strength     UMETA(DisplayName = "Strength"),
    Endurance    UMETA(DisplayName = "Endurance"),
    Vitality     UMETA(DisplayName = "Vitality"),
    Agility      UMETA(DisplayName = "Agility"),
    Accuracy     UMETA(DisplayName = "Accuracy"),
    Intelligence UMETA(DisplayName = "Intelligence"),
    Wisdom       UMETA(DisplayName = "Wisdom"),
    Charisma     UMETA(DisplayName = "Charisma"),
    Luck        UMETA(DisplayName = "Luck"),
    Stealth      UMETA(DisplayName = "Stealth")
};

USTRUCT(BlueprintType)
struct FCharacterStats : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAttribute Attribute;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BaseValue = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 LevelBonus = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HealthPerPoint = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaPerPoint = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CarryPerPoint = 2.0f;
};

USTRUCT(BlueprintType)
struct FStatBonuses
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxStamina = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentStamina = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CarryCapacity = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentWeight = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaRegen = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MoveSpeed = 600.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MeleeDamage = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RangedDamage = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ArmorRating = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CriticalChance = 0.05f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DodgeChance = 0.05f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlockChance = 0.10f;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UExperienceSystem : public UObject
{
    GENERATED_BODY()

public:
    UExperienceSystem();

    static void AddExperience(int32 Amount);

    static int32 GetCurrentXP();

    static int32 GetLevel();

    static int32 GetXPToNextLevel();

    static void LevelUp();

    static int32 GetAvailablePoints();

    static void SpendPoint(EAttribute Attribute);

    static int32 GetAttributeValue(EAttribute Atr);

    static void AddAttributeBonus(EAttribute Attribute, int32 Bonus);

    static void CalculateStats();

    static float GetMaxHealth();

    static float GetCurrentHealth();

    static void SetCurrentHealth(float Value);

    static void ModifyHealth(float Delta);

    static float GetMaxStamina();

    static float GetCurrentStamina();

    static void SetCurrentStamina(float Value);

    static void ModifyStamina(float Delta);

    static float GetCarryCapacity();

    static float GetCurrentWeight();

    static bool IsEncumbered();

    static float GetEncumbrancePenalty();

    static void AddItemWeight(float Weight);

    static void RemoveItemWeight(float Weight);

    static float GetMovementPenalty();

    static float GetMeleeDamageBonus();

    static float GetArmorBonus();

    static float GetStaminaRegenBonus();

    static FStatBonuses GetAllBonuses();

private:
    static int32 CurrentXP;
    static int32 CurrentLevel;
    static int32 XPForNextLevel;
    static int32 AvailablePoints;
    static int32 AttributePoints[10];
    static float CurrentHealth;
    static float MaxHealthBase;
    static float CurrentStamina;
    static float MaxStaminaBase;
    static float CurrentWeight;
    static FStatBonuses Bonuses;
};
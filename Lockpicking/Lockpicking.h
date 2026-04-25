#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Lockpicking.generated.h"

UENUM(BlueprintType)
enum class ELockDifficulty : uint8
{
    Simple    UMETA(DisplayName = "Simple"),
    Easy      UMETA(DisplayName = "Easy"),
    Medium    UMETA(DisplayName = "Medium"),
    Hard      UMETA(DisplayName = "Hard"),
    Expert    UMETA(DisplayName = "Expert"),
    Master    UMETA(DisplayName = "Master")
};

UENUM(BlueprintType)
enum class ELockpickTier : uint8
{
    Wooden    UMETA(DisplayName = "Wooden"),
    Iron      UMETA(DisplayName = "Iron"),
    Steel     UMETA(DisplayName = "Steel"),
    Mithril   UMETA(DisplayName = "Mithril"),
    Adamant   UMETA(DisplayName = "Adamant")
};

USTRUCT(BlueprintType)
struct FLockData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LockID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ELockDifficulty Difficulty = ELockDifficulty::Simple;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredSkill = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Durability = 100.0f;
};

USTRUCT(BlueprintType)
struct FLockpickData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ELockpickTier Tier = ELockpickTier::Wooden;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Durability = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BreakChance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SuccessBonus = 0;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API ULockpickingSystem : public UObject
{
    GENERATED_BODY()

public:
    ULockpickingSystem();

    static bool AttemptPick(FLockData Lock, FLockpickData Pick);

    static void CalculateChance(ELockDifficulty Difficulty, int32 PlayerSkill, float& SuccessChance, float& BreakChance);

    static void ApplyDamage(FLockpickData& Pick, float Damage);

    static bool CanCraftPick(ELockpickTier Tier, int32 PlayerSkill);
};
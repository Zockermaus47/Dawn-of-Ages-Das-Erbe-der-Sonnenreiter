#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Theft.generated.h"

UENUM(BlueprintType)
enum class EPickpocketDifficulty : uint8
{
    Trivial    UMETA(DisplayName = "Trivial"),
    Easy      UMETA(DisplayName = "Easy"),
    Medium    UMETA(DisplayName = "Medium"),
    Hard      UMETA(DisplayName = "Hard"),
    Dangerous UMETA(DisplayName = "Dangerous")
};

USTRUCT(BlueprintType)
struct FTheftTarget
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName TargetID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Awareness = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 InventoryValue = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsGuarded = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DetectChance = 0.1f;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UTheftSystem : public UObject
{
    GENERATED_BODY()

public:
    UTheftSystem();

    static bool AttemptPickpocket(FTheftTarget Target, int32 PlayerSkill);

    static bool CanStealItem(FName ItemID, int32 PlayerSkill);

    static int32 CalculateRisk(FTheftTarget Target, int32 PlayerSkill);

    static void ApplyBounty(int32 Amount);

    static void ReduceBounty(int32 Amount);

    static int32 GetBounty();

    static void SetWanted(bool bWanted);
};
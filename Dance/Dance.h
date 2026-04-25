#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dance.generated.h"

UENUM(BlueprintType)
enum class EDanceStyle : uint8
{
    Folk       UMETA(DisplayName = "Folk"),
    Celtic     UMETA(DisplayName = "Celtic"),
    Tribal     UMETA(DisplayName = "Tribal"),
    Formal     UMETA(DisplayName = "Formal"),
    War        UMETA(DisplayName = "War"),
    Ritual     UMETA(DisplayName = "Ritual")
};

UENUM(BlueprintType)
enum class EDanceRank : uint8
{
    Novice     UMETA(DisplayName = "Novice"),
    Adept      UMETA(DisplayName = "Adept"),
    Expert     UMETA(DisplayName = "Expert"),
    Master     UMETA(DisplayName = "Master"),
    GrandMaster UMETA(DisplayName = "Grand Master")
};

USTRUCT(BlueprintType)
struct FDanceMove
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MoveID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RhythmRequired = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaCost = 5.0f;
};

USTRUCT(BlueprintType)
struct FDanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName DanceID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EDanceStyle Style;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EDanceRank Rank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredSkill = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HealBonus = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BuffBonus = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AudienceBonus = 0;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UDanceSystem : public UObject
{
    GENERATED_BODY()

public:
    UDanceSystem();

    static FDanceData GetDance(FName DanceID);

    static bool PerformDance(FDanceData Dance, int32 PlayerSkill);

    static TArray<FDanceData> GetDancesByStyle(EDanceStyle Style);

    static void ApplyDanceBuff(float Duration, float HealBonus);

    static int32 CalculateAudienceReaction(EDanceStyle Style, int32 AudienceSize);
};
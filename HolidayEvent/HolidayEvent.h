#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HolidayEvent.generated.h"

UENUM(BlueprintType)
enum class EHolidayType : uint8
{
    Christmas  UMETA(DisplayName = "Weihnachten"),
    Halloween  UMETA(DisplayName = "Halloween"),
    Easter     UMETA(DisplayName = "Ostern"),
    NewYear    UMETA(DisplayName = "Neujahr"),
    Anniversary UMETA(DisplayName = "Jubiläum")
};

USTRUCT(BlueprintType)
struct FHolidayReward
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName ItemID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Amount;
};

USTRUCT(BlueprintType)
struct FHolidayEvent
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName EventID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EHolidayType Type;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FHolidayReward> Rewards;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float Multiplier;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UHolidayEventSystem : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable) static bool IsHolidayActive();
    UFUNCTION(BlueprintCallable) static FHolidayEvent GetCurrentHoliday();
    UFUNCTION(BlueprintCallable) static TArray<FHolidayReward> GetRewards();
};
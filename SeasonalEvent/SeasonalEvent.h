#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SeasonalEvent.generated.h"

UENUM(BlueprintType)
enum class ESeasonEvent : uint8
{
    Spring     UMETA(DisplayName = "Frühling"),
    Summer     UMETA(DisplayName = "Sommer"),
    Autumn     UMETA(DisplayName = "Herbst"),
    Winter     UMETA(DisplayName = "Winter"),
    Festival   UMETA(DisplayName = "Festival"),
    Harvest    UMETA(DisplayName = "Ernte"),
    Hunt       UMETA(DisplayName = "Jagd"),
    Breeding   UMETA(DisplayName = "Paarungszeit")
};

UENUM(BlueprintType)
enum class ESeasonalModifier : uint8
{
    None           UMETA(DisplayName = "Keiner"),
    DoubleXP       UMETA(DisplayName = "Doppelte XP"),
    DoubleLoot     UMETA(DisplayName = "Doppelte Beute"),
    DoubleCrafting UMETA(DisplayName = "Doppeltes Crafting"),
    SpeedBoost     UMETA(DisplayName = "Geschwindigkeitsbonus"),
    Discount       UMETA(DisplayName = "Rabatt")
};

USTRUCT(BlueprintType)
struct FSeasonalEvent
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EventID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESeasonEvent EventType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<ESeasonalModifier> Modifiers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StartDay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration = 7.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> RewardItemIDs;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API USeasonalEventSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "SeasonalEvent")
    static FSeasonalEvent GetCurrentEvent();

    UFUNCTION(BlueprintCallable, Category = "SeasonalEvent")
    static TArray<FSeasonalEvent> GetActiveEvents();

    UFUNCTION(BlueprintCallable, Category = "SeasonalEvent")
    static bool IsEventActive(FName EventID);

    UFUNCTION(BlueprintCallable, Category = "SeasonalEvent")
    static float GetEventMultiplier(ESeasonalModifier Modifier);

    UFUNCTION(BlueprintCallable, Category = "SeasonalEvent")
    static TArray<FName> GetEventRewards(FName EventID);

    UFUNCTION(BlueprintCallable, Category = "SeasonalEvent")
    static void TriggerEvent(FSeasonalEvent Event);

    UFUNCTION(BlueprintCallable, Category = "SeasonalEvent")
    static void EndEvent(FName EventID);

private:
    static TArray<FSeasonalEvent> ActiveEvents;
    static float CurrentDay;
};

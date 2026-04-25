#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Infiltration.generated.h"

UENUM(BlueprintType)
enum class EInfiltrationPhase : uint8
{
    Recon     UMETA(DisplayName = "Recon"),
    Breach    UMETA(DisplayName = "Breach"),
    Search    UMETA(DisplayName = "Search"),
    Escape    UMETA(DisplayName = "Escape")
};

USTRUCT(BlueprintType)
struct FFortressData
{
    GENERATED_BODY()
    FName FortressID;
    FText DisplayName;
    int32 DefenseLevel = 1;
    int32 Guards = 10;
    int32 TreasureValue = 1000;
    bool bAlarmTriggered = false;
    TArray<FName> LootTable;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UInfiltrationSystem : public UObject
{
    GENERATED_BODY()
public:
    static bool StartInfiltration(FFortressData Fortress);
    static bool TriggerAlarm();
    static bool BribeGuard(int32 Amount);
    static bool SabotageDefense();
    static bool StealLoot(FName ItemID);
    static bool Escape();
    static void TickInfiltration(float DeltaTime);
    static EInfiltrationPhase GetPhase();
    static int32 GetAlertLevel();
    static bool IsDetected();
private:
    static EInfiltrationPhase CurrentPhase;
    static int32 AlertLevel;
    static bool bDetected;
};
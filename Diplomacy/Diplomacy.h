#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Diplomacy.generated.h"

UENUM(BlueprintType)
enum class EFactionRelation : uint8
{
    Hostile    UMETA(DisplayName = "Hostile"),
    Unfriendly UMETA(DisplayName = "Unfriendly"),
    Neutral   UMETA(DisplayName = "Neutral"),
    Friendly  UMETA(DisplayName = "Friendly"),
    Allied    UMETA(DisplayName = "Allied")
};

UENUM(BlueprintType)
enum class EDiplomacyAction : uint8
{
    Trade     UMETA(DisplayName = "Trade"),
    Treaty    UMETA(DisplayName = "Treaty"),
    Alliance  UMETA(DisplayName = "Alliance"),
    War       UMETA(DisplayName = "War"),
    NonAggression UMETA(DisplayName = "Non-Aggression"),
    Gift      UMETA(DisplayName = "Gift"),
    Demand    UMETA(DisplayName = "Demand")
};

USTRUCT(BlueprintType)
struct FFactionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName FactionID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Power = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Gold = 1000;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Territory = 1;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UDiplomacySystem : public UObject
{
    GENERATED_BODY()

public:
    UDiplomacySystem();

    static FFactionData GetFaction(FName FactionID);

    static EFactionRelation GetRelation(FName FactionA, FName FactionB);

    static bool SetRelation(FName FactionA, FName FactionB, EFactionRelation Relation);

    static bool AttemptNegotiation(FName FactionA, FName FactionB, EDiplomacyAction Action, int32 PlayerSkill);

    static int32 CalculateRelationChange(EFactionRelation Current, EDiplomacyAction Action);

    static TArray<FFactionData> GetAllies(FName FactionID);

    static TArray<FFactionData> GetEnemies(FName FactionID);

    static void JoinFaction(FName FactionID);

    static void LeaveFaction();
};
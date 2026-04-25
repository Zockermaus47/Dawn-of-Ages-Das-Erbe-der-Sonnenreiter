#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Reputation.generated.h"

UENUM(BlueprintType)
enum class EFaction : uint8
{
    Village   UMETA(DisplayName = "Dorf"),
    Guards    UMETA(DisplayName = "Wachen"),
    Merchants UMETA(DisplayName = "Händler"),
    Thieves  UMETA(DisplayName = "Diebe"),
    Mages    UMETA(DisplayName = "Magier"),
    Druids   UMETA(DisplayName = "Druiden")
};

UENUM(BlueprintType)
enum class ERepRank : uint8
{
    Stranger UMETA(DisplayName = "Fremder"),
    Ally     UMETA(DisplayName = "Verbündeter"),
    Friend   UMETA(DisplayName = "Freund"),
    Trusted  UMETA(DisplayName = "Vertraut"),
    VIP      UMETA(DisplayName = "Ehrenmitglied"),
    Leader   UMETA(DisplayName = "Anführer")
};

USTRUCT(BlueprintType)
struct FFactionReputation
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EFaction Faction;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ERepRank Rank;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Points;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UReputationSystem : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable) static bool ChangeReputation(EFaction Faction, int32 Amount);
    UFUNCTION(BlueprintCallable) static ERepRank GetRank(EFaction Faction);
    UFUNCTION(BlueprintCallable) static int32 GetPoints(EFaction Faction);
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Arena.generated.h"

UENUM(BlueprintType)
enum class EArenaType : uint8
{
    Duel      UMETA(DisplayName = "Duel"),
    Team      UMETA(DisplayName = "Team"),
    FreeForAll UMETA(DisplayName = "Free For All"),
    Capture  UMETA(DisplayName = "Capture"),
    KingOfHill UMETA(DisplayName = "King Of The Hill"),
    Tournament UMETA(DisplayName = "Tournament")
};

UENUM(BlueprintType)
enum class EArenaState : uint8
{
    Open     UMETA(DisplayName = "Open"),
    Counting UMETA(DisplayName = "Counting"),
    Active   UMETA(DisplayName = "Active"),
    Finished UMETA(DisplayName = "Finished")
};

USTRUCT(BlueprintType)
struct FArenaMatch
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere) FName MatchID;
    UPROPERTY(EditAnywhere) EArenaType Type;
    UPROPERTY(EditAnywhere) EArenaState State;
    UPROPERTY(EditAnywhere) int32 PlayerCount = 0;
    UPROPERTY(EditAnywhere) int32 MaxPlayers = 4;
    UPROPERTY(EditAnywhere) int32 EntryFee = 100;
    UPROPERTY(EditAnywhere) int32 PrizePool = 500;
    UPROPERTY(EditAnywhere) float Duration = 300.0f;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UArenaSystem : public UObject
{
    GENERATED_BODY()
public:
    static FArenaMatch CreateMatch(EArenaType Type, int32 EntryFee);
    static bool JoinMatch(FName MatchID);
    static bool StartMatch();
    static void EndMatch();
    static int32 GetWinner();
    static int32 GetReward();
    static TArray<FName> GetActivePlayers();
    static bool IsMatchActive();
    static void RegisterKill(FName KillerID, FName VictimID);
    static int32 GetScore(FName PlayerID);
private:
    static TMap<FName, int32> Scores;
};
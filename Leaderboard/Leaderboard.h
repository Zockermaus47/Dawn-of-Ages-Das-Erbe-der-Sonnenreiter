#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Leaderboard.generated.h"

UENUM(BlueprintType)
enum class ELeaderboardType : uint8
{
    Level        UMETA(DisplayName = "Level"),
    Kills        UMETA(DisplayName = "Kills"),
    Gold         UMETA(DisplayName = "Gold"),
    Reputation  UMETA(DisplayName = "Reputation"),
    Crafting     UMETA(DisplayName = "Crafting"),
    PvP          UMETA(DisplayName = "PvP")
};

UENUM(BlueprintType)
enum class ELeaderboardPeriod : uint8
{
    Hourly    UMETA(DisplayName = "Hourly"),
    Daily     UMETA(DisplayName = "Daily"),
    Weekly    UMETA(DisplayName = "Weekly"),
    Monthly   UMETA(DisplayName = "Monthly"),
    AllTime   UMETA(DisplayName = "All Time")
};

USTRUCT(BlueprintType)
struct FLeaderboardEntry
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName PlayerID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText PlayerName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Rank = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Value = 0;
};

USTRUCT(BlueprintType)
struct FLeaderboardData
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName LeaderboardID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ELeaderboardType Type;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ELeaderboardPeriod Period;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FLeaderboardEntry> Entries;
};

UCLASS() class STEFFIS_DAWNOFAGES_API ULeaderboardSystem : public UObject { GENERATED_BODY() public:
    static FLeaderboardData GetLeaderboard(ELeaderboardType Type, ELeaderboardPeriod Period);
    static void UpdateScore(FName PlayerID, ELeaderboardType Type, int32 Amount);
    static int32 GetRank(FName PlayerID, ELeaderboardType Type);
    static TArray<FLeaderboardEntry> GetTopPlayers(int32 Count, ELeaderboardType Type);
    static void RefreshLeaderboards();
};
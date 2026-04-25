#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AchievementEx.generated.h"

UENUM(BlueprintType)
enum class EAchievementCategory : uint8
{
    Combat     UMETA(DisplayName = "Combat"),
    Exploration UMETA(DisplayName = "Exploration"),
    Crafting   UMETA(DisplayName = "Crafting"),
    Social    UMETA(DisplayName = "Social"),
    Story     UMETA(DisplayName = "Story"),
    Rare      UMETA(DisplayName = "Rare"),
    Seasonal  UMETA(DisplayName = "Seasonal")
};

USTRUCT(BlueprintType)
struct FAchievementEx
{
    GENERATED_BODY()
    FName AchievementID;
    FText DisplayName;
    FText Description;
    EAchievementCategory Category;
    int32 Points = 10;
    int32 Rarity = 1;
    bool bSecret = false;
    FName IconID;
    FName RewardItem;
    int32 RewardGold = 0;
    float ProgressRequired = 0.0f;
    float CurrentProgress = 0.0f;
    bool bCompleted = false;
    FDateTime CompletionDate;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UAchievementExSystem : public UObject
{
    GENERATED_BODY()
public:
    static TArray<FAchievementEx> GetAllAchievements();
    static TArray<FAchievementEx> GetCategory(EAchievementCategory Category);
    static bool UnlockAchievement(FName AchievementID);
    static void UpdateProgress(FName AchievementID, float Amount);
    static FAchievementEx GetAchievement(FName AchievementID);
    static int32 GetTotalPoints();
    static int32 GetCompletedCount();
    static float GetCompletionPercentage();
    static TArray<FAchievementEx> GetRecentlyUnlocked();
    static void ClaimReward(FName AchievementID);
    static bool IsUnlocked(FName AchievementID);
    static TArray<FAchievementEx> GetSecretAchievements();
    static void RefreshLeaderboard();
    static bool HasRewardClaimed(FName AchievementID);
private:
    static TMap<FName, FAchievementEx> Achievements;
};
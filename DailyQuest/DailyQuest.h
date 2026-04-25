#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DailyQuest.generated.h"

UENUM(BlueprintType)
enum class EDailyQuestType : uint8
{
    Kill      UMETA(DisplayName = "Kill"),
    Gather   UMETA(DisplayName = "Gather"),
    Craft    UMETA(DisplayName = "Craft"),
    Trade    UMETA(DisplayName = "Trade"),
    Explore  UMETA(DisplayName = "Explore")
};

USTRUCT(BlueprintType)
struct FDailyQuest
{
    GENERATED_BODY()
    FName QuestID;
    FText DisplayName;
    EDailyQuestType Type;
    int32 Amount = 10;
    int32 GoldReward = 100;
    int32 XPReward = 50;
    float TimeRemaining = 24.0f;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UDailyQuestSystem : public UObject
{
    GENERATED_BODY()

public:
    static void RefreshDailyQuests();

    static TArray<FDailyQuest> GetDailyQuests();

    static bool CompleteQuest(FName QuestID);

    static FDailyQuest GetQuest(FName QuestID);

    static int32 GetRemainingTime(FName QuestID);

    static int32 GetCompletedCount();

    static float GetTotalProgress(FName QuestID);

private:
    static TArray<FDailyQuest> Quests;
};
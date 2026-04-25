#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GameFramework/PlayerState.h"
#include "Quest.generated.h"

UENUM(BlueprintType)
enum class EQuestType : uint8
{
    None        UMETA(DisplayName = "None"),
    Main        UMETA(DisplayName = "Main"),
    Side        UMETA(DisplayName = "Side"),
    Daily       UMETA(DisplayName = "Daily"),
    Weekly      UMETA(DisplayName = "Weekly"),
    Repeatable  UMETA(DisplayName = "Repeatable")
};

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
    Locked      UMETA(DisplayName = "Locked"),
    Available  UMETA(DisplayName = "Available"),
    InProgress UMETA(DisplayName = "In Progress"),
    Completed  UMETA(DisplayName = "Completed"),
    Failed     UMETA(DisplayName = "Failed")
};

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
    Kill            UMETA(DisplayName = "Kill"),
    Collect        UMETA(DisplayName = "Collect"),
    Talk           UMETA(DisplayName = "Talk"),
    Travel         UMETA(DisplayName = "Travel"),
    Craft          UMETA(DisplayName = "Craft"),
    UseItem        UMETA(DisplayName = "UseItem"),
    Interact      UMETA(DisplayName = "Interact"),
    SkillCheck    UMETA(DisplayName = "Skill Check")
};

USTRUCT(BlueprintType)
struct FQuestObjective
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ObjectiveID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EObjectiveType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TargetAmount = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName TargetTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsOptional = false;
};

USTRUCT(BlueprintType)
struct FQuestReward
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Amount = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Chance = 100.0f;
};

USTRUCT(BlueprintType)
struct FQuestData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName QuestID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQuestType QuestType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FQuestObjective> Objectives;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FQuestReward> Rewards;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperienceGained = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 GoldReward = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RequiredQuest;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LevelRequired = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Difficulty = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsRepeatable = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsHidden = false;
};

USTRUCT(BlueprintType)
struct FQuestProgress
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName QuestID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQuestStatus Status = EQuestStatus::Locked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, int32> ObjectiveProgress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentStep = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StartTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bWasCompleted = false;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UQuestSystem : public UObject
{
    GENERATED_BODY()

public:
    UQuestSystem();

    UFUNCTION(BlueprintCallable, Category = "Quest")
    static FQuestData GetQuestData(FName QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    static bool StartQuest(APlayerState* PlayerState, FName QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    static bool CompleteQuest(APlayerState* PlayerState, FName QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    static bool FailQuest(APlayerState* PlayerState, FName QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    static bool UpdateObjective(APlayerState* PlayerState, FName QuestID, FName ObjectiveID, int32 Amount = 1);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    static TArray<FQuestData> GetDailyQuests();

    UFUNCTION(BlueprintCallable, Category = "Quest")
    static TArray<FQuestData> GetAllQuests();

    UFUNCTION(BlueprintCallable, Category = "Quest")
    static TArray<FQuestProgress> GetActiveQuests(APlayerState* PlayerState);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    static bool IsQuestCompleted(FName QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    static bool CanStartQuest(FName QuestID, int32 PlayerLevel);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    static void GrantRewards(APlayerState* PlayerState, const TArray<FQuestReward>& Rewards);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    static void InitializeQuestData();

private:
    static bool LoadQuestDataTable();

    static UDataTable* QuestDataTable;

    static TSet<FName> CompletedQuests;

    static TArray<FName> AvailableQuestIDs;
};
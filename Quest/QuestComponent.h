#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Quest.h"
#include "QuestComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestStarted, FName, QuestID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestCompleted, FName, QuestID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestObjectiveUpdated, FName, QuestID, FName, ObjectiveID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestFailed, FName, QuestID);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_DAWNOFAGES_API UQuestComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UQuestComponent();

    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool AcceptQuest(FName QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool CompleteQuest(FName QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool AbandonQuest(FName QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool UpdateObjective(FName ObjectiveID, int32 Amount = 1);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool UpdateObjectiveByTag(FName ObjectiveTag, int32 Amount = 1);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool IsQuestActive(FName QuestID) const;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool HasQuestCompleted(FName QuestID) const;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    TArray<FQuestProgress> GetActiveQuests() const { return ActiveQuests; }

    UFUNCTION(BlueprintCallable, Category = "Quest")
    FQuestProgress GetQuestProgress(FName QuestID) const;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    int32 GetObjectiveProgress(FName QuestID, FName ObjectiveID) const;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool IsObjectiveComplete(FName QuestID, FName ObjectiveID) const;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool AreAllObjectivesComplete(FName QuestID) const;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    TArray<FQuestData> GetAvailableQuests() const;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    void AddQuestReward(FName QuestID, const FQuestReward& Reward);

    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestStarted OnQuestStarted;

    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestCompleted OnQuestCompleted;

    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestObjectiveUpdated OnQuestObjectiveUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestFailed OnQuestFailed;

protected:
    virtual void BeginPlay() override;

private:
    void LoadQuestProgress();
    void SaveQuestProgress();
    bool CheckQuestCompletion(FName QuestID);
    void GrantQuestRewards(FName QuestID);

    UPROPERTY()
    TArray<FQuestProgress> ActiveQuests;

    UPROPERTY()
    TSet<FName> CompletedQuestIDs;

    UPROPERTY()
    TMap<FName, FQuestReward> PendingRewards;
};
#include "QuestComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UQuestComponent::UQuestComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UQuestComponent::BeginPlay()
{
    Super::BeginPlay();
    LoadQuestProgress();
}

bool UQuestComponent::AcceptQuest(FName QuestID)
{
    if (IsQuestActive(QuestID) || HasQuestCompleted(QuestID))
    {
        return false;
    }

    FQuestData QuestData = UQuestSystem::GetQuestData(QuestID);

    if (QuestData.QuestID == NAME_None)
    {
        return false;
    }

    ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
    if (!OwnerChar)
    {
        return false;
    }

    APlayerState* PlayerState = OwnerChar->GetPlayerState<APlayerState>();
    if (!PlayerState)
    {
        return false;
    }

    if (!UQuestSystem::CanStartQuest(QuestID, FMath::Max(1, PlayerState->GetScore())))
    {
        return false;
    }

    FQuestProgress Progress;
    Progress.QuestID = QuestID;
    Progress.Status = EQuestStatus::InProgress;
    Progress.StartTime = GetWorld()->GetTimeSeconds();

    for (const FQuestObjective& Objective : QuestData.Objectives)
    {
        Progress.ObjectiveProgress.Add(Objective.ObjectiveID, 0);
    }

    ActiveQuests.Add(Progress);
    SaveQuestProgress();

    OnQuestStarted.Broadcast(QuestID);
    UE_LOG(LogTemp, Log, TEXT("Quest started: %s"), *QuestID.ToString());

    return true;
}

bool UQuestComponent::CompleteQuest(FName QuestID)
{
    if (!IsQuestActive(QuestID))
    {
        return false;
    }

    if (!AreAllObjectivesComplete(QuestID))
    {
        return false;
    }

    FQuestData QuestData = UQuestSystem::GetQuestData(QuestID);
    GrantQuestRewards(QuestID);

    CompletedQuestIDs.Add(QuestID);

    ActiveQuests.RemoveAll([QuestID](const FQuestProgress& P) {
        return P.QuestID == QuestID;
    });

    SaveQuestProgress();

    OnQuestCompleted.Broadcast(QuestID);
    UE_LOG(LogTemp, Log, TEXT("Quest completed: %s"), *QuestID.ToString());

    return true;
}

bool UQuestComponent::AbandonQuest(FName QuestID)
{
    if (!IsQuestActive(QuestID))
    {
        return false;
    }

    ActiveQuests.RemoveAll([QuestID](const FQuestProgress& P) {
        return P.QuestID == QuestID;
    });

    SaveQuestProgress();
    UE_LOG(LogTemp, Log, TEXT("Quest abandoned: %s"), *QuestID.ToString());

    return true;
}

bool UQuestComponent::UpdateObjective(FName ObjectiveID, int32 Amount)
{
    for (FQuestProgress& Progress : ActiveQuests)
    {
        if (Progress.ObjectiveProgress.Contains(ObjectiveID))
        {
            int32 Current = Progress.ObjectiveProgress[ObjectiveID];
            Progress.ObjectiveProgress[ObjectiveID] = Current + Amount;

            OnQuestObjectiveUpdated.Broadcast(Progress.QuestID, ObjectiveID);

            CheckQuestCompletion(Progress.QuestID);

            return true;
        }
    }

    return false;
}

bool UQuestComponent::UpdateObjectiveByTag(FName ObjectiveTag, int32 Amount)
{
    for (FQuestProgress& Progress : ActiveQuests)
    {
        FQuestData QuestData = UQuestSystem::GetQuestData(Progress.QuestID);

        for (const FQuestObjective& Objective : QuestData.Objectives)
        {
            if (Objective.TargetTag == ObjectiveTag)
            {
                int32 Current = Progress.ObjectiveProgress[Objective.ObjectiveID];
                Progress.ObjectiveProgress[Objective.ObjectiveID] = Current + Amount;

                OnQuestObjectiveUpdated.Broadcast(Progress.QuestID, Objective.ObjectiveID);

                CheckQuestCompletion(Progress.QuestID);

                return true;
            }
        }
    }

    return false;
}

bool UQuestComponent::IsQuestActive(FName QuestID) const
{
    return ActiveQuests.ContainsByPredicate([QuestID](const FQuestProgress& P) {
        return P.QuestID == QuestID && P.Status == EQuestStatus::InProgress;
    });
}

bool UQuestComponent::HasQuestCompleted(FName QuestID) const
{
    return CompletedQuestIDs.Contains(QuestID);
}

FQuestProgress UQuestComponent::GetQuestProgress(FName QuestID) const
{
    for (const FQuestProgress& Progress : ActiveQuests)
    {
        if (Progress.QuestID == QuestID)
        {
            return Progress;
        }
    }

    return FQuestProgress();
}

int32 UQuestComponent::GetObjectiveProgress(FName QuestID, FName ObjectiveID) const
{
    const FQuestProgress* Progress = GetActiveQuests().FindByPredicate([QuestID](const FQuestProgress& P) {
        return P.QuestID == QuestID;
    });

    if (Progress)
    {
        return Progress->ObjectiveProgress[ObjectiveID];
    }

    return 0;
}

bool UQuestComponent::IsObjectiveComplete(FName QuestID, FName ObjectiveID) const
{
    const FQuestProgress* Progress = GetActiveQuests().FindByPredicate([QuestID](const FQuestProgress& P) {
        return P.QuestID == QuestID;
    });

    if (!Progress)
    {
        return false;
    }

    FQuestData QuestData = UQuestSystem::GetQuestData(QuestID);
    for (const FQuestObjective& Objective : QuestData.Objectives)
    {
        if (Objective.ObjectiveID == ObjectiveID)
        {
            int32 Current = Progress->ObjectiveProgress[ObjectiveID];
            return Current >= Objective.TargetAmount;
        }
    }

    return false;
}

bool UQuestComponent::AreAllObjectivesComplete(FName QuestID) const
{
    FQuestData QuestData = UQuestSystem::GetQuestData(QuestID);
    const FQuestProgress* Progress = GetActiveQuests().FindByPredicate([QuestID](const FQuestProgress& P) {
        return P.QuestID == QuestID;
    });

    if (!Progress)
    {
        return false;
    }

    for (const FQuestObjective& Objective : QuestData.Objectives)
    {
        if (!Objective.bIsOptional)
        {
            int32 Current = Progress->ObjectiveProgress[Objective.ObjectiveID];
            if (Current < Objective.TargetAmount)
            {
                return false;
            }
        }
    }

    return true;
}

TArray<FQuestData> UQuestComponent::GetAvailableQuests() const
{
    TArray<FQuestData> Available;
    TArray<FQuestData> AllQuests = UQuestSystem::GetAllQuests();

    ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
    if (!OwnerChar)
    {
        return Available;
    }

    APlayerState* PlayerState = OwnerChar->GetPlayerState<APlayerState>();
    int32 PlayerLevel = PlayerState ? FMath::Max(1, PlayerState->GetScore()) : 1;

    for (const FQuestData& Quest : AllQuests)
    {
        if (HasQuestCompleted(Quest.QuestID) || IsQuestActive(Quest.QuestID))
        {
            continue;
        }

        if (Quest.LevelRequired > PlayerLevel)
        {
            continue;
        }

        if (Quest.RequiredQuest != NAME_None && !HasQuestCompleted(Quest.RequiredQuest))
        {
            continue;
        }

        Available.Add(Quest);
    }

    return Available;
}

void UQuestComponent::AddQuestReward(FName QuestID, const FQuestReward& Reward)
{
    PendingRewards.Add(QuestID, Reward);
}

bool UQuestComponent::CheckQuestCompletion(FName QuestID)
{
    if (AreAllObjectivesComplete(QuestID))
    {
        CompleteQuest(QuestID);
        return true;
    }

    return false;
}

void UQuestComponent::GrantQuestRewards(FName QuestID)
{
    FQuestData QuestData = UQuestSystem::GetQuestData(QuestID);

    ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());
    if (!OwnerChar)
    {
        return;
    }

    UQuestSystem::GrantRewards(OwnerChar->GetPlayerState(), QuestData.Rewards);

    if (FQuestReward* Pending = PendingRewards.Find(QuestID))
    {
        UE_LOG(LogTemp, Log, TEXT("Granting pending reward for: %s"), *QuestID.ToString());
        PendingRewards.Remove(QuestID);
    }
}

void UQuestComponent::LoadQuestProgress()
{
}

void UQuestComponent::SaveQuestProgress()
{
}
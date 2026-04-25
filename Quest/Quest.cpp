#include "Quest.h"
#include "Kismet/GameplayStatics.h"

UDataTable* UQuestSystem::QuestDataTable = nullptr;
TSet<FName> UQuestSystem::CompletedQuests;
TArray<FName> UQuestSystem::AvailableQuestIDs;

UQuestSystem::UQuestSystem()
{
    InitializeQuestData();
}

void UQuestSystem::InitializeQuestData()
{
    LoadQuestDataTable();
}

bool UQuestSystem::LoadQuestDataTable()
{
    if (QuestDataTable)
    {
        return true;
    }

    QuestDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Quests/QuestDataTable"));
    if (!QuestDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("QuestDataTable not found in Content!"));
        return false;
    }

    if (QuestDataTable->GetRowStruct())
    {
        AvailableQuestIDs = QuestDataTable->GetRowNames();
    }

    return true;
}

FQuestData UQuestSystem::GetQuestData(FName QuestID)
{
    if (!QuestDataTable)
    {
        LoadQuestDataTable();
    }

    if (QuestDataTable)
    {
        FQuestData* QuestDataRow = QuestDataTable->FindRow<FQuestData>(QuestID, TEXT(""));
        if (QuestDataRow)
        {
            return *QuestDataRow;
        }
    }

    return FQuestData();
}

bool UQuestSystem::CanStartQuest(FName QuestID, int32 PlayerLevel)
{
    FQuestData QuestData = GetQuestData(QuestID);

    if (QuestData.QuestID == NAME_None)
    {
        return false;
    }

    if (CompletedQuests.Contains(QuestID))
    {
        return false;
    }

    if (QuestData.LevelRequired > PlayerLevel)
    {
        return false;
    }

    if (QuestData.RequiredQuest != NAME_None && !CompletedQuests.Contains(QuestData.RequiredQuest))
    {
        return false;
    }

    return true;
}

bool UQuestSystem::StartQuest(APlayerState* PlayerState, FName QuestID)
{
    if (!PlayerState)
    {
        return false;
    }

    FQuestData QuestData = GetQuestData(QuestID);

    if (QuestData.QuestID == NAME_None)
    {
        UE_LOG(LogTemp, Warning, TEXT("Quest %s not found!"), *QuestID.ToString());
        return false;
    }

    if (!CanStartQuest(QuestID, FMath::Max(1, PlayerState->GetPlayerState<APlayerState>()->GetScore())))
    {
        return false;
    }

    return true;
}

bool UQuestSystem::UpdateObjective(APlayerState* PlayerState, FName QuestID, FName ObjectiveID, int32 Amount)
{
    if (!PlayerState)
    {
        return false;
    }

    FQuestData QuestData = GetQuestData(QuestID);

    for (const FQuestObjective& Objective : QuestData.Objectives)
    {
        if (Objective.ObjectiveID == ObjectiveID)
        {
            return true;
        }
    }

    return false;
}

bool UQuestSystem::CompleteQuest(APlayerState* PlayerState, FName QuestID)
{
    if (!PlayerState)
    {
        return false;
    }

    FQuestData QuestData = GetQuestData(QuestID);

    if (QuestData.QuestID == NAME_None)
    {
        return false;
    }

    CompletedQuests.Add(QuestID);

    GrantRewards(PlayerState, QuestData.Rewards);

    UE_LOG(LogTemp, Log, TEXT("Quest completed: %s"), *QuestID.ToString());

    return true;
}

bool UQuestSystem::FailQuest(APlayerState* PlayerState, FName QuestID)
{
    if (!PlayerState)
    {
        return false;
    }

    UE_LOG(LogTemp, Log, TEXT("Quest failed: %s"), *QuestID.ToString());

    return true;
}

void UQuestSystem::GrantRewards(APlayerState* PlayerState, const TArray<FQuestReward>& Rewards)
{
    if (!PlayerState)
    {
        return;
    }

    for (const FQuestReward& Reward : Rewards)
    {
        float Roll = FMath::FRand() * 100.0f;

        if (Roll <= Reward.Chance)
        {
            UE_LOG(LogTemp, Log,TEXT("Granting reward: %s x%d"), *Reward.ItemID.ToString(), Reward.Amount);
        }
    }
}

TArray<FQuestData> UQuestSystem::GetDailyQuests()
{
    TArray<FQuestData> DailyQuests;
    FQuestData QuestData;

    if (QuestDataTable)
    {
        for (FName RowName : AvailableQuestIDs)
        {
            QuestData = GetQuestData(RowName);
            if (QuestData.QuestType == EQuestType::Daily)
            {
                DailyQuests.Add(QuestData);
            }
        }
    }

    return DailyQuests;
}

TArray<FQuestData> UQuestSystem::GetAllQuests()
{
    TArray<FQuestData> AllQuests;

    if (QuestDataTable)
    {
        for (FName RowName : AvailableQuestIDs)
        {
            AllQuests.Add(GetQuestData(RowName));
        }
    }

    return AllQuests;
}

TArray<FQuestProgress> UQuestSystem::GetActiveQuests(APlayerState* PlayerState)
{
    return TArray<FQuestProgress>();
}

bool UQuestSystem::IsQuestCompleted(FName QuestID)
{
    return CompletedQuests.Contains(QuestID);
}
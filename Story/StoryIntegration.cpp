#include "StoryIntegration.h"

UStoryIntegration::UStoryIntegration()
{
}

FMainQuest UStoryIntegration::GetMainQuest(FName QuestID)
{
    return FMainQuest();
}

TArray<FMainQuest> UStoryIntegration::GetQuestsByAct(EStoryAct Act)
{
    return TArray<FMainQuest>();
}

bool UStoryIntegration::StartMainQuest(FName QuestID)
{
    return false;
}

bool UStoryIntegration::CompleteMainQuest(FName QuestID)
{
    return false;
}

EStoryAct UStoryIntegration::GetCurrentAct()
{
    return EStoryAct::Act1_Anomalie;
}

void UStoryIntegration::AdvanceToAct(EStoryAct NewAct)
{
}

FFragmentQuest UStoryIntegration::GetFragmentQuest(FName FragmentID)
{
    return FFragmentQuest();
}

TArray<FFragmentQuest> UStoryIntegration::GetFragmentQuests(EFragment Fragment)
{
    return TArray<FFragmentQuest>();
}

FDiaryEntry UStoryIntegration::GetDiaryEntry(FName EntryID)
{
    return FDiaryEntry();
}

TArray<FDiaryEntry> UStoryIntegration::GetDiaryEntriesByLocation(FName LocationID)
{
    return TArray<FDiaryEntry>();
}

TArray<FDiaryEntry> UStoryIntegration::GetAllDiaryEntries()
{
    return TArray<FDiaryEntry>();
}

bool UStoryIntegration::UnlockEnding(EEnding Ending)
{
    return false;
}

TArray<EEnding> UStoryIntegration::GetUnlockedEndings()
{
    return TArray<EEnding>();
}

EEnding UStoryIntegration::GetCurrentEnding()
{
    return EEnding::None;
}

FText UStoryIntegration::GetAeonDialog()
{
    return FText();
}

void UStoryIntegration::SetAeonDialog(FText NewDialog)
{
}

bool UStoryIntegration::IsEchoFound()
{
    return false;
}

void UStoryIntegration::SetEchoFound(bool bFound)
{
}

int32 UStoryIntegration::GetIterationCount()
{
    return 1;
}

void UStoryIntegration::IncrementIterationCount()
{
}

void UStoryIntegration::SetCreatorModeEnabled(bool bEnabled)
{
}

bool UStoryIntegration::IsCreatorModeEnabled()
{
    return false;
}
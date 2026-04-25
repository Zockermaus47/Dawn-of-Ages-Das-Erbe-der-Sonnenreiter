#include "StoryNPCs.h"

UStoryNPCSystem::UStoryNPCSystem()
{
}

FStoryNPCData UStoryNPCSystem::GetNPCData(FName NPCID)
{
    return FStoryNPCData();
}

TArray<FStoryNPCData> UStoryNPCSystem::GetNPCsByFragment(EFragment Fragment)
{
    return TArray<FStoryNPCData>();
}

TArray<FStoryNPCData> UStoryNPCSystem::GetAllStoryNPCs()
{
    return TArray<FStoryNPCData>();
}

FText UStoryNPCSystem::GetNPCDialog(FName NPCID, FName QuestID)
{
    return FText();
}

FEchoData UStoryNPCSystem::GetEchoData()
{
    return FEchoData();
}

bool UStoryNPCSystem::IsEchoAvailable()
{
    return false;
}

void UStoryNPCSystem::UnlockEcho()
{
}
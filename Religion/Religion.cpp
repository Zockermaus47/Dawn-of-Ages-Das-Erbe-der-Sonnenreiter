#include "Religion.h"
#include "Story/StoryIntegration.h"

UReligionSystem::UReligionSystem()
{
}

FGodData UReligionSystem::GetGodData(FName GodID)
{
    return FGodData();
}

void UReligionSystem::Pray(FName GodID)
{
    if (GodID == TEXT("Aeon"))
    {
        UStoryIntegration::IncrementIterationCount();
    }
}

void UReligionSystem::PerformRitual(FName GodID, FName RitualID)
{
}

TArray<FGodData> UReligionSystem::GetAllGods()
{
    return TArray<FGodData>();
}

FGodData UReligionSystem::GetAeonData()
{
    FGodData Aeon;
    Aeon.GodID = TEXT("Aeon");
    Aeon.GodName = EGodName::Aeon;
    Aeon.DisplayName = FText::FromString(TEXT("Aeon – Der Schöpfer"));
    Aeon.Description = FText::FromString(TEXT("Eine kosmische Entität, die diese Welt erschuf. Aber was bedeutet Schöpfung, wenn man nie gelebt hat?"));
    Aeon.Blessings.Add(TEXT("Vision"));
    Aeon.Blessings.Add(TEXT("Creation"));
    Aeon.DevotionRequired = 0;
    Aeon.bIsHidden = true;
    Aeon.bIsStoryGod = true;
    return Aeon;
}

bool UReligionSystem::IsAeonKnown()
{
    return UStoryIntegration::GetCurrentAct() >= EStoryAct::Act2_Begegnung;
}

void UReligionSystem::RevealAeon()
{
}

FAeonReligionData UReligionSystem::GetAeonReligionData()
{
    return FAeonReligionData();
}
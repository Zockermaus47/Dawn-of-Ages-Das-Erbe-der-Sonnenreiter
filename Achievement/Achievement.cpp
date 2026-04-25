#include "Achievement.h"

UAchievementSystem::UAchievementSystem()
{
}

FAchievementData UAchievementSystem::GetAchievementData(FName AchievementID)
{
    return FAchievementData();
}

bool UAchievementSystem::UnlockAchievement(FName AchievementID)
{
    return false;
}

TArray<FAchievementData> UAchievementSystem::GetAllAchievements()
{
    return TArray<FAchievementData>();
}
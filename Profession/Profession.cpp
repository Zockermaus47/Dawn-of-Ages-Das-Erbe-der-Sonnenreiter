#include "Profession.h"

UProfessionSystem::UProfessionSystem()
{
}

FProfessionData UProfessionSystem::GetProfessionData(FName ProfessionID)
{
    return FProfessionData();
}

bool UProfessionSystem::CanUnlockAbility(FProfessionInstance Profession, FName AbilityID)
{
    return false;
}

void UProfessionSystem::UnlockAbility(FProfessionInstance& Profession, FName AbilityID)
{
}

void UProfessionSystem::AddExperience(FProfessionInstance& Profession, int32 Amount)
{
}

bool UProfessionSystem::LevelUp(FProfessionInstance& Profession)
{
    return false;
}

TArray<FSkillTreeNode> UProfessionSystem::GetSkillTree(FName ProfessionID)
{
    return TArray<FSkillTreeNode>();
}

TArray<FProfessionData> UProfessionSystem::GetAllProfessions()
{
    return TArray<FProfessionData>();
}
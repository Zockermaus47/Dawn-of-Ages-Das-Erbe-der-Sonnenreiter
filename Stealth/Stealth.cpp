#include "Stealth.h"

FStealthPlayerData UStealthSystem::PlayerStealthData;
float UStealthSystem::NoiseLevel = 0.0f;
bool UStealthSystem::bIsHidden = false;
bool UStealthSystem::bIsSneaking = false;

UStealthSystem::UStealthSystem()
{
    PlayerStealthData.StealthLevel = 1;
    PlayerStealthData.StealthState = EStealthState::Visible;
    PlayerStealthData.NotorietyLevel = 0;
    PlayerStealthData.bCanHideInShadows = false;
    PlayerStealthData.DetectionRadius = 500.0f;
}

FStealthSkillData UStealthSystem::GetStealthSkill(FName SkillID)
{
    FStealthSkillData Data;
    Data.SkillID = SkillID;
    
    if (SkillID == "Stealth_Novice")
    {
        Data.DisplayName = FText::FromString("Anfanger-Schleicher");
        Data.Description = FText::FromString("Kann sich in hellen Bereichen verstecken.");
        Data.StealthBonus = 1.0f;
        Data.bCanSilentKill = false;
        Data.DetectionMod = 1.0f;
        Data.NoiseMod = 1.0f;
    }
    else if (SkillID == "Stealth_Adept")
    {
        Data.DisplayName = FText::FromString("Geubter Schleicher");
        Data.Description = FText::FromString("Kann in Schatten huschen und lautlos angreifen.");
        Data.StealthBonus = 1.5f;
        Data.bCanSilentKill = true;
        Data.DetectionMod = 0.75f;
        Data.NoiseMod = 0.7f;
    }
    else if (SkillID == "Stealth_Master")
    {
        Data.DisplayName = FText::FromString("Meister-Schleicher");
        Data.Description = FText::FromString("Kann praktisch unsichtbar werden.");
        Data.StealthBonus = 2.0f;
        Data.bCanSilentKill = true;
        Data.DetectionMod = 0.5f;
        Data.NoiseMod = 0.5f;
    }
    else if (SkillID == "Stealth_Legend")
    {
        Data.DisplayName = FText::FromString("Legendarer Schatten");
        Data.Description = FText::FromString("Ist nur ein Flstern in der Dunkelheit.");
        Data.StealthBonus = 3.0f;
        Data.bCanSilentKill = true;
        Data.DetectionMod = 0.25f;
        Data.NoiseMod = 0.25f;
    }
    
    return Data;
}

void UStealthSystem::EnterStealth()
{
    if (PlayerStealthData.StealthState != EStealthState::Hidden)
    {
        PlayerStealthData.StealthState = EStealthState::Hidden;
        bIsHidden = true;
    }
}

void UStealthSystem::ExitStealth()
{
    PlayerStealthData.StealthState = EStealthState::Visible;
    bIsHidden = false;
    PlayerStealthData.NotorietyLevel = FMath::Max(0, PlayerStealthData.NotorietyLevel - 10);
}

void UStealthSystem::StartSneaking()
{
    bIsSneaking = true;
    PlayerStealthData.StealthState = EStealthState::Sneaking;
    NoiseLevel = PlayerStealthData.NoiseLevel * 0.5f;
}

void UStealthSystem::StopSneaking()
{
    bIsSneaking = false;
    if (!bIsHidden)
    {
        PlayerStealthData.StealthState = EStealthState::Visible;
    }
    NoiseLevel = PlayerStealthData.NoiseLevel;
}

void UStealthSystem::MoveSilently()
{
    if (bIsSneaking)
    {
        NoiseLevel = PlayerStealthData.NoiseLevel * 0.3f;
    }
}

FStealthPlayerData UStealthSystem::GetPlayerStealthData()
{
    return PlayerStealthData;
}

EStealthState UStealthSystem::GetStealthState()
{
    return PlayerStealthData.StealthState;
}

float UStealthSystem::GetDetectionRadius()
{
    return PlayerStealthData.DetectionRadius * GetStealthSkill("Stealth_Adept").DetectionMod;
}

float UStealthSystem::GetCurrentStealthValue()
{
    float BaseStealth = PlayerStealthData.StealthLevel * 10.0f;
    FStealthSkillData Skill = GetStealthSkill("Stealth_Adept");
    
    float VisualMod = 1.0f;
    
    switch (PlayerStealthData.StealthState)
    {
        case EStealthState::Hidden:
            VisualMod = 0.1f;
            break;
        case EStealthState::Sneaking:
            VisualMod = 0.3f;
            break;
        case EStealthState::Crouching:
            VisualMod = 0.5f;
            break;
        default:
            VisualMod = 1.0f;
            break;
    }
    
    if (bIsSneaking)
    {
        BaseStealth *= Skill.StealthBonus;
    }
    
    return BaseStealth * VisualMod * Skill.StealthBonus;
}

float UStealthSystem::GetNoiseLevel()
{
    return NoiseLevel;
}

void UStealthSystem::MakeNoise(float Amount)
{
    float SkillMod = GetStealthSkill("Stealth_Adept").NoiseMod;
    NoiseLevel = Amount * SkillMod;
}

bool UStealthSystem::CanBeDetected(float DetectorStealth, float Distance)
{
    float CurrentStealth = GetCurrentStealthValue();
    
    float DetectionChance = (1.0f - (CurrentStealth / DetectorStealth));
    
    if (Distance < 100.0f)
    {
        DetectionChance *= 1.5f;
    }
    else if (Distance < 300.0f)
    {
        DetectionChance *= 1.0f;
    }
    else
    {
        DetectionChance *= 0.5f;
    }
    
    return DetectionChance > FMath::FRand();
}

bool UStealthSystem::IsTargetAware(FName TargetID)
{
    return PlayerStealthData.AwareEnemies.Contains(TargetID);
}

void UStealthSystem::MarkTargetAware(FName TargetID)
{
    if (!PlayerStealthData.AwareEnemies.Contains(TargetID))
    {
        PlayerStealthData.AwareEnemies.Add(TargetID);
    }
}

void UStealthSystem::MarkTargetUnaware(FName TargetID)
{
    PlayerStealthData.AwareEnemies.Remove(TargetID);
}

void UStealthSystem::AddNotoriety(int32 Amount)
{
    PlayerStealthData.NotorietyLevel = FMath::Clamp(PlayerStealthData.NotorietyLevel + Amount, 0, 100);
}

void UStealthSystem::ReduceNotoriety(int32 Amount)
{
    PlayerStealthData.NotorietyLevel = FMath::Max(0, PlayerStealthData.NotorietyLevel - Amount);
}

int32 UStealthSystem::GetNotorietyLevel()
{
    return PlayerStealthData.NotorietyLevel;
}

void UStealthSystem::ApplyStealthSkill(FName SkillID)
{
    FStealthSkillData Skill = GetStealthSkill(SkillID);
    PlayerStealthData.StealthLevel = (int32)(Skill.StealthBonus * 10);
    PlayerStealthData.bCanHideInShadows = true;
    PlayerStealthData.DetectionRadius *= Skill.DetectionMod;
}

void UStealthSystem::TickStealth(float DeltaTime)
{
    if (bIsHidden)
    {
        if (FMath::FRand() > 0.98f)
        {
            PlayerStealthData.NotorietyLevel = FMath::Max(0, PlayerStealthData.NotorietyLevel - 1);
        }
    }
    
    if (!bIsHidden && !bIsSneaking)
    {
        PlayerStealthData.StealthState = EStealthState::Visible;
    }
}
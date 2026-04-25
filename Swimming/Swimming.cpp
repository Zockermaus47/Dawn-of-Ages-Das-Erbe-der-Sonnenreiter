#include "Swimming.h"

FSwimPlayerData USwimmingSystem::PlayerData;
FWaterEnvironmentData USwimmingSystem::CurrentWater;
ESwimState USwimmingSystem::SwimState = ESwimState::Land;
EBreathState USwimmingSystem::Breath = EBreathState::Normal;
float USwimmingSystem::DiveStartTime = 0.0f;
float USwimmingSystem::BreathRecoveryRate = 10.0f;
float USwimmingSystem::SurfaceRecoveryDelay = 2.0f;

USwimmingSystem::USwimmingSystem()
{
    PlayerData.CurrentState = ESwimState::Land;
    PlayerData.BreathState = EBreathState::Normal;
    PlayerData.CurrentBreath = 30.0f;
    PlayerData.MaxBreath = 30.0f;
    PlayerData.SwimSpeed = 400.0f;
    PlayerData.bCanSwim = true;
}

FSwimSkillData USwimmingSystem::GetSwimSkill(FName SkillID)
{
    FSwimSkillData Data;
    Data.SkillID = SkillID;
    
    if (SkillID == "Swim_Novice")
    {
        Data.DisplayName = FText::FromString("Anfanger-Schwimmer");
        Data.Description = FText::FromString("Kann in flachen Gewassern schwimmen.");
        Data.BreathCapacity = 20.0f;
        Data.SwimSpeedMod = 0.8f;
        Data.DiveDepthMod = 0.5f;
        Data.bCanDive = false;
        Data.bCanHoldBreath = false;
        Data.StaminaDrainMod = 1.5f;
    }
    else if (SkillID == "Swim_Adept")
    {
        Data.DisplayName = FText::FromString("Geubter Schwimmer");
        Data.Description = FText::FromString("Kann tiefer tauchen und atemanhalten.");
        Data.BreathCapacity = 45.0f;
        Data.SwimSpeedMod = 1.0f;
        Data.DiveDepthMod = 0.75f;
        Data.bCanDive = true;
        Data.bCanHoldBreath = true;
        Data.StaminaDrainMod = 1.0f;
    }
    else if (SkillID == "Swim_Master")
    {
        Data.DisplayName = FText::FromString("Meister-Schwimmer");
        Data.Description = FText::FromString("Kann in grosser Tiefe tauchen und lange tauchen.");
        Data.BreathCapacity = 90.0f;
        Data.SwimSpeedMod = 1.2f;
        Data.DiveDepthMod = 1.0f;
        Data.bCanDive = true;
        Data.bCanHoldBreath = true;
        Data.StaminaDrainMod = 0.7f;
    }
    else if (SkillID == "Swim_Legend")
    {
        Data.DisplayName = FText::FromString("Legendarer Schwimmer");
        Data.Description = FText::FromString(" Kann wie ein Fisch atmen und tief tauchen.");
        Data.BreathCapacity = 150.0f;
        Data.SwimSpeedMod = 1.5f;
        Data.DiveDepthMod = 1.5f;
        Data.bCanDive = true;
        Data.bCanHoldBreath = true;
        Data.StaminaDrainMod = 0.4f;
    }
    
    return Data;
}

void USwimmingSystem::EnterWater(FWaterEnvironmentData WaterData)
{
    CurrentWater = WaterData;
    SwimState = ESwimState::Wading;
    PlayerData.CurrentState = ESwimState::Wading;
    Breath = EBreathState::Normal;
    PlayerData.BreathState = EBreathState::Normal;
    
    if (WaterData.WaterType == EWaterBody::HotSpring)
    {
        PlayerData.MaxBreath = FMath::Min(PlayerData.MaxBreath + 5.0f, 150.0f);
    }
}

void USwimmingSystem::ExitWater()
{
    SwimState = ESwimState::Land;
    PlayerData.CurrentState = ESwimState::Land;
    PlayerData.bIsDiving = false;
    PlayerData.DiveDepth = 0.0f;
    
    if (Breath == EBreathState::Drowning)
    {
        Breath = EBreathState::Recovering;
        PlayerData.BreathState = EBreathState::Recovering;
    }
    else
    {
        Breath = EBreathState::Normal;
        PlayerData.BreathState = EBreathState::Normal;
    }
}

void USwimmingSystem::StartSwimming()
{
    if (SwimState == ESwimState::Wading || SwimState == ESwimState::Land)
    {
        SwimState = ESwimState::Swimming;
        PlayerData.CurrentState = ESwimState::Swimming;
    }
}

void USwimmingSystem::StopSwimming()
{
    if (SwimState == ESwimState::Swimming || SwimState == ESwimState::Diving)
    {
        SwimState = ESwimState::Wading;
        PlayerData.CurrentState = ESwimState::Wading;
    }
}

void USwimmingSystem::StartDiving()
{
    if (SwimState == ESwimState::Swimming && PlayerData.bCanDive)
    {
        SwimState = ESwimState::Diving;
        PlayerData.CurrentState = ESwimState::Diving;
        PlayerData.bIsDiving = true;
        DiveStartTime = 0.0f;
    }
}

void USwimmingSystem::Surface()
{
    if (SwimState == ESwimState::Diving || SwimState == ESwimState::Underwater)
    {
        SwimState = ESwimState::Swimming;
        PlayerData.CurrentState = ESwimState::Swimming;
        PlayerData.bIsDiving = false;
    }
}

void USwimmingSystem::HoldBreath()
{
    if (Breath != EBreathState::Holding && PlayerData.CurrentBreath > 0.0f)
    {
        Breath = EBreathState::Holding;
        PlayerData.BreathState = EBreathState::Holding;
    }
}

void USwimmingSystem::ReleaseBreath()
{
    if (Breath == EBreathState::Holding)
    {
        Breath = EBreathState::Normal;
        PlayerData.BreathState = EBreathState::Normal;
    }
}

void USwimmingSystem::TickSwimming(float DeltaTime)
{
    if (SwimState == ESwimState::Land)
        return;
    
    PlayerData.UnderwaterTime += DeltaTime;
    DiveStartTime += DeltaTime;
    
    FSwimSkillData Skill = GetSwimSkill("Swim_Adept");
    
    if (SwimState == ESwimState::Swimming || SwimState == ESwimState::Diving || SwimState == ESwimState::Underwater)
    {
        PlayerData.CurrentBreath -= DeltaTime * Skill.StaminaDrainMod;
        
        if (SwimState == ESwimState::Diving || SwimState == ESwimState::Underwater)
        {
            float DepthPenalty = PlayerData.DiveDepth * 0.5f;
            PlayerData.CurrentBreath -= DeltaTime * DepthPenalty;
        }
        
        if (CurrentWater.WaterType == EWaterBody::HotSpring)
        {
            PlayerData.CurrentBreath -= DeltaTime * 1.5f;
        }
    }
    
    if (CurrentWater.bHasCurrents)
    {
        float CurrentDrain = CurrentWater.CurrentStrength * DeltaTime * 2.0f;
        PlayerData.StaminaDrain += CurrentDrain;
    }
    
    if (PlayerData.CurrentBreath <= 0.0f)
    {
        if (Breath != EBreathState::Drowning)
        {
            Breath = EBreathState::Stressed;
            PlayerData.BreathState = EBreathState::Stressed;
        }
        
        if (PlayerData.CurrentBreath <= -10.0f)
        {
            Breath = EBreathState::Drowning;
            PlayerData.BreathState = EBreathState::Drowning;
        }
    }
    else if (Breath == EBreathState::Stressed || Breath == EBreathState::Drowning)
    {
        if (SwimState == ESwimState::Wading || SwimState == ESwimState::Land)
        {
            RecoverBreath(DeltaTime * BreathRecoveryRate);
        }
    }
}

FSwimPlayerData USwimmingSystem::GetPlayerSwimData()
{
    return PlayerData;
}

ESwimState USwimmingSystem::GetSwimState()
{
    return SwimState;
}

float USwimmingSystem::GetSwimSpeed()
{
    float Speed = PlayerData.SwimSpeed;
    
    FSwimSkillData Skill = GetSwimSkill("Swim_Adept");
    Speed *= Skill.SwimSpeedMod;
    
    switch (CurrentWater.WaterType)
    {
        case EWaterBody::Saltwater:
            Speed *= 1.1f;
            break;
        case EWaterBody::HotSpring:
            Speed *= 0.9f;
            break;
        case EWaterBody::MurkyWater:
            Speed *= 0.7f;
            break;
        case EWaterBody::DeepOcean:
            Speed *= 0.8f;
            break;
        default:
            break;
    }
    
    if (CurrentWater.bHasCurrents)
    {
        FVector2D PlayerDir = FVector2D(1.0f, 0.0f);
        float DotProduct = FVector2D::DotProduct(PlayerDir, CurrentWater.CurrentDirection);
        Speed += CurrentWater.CurrentStrength * DotProduct;
    }
    
    return Speed;
}

float USwimmingSystem::GetBreathPercentage()
{
    return FMath::Clamp(PlayerData.CurrentBreath / PlayerData.MaxBreath, 0.0f, 1.0f);
}

bool USwimmingSystem::IsUnderwater()
{
    return SwimState == ESwimState::Diving || SwimState == ESwimState::Underwater;
}

bool USwimmingSystem::CanDiveTo(EDiveDepth TargetDepth)
{
    if (!PlayerData.bCanDive)
        return false;
    
    FSwimSkillData Skill = GetSwimSkill("Swim_Adept");
    
    float MaxDepth = 0.0f;
    switch (TargetDepth)
    {
        case EDiveDepth::Surface: MaxDepth = 2.0f; break;
        case EDiveDepth::Shallow: MaxDepth = 10.0f; break;
        case EDiveDepth::Medium: MaxDepth = 25.0f; break;
        case EDiveDepth::Deep: MaxDepth = 50.0f; break;
        case EDiveDepth::Abyss: MaxDepth = 100.0f; break;
    }
    
    float AllowedDepth = 10.0f * Skill.DiveDepthMod;
    return CurrentWater.Depth >= AllowedDepth;
}

float USwimmingSystem::GetPressureDamage()
{
    if (!IsUnderwater())
        return 0.0f;
    
    float BaseDamage = 0.0f;
    float Depth = PlayerData.DiveDepth;
    
    if (Depth > 30.0f)
    {
        BaseDamage = (Depth - 30.0f) * 0.5f;
    }
    else if (Depth > 50.0f)
    {
        BaseDamage = (Depth - 50.0f) * 1.0f;
    }
    else if (Depth > 80.0f)
    {
        BaseDamage = (Depth - 80.0f) * 2.0f;
    }
    
    FSwimSkillData Skill = GetSwimSkill("Swim_Adept");
    if (Skill.DiveDepthMod >= 1.5f)
    {
        BaseDamage *= 0.1f;
    }
    else if (Skill.DiveDepthMod >= 1.0f)
    {
        BaseDamage *= 0.5f;
    }
    
    return FMath::Max(0.0f, BaseDamage);
}

void USwimmingSystem::ApplySwimSkill(FName SkillID)
{
    FSwimSkillData Skill = GetSwimSkill(SkillID);
    
    PlayerData.MaxBreath = Skill.BreathCapacity;
    PlayerData.SwimSpeed = 400.0f * Skill.SwimSpeedMod;
    PlayerData.bCanDive = Skill.bCanDive;
    PlayerData.StaminaDrain = 5.0f * Skill.StaminaDrainMod;
}

void USwimmingSystem::RecoverBreath(float Amount)
{
    PlayerData.CurrentBreath = FMath::Min(PlayerData.CurrentBreath + Amount, PlayerData.MaxBreath);
    
    if (PlayerData.CurrentBreath > 0.0f && Breath == EBreathState::Stressed)
    {
        Breath = EBreathState::Normal;
        PlayerData.BreathState = EBreathState::Normal;
    }
    else if (PlayerData.CurrentBreath > 10.0f && Breath == EBreathState::Drowning)
    {
        Breath = EBreathState::Recovering;
        PlayerData.BreathState = EBreathState::Recovering;
    }
}

FWaterEnvironmentData USwimmingSystem::GetCurrentWaterData()
{
    return CurrentWater;
}
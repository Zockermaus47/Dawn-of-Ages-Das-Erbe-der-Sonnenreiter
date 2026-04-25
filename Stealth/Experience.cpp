#include "Experience.h"

int32 UExperienceSystem::CurrentXP = 0;
int32 UExperienceSystem::CurrentLevel = 1;
int32 UExperienceSystem::XPForNextLevel = 1000;
int32 UExperienceSystem::AvailablePoints = 0;
int32 UExperienceSystem::AttributePoints[10] = {10,10,10,10,10,10,10,10,10,10};
float UExperienceSystem::CurrentHealth = 100.0f;
float UExperienceSystem::MaxHealthBase = 100.0f;
float UExperienceSystem::CurrentStamina = 100.0f;
float UExperienceSystem::MaxStaminaBase = 100.0f;
float UExperienceSystem::CurrentWeight = 0.0f;
FStatBonuses UExperienceSystem::Bonuses;

UExperienceSystem::UExperienceSystem()
{
    CurrentXP = 0;
    CurrentLevel = 1;
    AvailablePoints = 0;
    for (int i = 0; i < 10; i++) AttributePoints[i] = 10;
    CalculateStats();
}

void UExperienceSystem::AddExperience(int32 Amount)
{
    CurrentXP += Amount;
    while (CurrentXP >= XPForNextLevel)
    {
        CurrentXP -= XPForNextLevel;
        LevelUp();
    }
}

int32 UExperienceSystem::GetCurrentXP()
{
    return CurrentXP;
}

int32 UExperienceSystem::GetLevel()
{
    return CurrentLevel;
}

int32 UExperienceSystem::GetXPToNextLevel()
{
    return XPForNextLevel;
}

void UExperienceSystem::LevelUp()
{
    CurrentLevel++;
    AvailablePoints += 5;
    XPForNextLevel = (int32)(XPForNextLevel * 1.2f);
    
    MaxHealthBase += 10.0f;
    MaxStaminaBase += 5.0f;
    
    CalculateStats();
}

int32 UExperienceSystem::GetAvailablePoints()
{
    return AvailablePoints;
}

void UExperienceSystem::SpendPoint(EAttribute Attribute)
{
    if (AvailablePoints > 0)
    {
        int32 AttrIndex = (int32)Attribute;
        if (AttrIndex >= 0 && AttrIndex < 10)
        {
            AttributePoints[AttrIndex]++;
            AvailablePoints--;
            CalculateStats();
        }
    }
}

int32 UExperienceSystem::GetAttributeValue(EAttribute Atr)
{
    int32 Index = (int32)Atr;
    if (Index >= 0 && Index < 10)
        return AttributePoints[Index];
    return 10;
}

void UExperienceSystem::AddAttributeBonus(EAttribute Attribute, int32 Bonus)
{
    int32 Index = (int32)Attribute;
    if (Index >= 0 && Index < 10)
    {
        AttributePoints[Index] += Bonus;
        CalculateStats();
    }
}

void UExperienceSystem::CalculateStats()
{
    int32 STR = AttributePoints[0];
    int32 END = AttributePoints[1];
    int32 VIT = AttributePoints[2];
    int32 AGI = AttributePoints[3];
    int32 ACC = AttributePoints[4];
    int32 INT = AttributePoints[5];
    int32 WIS = AttributePoints[6];
    int32 CHA = AttributePoints[7];
    int32 LCK = AttributePoints[8];
    int32 STL = AttributePoints[9];
    
    MaxHealthBase = 100.0f + (VIT * 10.0f) + (END * 5.0f) + (STR * 2.0f);
    Bonuses.MaxHealth = MaxHealthBase;
    
    MaxStaminaBase = 100.0f + (END * 10.0f) + (AGI * 5.0f);
    Bonuses.MaxStamina = MaxStaminaBase;
    
    Bonuses.CarryCapacity = 30.0f + (STR * 5.0f) + (END * 2.0f);
    
    Bonuses.StaminaRegen = 5.0f + (END * 0.5f) + (VIT * 0.2f);
    
    float BaseMoveSpeed = 600.0f;
    if (IsEncumbered())
        BaseMoveSpeed *= GetEncumbrancePenalty();
    Bonuses.MoveSpeed = BaseMoveSpeed + (AGI * 10.0f);
    
    Bonuses.MeleeDamage = 1.0f + (STR * 0.1f) + (END * 0.05f);
    Bonuses.RangedDamage = 1.0f + (ACC * 0.1f);
    
    Bonuses.ArmorRating = (VIT * 0.5f) + (END * 0.3f);
    
    Bonuses.AttackSpeed = 1.0f + (AGI * 0.02f) + (STR * 0.01f);
    
    Bonuses.CriticalChance = 0.05f + (LCK * 0.005f) + (ACC * 0.002f);
    
    Bonuses.DodgeChance = 0.05f + (AGI * 0.005f);
    
    Bonuses.BlockChance = 0.10f + (STR * 0.005f) + (END * 0.005f);
    
    if (CurrentHealth > MaxHealthBase)
        CurrentHealth = MaxHealthBase;
    if (CurrentStamina > MaxStaminaBase)
        CurrentStamina = MaxStaminaBase;
}

float UExperienceSystem::GetMaxHealth()
{
    return MaxHealthBase;
}

float UExperienceSystem::GetCurrentHealth()
{
    return CurrentHealth;
}

void UExperienceSystem::SetCurrentHealth(float Value)
{
    CurrentHealth = FMath::Clamp(Value, 0.0f, MaxHealthBase);
}

void UExperienceSystem::ModifyHealth(float Delta)
{
    CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0.0f, MaxHealthBase);
}

float UExperienceSystem::GetMaxStamina()
{
    return MaxStaminaBase;
}

float UExperienceSystem::GetCurrentStamina()
{
    return CurrentStamina;
}

void UExperienceSystem::SetCurrentStamina(float Value)
{
    CurrentStamina = FMath::Clamp(Value, 0.0f, MaxStaminaBase);
}

void UExperienceSystem::ModifyStamina(float Delta)
{
    CurrentStamina = FMath::Clamp(CurrentStamina + Delta, 0.0f, MaxStaminaBase);
}

float UExperienceSystem::GetCarryCapacity()
{
    return Bonuses.CarryCapacity;
}

float UExperienceSystem::GetCurrentWeight()
{
    return CurrentWeight;
}

bool UExperienceSystem::IsEncumbered()
{
    return CurrentWeight >= Bonuses.CarryCapacity;
}

float UExperienceSystem::GetEncumbrancePenalty()
{
    if (!IsEncumbered()) return 1.0f;
    
    float OverWeight = CurrentWeight - Bonuses.CarryCapacity;
    float Penalty = OverWeight / Bonuses.CarryCapacity;
    return FMath::Clamp(1.0f - (Penalty * 0.5f), 0.3f, 1.0f);
}

void UExperienceSystem::AddItemWeight(float Weight)
{
    CurrentWeight += Weight;
}

void UExperienceSystem::RemoveItemWeight(float Weight)
{
    CurrentWeight = FMath::Max(0.0f, CurrentWeight - Weight);
}

float UExperienceSystem::GetMovementPenalty()
{
    return GetEncumbrancePenalty();
}

float UExperienceSystem::GetMeleeDamageBonus()
{
    return Bonuses.MeleeDamage;
}

float UExperienceSystem::GetArmorBonus()
{
    return Bonuses.ArmorRating;
}

float UExperienceSystem::GetStaminaRegenBonus()
{
    return Bonuses.StaminaRegen;
}

FStatBonuses UExperienceSystem::GetAllBonuses()
{
    return Bonuses;
}
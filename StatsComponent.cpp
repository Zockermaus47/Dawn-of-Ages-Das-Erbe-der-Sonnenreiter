#include "StatsComponent.h"
#include "Net/UnrealNetwork.h"

UStatsComponent::UStatsComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicated(true);
}

void UStatsComponent::BeginPlay()
{
    Super::BeginPlay();

    Hunger = MaxHunger;
    Thirst = MaxThirst;
    Health = MaxHealth;
    Stamina = MaxStamina;
    Temperature = MaxTemperature / 2.0f;

    LastHungerValue = Hunger;
    LastThirstValue = Thirst;
    LastHealthValue = Health;
    LastStaminaValue = Stamina;
    LastTemperatureValue = Temperature;
}

void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!GetOwner()->HasAuthority())
    {
        return;
    }

    DrainStat(FName("Hunger"), HungerDrainRate, DeltaTime);
    DrainStat(FName("Thirst"), ThirstDrainRate, DeltaTime);

    if (StaminaDrainRate > 0.0f)
    {
        Stamina = FMath::Clamp(Stamina - (StaminaDrainRate * DeltaTime), 0.0f, MaxStamina);
    }
    else if (Stamina < MaxStamina)
    {
        RegenStat(Stamina, MaxStamina, StaminaRegenRate, DeltaTime);
    }

    ApplyStatDamage(FName("Hunger"), HungerDamageThreshold, HungerDamagePerSecond);
    ApplyStatDamage(FName("Thirst"), ThirstDamageThreshold, ThirstDamagePerSecond);

    if (HealthRegenRate > 0.0f && Health < MaxHealth)
    {
        bool bCanRegen = true;
        
        if (Hunger <= HungerDamageThreshold || Thirst <= ThirstDamageThreshold)
        {
            bCanRegen = false;
        }

        if (bCanRegen)
        {
            TimeSinceLastRegen += DeltaTime;
            if (TimeSinceLastRegen >= HealthRegenDelay)
            {
                Health = FMath::Clamp(Health + (HealthRegenRate * DeltaTime), 0.0f, MaxHealth);
            }
        }
    }
    else
    {
        TimeSinceLastRegen = 0.0f;
    }

    BroadcastChanges();
}

void UStatsComponent::BroadcastChanges()
{
    if (!FMath::IsNearlyEqual(Hunger, LastHungerValue))
    {
        OnHungerChanged.Broadcast(Hunger);
        LastHungerValue = Hunger;
    }

    if (!FMath::IsNearlyEqual(Thirst, LastThirstValue))
    {
        OnThirstChanged.Broadcast(Thirst);
        LastThirstValue = Thirst;
    }

    if (!FMath::IsNearlyEqual(Health, LastHealthValue))
    {
        OnHealthChanged.Broadcast(Health);
        LastHealthValue = Health;
    }

    if (!FMath::IsNearlyEqual(Stamina, LastStaminaValue))
    {
        OnStaminaChanged.Broadcast(Stamina);
        LastStaminaValue = Stamina;
    }

    if (!FMath::IsNearlyEqual(Temperature, LastTemperatureValue))
    {
        OnTemperatureChanged.Broadcast(Temperature);
        LastTemperatureValue = Temperature;
    }
}

void UStatsComponent::DrainStat(FName StatName, float DrainRate, float DeltaTime)
{
    if (StatName == FName("Hunger"))
    {
        Hunger = FMath::Clamp(Hunger - (DrainRate * DeltaTime), 0.0f, MaxHunger);
        if (Hunger <= HungerDamageThreshold && LastHungerValue > HungerDamageThreshold)
        {
            OnHungerDepleted.Broadcast(FName("Hunger"));
        }
    }
    else if (StatName == FName("Thirst"))
    {
        Thirst = FMath::Clamp(Thirst - (DrainRate * DeltaTime), 0.0f, MaxThirst);
        if (Thirst <= ThirstDamageThreshold && LastThirstValue > ThirstDamageThreshold)
        {
            OnThirstDepleted.Broadcast(FName("Thirst"));
        }
    }
    else if (StatName == FName("Temperature"))
    {
        Temperature = FMath::Clamp(Temperature + (DrainRate * DeltaTime), 0.0f, MaxTemperature);
        if (Temperature <= 0.0f || Temperature >= MaxTemperature)
        {
            OnTemperatureDepleted.Broadcast(FName("Temperature"));
        }
    }
}

void UStatsComponent::ApplyStatDamage(FName StatName, float Threshold, float DPS)
{
    float StatValue = 0.0f;
    float MaxValue = 100.0f;

    if (StatName == FName("Hunger"))
    {
        StatValue = Hunger;
        MaxValue = MaxHunger;
    }
    else if (StatName == FName("Thirst"))
    {
        StatValue = Thirst;
        MaxValue = MaxThirst;
    }
    else if (StatName == FName("Health"))
    {
        StatValue = Health;
        MaxValue = MaxHealth;
    }

    if (StatValue <= Threshold)
    {
        Health = FMath::Clamp(Health - (DPS * GetWorld()->GetDeltaSeconds()), 0.0f, MaxHealth);
        TimeSinceLastDamage = 0.0f;

        if (StatName == FName("Health") && Health <= 0.0f)
        {
            OnHealthDepleted.Broadcast(FName("Health"));
        }
    }
}

void UStatsComponent::RegenStat(float& CurrentValue, float MaxValue, float RegenRate, float DeltaTime)
{
    CurrentValue = FMath::Clamp(CurrentValue + (RegenRate * DeltaTime), 0.0f, MaxValue);
}

void UStatsComponent::ModifyStat(FName StatName, float Delta)
{
    if (StatName == FName("Hunger"))
    {
        Hunger = FMath::Clamp(Hunger + Delta, 0.0f, MaxHunger);
    }
    else if (StatName == FName("Thirst"))
    {
        Thirst = FMath::Clamp(Thirst + Delta, 0.0f, MaxThirst);
    }
    else if (StatName == FName("Health"))
    {
        Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);
    }
    else if (StatName == FName("Stamina"))
    {
        Stamina = FMath::Clamp(Stamina + Delta, 0.0f, MaxStamina);
    }
    else if (StatName == FName("Temperature"))
    {
        Temperature = FMath::Clamp(Temperature + Delta, 0.0f, MaxTemperature);
    }
}

void UStatsComponent::SetStat(FName StatName, float Value)
{
    if (StatName == FName("Hunger"))
    {
        Hunger = FMath::Clamp(Value, 0.0f, MaxHunger);
    }
    else if (StatName == FName("Thirst"))
    {
        Thirst = FMath::Clamp(Value, 0.0f, MaxThirst);
    }
    else if (StatName == FName("Health"))
    {
        Health = FMath::Clamp(Value, 0.0f, MaxHealth);
    }
    else if (StatName == FName("Stamina"))
    {
        Stamina = FMath::Clamp(Value, 0.0f, MaxStamina);
    }
    else if (StatName == FName("Temperature"))
    {
        Temperature = FMath::Clamp(Value, 0.0f, MaxTemperature);
    }
}

float UStatsComponent::GetStat(FName StatName) const
{
    if (StatName == FName("Hunger")) return Hunger;
    if (StatName == FName("Thirst")) return Thirst;
    if (StatName == FName("Health")) return Health;
    if (StatName == FName("Stamina")) return Stamina;
    if (StatName == FName("Temperature")) return Temperature;
    return 0.0f;
}

float UStatsComponent::GetStatPercent(FName StatName) const
{
    if (StatName == FName("Hunger")) return (Hunger / MaxHunger) * 100.0f;
    if (StatName == FName("Thirst")) return (Thirst / MaxThirst) * 100.0f;
    if (StatName == FName("Health")) return (Health / MaxHealth) * 100.0f;
    if (StatName == FName("Stamina")) return (Stamina / MaxStamina) * 100.0f;
    if (StatName == FName("Temperature")) return (Temperature / MaxTemperature) * 100.0f;
    return 0.0f;
}

bool UStatsComponent::HasStat(FName StatName) const
{
    float Value = GetStat(StatName);
    return Value > 0.0f;
}

void UStatsComponent::RestoreAllStats(float Amount)
{
    ModifyStat(FName("Hunger"), Amount);
    ModifyStat(FName("Thirst"), Amount);
    ModifyStat(FName("Health"), Amount);
    ModifyStat(FName("Stamina"), Amount);
}

void UStatsComponent::DrainAllStats(float Amount)
{
    ModifyStat(FName("Hunger"), -Amount);
    ModifyStat(FName("Thirst"), -Amount);
    ModifyStat(FName("Stamina"), -Amount);
}

bool UStatsComponent::IsStarving() const
{
    return Hunger <= HungerDamageThreshold;
}

bool UStatsComponent::IsDehydrated() const
{
    return Thirst <= ThirstDamageThreshold;
}

bool UStatsComponent::IsFreezing() const
{
    return Temperature <= 0.0f;
}

bool UStatsComponent::IsOverheating() const
{
    return Temperature >= MaxTemperature;
}

void UStatsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UStatsComponent, Hunger);
    DOREPLIFETIME(UStatsComponent, Thirst);
    DOREPLIFETIME(UStatsComponent, Health);
    DOREPLIFETIME(UStatsComponent, Stamina);
    DOREPLIFETIME(UStatsComponent, Temperature);
}
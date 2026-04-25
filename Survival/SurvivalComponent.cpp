#include "Survival/SurvivalComponent.h"

USurvivalComponent::USurvivalComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    MaxHunger = 100.0f;
    MaxThirst = 100.0f;
    MaxStamina = 100.0f;
    
    CurrentHunger = 100.0f;
    CurrentThirst = 100.0f;
    CurrentStamina = 100.0f;
    CurrentTemperature = 37.0f;

    MinTemperature = 20.0f;
    MaxTemperature = 40.0f;

    HungerDecreaseRate = 1.0f;
    ThirstDecreaseRate = 1.5f;
    TemperatureDecreaseRate = 0.5f;
    StaminaRegenRate = 5.0f;
    StaminaDecreaseRate = 10.0f;

    CurrentHealthState = EHealthState::Healthy;
    bIsDead = false;
}

void USurvivalComponent::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(
        HealthEffectTimer,
        this,
        &USurvivalComponent::ApplyPeriodicHealthEffects,
        1.0f,
        true
    );
}

void USurvivalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bIsDead) return;

    UpdateSurvivalStats(DeltaTime);
    UpdateHealthState();
    ApplyHealthEffects(DeltaTime);
}

void USurvivalComponent::UpdateSurvivalStats(float DeltaTime)
{
    if (bIsDead) return;

    CurrentHunger = FMath::Clamp(CurrentHunger - HungerDecreaseRate * DeltaTime, 0.0f, MaxHunger);
    CurrentThirst = FMath::Clamp(CurrentThirst - ThirstDecreaseRate * DeltaTime, 0.0f, MaxThirst);

    if (CurrentTemperature > 37.0f)
    {
        CurrentTemperature = FMath::Clamp(CurrentTemperature - TemperatureDecreaseRate * DeltaTime, 37.0f, MaxTemperature);
    }
    else if (CurrentTemperature < 37.0f)
    {
        CurrentTemperature = FMath::Clamp(CurrentTemperature + TemperatureDecreaseRate * DeltaTime, MinTemperature, 37.0f);
    }

    if (CurrentStamina < MaxStamina && CurrentHunger > 20.0f && CurrentThirst > 20.0f)
    {
        CurrentStamina = FMath::Clamp(CurrentStamina + StaminaRegenRate * DeltaTime, 0.0f, MaxStamina);
    }
}

void USurvivalComponent::UpdateHealthState()
{
    if (bIsDead) return;

    if (CurrentHunger <= 0.0f && CurrentThirst <= 0.0f)
    {
        CurrentHealthState = EHealthState::Dead;
        bIsDead = true;
        UE_LOG(LogTemp, Log, TEXT("Spieler ist gestorben!"));
    }
    else if (CurrentHunger <= 0.0f)
    {
        CurrentHealthState = EHealthState::Starving;
    }
    else if (CurrentThirst <= 0.0f)
    {
        CurrentHealthState = EHealthState::Dehydrated;
    }
    else if (CurrentHunger < 30.0f)
    {
        CurrentHealthState = EHealthState::Hungry;
    }
    else if (CurrentThirst < 30.0f)
    {
        CurrentHealthState = EHealthState::Thirsty;
    }
    else
    {
        CurrentHealthState = EHealthState::Healthy;
    }
}

void USurvivalComponent::ApplyHealthEffects(float DeltaTime)
{
}

void USurvivalComponent::ApplyPeriodicHealthEffects()
{
    if (bIsDead) return;

    AActor* Owner = GetOwner();
    if (!Owner) return;

    if (IsStarving())
    {
        UE_LOG(LogTemp, Warning, TEXT("Spieler verhungert!"));
    }

    if (IsDehydrated())
    {
        UE_LOG(LogTemp, Warning, TEXT("Spieler verdurstet!"));
    }

    if (IsTooHot())
    {
        UE_LOG(LogTemp, Warning, TEXT("Zu heiß!"));
    }

    if (IsTooCold())
    {
        UE_LOG(LogTemp, Warning, TEXT("Zu kalt!"));
    }
}

void USurvivalComponent::ModifyHunger(float Amount)
{
    CurrentHunger = FMath::Clamp(CurrentHunger + Amount, 0.0f, MaxHunger);
    UE_LOG(LogTemp, Log, TEXT("Hunger: %f"), CurrentHunger);
}

void USurvivalComponent::ModifyThirst(float Amount)
{
    CurrentThirst = FMath::Clamp(CurrentThirst + Amount, 0.0f, MaxThirst);
    UE_LOG(LogTemp, Log, TEXT("Durst: %f"), CurrentThirst);
}

void USurvivalComponent::ModifyTemperature(float Amount)
{
    CurrentTemperature = FMath::Clamp(CurrentTemperature + Amount, MinTemperature, MaxTemperature);
    UE_LOG(LogTemp, Log, TEXT("Temperatur: %f"), CurrentTemperature);
}

void USurvivalComponent::ModifyStamina(float Amount)
{
    CurrentStamina = FMath::Clamp(CurrentStamina + Amount, 0.0f, MaxStamina);
}

void USurvivalComponent::UseStamina(float Amount)
{
    if (CurrentStamina >= Amount)
    {
        CurrentStamina = FMath::Clamp(CurrentStamina - Amount, 0.0f, MaxStamina);
    }
}

float USurvivalComponent::GetHungerPercent() const
{
    return MaxHunger > 0.0f ? (CurrentHunger / MaxHunger) * 100.0f : 0.0f;
}

float USurvivalComponent::GetThirstPercent() const
{
    return MaxThirst > 0.0f ? (CurrentThirst / MaxThirst) * 100.0f : 0.0f;
}

float USurvivalComponent::GetStaminaPercent() const
{
    return MaxStamina > 0.0f ? (CurrentStamina / MaxStamina) * 100.0f : 0.0f;
}

float USurvivalComponent::GetTemperaturePercent() const
{
    float Range = MaxTemperature - MinTemperature;
    if (Range <= 0.0f) return 50.0f;
    return ((CurrentTemperature - MinTemperature) / Range) * 100.0f;
}

bool USurvivalComponent::IsStarving() const
{
    return CurrentHunger <= 0.0f;
}

bool USurvivalComponent::IsDehydrated() const
{
    return CurrentThirst <= 0.0f;
}

bool USurvivalComponent::IsTooHot() const
{
    return CurrentTemperature >= 38.0f;
}

bool USurvivalComponent::IsTooCold() const
{
    return CurrentTemperature <= 30.0f;
}

void USurvivalComponent::ConsumeFood(float FoodAmount)
{
    ModifyHunger(FoodAmount);
    UE_LOG(LogTemp, Log, TEXT("Food gegessen: +%f"), FoodAmount);
}

void USurvivalComponent::ConsumeWater(float WaterAmount)
{
    ModifyThirst(WaterAmount);
    UE_LOG(LogTemp, Log, TEXT("Wasser getrunken: +%f"), WaterAmount);
}
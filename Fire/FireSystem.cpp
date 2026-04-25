#include "FireSystem.h"

float UFireSystem::PlayerWarmth = 0.0f;

FCampfire UFireSystem::CreateFire(EFireType Type, bool bIsIndoor)
{
    FCampfire Fire;
    Fire.Type = Type;
    Fire.bIsIndoor = bIsIndoor;
    Fire.State = EFireState::Unlit;
    Fire.FuelLevel = 0.0f;
    Fire.HeatOutput = 0.0f;
    Fire.LightRadius = 0.0f;
    Fire.BurnRate = 1.0f;
    
    switch (Type)
    {
        case EFireType::Campfire:
            Fire.MaxFuel = 100.0f;
            Fire.HeatOutput = 20.0f;
            Fire.LightRadius = 300.0f;
            Fire.BurnRate = 1.0f;
            Fire.bCanCook = true;
            break;
        case EFireType::Bonfire:
            Fire.MaxFuel = 200.0f;
            Fire.HeatOutput = 40.0f;
            Fire.LightRadius = 500.0f;
            Fire.BurnRate = 2.0f;
            Fire.bCanCook = true;
            break;
        case EFireType::Fireplace:
            Fire.MaxFuel = 150.0f;
            Fire.HeatOutput = 30.0f;
            Fire.LightRadius = 200.0f;
            Fire.BurnRate = 1.5f;
            Fire.bCanCook = false;
            break;
        case EFireType::Torch:
            Fire.MaxFuel = 50.0f;
            Fire.HeatOutput = 10.0f;
            Fire.LightRadius = 150.0f;
            Fire.BurnRate = 0.5f;
            Fire.bCanCook = false;
            break;
        case EFireType::Lantern:
            Fire.MaxFuel = 30.0f;
            Fire.HeatOutput = 5.0f;
            Fire.LightRadius = 100.0f;
            Fire.BurnRate = 0.3f;
            Fire.bCanCook = false;
            break;
        case EFireType::Brazier:
            Fire.MaxFuel = 80.0f;
            Fire.HeatOutput = 25.0f;
            Fire.LightRadius = 250.0f;
            Fire.BurnRate = 1.2f;
            Fire.bCanCook = true;
            break;
    }
    
    return Fire;
}

bool UFireSystem::LightFire(FCampfire& Fire, EFuelType Fuel)
{
    if (Fire.State != EFireState::Unlit && Fire.State != EFireState::Extinguished)
        return false;
    
    float FuelAmount = 0.0f;
    switch (Fuel)
    {
        case EFuelType::Wood: FuelAmount = 30.0f; break;
        case EFuelType::Coal: FuelAmount = 50.0f; break;
        case EFuelType::Charcoal: FuelAmount = 40.0f; break;
        case EFuelType::Oil: FuelAmount = 60.0f; break;
        case EFuelType::MagicFuel: FuelAmount = 100.0f; break;
    }
    
    Fire.FuelLevel = FuelAmount;
    Fire.State = EFireState::Lighting;
    return true;
}

void UFireSystem::UpdateFire(FCampfire& Fire, float DeltaTime)
{
    if (Fire.State == EFireState::Unlit || Fire.State == EFireState::Extinguished)
        return;
    
    Fire.FuelLevel -= Fire.BurnRate * DeltaTime;
    
    if (Fire.FuelLevel > Fire.MaxFuel * 0.7f)
        Fire.State = EFireState::Burning;
    else if (Fire.FuelLevel > Fire.MaxFuel * 0.3f)
        Fire.State = EFireState::Flickering;
    else if (Fire.FuelLevel > 0.0f)
        Fire.State = EFireState::Dying;
    else
    {
        Fire.State = EFireState::Extinguished;
        Fire.HeatOutput = 0.0f;
        Fire.LightRadius = 0.0f;
    }
}

bool UFireSystem::AddFuel(FCampfire& Fire, EFuelType Fuel, int32 Amount)
{
    if (Fire.State == EFireState::Unlit)
        return false;
    
    float FuelAmount = 0.0f;
    for (int32 i = 0; i < Amount; i++)
    {
        switch (Fuel)
        {
            case EFuelType::Wood: FuelAmount += 20.0f; break;
            case EFuelType::Coal: FuelAmount += 35.0f; break;
            case EFuelType::Charcoal: FuelAmount += 30.0f; break;
            case EFuelType::Oil: FuelAmount += 45.0f; break;
            case EFuelType::MagicFuel: FuelAmount += 80.0f; break;
        }
    }
    
    Fire.FuelLevel = FMath::Clamp(Fire.FuelLevel + FuelAmount, 0.0f, Fire.MaxFuel);
    return true;
}

void UFireSystem::ExtinguishFire(FCampfire& Fire)
{
    Fire.State = EFireState::Extinguished;
    Fire.FuelLevel = 0.0f;
    Fire.HeatOutput = 0.0f;
    Fire.LightRadius = 0.0f;
}

float UFireSystem::GetHeatOutput(FCampfire Fire)
{
    return Fire.HeatOutput;
}

float UFireSystem::GetLightRadius(FCampfire Fire)
{
    return Fire.LightRadius;
}

bool UFireSystem::IsFireBurning(FCampfire Fire)
{
    return Fire.State == EFireState::Burning || 
           Fire.State == EFireState::Flickering ||
           Fire.State == EFireState::Lighting;
}

FCookingPot UFireSystem::StartCooking(FCampfire& Fire, FName Recipe)
{
    if (!Fire.bCanCook || !IsFireBurning(Fire))
    {
        FCookingPot Empty;
        return Empty;
    }
    
    FCookingPot Pot;
    Pot.PotID = FName(*FString::Printf(TEXT("Pot_%d"), 0));
    Pot.CookingRecipe = Recipe;
    Pot.CookProgress = 0.0f;
    Pot.RequiredTime = 30.0f;
    Pot.bIsCooking = true;
    Pot.bIsDone = false;
    return Pot;
}

void UFireSystem::UpdateCooking(FCookingPot& Pot, float DeltaTime)
{
    if (!Pot.bIsCooking || Pot.bIsDone)
        return;
    
    Pot.CookProgress += DeltaTime;
    
    if (Pot.CookProgress >= Pot.RequiredTime)
    {
        Pot.bIsDone = true;
        Pot.bIsCooking = false;
    }
}

FName UFireSystem::CollectFood(FCookingPot& Pot)
{
    if (Pot.bIsDone)
    {
        FName Food = Pot.CookingRecipe;
        Pot.bIsDone = false;
        Pot.CookProgress = 0.0f;
        return Food;
    }
    return FName();
}

float UFireSystem::GetPlayerWarmth()
{
    return PlayerWarmth;
}

bool UFireSystem::IsNearFire(FVector PlayerLoc, FCampfire Fire, float Range)
{
    if (!IsFireBurning(Fire))
        return false;
    
    float Distance = Fire.LightRadius;
    return Distance <= Range;
}
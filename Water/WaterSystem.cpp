#include "WaterSystem.h"

static float PlayerWater = 100.0f;

FWaterSource UWaterSystem::CreateSource(EWaterSource Type, float Capacity)
{
    FWaterSource Source;
    Source.Type = Type;
    Source.MaxCapacity = Capacity;
    Source.WaterAmount = Capacity;
    Source.FillRate = 10.0f;
    Source.bIsActive = true;
    
    switch (Type)
    {
        case EWaterSource::Well:
            Source.Quality = EWaterQuality::Clean;
            break;
        case EWaterSource::RainCatcher:
            Source.Quality = EWaterQuality::Normal;
            break;
        case EWaterSource::River:
            Source.Quality = EWaterQuality::Dirty;
            Source.FillRate = 50.0f;
            break;
        case EWaterSource::Lake:
            Source.Quality = EWaterQuality::Normal;
            Source.FillRate = 30.0f;
            break;
        case EWaterSource::Spring:
            Source.Quality = EWaterQuality::Purified;
            break;
        case EWaterSource::Ocean:
            Source.Quality = EWaterQuality::Dirty;
            Source.FillRate = 100.0f;
            break;
    }
    return Source;
}

bool UWaterSystem::CollectWater(FWaterSource& Source, float Amount)
{
    if (Source.WaterAmount >= Amount)
    {
        Source.WaterAmount -= Amount;
        return true;
    }
    return false;
}

bool UWaterSystem::DepositWater(FWaterSource& Source, float Amount)
{
    if (Source.WaterAmount + Amount <= Source.MaxCapacity)
    {
        Source.WaterAmount += Amount;
        return true;
    }
    Source.WaterAmount = Source.MaxCapacity;
    return false;
}

float UWaterSystem::GetWaterLevel(FWaterSource Source)
{
    return Source.WaterAmount;
}

bool UWaterSystem::IsEmpty(FWaterSource Source)
{
    return Source.WaterAmount <= 0.0f;
}

FRainCollector UWaterSystem::CreateRainCollector(float Capacity)
{
    FRainCollector Collector;
    Collector.Capacity = Capacity;
    Collector.CurrentWater = 0.0f;
    Collector.CollectionRate = 10.0f;
    Collector.bIsCollecting = true;
    return Collector;
}

void UWaterSystem::UpdateRainCollector(FRainCollector& Collector, float RainAmount, float DeltaTime)
{
    if (Collector.bIsCollecting && RainAmount > 0.0f)
    {
        float Collected = RainAmount * Collector.CollectionRate * DeltaTime;
        Collector.CurrentWater = FMath::Clamp(Collector.CurrentWater + Collected, 0.0f, Collector.Capacity);
    }
}

float UWaterSystem::CollectFromRain(FRainCollector& Collector, float Amount)
{
    if (Collector.CurrentWater >= Amount)
    {
        Collector.CurrentWater -= Amount;
        return Amount;
    }
    float Collected = Collector.CurrentWater;
    Collector.CurrentWater = 0.0f;
    return Collected;
}

FWell UWaterSystem::CreateWell(float Capacity)
{
    FWell Well;
    Well.MaxWater = Capacity;
    Well.CurrentWater = Capacity;
    Well.ReplenishRate = 1.0f;
    Well.bHasPump = false;
    Well.bNeedsRepair = false;
    return Well;
}

void UWaterSystem::UpdateWell(FWell& Well, float DeltaTime)
{
    if (!Well.bNeedsRepair && Well.CurrentWater < Well.MaxWater)
    {
        Well.CurrentWater = FMath::Clamp(Well.CurrentWater + Well.ReplenishRate * DeltaTime, 0.0f, Well.MaxWater);
    }
}

float UWaterSystem::DrawFromWell(FWell& Well, float Amount)
{
    if (Well.CurrentWater >= Amount)
    {
        Well.CurrentWater -= Amount;
        return Amount;
    }
    float Drawn = Well.CurrentWater;
    Well.CurrentWater = 0.0f;
    return Drawn;
}

void UWaterSystem::RepairWell(FWell& Well)
{
    Well.bNeedsRepair = false;
    Well.ReplenishRate = 1.0f;
}

bool UWaterSystem::PurifyWater(EWaterQuality& Quality)
{
    if (Quality == EWaterQuality::Dirty)
    {
        Quality = EWaterQuality::Normal;
        return true;
    }
    if (Quality == EWaterQuality::Normal)
    {
        Quality = EWaterQuality::Clean;
        return true;
    }
    if (Quality == EWaterQuality::Clean)
    {
        Quality = EWaterQuality::Purified;
        return true;
    }
    return false;
}

bool UWaterSystem::DrinkWater(float Amount)
{
    if (PlayerWater >= Amount)
    {
        PlayerWater -= Amount;
        return true;
    }
    return false;
}

float UWaterSystem::GetPlayerWater()
{
    return PlayerWater;
}
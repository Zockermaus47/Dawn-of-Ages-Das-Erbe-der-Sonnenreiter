#include "WildlifeArea.h"

FName UWildlifeAreaSystem::CurrentShelter;
bool UWildlifeAreaSystem::bInsideShelter = false;
float UWildlifeAreaSystem::CurrentWarmth = 0.0f;

FShelterData UWildlifeAreaSystem::CreateShelter(EWildlifeShelter Type)
{
    FShelterData Data;
    Data.Type = Type;
    
    switch (Type)
    {
        case EWildlifeShelter::StrawHut:
            Data.DisplayName = FText::FromString("Stroh Hutte");
            Data.Capacity = 1;
            Data.Warmth = 20.0f;
            Data.bHasFire = false;
            break;
        case EWildlifeShelter::WoodenCabin:
            Data.DisplayName = FText::FromString("Holz Cabin");
            Data.Capacity = 2;
            Data.Warmth = 40.0f;
            Data.bHasFire = true;
            Data.StorageSlots = 5;
            Data.bHasStorage = true;
            break;
        case EWildlifeShelter::StoneHouse:
            Data.DisplayName = FText::FromString("Stein Haus");
            Data.Capacity = 4;
            Data.Warmth = 60.0f;
            Data.bHasFire = true;
            Data.StorageSlots = 10;
            Data.bHasStorage = true;
            break;
        case EWildlifeShelter::Cave:
            Data.DisplayName = FText::FromString("Hohle");
            Data.Capacity = 3;
            Data.Warmth = 30.0f;
            Data.bHasFire = false;
            break;
        case EWildlifeShelter::Tent:
            Data.DisplayName = FText::FromString("Zelt");
            Data.Capacity = 2;
            Data.Warmth = 15.0f;
            Data.bHasFire = false;
            break;
        case EWildlifeShelter::Treehouse:
            Data.DisplayName = FText::FromString("Baumhaus");
            Data.Capacity = 2;
            Data.Warmth = 35.0f;
            Data.bHasFire = false;
            Data.StorageSlots = 8;
            Data.bHasStorage = true;
            break;
    }
    
    return Data;
}

FCaveData UWildlifeAreaSystem::CreateCave(ECaveType Type, FVector Location)
{
    FCaveData Cave;
    Cave.Type = Type;
    Cave.Location = Location;
    
    switch (Type)
    {
        case ECaveType::SmallCave:
            Cave.Depth = 10;
            Cave.DangerLevel = 10.0f;
            Cave.OreSpawnChance = 0.3f;
            Cave.Ores = { EOreType::Stone, EOreType::Coal };
            break;
        case ECaveType::MediumCave:
            Cave.Depth = 25;
            Cave.DangerLevel = 30.0f;
            Cave.OreSpawnChance = 0.5f;
            Cave.Ores = { EOreType::Stone, EOreType::Coal, EOreType::IronOre, EOreType::CopperOre };
            break;
        case ECaveType::LargeCave:
            Cave.Depth = 50;
            Cave.DangerLevel = 50.0f;
            Cave.OreSpawnChance = 0.7f;
            Cave.Ores = { EOreType::IronOre, EOreType::CopperOre, EOreType::GoldOre, EOreType::SilverOre };
            break;
        case ECaveType::MineShaft:
            Cave.Depth = 100;
            Cave.DangerLevel = 70.0f;
            Cave.OreSpawnChance = 0.8f;
            Cave.Ores = { EOreType::GoldOre, EOreType::SilverOre, EOreType::Mithril };
            break;
        case ECaveType::HiddenCave:
            Cave.Depth = 30;
            Cave.DangerLevel = 40.0f;
            Cave.OreSpawnChance = 0.9f;
            Cave.Ores = { EOreType::GoldOre, EOreType::SilverOre, EOreType::Mithril, EOreType::Adamantite, EOreType::Gem };
            break;
    }
    
    return Cave;
}

FOreDeposit UWildlifeAreaSystem::CreateOreDeposit(EOreType Ore, int32 Quantity)
{
    FOreDeposit Deposit;
    Deposit.Ore = Ore;
    Deposit.Quantity = Quantity;
    Deposit.ReplenishTime = 3600.0f;
    Deposit.LastHarvested = 0.0f;
    Deposit.bIsDepleted = false;
    return Deposit;
}

bool UWildlifeAreaSystem::EnterShelter(FName ShelterID)
{
    if (!bInsideShelter)
    {
        CurrentShelter = ShelterID;
        bInsideShelter = true;
        CurrentWarmth = GetShelterWarmth();
        return true;
    }
    return false;
}

bool UWildlifeAreaSystem::ExitShelter()
{
    if (bInsideShelter)
    {
        bInsideShelter = false;
        CurrentShelter = FName();
        CurrentWarmth = 0.0f;
        return true;
    }
    return false;
}

bool UWildlifeAreaSystem::IsInsideShelter()
{
    return bInsideShelter;
}

float UWildlifeAreaSystem::GetShelterWarmth()
{
    return CurrentWarmth;
}

TArray<FOreDeposit> UWildlifeAreaSystem::GetOresInRadius(FVector Location, float Radius)
{
    return TArray<FOreDeposit>();
}

bool UWildlifeAreaSystem::HarvestOre(FOreDeposit& Deposit, int32& Amount)
{
    if (Deposit.bIsDepleted || Deposit.Quantity <= 0)
        return false;
    
    Amount = FMath::Min(Deposit.Quantity, 3);
    Deposit.Quantity -= Amount;
    Deposit.LastHarvested = 0.0f;
    
    if (Deposit.Quantity <= 0)
        Deposit.bIsDepleted = true;
    
    return true;
}

void UWildlifeAreaSystem::UpdateCave(FCaveData& Cave, float DeltaTime)
{
    if (Cave.OreSpawnChance > 0.0f && !Cave.bIsCleared)
    {
        Cave.OreSpawnChance += DeltaTime * 0.01f;
    }
}

bool UWildlifeAreaSystem::ExploreCave(FCaveData& Cave)
{
    if (!Cave.bIsDiscovered)
    {
        Cave.bIsDiscovered = true;
        return true;
    }
    return false;
}

int32 UWildlifeAreaSystem::GetCaveDanger(FCaveData Cave)
{
    return (int32)Cave.DangerLevel;
}

TArray<EOreType> UWildlifeAreaSystem::GetAvailableOres()
{
    TArray<EOreType> Ores;
    Ores.Add(EOreType::Stone);
    Ores.Add(EOreType::Coal);
    Ores.Add(EOreType::IronOre);
    Ores.Add(EOreType::CopperOre);
    Ores.Add(EOreType::GoldOre);
    Ores.Add(EOreType::SilverOre);
    Ores.Add(EOreType::Mithril);
    Ores.Add(EOreType::Adamantite);
    Ores.Add(EOreType::Gem);
    return Ores;
}
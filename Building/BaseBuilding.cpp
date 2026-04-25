#include "BaseBuilding.h"

TArray<FPlacedBuilding> Buildings;

FBuildingData UBaseBuildingSystem::GetBuildingData(FName BuildingID)
{
    return FBuildingData();
}

FPlacedBuilding UBaseBuildingSystem::PlaceBuilding(FBuildingData Data, FVector Location, FRotator Rotation)
{
    FPlacedBuilding Building;
    Building.BuildingInstanceID = FName(*FString::Printf(TEXT("Building_%d"), Buildings.Num()));
    Building.Data = Data;
    Building.Location = Location;
    Building.Rotation = Rotation;
    Building.State = EBuildingState::Blueprint;
    Building.BuildProgress = 0.0f;
    Building.CurrentHealth = Data.Health;
    Buildings.Add(Building);
    return Building;
}

bool UBaseBuildingSystem::StartConstruction(FName BuildingID)
{
    for (auto& Building : Buildings)
    {
        if (Building.BuildingInstanceID == BuildingID)
        {
            Building.State = EBuildingState::UnderConstruction;
            return true;
        }
    }
    return false;
}

void UBaseBuildingSystem::CompleteConstruction(FName BuildingID)
{
    for (auto& Building : Buildings)
    {
        if (Building.BuildingInstanceID == BuildingID)
        {
            Building.State = EBuildingState::Completed;
            Building.BuildProgress = 100.0f;
        }
    }
}

void UBaseBuildingSystem::DemolishBuilding(FName BuildingID)
{
    Buildings.RemoveAll([&](FPlacedBuilding B) { return B.BuildingInstanceID == BuildingID; });
}

void UBaseBuildingSystem::RepairBuilding(FName BuildingID, int32 WoodAmount, int32 StoneAmount)
{
    for (auto& Building : Buildings)
    {
        if (Building.BuildingInstanceID == BuildingID)
        {
            int32 RepairAmount = WoodAmount * 2 + StoneAmount * 2;
            Building.CurrentHealth = FMath::Clamp(Building.CurrentHealth + RepairAmount, 0, Building.Data.Health);
            if (Building.CurrentHealth > Building.Data.Health * 0.5f)
                Building.State = EBuildingState::Completed;
        }
    }
}

TArray<FPlacedBuilding> UBaseBuildingSystem::GetBuildingsInRadius(FVector Location, float Radius)
{
    TArray<FPlacedBuilding> Result;
    for (auto& Building : Buildings)
    {
        if (FVector::Distance(Building.Location, Location) <= Radius)
            Result.Add(Building);
    }
    return Result;
}

bool UBaseBuildingSystem::CanBuildAtLocation(FVector Location, EBuildingCategory Category)
{
    return true;
}

FFarmPlot UBaseBuildingSystem::CreateFarmPlot(FName BuildingID, EFarmCrop Crop)
{
    FFarmPlot Plot;
    Plot.PlotID = FName(*FString::Printf(TEXT("Plot_%d"), 0));
    Plot.Crop = Crop;
    Plot.GrowthProgress = 0.0f;
    Plot.WaterLevel = 50.0f;
    Plot.Fertilizer = 0.0f;
    Plot.bIsPlanted = false;
    return Plot;
}

void UBaseBuildingSystem::PlantCrop(FFarmPlot& Plot, EFarmCrop Crop)
{
    Plot.Crop = Crop;
    Plot.bIsPlanted = true;
    Plot.GrowthProgress = 0.0f;
    Plot.WaterLevel = 50.0f;
}

void UBaseBuildingSystem::HarvestCrop(FFarmPlot& Plot, int32& Amount)
{
    if (Plot.GrowthProgress >= 100.0f)
    {
        Amount = FMath::RandRange(1, 3);
        if (Plot.Fertilizer > 50.0f)
            Amount = FMath::Floor(Amount * 1.5f);
        Plot.bIsPlanted = false;
        Plot.GrowthProgress = 0.0f;
    }
}

void UBaseBuildingSystem::WaterCrop(FFarmPlot& Plot, float Amount)
{
    Plot.WaterLevel = FMath::Clamp(Plot.WaterLevel + Amount, 0.0f, 100.0f);
}

void UBaseBuildingSystem::FertilizeCrop(FFarmPlot& Plot, float Amount)
{
    Plot.Fertilizer = FMath::Clamp(Plot.Fertilizer + Amount, 0.0f, 100.0f);
}

void UBaseBuildingSystem::UpdateFarmPlot(FFarmPlot& Plot, float DeltaTime)
{
    if (!Plot.bIsPlanted) return;

    float GrowthRate = 5.0f;

    if (Plot.WaterLevel > 30.0f && Plot.WaterLevel < 80.0f)
        GrowthRate *= 1.5f;
    else if (Plot.WaterLevel < 10.0f || Plot.WaterLevel > 90.0f)
        GrowthRate *= 0.5f;

    if (Plot.Fertilizer > 50.0f)
        GrowthRate *= 1.3f;

    Plot.GrowthProgress += DeltaTime * GrowthRate;
    Plot.WaterLevel = FMath::Clamp(Plot.WaterLevel - DeltaTime * 0.5f, 0.0f, 100.0f);
}

bool UBaseBuildingSystem::IsReadyToHarvest(FFarmPlot Plot)
{
    return Plot.bIsPlanted && Plot.GrowthProgress >= 100.0f;
}

void UBaseBuildingSystem::AddWorker(FName BuildingID, FName WorkerID)
{
    for (auto& Building : Buildings)
    {
        if (Building.BuildingInstanceID == BuildingID)
        {
            if (Building.Workers.Num() < Building.Data.Workers)
                Building.Workers.Add(WorkerID);
        }
    }
}

void UBaseBuildingSystem::RemoveWorker(FName BuildingID, FName WorkerID)
{
    for (auto& Building : Buildings)
    {
        if (Building.BuildingInstanceID == BuildingID)
            Building.Workers.Remove(WorkerID);
    }
}

TArray<FName> UBaseBuildingSystem::GetWorkers(FName BuildingID)
{
    for (auto& Building : Buildings)
    {
        if (Building.BuildingInstanceID == BuildingID)
            return Building.Workers;
    }
    return TArray<FName>();
}

bool UBaseBuildingSystem::HasRoomForItem(FName BuildingID, FName ItemID)
{
    for (auto& Building : Buildings)
    {
        if (Building.BuildingInstanceID == BuildingID)
            return Building.Inventory.Num() < Building.Data.StorageSlots;
    }
    return false;
}

void UBaseBuildingSystem::AddItemToStorage(FName BuildingID, FName ItemID, int32 Quantity)
{
    for (auto& Building : Buildings)
    {
        if (Building.BuildingInstanceID == BuildingID)
        {
            if (Building.Inventory.Num() < Building.Data.StorageSlots)
                Building.Inventory.Add(ItemID);
        }
    }
}

TArray<FName> UBaseBuildingSystem::GetStorageItems(FName BuildingID)
{
    for (auto& Building : Buildings)
    {
        if (Building.BuildingInstanceID == BuildingID)
            return Building.Inventory;
    }
    return TArray<FName>();
}

float UBaseBuildingSystem::GetBuildingHealth(FName BuildingID)
{
    for (auto& Building : Buildings)
    {
        if (Building.BuildingInstanceID == BuildingID)
            return (float)Building.CurrentHealth / (float)Building.Data.Health;
    }
    return 0.0f;
}

EBuildingState UBaseBuildingSystem::GetBuildingState(FName BuildingID)
{
    for (auto& Building : Buildings)
    {
        if (Building.BuildingInstanceID == BuildingID)
            return Building.State;
    }
    return EBuildingState::Blueprint;
}

bool UBaseBuildingSystem::CanAffordMaterial(FBuildingData Data)
{
    return Data.WoodCost >= 0 && Data.StoneCost >= 0 && Data.MetalCost >= 0;
}

int32 UBaseBuildingSystem::GetTotalMaterialCost(FBuildingData Data)
{
    return Data.WoodCost + Data.StrawCost + Data.StoneCost + Data.BrickCost + Data.AdobeCost + Data.MetalCost;
}

float UBaseBuildingSystem::GetBuildingInsulation(FBuildingData Data)
{
    return Data.Insulation;
}

bool UBaseBuildingSystem::UpgradeMaterial(FName BuildingID, EBuildingMaterial NewMaterial)
{
    for (auto& Building : Buildings)
    {
        if (Building.BuildingInstanceID == BuildingID)
        {
            Building.Data.PrimaryMaterial = NewMaterial;
            Building.CurrentHealth = FMath::Min(Building.CurrentHealth + 50, Building.Data.MaxHealth);
            return true;
        }
    }
    return false;
}

TArray<FBuildingData> UBaseBuildingSystem::GetBuildingsByMaterial(EBuildingMaterial Material)
{
    TArray<FBuildingData> Result;
    return Result;
}
}

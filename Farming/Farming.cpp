#include "Farming.h"

UFarmingSystem::UFarmingSystem()
{
}

FCropData UFarmingSystem::GetCropData(FName CropID)
{
    return FCropData();
}

bool UFarmingSystem::CanPlant(FName CropID, const TMap<FName, int32>& Inventory)
{
    return false;
}

TMap<FName, int32> UFarmingSystem::Plant(FName CropID, const TMap<FName, int32>& Inventory)
{
    return TMap<FName, int32>();
}

bool UFarmingSystem::CanHarvest(FGardenPlot Plot)
{
    return false;
}

TMap<FName, int32> UFarmingSystem::Harvest(FGardenPlot Plot)
{
    return TMap<FName, int32>();
}

void UFarmingSystem::UpdateGrowth(FGardenPlot& Plot, float DeltaTime)
{
}

void UFarmingSystem::Water(FGardenPlot& Plot, float Amount)
{
}

void UFarmingSystem::Fertilize(FGardenPlot& Plot, float Amount)
{
}

TArray<FCropData> UFarmingSystem::GetCropsBySeason(ESeason Season)
{
    return TArray<FCropData>();
}

TArray<FCropData> UFarmingSystem::GetAllCrops()
{
    return TArray<FCropData>();
}
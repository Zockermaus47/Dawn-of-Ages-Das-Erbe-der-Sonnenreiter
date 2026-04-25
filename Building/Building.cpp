#include "Building.h"

UBuildingSystem::UBuildingSystem()
{
}

FBuildingData UBuildingSystem::GetBuildingData(FName BuildingID)
{
    return FBuildingData();
}

bool UBuildingSystem::CanBuild(FName BuildingID, const TMap<FName, int32>& Resources)
{
    return false;
}

TArray<FBuildingData> UBuildingSystem::GetAllBuildings()
{
    return TArray<FBuildingData>();
}
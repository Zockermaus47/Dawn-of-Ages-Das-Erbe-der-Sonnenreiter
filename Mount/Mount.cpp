#include "Mount.h"

UMountSystem::UMountSystem()
{
}

FMountData UMountSystem::GetMountData(FName MountID)
{
    return FMountData();
}

bool UMountSystem::CanTame(FMountData Mount, const TMap<FName, int32>& Inventory)
{
    return false;
}

FMountData UMountSystem::Tame(FMountData Mount, const TMap<FName, int32>& Inventory)
{
    return FMountData();
}

TArray<FMountData> UMountSystem::GetMountsByType(EMountType Type)
{
    return TArray<FMountData>();
}

TArray<FMountData> UMountSystem::GetAllMounts()
{
    return TArray<FMountData>();
}
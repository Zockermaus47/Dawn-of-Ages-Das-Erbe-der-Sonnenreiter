#include "Siege.h"

USiegeWarfareSystem::USiegeWarfareSystem()
{
}

FSiegeWeaponData USiegeWarfareSystem::GetWeaponData(FName WeaponID)
{
    return FSiegeWeaponData();
}

void USiegeWarfareSystem::Fire(FSiegeWeaponData Weapon, FVector TargetLocation)
{
}

TArray<FSiegeWeaponData> USiegeWarfareSystem::GetAllWeapons()
{
    return TArray<FSiegeWeaponData>();
}
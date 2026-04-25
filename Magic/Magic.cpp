#include "Magic.h"

UMagicSystem::UMagicSystem()
{
}

FSpellData UMagicSystem::GetSpellData(FName SpellID)
{
    return FSpellData();
}

TArray<FSpellData> UMagicSystem::GetSpellsBySchool(EMagicSchool School)
{
    return TArray<FSpellData>();
}

TArray<FSpellData> UMagicSystem::GetAllSpells()
{
    return TArray<FSpellData>();
}
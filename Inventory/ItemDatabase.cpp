#include "ItemDatabase.h"

UItemDatabase::UItemDatabase()
{
}

FItemData UItemDatabase::GetItemData(FName ItemID)
{
    return FItemData();
}

TArray<FItemData> UItemDatabase::GetItemsByType(EItemType Type)
{
    return TArray<FItemData>();
}

TArray<FItemData> UItemDatabase::GetItemsByEra(EItemEra Era)
{
    return TArray<FItemData>();
}

TArray<FItemData> UItemDatabase::GetItemsByRarity(EItemRarity Rarity)
{
    return TArray<FItemData>();
}

TArray<FItemData> UItemDatabase::GetAllItems()
{
    return TArray<FItemData>();
}

bool UItemDatabase::IsValidItem(FName ItemID)
{
    return false;
}

int32 UItemDatabase::GetItemValue(FName ItemID)
{
    return 1;
}

float UItemDatabase::GetItemWeight(FName ItemID)
{
    return 1.0f;
}

EItemRarity UItemDatabase::CalculateRarity(float Roll)
{
    if (Roll > 99.0f) return EItemRarity::Legendary;
    if (Roll > 95.0f) return EItemRarity::Epic;
    if (Roll > 85.0f) return EItemRarity::Rare;
    if (Roll > 70.0f) return EItemRarity::Uncommon;
    return EItemRarity::Common;
}
#include "ItemData.h"

FItemInfo UItemDataAsset::GetItemInfo(FName ItemID) const
{
    if (AllItems.Contains(ItemID))
    {
        return AllItems[ItemID];
    }
    return FItemInfo();
}

bool UItemDataAsset::HasItem(FName ItemID) const
{
    return AllItems.Contains(ItemID);
}

TArray<FName> UItemDataAsset::GetAllItemIDs() const
{
    TArray<FName> Keys;
    AllItems.GetKeys(Keys);
    return Keys;
}
#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    Items.SetNum(MaxSlots);
}

bool UInventoryComponent::AddItem(FString ItemName, UTexture2D* ItemIcon, int32 ItemAmount)
{
    int32 RemainingAmount = ItemAmount;

    int32 ExistingSlot = FindItemSlot(ItemName);
    if (ExistingSlot != -1)
    {
        int32 CanAdd = MaxSlots - Items[ExistingSlot].Amount;
        int32 ToAdd = FMath::Min(CanAdd, RemainingAmount);
        Items[ExistingSlot].Amount += ToAdd;
        RemainingAmount -= ToAdd;
    }

    while (RemainingAmount > 0)
    {
        int32 EmptySlot = FindEmptySlot();
        if (EmptySlot == -1) return false;

        int32 ToAdd = FMath::Min(Items[EmptySlot].MaxStack, RemainingAmount);
        Items[EmptySlot].Name = ItemName;
        Items[EmptySlot].Icon = ItemIcon;
        Items[EmptySlot].Amount = ToAdd;
        RemainingAmount -= ToAdd;
    }
    return true;
}

bool UInventoryComponent::RemoveItem(int32 SlotIndex, int32 Amount)
{
    if (SlotIndex < 0 || SlotIndex >= MaxSlots) return false;
    if (Items[SlotIndex].Amount < Amount) return false;

    Items[SlotIndex].Amount -= Amount;
    if (Items[SlotIndex].Amount <= 0)
    {
        Items[SlotIndex].Name = "";
        Items[SlotIndex].Icon = nullptr;
    }
    return true;
}

void UInventoryComponent::UseItem(int32 SlotIndex)
{
    if (SlotIndex < 0 || SlotIndex >= MaxSlots) return;
    if (Items[SlotIndex].Amount > 0)
    {
        RemoveItem(SlotIndex, 1);
    }
}

FItemData UInventoryComponent::GetItemAt(int32 Index) const
{
    if (Index >= 0 && Index < MaxSlots)
    {
        return Items[Index];
    }
    return FItemData();
}

int32 UInventoryComponent::FindEmptySlot() const
{
    for (int32 i = 0; i < MaxSlots; i++)
    {
        if (Items[i].Amount <= 0) return i;
    }
    return -1;
}

int32 UInventoryComponent::FindItemSlot(FString ItemName) const
{
    for (int32 i = 0; i < MaxSlots; i++)
    {
        if (Items[i].Name == ItemName && Items[i].Amount < Items[i].MaxStack)
        {
            return i;
        }
    }
    return -1;
}
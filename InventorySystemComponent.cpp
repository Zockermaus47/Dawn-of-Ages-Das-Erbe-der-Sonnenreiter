#include "InventorySystemComponent.h"

UInventorySystemComponent::UInventorySystemComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    Slots.SetNum(MaxSlots);
}

void UInventorySystemComponent::BeginPlay()
{
    Super::BeginPlay();
    Slots.SetNum(MaxSlots);
    for (int32 i = 0; i < MaxSlots; i++)
    {
        Slots[i] = FInventorySlot();
    }
}

int32 UInventorySystemComponent::FindItemSlot(FName ItemID) const
{
    for (int32 i = 0; i < Slots.Num(); i++)
    {
        if (Slots[i].ItemID == ItemID)
        {
            return i;
        }
    }
    return -1;
}

int32 UInventorySystemComponent::FindEmptySlot() const
{
    for (int32 i = 0; i < Slots.Num(); i++)
    {
        if (Slots[i].IsEmpty())
        {
            return i;
        }
    }
    return -1;
}

int32 UInventorySystemComponent::FindStackableSlot(FName ItemID, int32 MaxStack) const
{
    for (int32 i = 0; i < Slots.Num(); i++)
    {
        if (Slots[i].ItemID == ItemID && Slots[i].Quantity < MaxStack)
        {
            return i;
        }
    }
    return -1;
}

bool UInventorySystemComponent::CanAddItem(FName ItemID, int32 Quantity) const
{
    FItemInfo ItemInfo;
    if (ItemDatabase)
    {
        ItemInfo = ItemDatabase->GetItemInfo(ItemID);
    }
    
    if (bUseWeightLimit)
    {
        float TotalWeight = ItemInfo.Weight * Quantity;
        if (CurrentWeight + TotalWeight > MaxWeight)
        {
            return false;
        }
    }
    return true;
}

bool UInventorySystemComponent::AddItem(FName ItemID, int32 Quantity)
{
    if (!CanAddItem(ItemID, Quantity))
    {
        OnInventoryFull.Broadcast(ItemID);
        return false;
    }

    FItemInfo ItemInfo;
    if (ItemDatabase)
    {
        ItemInfo = ItemDatabase->GetItemInfo(ItemID);
    }

    int32 Remaining = Quantity;
    int32 StackSlot = FindStackableSlot(ItemID, ItemInfo.MaxStackSize);
    
    while (Remaining > 0 && StackSlot != -1)
    {
        int32 CanAdd = ItemInfo.MaxStackSize - Slots[StackSlot].Quantity;
        int32 ToAdd = FMath::Min(CanAdd, Remaining);
        
        Slots[StackSlot].Quantity += ToAdd;
        Remaining -= ToAdd;
        
        if (bUseWeightLimit)
        {
            CurrentWeight += ItemInfo.Weight * ToAdd;
        }
        
        OnInventoryUpdated.Broadcast(StackSlot, Slots[StackSlot]);
        StackSlot = FindStackableSlot(ItemID, ItemInfo.MaxStackSize);
    }

    while (Remaining > 0)
    {
        int32 EmptySlot = FindEmptySlot();
        if (EmptySlot == -1)
        {
            OnInventoryFull.Broadcast(ItemID);
            return Quantity - Remaining > 0;
        }

        int32 ToAdd = FMath::Min(ItemInfo.MaxStackSize, Remaining);
        Slots[EmptySlot].ItemID = ItemID;
        Slots[EmptySlot].Quantity = ToAdd;
        Remaining -= ToAdd;
        
        if (bUseWeightLimit)
        {
            CurrentWeight += ItemInfo.Weight * ToAdd;
        }
        
        OnInventoryUpdated.Broadcast(EmptySlot, Slots[EmptySlot]);
    }

    OnItemAdded.Broadcast(ItemID);
    return true;
}

bool UInventorySystemComponent::RemoveItem(FName ItemID, int32 Quantity)
{
    int32 ToRemove = Quantity;
    
    for (int32 i = 0; i < Slots.Num() && ToRemove > 0; i++)
    {
        if (Slots[i].ItemID == ItemID)
        {
            FItemInfo ItemInfo;
            if (ItemDatabase)
            {
                ItemInfo = ItemDatabase->GetItemInfo(ItemID);
            }
            
            int32 RemoveFromSlot = FMath::Min(Slots[i].Quantity, ToRemove);
            Slots[i].Quantity -= RemoveFromSlot;
            ToRemove -= RemoveFromSlot;
            
            if (bUseWeightLimit)
            {
                CurrentWeight -= ItemInfo.Weight * RemoveFromSlot;
            }
            
            if (Slots[i].Quantity <= 0)
            {
                Slots[i].ItemID = NAME_None;
            }
            
            OnInventoryUpdated.Broadcast(i, Slots[i]);
        }
    }

    if (ToRemove > 0)
    {
        return false;
    }

    OnItemRemoved.Broadcast(ItemID);
    return true;
}

bool UInventorySystemComponent::UseItem(int32 SlotIndex)
{
    if (SlotIndex < 0 || SlotIndex >= Slots.Num())
    {
        return false;
    }

    if (Slots[SlotIndex].IsEmpty())
    {
        return false;
    }

    FName ItemID = Slots[SlotIndex].ItemID;
    RemoveItem(ItemID, 1);
    return true;
}

bool UInventorySystemComponent::SwapSlots(int32 IndexA, int32 IndexB)
{
    if (IndexA < 0 || IndexA >= Slots.Num() || IndexB < 0 || IndexB >= Slots.Num())
    {
        return false;
    }

    FInventorySlot Temp = Slots[IndexA];
    Slots[IndexA] = Slots[IndexB];
    Slots[IndexB] = Temp;

    OnInventoryUpdated.Broadcast(IndexA, Slots[IndexA]);
    OnInventoryUpdated.Broadcast(IndexB, Slots[IndexB]);
    return true;
}

bool UInventorySystemComponent::SplitStack(int32 SourceIndex, int32 TargetIndex, int32 Amount)
{
    if (SourceIndex < 0 || SourceIndex >= Slots.Num() || TargetIndex < 0 || TargetIndex >= Slots.Num())
    {
        return false;
    }

    if (!Slots[TargetIndex].IsEmpty())
    {
        return false;
    }

    if (Slots[SourceIndex].Quantity < Amount)
    {
        return false;
    }

    Slots[TargetIndex].ItemID = Slots[SourceIndex].ItemID;
    Slots[TargetIndex].Quantity = Amount;
    Slots[SourceIndex].Quantity -= Amount;

    if (Slots[SourceIndex].Quantity <= 0)
    {
        Slots[SourceIndex].ItemID = NAME_None;
    }

    OnInventoryUpdated.Broadcast(SourceIndex, Slots[SourceIndex]);
    OnInventoryUpdated.Broadcast(TargetIndex, Slots[TargetIndex]);
    return true;
}

FInventorySlot UInventorySystemComponent::GetSlot(int32 Index) const
{
    if (Index >= 0 && Index < Slots.Num())
    {
        return Slots[Index];
    }
    return FInventorySlot();
}

bool UInventorySystemComponent::IsSlotEmpty(int32 Index) const
{
    if (Index >= 0 && Index < Slots.Num())
    {
        return Slots[Index].IsEmpty();
    }
    return true;
}

void UInventorySystemComponent::ClearInventory()
{
    for (int32 i = 0; i < Slots.Num(); i++)
    {
        Slots[i] = FInventorySlot();
        OnInventoryUpdated.Broadcast(i, Slots[i]);
    }
    CurrentWeight = 0.0f;
}

int32 UInventorySystemComponent::CountItem(FName ItemID) const
{
    int32 Count = 0;
    for (const FInventorySlot& Slot : Slots)
    {
        if (Slot.ItemID == ItemID)
        {
            Count += Slot.Quantity;
        }
    }
    return Count;
}
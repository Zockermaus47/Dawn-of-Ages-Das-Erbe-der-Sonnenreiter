#include "Inventory/InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    NumSlots = 20;
    MaxWeight = 50.0f;
    CurrentWeight = 0.0f;
    GoldAmount = 0;

    InitializeSlots();
}

void UInventoryComponent::InitializeSlots()
{
    InventorySlots.SetNum(NumSlots);
    for (int32 i = 0; i < NumSlots; i++)
    {
        InventorySlots[i].bIsEmpty = true;
        InventorySlots[i].SlotType = EInventorySlotType::Any;
    }

    EquipmentSlots.SetNum(14);
    EquipmentSlots[0].SlotType = EInventorySlotType::Head;
    EquipmentSlots[1].SlotType = EInventorySlotType::Chest;
    EquipmentSlots[2].SlotType = EInventorySlotType::Legs;
    EquipmentSlots[3].SlotType = EInventorySlotType::Feet;
    EquipmentSlots[4].SlotType = EInventorySlotType::Hands;
    EquipmentSlots[5].SlotType = EInventorySlotType::Back;
    EquipmentSlots[6].SlotType = EInventorySlotType::PrimaryWeapon;
    EquipmentSlots[7].SlotType = EInventorySlotType::SecondaryWeapon;
    EquipmentSlots[8].SlotType = EInventorySlotType::Belt;
    EquipmentSlots[9].SlotType = EInventorySlotType::Neck;
    EquipmentSlots[10].SlotType = EInventorySlotType::Ring1;
    EquipmentSlots[11].SlotType = EInventorySlotType::Ring2;
    EquipmentSlots[12].SlotType = EInventorySlotType::Quiver;
    EquipmentSlots[13].SlotType = EInventorySlotType::Pouch;
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
    CurrentWeight = CalculateTotalWeight();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UInventoryComponent::CalculateTotalWeight() const
{
    float Total = 0.0f;
    for (const FInventorySlot& Slot : InventorySlots)
    {
        Total += GetSlotWeight(Slot);
    }
    for (const FInventorySlot& Slot : EquipmentSlots)
    {
        Total += GetSlotWeight(Slot);
    }
    return Total;
}

float UInventoryComponent::GetSlotWeight(const FInventorySlot& Slot) const
{
    if (Slot.bIsEmpty) return 0.0f;
    return Slot.Weight * Slot.Quantity;
}

FInventorySlot UInventoryComponent::CreateItemFromID(FName ItemID)
{
    FInventorySlot NewItem;
    NewItem.ItemID = ItemID;
    NewItem.ItemName = ItemID;
    NewItem.bIsEmpty = false;
    NewItem.Quantity = 1;
    return NewItem;
}

bool UInventoryComponent::AddItem(FName ItemID, int32 Quantity)
{
    if (!CanCarry(1.0f * Quantity)) return false;

    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        if (!InventorySlots[i].bIsEmpty && 
            InventorySlots[i].ItemID == ItemID && 
            InventorySlots[i].Quantity < InventorySlots[i].MaxStackSize)
        {
            int32 Space = InventorySlots[i].MaxStackSize - InventorySlots[i].Quantity;
            int32 ToAdd = FMath::Min(Quantity, Space);
            InventorySlots[i].Quantity += ToAdd;
            Quantity -= ToAdd;

            if (Quantity <= 0)
            {
                CurrentWeight = CalculateTotalWeight();
                return true;
            }
        }
    }

    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        if (InventorySlots[i].bIsEmpty)
        {
            FInventorySlot NewItem = CreateItemFromID(ItemID);
            NewItem.Quantity = FMath::Min(Quantity, NewItem.MaxStackSize);
            InventorySlots[i] = NewItem;
            Quantity -= NewItem.Quantity;

            if (Quantity <= 0)
            {
                CurrentWeight = CalculateTotalWeight();
                return true;
            }
        }
    }

    CurrentWeight = CalculateTotalWeight();
    return Quantity <= 0;
}

bool UInventoryComponent::RemoveItem(FName ItemID, int32 Quantity)
{
    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        if (!InventorySlots[i].bIsEmpty && InventorySlots[i].ItemID == ItemID)
        {
            if (InventorySlots[i].Quantity <= Quantity)
            {
                Quantity -= InventorySlots[i].Quantity;
                InventorySlots[i].bIsEmpty = true;
                InventorySlots[i].Quantity = 0;
                InventorySlots[i].ItemID = NAME_None;
            }
            else
            {
                InventorySlots[i].Quantity -= Quantity;
                Quantity = 0;
            }

            if (Quantity <= 0)
            {
                CurrentWeight = CalculateTotalWeight();
                return true;
            }
        }
    }

    CurrentWeight = CalculateTotalWeight();
    return Quantity <= 0;
}

bool UInventoryComponent::EquipItem(int32 SlotIndex)
{
    if (SlotIndex < 0 || SlotIndex >= InventorySlots.Num()) return false;
    if (InventorySlots[SlotIndex].bIsEmpty) return false;
    if (InventorySlots[SlotIndex].ItemType != EItemType::Weapon && 
        InventorySlots[SlotIndex].ItemType != EItemType::Armor) return false;

    EInventorySlotType TargetSlot = EInventorySlotType::Any;
    switch (InventorySlots[SlotIndex].ItemType)
    {
        case EItemType::Weapon:
            TargetSlot = EInventorySlotType::PrimaryWeapon;
            break;
        case EItemType::Armor:
            TargetSlot = EInventorySlotType::Chest;
            break;
        default:
            break;
    }

    for (int32 i = 0; i < EquipmentSlots.Num(); i++)
    {
        if (EquipmentSlots[i].SlotType == TargetSlot)
        {
            FInventorySlot Temp = EquipmentSlots[i];
            EquipmentSlots[i] = InventorySlots[SlotIndex];
            InventorySlots[SlotIndex] = Temp;
            CurrentWeight = CalculateTotalWeight();
            return true;
        }
    }

    return false;
}

bool UInventoryComponent::UnequipItem(EInventorySlotType SlotType)
{
    for (int32 i = 0; i < EquipmentSlots.Num(); i++)
    {
        if (EquipmentSlots[i].SlotType == SlotType && !EquipmentSlots[i].bIsEmpty)
        {
            return AddItem(EquipmentSlots[i].ItemID, EquipmentSlots[i].Quantity);
        }
    }
    return false;
}

bool UInventoryComponent::SwapSlots(int32 FromSlot, int32 ToSlot)
{
    if (FromSlot < 0 || FromSlot >= InventorySlots.Num()) return false;
    if (ToSlot < 0 || ToSlot >= InventorySlots.Num()) return false;

    FInventorySlot Temp = InventorySlots[FromSlot];
    InventorySlots[FromSlot] = InventorySlots[ToSlot];
    InventorySlots[ToSlot] = Temp;

    CurrentWeight = CalculateTotalWeight();
    return true;
}

bool UInventoryComponent::UseItem(int32 SlotIndex)
{
    if (SlotIndex < 0 || SlotIndex >= InventorySlots.Num()) return false;
    if (InventorySlots[SlotIndex].bIsEmpty) return false;

    FInventorySlot& Item = InventorySlots[SlotIndex];

    if (Item.ItemType == EItemType::Consumable)
    {
        RemoveItem(Item.ItemID, 1);
        return true;
    }

    return false;
}

bool UInventoryComponent::DropItem(int32 SlotIndex, int32 Quantity)
{
    if (SlotIndex < 0 || SlotIndex >= InventorySlots.Num()) return false;
    if (InventorySlots[SlotIndex].bIsEmpty) return false;

    RemoveItem(InventorySlots[SlotIndex].ItemID, Quantity);
    return true;
}

bool UInventoryComponent::HasItem(FName ItemID, int32 Quantity) const
{
    return GetItemCount(ItemID) >= Quantity;
}

int32 UInventoryComponent::GetItemCount(FName ItemID) const
{
    int32 Count = 0;
    for (const FInventorySlot& Slot : InventorySlots)
    {
        if (!Slot.bIsEmpty && Slot.ItemID == ItemID)
        {
            Count += Slot.Quantity;
        }
    }
    return Count;
}

int32 UInventoryComponent::GetFirstEmptySlot() const
{
    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        if (InventorySlots[i].bIsEmpty) return i;
    }
    return -1;
}

int32 UInventoryComponent::GetSlotWithItem(FName ItemID) const
{
    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        if (!InventorySlots[i].bIsEmpty && InventorySlots[i].ItemID == ItemID) return i;
    }
    return -1;
}

float UInventoryComponent::GetWeightPercent() const
{
    return MaxWeight > 0.0f ? (CurrentWeight / MaxWeight) * 100.0f : 0.0f;
}

bool UInventoryComponent::CanCarry(float AdditionalWeight) const
{
    return (CurrentWeight + AdditionalWeight) <= MaxWeight;
}

void UInventoryComponent::AddGold(int32 Amount)
{
    GoldAmount += Amount;
    UE_LOG(LogTemp, Log, TEXT("Gold added: %d"), Amount);
}

bool UInventoryComponent::SpendGold(int32 Amount)
{
    if (GoldAmount < Amount) return false;
    GoldAmount -= Amount;
    return true;
}

void UInventoryComponent::ClearInventory()
{
    for (int32 i = 0; i < InventorySlots.Num(); i++)
    {
        InventorySlots[i].bIsEmpty = true;
        InventorySlots[i].Quantity = 0;
    }
    CurrentWeight = 0.0f;
}

void UInventoryComponent::SetItem(int32 SlotIndex, FInventorySlot Item)
{
    if (SlotIndex >= 0 && SlotIndex < InventorySlots.Num())
    {
        InventorySlots[SlotIndex] = Item;
        CurrentWeight = CalculateTotalWeight();
    }
}
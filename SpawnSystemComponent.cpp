#include "SpawnSystemComponent.h"
#include "InventorySystemComponent.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"

USpawnSystemComponent::USpawnSystemComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USpawnSystemComponent::BeginPlay()
{
    Super::BeginPlay();

    for (FSpawnTable& Table : SpawnTables)
    {
        Table.TotalWeight = CalculateTotalWeight(Table);
    }
}

int32 USpawnSystemComponent::CalculateTotalWeight(const FSpawnTable& Table) const
{
    int32 Total = 0;
    for (const FSpawnEntry& Entry : Table.Entries)
    {
        Total += FMath::RoundToInt(Entry.SpawnChance * GlobalSpawnMultiplier);
    }
    return Total;
}

FName USpawnSystemComponent::SelectWeightedItem(const FSpawnTable& Table) const
{
    if (Table.TotalWeight <= 0 || Table.Entries.Num() == 0)
    {
        return NAME_None;
    }

    int32 Roll = FMath::RandRange(0, Table.TotalWeight - 1);
    int32 CurrentWeight = 0;

    for (const FSpawnEntry& Entry : Table.Entries)
    {
        CurrentWeight += FMath::RoundToInt(Entry.SpawnChance * GlobalSpawnMultiplier);
        if (Roll < CurrentWeight)
        {
            return Entry.ItemID;
        }
    }

    return Table.Entries.Last().ItemID;
}

FName USpawnSystemComponent::RollSpawn() const
{
    if (SpawnTables.Num() == 0)
    {
        return NAME_None;
    }

    int32 TableIndex = FMath::RandRange(0, SpawnTables.Num() - 1);
    return SelectWeightedItem(SpawnTables[TableIndex]);
}

TArray<FName> USpawnSystemComponent::RollMultipleSpawns(int32 Count) const
{
    TArray<FName> Results;
    
    for (int32 i = 0; i < Count; i++)
    {
        FName Item = RollSpawn();
        if (Item != NAME_None)
        {
            Results.Add(Item);
        }
    }
    
    return Results;
}

void USpawnSystemComponent::AddSpawnTable(const FSpawnTable& Table)
{
    for (int32 i = 0; i < SpawnTables.Num(); i++)
    {
        if (SpawnTables[i].TableID == Table.TableID)
        {
            SpawnTables[i] = Table;
            SpawnTables[i].TotalWeight = CalculateTotalWeight(Table);
            return;
        }
    }
    SpawnTables.Add(Table);
}

void USpawnSystemComponent::RemoveSpawnTable(FName TableID)
{
    SpawnTables.RemoveAll([TableID](const FSpawnTable& Table) {
        return Table.TableID == TableID;
    });
}

FSpawnTable USpawnSystemComponent::GetSpawnTable(FName TableID) const
{
    for (const FSpawnTable& Table : SpawnTables)
    {
        if (Table.TableID == TableID)
        {
            return Table;
        }
    }
    return FSpawnTable();
}

TArray<FName> USpawnSystemComponent::GetAllSpawnTableIDs() const
{
    TArray<FName> IDs;
    for (const FSpawnTable& Table : SpawnTables)
    {
        IDs.Add(Table.TableID);
    }
    return IDs;
}

void USpawnSystemComponent::SpawnItemAtLocation(FName ItemID, int32 Quantity, FVector Location)
{
}

void USpawnSystemComponent::SpawnRandomItemInRadius(FName TableID, FVector Center, float Radius)
{
}

FInventorySlot USpawnSystemComponent::GenerateRandomItem(FName TableID) const
{
    FSpawnTable Table = GetSpawnTable(TableID);
    FName ItemID = SelectWeightedItem(Table);
    
    FInventorySlot Slot;
    Slot.ItemID = ItemID;
    
    if (ItemID != NAME_None)
    {
        for (const FSpawnEntry& Entry : Table.Entries)
        {
            if (Entry.ItemID == ItemID)
            {
                Slot.Quantity = FMath::RandRange(Entry.MinQuantity, Entry.MaxQuantity);
                break;
            }
        }
    }
    
    return Slot;
}
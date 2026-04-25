#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "SpawnSystemComponent.generated.h"

USTRUCT(BlueprintType)
struct FSpawnEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnChance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinQuantity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxQuantity = 1;

    FSpawnEntry()
    {
        ItemID = NAME_None;
        SpawnChance = 0.0f;
        MinQuantity = 1;
        MaxQuantity = 1;
    }
};

USTRUCT(BlueprintType)
struct FSpawnTable
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName TableID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FSpawnEntry> Entries;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalWeight = 0;

    FSpawnTable()
    {
        TableID = NAME_None;
        TotalWeight = 0;
    }
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_SPIEL_API USpawnSystemComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USpawnSystemComponent();

    UFUNCTION(BlueprintCallable)
    FName RollSpawn() const;

    UFUNCTION(BlueprintCallable)
    TArray<FName> RollMultipleSpawns(int32 Count) const;

    UFUNCTION(BlueprintCallable)
    void AddSpawnTable(const FSpawnTable& Table);

    UFUNCTION(BlueprintCallable)
    void RemoveSpawnTable(FName TableID);

    UFUNCTION(BlueprintCallable)
    FSpawnTable GetSpawnTable(FName TableID) const;

    UFUNCTION(BlueprintPure)
    TArray<FName> GetAllSpawnTableIDs() const;

    UFUNCTION(BlueprintCallable)
    void SpawnItemAtLocation(FName ItemID, int32 Quantity, FVector Location);

    UFUNCTION(BlueprintCallable)
    void SpawnRandomItemInRadius(FName TableID, FVector Center, float Radius);

    UFUNCTION(BlueprintCallable)
    FInventorySlot GenerateRandomItem(FName TableID) const;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Tables")
    TArray<FSpawnTable> SpawnTables;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
    float GlobalSpawnMultiplier = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
    bool bUseWeightedSpawning = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Settings")
    bool bCanSpawnSameItemMultipleTimes = true;

protected:
    virtual void BeginPlay() override;

private:
    int32 CalculateTotalWeight(const FSpawnTable& Table) const;
    FName SelectWeightedItem(const FSpawnTable& Table) const;
};
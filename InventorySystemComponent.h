#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemData.h"
#include "InventorySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryUpdated, int32, SlotIndex, FInventorySlot, SlotData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded, FName, ItemID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, FName, ItemID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryFull, FName, ItemID);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_SPIEL_API UInventorySystemComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventorySystemComponent();

    UFUNCTION(BlueprintCallable)
    bool AddItem(FName ItemID, int32 Quantity = 1);

    UFUNCTION(BlueprintCallable)
    bool RemoveItem(FName ItemID, int32 Quantity = 1);

    UFUNCTION(BlueprintCallable)
    bool UseItem(int32 SlotIndex);

    UFUNCTION(BlueprintCallable)
    bool SwapSlots(int32 IndexA, int32 IndexB);

    UFUNCTION(BlueprintCallable)
    bool SplitStack(int32 SourceIndex, int32 TargetIndex, int32 Amount);

    UFUNCTION(BlueprintCallable)
    FInventorySlot GetSlot(int32 Index) const;

    UFUNCTION(BlueprintCallable)
    int32 GetSlotCount() const { return Slots.Num(); }

    UFUNCTION(BlueprintCallable)
    bool IsSlotEmpty(int32 Index) const;

    UFUNCTION(BlueprintCallable)
    void ClearInventory();

    UFUNCTION(BlueprintCallable)
    int32 CountItem(FName ItemID) const;

    UFUNCTION(BlueprintCallable)
    TArray<FInventorySlot> GetAllItems() const { return Slots; }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 MaxSlots = 20;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    float MaxWeight = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (EditCondition = "bUseWeightLimit"))
    float CurrentWeight = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    bool bUseWeightLimit = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
    UItemDataAsset* ItemDatabase;

    UPROPERTY(BlueprintAssignable)
    FOnInventoryUpdated OnInventoryUpdated;

    UPROPERTY(BlueprintAssignable)
    FOnItemAdded OnItemAdded;

    UPROPERTY(BlueprintAssignable)
    FOnItemRemoved OnItemRemoved;

    UPROPERTY(BlueprintAssignable)
    FOnInventoryFull OnInventoryFull;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TArray<FInventorySlot> Slots;

    int32 FindItemSlot(FName ItemID) const;
    int32 FindEmptySlot() const;
    int32 FindStackableSlot(FName ItemID, int32 MaxStack) const;
    bool CanAddItem(FName ItemID, int32 Quantity) const;
};
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Amount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStack;

    FItemData()
    {
        Name = "";
        Icon = nullptr;
        Amount = 0;
        MaxStack = 99;
    }
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_SPIEL_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventoryComponent();

    UFUNCTION(BlueprintCallable)
    bool AddItem(FString ItemName, UTexture2D* ItemIcon, int32 ItemAmount);

    UFUNCTION(BlueprintCallable)
    bool RemoveItem(int32 SlotIndex, int32 Amount);

    UFUNCTION(BlueprintCallable)
    void UseItem(int32 SlotIndex);

    UFUNCTION(BlueprintCallable)
    FItemData GetItemAt(int32 Index) const;

    UFUNCTION(BlueprintCallable)
    int32 GetSlotCount() const { return MaxSlots; }

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 MaxSlots = 20;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<FItemData> Items;

    int32 FindEmptySlot() const;
    int32 FindItemSlot(FString ItemName) const;
};
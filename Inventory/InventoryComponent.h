#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

UENUM(BlueprintType)
enum class EInventorySlotType : uint8
{
    Head UMETA(DisplayName = "Kopf"),
    Chest UMETA(DisplayName = "Brust"),
    Legs UMETA(DisplayName = "Beine"),
    Feet UMETA(DisplayName = "Füße"),
    Hands UMETA(DisplayName = "Hände"),
    Back UMETA(DisplayName = "Rücken"),
    PrimaryWeapon UMETA(DisplayName = "Primärwaffe"),
    SecondaryWeapon UMETA(DisplayName = "Sekundärwaffe"),
    Belt UMETA(DisplayName = "Gürtel"),
    Neck UMETA(DisplayName = "Hals"),
    Ring1 UMETA(DisplayName = "Ring 1"),
    Ring2 UMETA(DisplayName = "Ring 2"),
    Quiver UMETA(DisplayName = "Köcher"),
    Pouch UMETA(DisplayName = "Beutel"),
    Any UMETA(DisplayName = "Beliebig")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
    None UMETA(DisplayName = "Keine"),
    Weapon UMETA(DisplayName = "Waffe"),
    Armor UMETA(DisplayName = "Rüstung"),
    Consumable UMETA(DisplayName = "Verbrauchbar"),
    Resource UMETA(DisplayName = "Ressource"),
    Tool UMETA(DisplayName = "Werkzeug"),
    QuestItem UMETA(DisplayName = "Quest-Item"),
    Building UMETA(DisplayName = "Baumaterial")
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EInventorySlotType SlotType = EInventorySlotType::Any;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsEmpty = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemName = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType ItemType = EItemType::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStackSize = 99;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Weight = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Value = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemMeshPath = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemIconPath = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ArmorValue = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageValue = 0.0f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_DAWNOFAGES_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UInventoryComponent();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 NumSlots = 20;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    float MaxWeight = 50.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    float CurrentWeight = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 GoldAmount = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<FInventorySlot> InventorySlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<FInventorySlot> EquipmentSlots;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(FName ItemID, int32 Quantity = 1);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool RemoveItem(FName ItemID, int32 Quantity = 1);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool EquipItem(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool UnequipItem(EInventorySlotType SlotType);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool SwapSlots(int32 FromSlot, int32 ToSlot);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool UseItem(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool DropItem(int32 SlotIndex, int32 Quantity = 1);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool HasItem(FName ItemID, int32 Quantity = 1) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    int32 GetItemCount(FName ItemID) const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    int32 GetFirstEmptySlot() const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    int32 GetSlotWithItem(FName ItemID) const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    float GetWeightPercent() const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    bool CanCarry(float AdditionalWeight) const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddGold(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool SpendGold(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void ClearInventory();

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void SetItem(int32 SlotIndex, FInventorySlot Item);

private:
    void InitializeSlots();
    FInventorySlot CreateItemFromID(FName ItemID);

    float CalculateTotalWeight() const;
    float GetSlotWeight(const FInventorySlot& Slot) const;
};

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName DisplayName = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType ItemType = EItemType::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EInventorySlotType equipSlot = EInventorySlotType::Any;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStackSize = 99;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Weight = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Value = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ArmorValue = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageValue = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HealAmount = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HungerRestore = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ThirstRestore = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMesh* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Icon;
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EquipmentSets.generated.h"

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
    Helmet     UMETA(DisplayName = "Helmet"),
    Chest     UMETA(DisplayName = "Chest"),
    Legs       UMETA(DisplayName = "Legs"),
    Gloves    UMETA(DisplayName = "Gloves"),
    Boots     UMETA(DisplayName = "Boots"),
    Weapon    UMETA(DisplayName = "Weapon"),
    Shield    UMETA(DisplayName = "Shield"),
    Amulet    UMETA(DisplayName = "Amulet"),
    Ring      UMETA(DisplayName = "Ring")
};

USTRUCT(BlueprintType)
struct FEquipmentSet
{
    GENERATED_BODY()
    FName SetID;
    FText DisplayName;
    TMap<EEquipmentSlot, FName> Items;
    int32 TotalPieces = 0;
    float ArmorBonus = 0.0f;
    float DamageBonus = 0.0f;
    float SetBonusPercent = 0.0f;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UEquipmentSetsSystem : public UObject
{
    GENERATED_BODY()
public:
    static FEquipmentSet GetSet(FName SetID);
    static float GetActiveSetBonus();
    static int32 GetEquippedPieces(FName SetID);
    static bool HasSetBonus(FName SetID);
    static void EquipItem(FName ItemID, EEquipmentSlot Slot);
    static void UnequipItem(EEquipmentSlot Slot);
    static TArray<FEquipmentSet> GetAllSets();
};
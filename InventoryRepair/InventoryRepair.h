#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryRepair.generated.h"

UENUM(BlueprintType)
enum class ERepairQuality : uint8
{
    Poor     UMETA(DisplayName = "Poor"),
    Standard UMETA(DisplayName = "Standard"),
    Good     UMETA(DisplayName = "Good"),
    Superior UMETA(DisplayName = "Superior"),
    Master   UMETA(DisplayName = "Master")
};

USTRUCT(BlueprintType)
struct FRepairCost
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere) int32 GoldCost = 0;
    UPROPERTY(EditAnywhere) int32 MaterialCost = 0;
    UPROPERTY(EditAnywhere) float Duration = 10.0f;
    UPROPERTY(EditAnywhere) float QualityBonus = 1.0f;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UInventoryRepairSystem : public UObject
{
    GENERATED_BODY()
public:
    static bool CanRepair(float CurrentDurability);
    static FRepairCost CalculateCost(float Durability, ERepairQuality Quality);
    static bool RepairItem(float& CurrentDurability, float Amount);
    static bool CanSalvage(FName ItemID);
    static TArray<FName> GetSalvageMaterials(FName ItemID);
    static float GetMaterialYield(FName MaterialID);
private:
    static int32 RepairKitCount;
};
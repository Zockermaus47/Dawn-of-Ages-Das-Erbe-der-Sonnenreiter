#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HousingDecoration.generated.h"

UENUM(BlueprintType)
enum class FFurnitureCategory : uint8
{
    Bed       UMETA(DisplayName = "Bed"),
    Chair    UMETA(DisplayName = "Chair"),
    Table    UMETA(DisplayName = "Table"),
    Cupboard  UMETA(DisplayName = "Cupboard"),
    Chest    UMETA(DisplayName = "Chest"),
    Rug      UMETA(DisplayName = "Rug"),
    Lamp     UMETA(DisplayName = "Lamp"),
    Plant    UMETA(DisplayName = "Plant"),
    Painting UMETA(DisplayName = "Painting"),
    Fountain UMETA(DisplayName = "Fountain"),
    Bar      UMETA(DisplayName = "Bar")
};

USTRUCT(BlueprintType)
struct FFurnitureItem
{
    GENERATED_BODY()
    FName ItemID;
    FText DisplayName;
    FFurnitureCategory Category;
    int32 GridX = 1;
    int32 GridY = 1;
    int32 GoldCost = 100;
    bool bCanRotate = true;
    bool bInteractive = false;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UHousingDecorationSystem : public UObject
{
    GENERATED_BODY()
public:
    static bool PlaceFurniture(FName PlotID, FFurnitureItem Item, FVector Position);
    static bool RemoveFurniture(FName PlotID, FName ItemID);
    static bool RotateFurniture(FName PlotID, FName ItemID);
    static TArray<FFurnitureItem> GetCategoryItems(FFurnitureCategory Category);
    static bool CanPlace(FName PlotID, FFurnitureItem Item, FVector Position);
    static int32 GetPlaceableCount(FName PlotID);
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Housing.generated.h"

UENUM(BlueprintType)
enum class EHouseBuildingType : uint8
{
    House      UMETA(DisplayName = "House"),
    Shop      UMETA(DisplayName = "Shop"),
    Workshop  UMETA(DisplayName = "Workshop"),
    Barn      UMETA(DisplayName = "Barn"),
    Tower     UMETA(DisplayName = "Tower"),
    Wall      UMETA(DisplayName = "Wall"),
    Gate      UMETA(DisplayName = "Gate")
};

USTRUCT(BlueprintType)
struct FHousingPlot
{
    GENERATED_BODY()
    FName PlotID;
    FText DisplayName;
    EBuildingType Type;
    FVector Location;
    int32 Level = 1;
    int32 MaxUpgrades = 5;
    TArray<FName> Furniture;
    FName OwnerID;
    bool bIsPublic = true;
};

USTRUCT(BlueprintType)
struct FFurnitureData
{
    GENERATED_BODY()
    FName FurnitureID;
    FText DisplayName;
    FName Category;
    int32 SizeX = 1;
    int32 SizeY = 1;
    int32 Cost = 100;
    float StorageCapacity = 0.0f;
    FName CraftRecipe;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UHousingSystem : public UObject
{
    GENERATED_BODY()
public:
    static FHousingPlot BuyPlot(FVector Location, EBuildingType Type);
    static bool UpgradePlot(FName PlotID);
    static bool AddFurniture(FName PlotID, FFurnitureData Furniture);
    static bool RemoveFurniture(FName PlotID, FName FurnitureID);
    static FHousingPlot GetPlot(FName PlotID);
    static TArray<FHousingPlot> GetOwnedPlots();
    static TArray<FFurnitureData> GetFurnitureByCategory(FName Category);
    static float GetStorageCapacity(FName PlotID);
    static bool SetPublic(FName PlotID, bool bPublic);
    static bool InvitePlayer(FName PlotID, FName PlayerID);
    static void SetRentPrice(FName PlotID, int32 Price);
    static int32 GetRentPrice(FName PlotID);
};
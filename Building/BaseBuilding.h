#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "BaseBuilding.generated.h"

UENUM(BlueprintType)
enum class EBuildingCategory : uint8
{
    House      UMETA(DisplayName = "House"),
    Farm       UMETA(DisplayName = "Farm"),
    Workshop  UMETA(DisplayName = "Workshop"),
    Storage   UMETA(DisplayName = "Storage"),
    Defense   UMETA(DisplayName = "Defense"),
    Garden    UMETA(DisplayName = "Garden"),
    Pen       UMETA(DisplayName = "Animal Pen"),
    Fence     UMETA(DisplayName = "Fence"),
    Tower     UMETA(DisplayName = "Tower"),
    Wall      UMETA(DisplayName = "Wall")
};

UENUM(BlueprintType)
enum class EBuildingState : uint8
{
    Blueprint UMETA(DisplayName = "Blueprint"),
    UnderConstruction UMETA(DisplayName = "Under Construction"),
    Completed UMETA(DisplayName = "Completed"),
    Damaged  UMETA(DisplayName = "Damaged"),
    Ruined   UMETA(DisplayName = "Ruined")
};

UENUM(BlueprintType)
enum class EBuildingMaterial : uint8
{
    Wood        UMETA(DisplayName = "Wood"),
    Straw       UMETA(DisplayName = "Straw"),
    Stone       UMETA(DisplayName = "Stone"),
    Brick        UMETA(DisplayName = "Brick"),
    Adobe       UMETA(DisplayName = "Adobe"),
    Log         UMETA(DisplayName = "Log"),
    Plank        UMETA(DisplayName = "Plank"),
    Iron        UMETA(DisplayName = "Iron"),
    Marble      UMETA(DisplayName = "Marble"),
    Crystal      UMETA(DisplayName = "Crystal")
};

UENUM(BlueprintType)
enum class EFarmCrop : uint8
{
    Wheat     UMETA(DisplayName = "Wheat"),
    Corn      UMETA(DisplayName = "Corn"),
    Carrot   UMETA(DisplayName = "Carrot"),
    Potato   UMETA(DisplayName = "Potato"),
    Tomato   UMETA(DisplayName = "Tomato"),
    Cabbage  UMETA(DisplayName = "Cabbage"),
    Pumpkin  UMETA(DisplayName = "Pumpkin"),
    Berry    UMETA(DisplayName = "Berry"),
    Grape    UMETA(DisplayName = "Grape"),
    Flax     UMETA(DisplayName = "Flax")
};

USTRUCT(BlueprintType)
struct FBuildingData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BuildingID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBuildingCategory Category;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBuildingMaterial PrimaryMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 WoodCost = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StrawCost = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StoneCost = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BrickCost = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AdobeCost = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MetalCost = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BuildTime = 60;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxHealth = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Insulation = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Health = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StorageSlots = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Workers = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WorkRadius = 500.0f;
};

USTRUCT(BlueprintType)
struct FPlacedBuilding
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BuildingInstanceID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FBuildingData Data;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator Rotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBuildingState State;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BuildProgress = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentHealth = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Inventory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Workers;
};

USTRUCT(BlueprintType)
struct FFarmPlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName PlotID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFarmCrop Crop;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GrowthProgress = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WaterLevel = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Fertilizer = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsPlanted = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DaysToHarvest = 5.0f;
};

USTRUCT(BlueprintType)
struct FWorkStation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName StationID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RecipeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CraftProgress = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ItemsInQueue = 0;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UBaseBuildingSystem : public UObject
{
    GENERATED_BODY()

public:
    static FBuildingData GetBuildingData(FName BuildingID);

    static FPlacedBuilding PlaceBuilding(FBuildingData Data, FVector Location, FRotator Rotation);

    static bool StartConstruction(FName BuildingID);

    static void CompleteConstruction(FName BuildingID);

    static void DemolishBuilding(FName BuildingID);

    static void RepairBuilding(FName BuildingID, int32 WoodAmount, int32 StoneAmount);

    static TArray<FPlacedBuilding> GetBuildingsInRadius(FVector Location, float Radius);

    static bool CanBuildAtLocation(FVector Location, EBuildingCategory Category);

    static FFarmPlot CreateFarmPlot(FName BuildingID, EFarmCrop Crop);

    static void PlantCrop(FFarmPlot& Plot, EFarmCrop Crop);

    static void HarvestCrop(FFarmPlot& Plot, int32& Amount);

    static void WaterCrop(FFarmPlot& Plot, float Amount);

    static void FertilizeCrop(FFarmPlot& Plot, float Amount);

    static void UpdateFarmPlot(FFarmPlot& Plot, float DeltaTime);

    static bool IsReadyToHarvest(FFarmPlot Plot);

    static void AddWorker(FName BuildingID, FName WorkerID);

    static void RemoveWorker(FName BuildingID, FName WorkerID);

    static TArray<FName> GetWorkers(FName BuildingID);

    static bool HasRoomForItem(FName BuildingID, FName ItemID);

    static void AddItemToStorage(FName BuildingID, FName ItemID, int32 Quantity);

    static TArray<FName> GetStorageItems(FName BuildingID);

    static float GetBuildingHealth(FName BuildingID);

    static EBuildingState GetBuildingState(FName BuildingID);

    UFUNCTION(BlueprintCallable, Category = "Building")
    static bool CanAffordMaterial(FBuildingData Data);

    UFUNCTION(BlueprintCallable, Category = "Building")
    static int32 GetTotalMaterialCost(FBuildingData Data);

    UFUNCTION(BlueprintCallable, Category = "Building")
    static float GetBuildingInsulation(FBuildingData Data);

    UFUNCTION(BlueprintCallable, Category = "Building")
    static bool UpgradeMaterial(FName BuildingID, EBuildingMaterial NewMaterial);

    UFUNCTION(BlueprintCallable, Category = "Building")
    static TArray<FBuildingData> GetBuildingsByMaterial(EBuildingMaterial Material);
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Farming.generated.h"

UENUM(BlueprintType)
enum class ECropType : uint8
{
    None        UMETA(DisplayName = "None"),
    Wheat       UMETA(DisplayName = "Wheat"),
    Barley      UMETA(DisplayName = "Barley"),
    Corn        UMETA(DisplayName = "Corn"),
    Rice        UMETA(DisplayName = "Rice"),
    Cotton      UMETA(DisplayName = "Cotton"),
    Flax        UMETA(DisplayName = "Flax"),
    Hemp        UMETA(DisplayName = "Hemp"),
    vegetables  UMETA(DisplayName = "Vegetables"),
    Fruit       UMETA(DisplayName = "Fruit"),
    Herbs       UMETA(DisplayName = "Herbs")
};

UENUM(BlueprintType)
enum class EGrowthStage : uint8
{
    Seed       UMETA(DisplayName = "Seed"),
    Sprout     UMETA(DisplayName = "Sprout"),
    Growing   UMETA(DisplayName = "Growing"),
    Mature    UMETA(DisplayName = "Mature"),
    Harvest   UMETA(DisplayName = "Harvest"),
    Dead      UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class ESeason : uint8
{
    Spring     UMETA(DisplayName = "Spring"),
    Summer    UMETA(DisplayName = "Summer"),
    Autumn    UMETA(DisplayName = "Autumn"),
    Winter    UMETA(DisplayName = "Winter"),
    All       UMETA(DisplayName = "All Seasons")
};

USTRUCT(BlueprintType)
struct FCropData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName CropID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECropType CropType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 GrowthTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 HarvestQuantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SeedQuantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperienceGained;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WaterRequirement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FertilizerRequirement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESeason GrowingSeason;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> RequiredItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkillLevelRequired;
};

USTRUCT(BlueprintType)
struct FGardenPlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName CropID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGrowthStage GrowthStage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WaterLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FertilizerLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GrowthProgress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DaysPlanted;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UFarmingSystem : public UObject
{
    GENERATED_BODY()

public:
    UFarmingSystem();

    UFUNCTION(BlueprintCallable, Category = "Farming")
    static FCropData GetCropData(FName CropID);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    static bool CanPlant(FName CropID, const TMap<FName, int32>& Inventory);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    static TMap<FName, int32> Plant(FName CropID, const TMap<FName, int32>& Inventory);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    static bool CanHarvest(FGardenPlot Plot);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    static TMap<FName, int32> Harvest(FGardenPlot Plot);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    static void UpdateGrowth(FGardenPlot& Plot, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    static void Water(FGardenPlot& Plot, float Amount);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    static void Fertilize(FGardenPlot& Plot, float Amount);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    static TArray<FCropData> GetCropsBySeason(ESeason Season);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    static TArray<FCropData> GetAllCrops();
};
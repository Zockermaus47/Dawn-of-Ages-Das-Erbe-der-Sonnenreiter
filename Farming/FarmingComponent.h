#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FarmingComponent.generated.h"

UENUM(BlueprintType)
enum class EFarmCropType : uint8
{
    Wheat UMETA(DisplayName = "Weizen"),
    Corn UMETA(DisplayName = "Mais"),
    Carrot UMETA(DisplayName = "Karotte"),
    Potato UMETA(DisplayName = "Kartoffel"),
    Berry UMETA(DisplayName = "Beere"),
    Flax UMETA(DisplayName = "Flachs"),
    Hemp UMETA(DisplayName = "Hanf")
};

UENUM(BlueprintType)
enum class ECropState : uint8
{
    Seeded UMETA(DisplayName = "Gepflanzt"),
    Growing UMETA(DisplayName = "Wächst"),
    Ready UMETA(DisplayName = "Erntebereit"),
    Harvested UMETA(DisplayName = "Geerntet")
};

UENUM(BlueprintType)
enum class EGeneticTrait : uint8
{
    None UMETA(DisplayName = "Keine"),
    Strong UMETA(DisplayName = "Stark"),
    Fast UMETA(DisplayName = "Schnell"),
    Fertile UMETA(DisplayName = "Fruchtbar"),
    Hardy UMETA(DisplayName = "Widerstandsfähig"),
    Efficient UMETA(DisplayName = "Effizient")
};

USTRUCT(BlueprintType)
struct FFarmingCropData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFarmCropType CropType = EFarmCropType::Wheat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName CropName = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GrowthTime = 60.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Yield = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName OutputItemID = NAME_None;
};

USTRUCT(BlueprintType)
struct FPlantedCrop
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PlotIndex = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName CropID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECropState State = ECropState::Seeded;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentGrowth = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WaterLevel = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FertilizerLevel = 0.0f;
};

USTRUCT(BlueprintType)
struct FFarmAnimalData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AnimalID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AnimalName = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BreedTier = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Hunger = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GrowthProgress = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsAdult = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Parent1 = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Parent2 = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<EGeneticTrait> InheritedTraits;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GeneticPotency = 1.0f;
};

USTRUCT(BlueprintType)
struct FCropGenetics
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SeedID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<EGeneticTrait> traits;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float YieldBonus = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GrowthSpeedBonus = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WeatherResistance = 1.0f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_DAWNOFAGES_API UFarmingComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UFarmingComponent();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Farming")
    int32 NumPlots = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Farming")
    TArray<FPlantedCrop> PlantedCrops;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Farming")
    TArray<int32> HarvestYields;

    UPROPERTY(BlueprintReadOnly, Category = "Farming")
    TArray<FFarmAnimalData> Animals;

    UFUNCTION(BlueprintCallable, Category = "Farming")
    bool PlantCrop(int32 PlotIndex, FName SeedItemID);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    FName GetSeedForCrop(EFarmCropType CropType) const;

    UFUNCTION(BlueprintCallable, Category = "Farming")
    bool HasSeeds(EFarmCropType CropType) const;

    static TMap<EFarmCropType, FName> SeedItemMap;

    UFUNCTION(BlueprintCallable, Category = "Farming")
    bool WaterCrop(int32 PlotIndex, float Amount);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    bool Fertilize(int32 PlotIndex, float Amount);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    bool HarvestCrop(int32 PlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    bool AddAnimal(FFarmAnimalData Animal);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    bool BreedAnimals(FName Parent1, FName Parent2);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    bool FeedAnimal(FName AnimalID, float FoodAmount);

    UFUNCTION(BlueprintCallable, Category = "Farming")
    TArray<FFarmAnimalData> GetAnimalsByType(FName AnimalType) const;

    UFUNCTION(BlueprintPure, Category = "Farming")
    int32 GetTotalAnimals() const;

    UFUNCTION(BlueprintCallable, Category = "Genetics")
    bool BreedWithGenetics(FName Parent1ID, FName Parent2ID);

    UFUNCTION(BlueprintCallable, Category = "Genetics")
    bool ApplyTraitToAnimal(FName AnimalID, EGeneticTrait Trait);

    UFUNCTION(BlueprintCallable, Category = "Genetics")
    TArray<EGeneticTrait> GetAnimalTraits(FName AnimalID) const;

    UFUNCTION(BlueprintPure, Category = "Genetics")
    float GetGeneticPotency(FName AnimalID) const;

private:
    TArray<EGeneticTrait> InheritTraits(FFarmAnimalData Parent1, FFarmAnimalData Parent2);
    float CalculateGeneticPotency(FFarmAnimalData Parent1, FFarmAnimalData Parent2);
    void UpdateCrops(float DeltaTime);
    void UpdateAnimals(float DeltaTime);
};
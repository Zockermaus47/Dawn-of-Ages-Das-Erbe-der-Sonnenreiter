#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Breeding.generated.h"

UENUM(BlueprintType)
enum class EAnimalType : uint8
{
    None        UMETA(DisplayName = "None"),
    Cow         UMETA(DisplayName = "Cow"),
    Sheep       UMETA(DisplayName = "Sheep"),
    Pig         UMETA(DisplayName = "Pig"),
    Chicken     UMETA(DisplayName = "Chicken"),
    Horse       UMETA(DisplayName = "Horse"),
    Donkey      UMETA(DisplayName = "Donkey"),
    Goat        UMETA(DisplayName = "Goat"),
    Duck        UMETA(DisplayName = "Duck"),
    Goose       UMETA(DisplayName = "Goose")
};

UENUM(BlueprintType)
enum class EAnimalMood : uint8
{
    Happy       UMETA(DisplayName = "Happy"),
    Neutral     UMETA(DisplayName = "Neutral"),
    Hungry      UMETA(DisplayName = "Hungry"),
    Sick       UMETA(DisplayName = "Sick"),
    Estrus     UMETA(DisplayName = "Estrus")
};

USTRUCT(BlueprintType)
struct FAnimalData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AnimalID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAnimalType AnimalType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 GrowthTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 HarvestQuantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MilkQuantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BreedingTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperienceGained;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FoodRequirement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpaceRequirement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Products;
};

USTRUCT(BlueprintType)
struct FAnimalGenetics
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HealthGene = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpeedGene = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StrengthGene = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FertilityGene = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MilkProductionGene = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WoolQualityGene = 50.0f;
};

USTRUCT(BlueprintType)
struct FAnimalInstance
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AnimalID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAnimalGenetics Genetics;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Age;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAnimalMood Mood;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsPregnant;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PregnancyTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Hunger = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Thirst = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsSick = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName DiseaseID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LastFed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LastDrank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HungerLevel = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ThirstLevel = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PregnancyProgress = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Eggs = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EggTimer = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Affection = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CareLevel = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GrowthStage = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DaysOld = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LastPet = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LastGroomed = 0.0f;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UBreedingSystem : public UObject
{
    GENERATED_BODY()

public:
    UBreedingSystem();

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static FAnimalData GetAnimalData(FName AnimalID);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static bool CanBreed(FAnimalInstance Animal1, FAnimalInstance Animal2);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static FAnimalInstance Breed(FAnimalInstance Parent1, FAnimalInstance Parent2);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static TMap<FName, int32> Harvest(FAnimalInstance Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static void Feed(FAnimalInstance& Animal, FName Food);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static void UpdateAnimal(FAnimalInstance& Animal, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static float CalculateProductivity(FAnimalInstance Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static TArray<FAnimalData> GetAllAnimals();

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static void FeedAnimal(FAnimalInstance& Animal, FName FoodID);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static void WaterAnimal(FAnimalInstance& Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static void InfectAnimal(FAnimalInstance& Animal, FName DiseaseID);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static void CureAnimal(FAnimalInstance& Animal, FName CureItem);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static bool CanReproduce(FAnimalInstance Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static void Reproduce(FAnimalInstance& Animal, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static void UpdateAnimalNeeds(FAnimalInstance& Animal, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static float GetHunger(FAnimalInstance Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static float GetThirst(FAnimalInstance Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static bool IsSick(FAnimalInstance Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static int32 CollectEggs(FAnimalInstance& Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static void PetAnimal(FAnimalInstance& Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static void GroomAnimal(FAnimalInstance& Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static void UpdateGrowth(FAnimalInstance& Animal, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static float GetAffection(FAnimalInstance Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static float GetCareLevel(FAnimalInstance Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static int32 GetGrowthStage(FAnimalInstance Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static bool IsFullyGrown(FAnimalInstance Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static float CalculateProductQuality(FAnimalInstance Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static int32 MilkCow(FAnimalInstance& Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static int32 ShearSheep(FAnimalInstance& Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static bool MountAnimal(FAnimalInstance& Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static bool DismountAnimal(FAnimalInstance& Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static bool IsMounted(FAnimalInstance Animal);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static bool RideAnimal(FAnimalInstance& Animal, FVector Direction);

    UFUNCTION(BlueprintCallable, Category = "Breeding")
    static int32 HarvestHoney(FAnimalInstance& Animal);
};
#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WildlifeArea.generated.h"

UENUM(BlueprintType)
enum class EWildlifeShelter : uint8
{
    StrawHut      UMETA(DisplayName = "Straw Hut"),
    WoodenCabin   UMETA(DisplayName = "Wooden Cabin"),
    StoneHouse   UMETA(DisplayName = "Stone House"),
    Cave        UMETA(DisplayName = "Cave"),
    Tent         UMETA(DisplayName = "Tent"),
    Treehouse   UMETA(DisplayName = "Treehouse")
};

UENUM(BlueprintType)
enum class ECaveType : uint8
{
    SmallCave    UMETA(DisplayName = "Small Cave"),
    MediumCave  UMETA(DisplayName = "Medium Cave"),
    LargeCave   UMETA(DisplayName = "Large Cave"),
    MineShaft   UMETA(DisplayName = "Mine Shaft"),
    HiddenCave  UMETA(DisplayName = "Hidden Cave")
};

UENUM(BlueprintType)
enum class EOreType : uint8
{
    Stone       UMETA(DisplayName = "Stone"),
    Coal        UMETA(DisplayName = "Coal"),
    IronOre     UMETA(DisplayName = "Iron Ore"),
    CopperOre   UMETA(DisplayName = "Copper Ore"),
    GoldOre     UMETA(DisplayName = "Gold Ore"),
    SilverOre  UMETA(DisplayName = "Silver Ore"),
    Mithril    UMETA(DisplayName = "Mithril"),
    Adamantite  UMETA(DisplayName = "Adamantite"),
    Gem        UMETA(DisplayName = "Gem")
};

USTRUCT(BlueprintType)
struct FShelterData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ShelterID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWildlifeShelter Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Capacity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasFire = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasStorage = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StorageSlots = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Warmth = 0.0f;
};

USTRUCT(BlueprintType)
struct FCaveData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName CaveID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECaveType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Depth = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DangerLevel = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<EOreType> Ores;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float OreSpawnChance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsDiscovered = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCleared = false;
};

USTRUCT(BlueprintType)
struct FOreInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName DepositID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EOreType Ore;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReplenishTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LastHarvested = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsDepleted = false;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UWildlifeAreaSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Wildlife")
    static FShelterData CreateShelter(EWildlifeShelter Type);

    UFUNCTION(BlueprintCallable, Category = "Wildlife")
    static FCaveData CreateCave(ECaveType Type, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Wildlife")
    static FOreDeposit CreateOreDeposit(EOreType Ore, int32 Quantity);

    UFUNCTION(BlueprintCallable, Category = "Wildlife")
    static bool EnterShelter(FName ShelterID);

    UFUNCTION(BlueprintCallable, Category = "Wildlife")
    static bool ExitShelter();

    UFUNCTION(BlueprintCallable, Category = "Wildlife")
    static bool IsInsideShelter();

    UFUNCTION(BlueprintCallable, Category = "Wildlife")
    static float GetShelterWarmth();

    UFUNCTION(BlueprintCallable, Category = "Wildlife")
    static TArray<FOreDeposit> GetOresInRadius(FVector Location, float Radius);

    UFUNCTION(BlueprintCallable, Category = "Wildlife")
    static bool HarvestOre(FOreDeposit& Deposit, int32& Amount);

    UFUNCTION(BlueprintCallable, Category = "Wildlife")
    static void UpdateCave(FCaveData& Cave, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Wildlife")
    static bool ExploreCave(FCaveData& Cave);

    UFUNCTION(BlueprintCallable, Category = "Wildlife")
    static int32 GetCaveDanger(FCaveData Cave);

    UFUNCTION(BlueprintCallable, Category = "Wildlife")
    static TArray<EOreType> GetAvailableOres();

private:
    static FName CurrentShelter;
    static bool bInsideShelter;
    static float CurrentWarmth;
};
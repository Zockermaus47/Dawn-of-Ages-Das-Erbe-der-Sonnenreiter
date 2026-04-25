#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WaterSystem.generated.h"

UENUM(BlueprintType)
enum class EWaterSource : uint8
{
    Well        UMETA(DisplayName = "Well"),
    RainCatcher UMETA(DisplayName = "Rain Catcher"),
    River      UMETA(DisplayName = "River"),
    Lake       UMETA(DisplayName = "Lake"),
    Spring     UMETA(DisplayName = "Spring"),
    Ocean      UMETA(DisplayName = "Ocean")
};

UENUM(BlueprintType)
enum class EWaterQuality : uint8
{
    Dirty      UMETA(DisplayName = "Dirty"),
    Normal     UMETA(DisplayName = "Normal"),
    Clean      UMETA(DisplayName = "Clean"),
    Purified   UMETA(DisplayName = "Purified"),
    Magical    UMETA(DisplayName = "Magical")
};

USTRUCT(BlueprintType)
struct FWaterSource
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SourceID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWaterSource Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WaterAmount = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxCapacity = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWaterQuality Quality = EWaterQuality::Normal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FillRate = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsActive = true;
};

USTRUCT(BlueprintType)
struct FRainCollector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName CollectorID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CollectionRate = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentWater = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Capacity = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCollecting = false;
};

USTRUCT(BlueprintType)
struct FWell
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName WellID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentWater = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxWater = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReplenishRate = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasPump = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bNeedsRepair = false;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UWaterSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Water")
    static FWaterSource CreateSource(EWaterSource Type, float Capacity);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static bool CollectWater(FWaterSource& Source, float Amount);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static bool DepositWater(FWaterSource& Source, float Amount);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static float GetWaterLevel(FWaterSource Source);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static bool IsEmpty(FWaterSource Source);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static FRainCollector CreateRainCollector(float Capacity);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static void UpdateRainCollector(FRainCollector& Collector, float RainAmount, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static float CollectFromRain(FRainCollector& Collector, float Amount);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static FWell CreateWell(float Capacity);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static void UpdateWell(FWell& Well, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static float DrawFromWell(FWell& Well, float Amount);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static void RepairWell(FWell& Well);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static bool PurifyWater(EWaterQuality& Quality);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static bool DrinkWater(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Water")
    static float GetPlayerWater();
};
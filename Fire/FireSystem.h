#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FireSystem.generated.h"

UENUM(BlueprintType)
enum class EFireType : uint8
{
    Campfire     UMETA(DisplayName = "Campfire"),
    Bonfire     UMETA(DisplayName = "Bonfire"),
    Fireplace   UMETA(DisplayName = "Fireplace"),
    Torch       UMETA(DisplayName = "Torch"),
    Lantern    UMETA(DisplayName = "Lantern"),
    Brazier    UMETA(DisplayName = "Brazier")
};

UENUM(BlueprintType)
enum class EFireState : uint8
{
    Unlit       UMETA(DisplayName = "Unlit"),
    Lighting    UMETA(DisplayName = "Lighting"),
    Burning    UMETA(DisplayName = "Burning"),
    Flickering UMETA(DisplayName = "Flickering"),
    Dying      UMETA(DisplayName = "Dying"),
    Extinguished UMETA(DisplayName = "Extinguished")
};

UENUM(BlueprintType)
enum class EFuelType : uint8
{
    Wood        UMETA(DisplayName = "Wood"),
    Coal        UMETA(DisplayName = "Coal"),
    Charcoal   UMETA(DisplayName = "Charcoal"),
    Oil        UMETA(DisplayName = "Oil"),
    MagicFuel  UMETA(DisplayName = "Magic Fuel")
};

USTRUCT(BlueprintType)
struct FCampfire
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName FireID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFireType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFireState State;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FuelLevel = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxFuel = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HeatOutput = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LightRadius = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BurnRate = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanCook = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsIndoor = false;
};

USTRUCT(BlueprintType)
struct FCookingPot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName PotID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName CookingRecipe;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CookProgress = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RequiredTime = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCooking = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsDone = false;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UFireSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Fire")
    static FCampfire CreateFire(EFireType Type, bool bIsIndoor);

    UFUNCTION(BlueprintCallable, Category = "Fire")
    static bool LightFire(FCampfire& Fire, EFuelType Fuel);

    UFUNCTION(BlueprintCallable, Category = "Fire")
    static void UpdateFire(FCampfire& Fire, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Fire")
    static bool AddFuel(FCampfire& Fire, EFuelType Fuel, int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Fire")
    static void ExtinguishFire(FCampfire& Fire);

    UFUNCTION(BlueprintCallable, Category = "Fire")
    static float GetHeatOutput(FCampfire Fire);

    UFUNCTION(BlueprintCallable, Category = "Fire")
    static float GetLightRadius(FCampfire Fire);

    UFUNCTION(BlueprintCallable, Category = "Fire")
    static bool IsFireBurning(FCampfire Fire);

    UFUNCTION(BlueprintCallable, Category = "Fire")
    static FCookingPot StartCooking(FCampfire& Fire, FName Recipe);

    UFUNCTION(BlueprintCallable, Category = "Fire")
    static void UpdateCooking(FCookingPot& Pot, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Fire")
    static FName CollectFood(FCookingPot& Pot);

    UFUNCTION(BlueprintCallable, Category = "Fire")
    static float GetPlayerWarmth();

    UFUNCTION(BlueprintCallable, Category = "Fire")
    static bool IsNearFire(FVector PlayerLoc, FCampfire Fire, float Range);

private:
    static float PlayerWarmth;
};
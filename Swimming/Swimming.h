#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Swimming.generated.h"

UENUM(BlueprintType)
enum class ESwimState : uint8
{
    Land        UMETA(DisplayName = "Land"),
    Wading       UMETA(DisplayName = "Wading"),
    Swimming    UMETA(DisplayName = "Swimming"),
    Diving      UMETA(DisplayName = "Diving"),
    Underwater  UMETA(DisplayName = "Underwater")
};

UENUM(BlueprintType)
enum class EWaterBody : uint8
{
    Freshwater   UMETA(DisplayName = "Freshwater"),
    Saltwater   UMETA(DisplayName = "Saltwater"),
    HotSpring   UMETA(DisplayName = "Hot Spring"),
    MurkyWater  UMETA(DisplayName = "Murky Water"),
    DeepOcean    UMETA(DisplayName = "Deep Ocean")
};

UENUM(BlueprintType)
enum class EBreathState : uint8
{
    Normal      UMETA(DisplayName = "Normal"),
    Holding     UMETA(DisplayName = "Holding"),
    Stressed    UMETA(DisplayName = "Stressed"),
    Drowning   UMETA(DisplayName = "Drowning"),
    Recovering UMETA(DisplayName = "Recovering")
};

UENUM(BlueprintType)
enum class EDiveDepth : uint8
{
    Surface     UMETA(DisplayName = "Surface"),
    Shallow     UMETA(DisplayName = "Shallow"),
    Medium      UMETA(DisplayName = "Medium"),
    Deep        UMETA(DisplayName = "Deep"),
    Abyss       UMETA(DisplayName = "Abyss")
};

USTRUCT(BlueprintType)
struct FSwimSkillData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SkillID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BreathCapacity = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SwimSpeedMod = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DiveDepthMod = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanDive = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanHoldBreath = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaDrainMod = 1.0f;
};

USTRUCT(BlueprintType)
struct FWaterEnvironmentData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWaterBody WaterType = EWaterBody::Freshwater;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Depth = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Temperature = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentStrength = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Visibility = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasCurrents = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D CurrentDirection = FVector2D(0.0f, 0.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> FishSpecies;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> UnderwaterItems;
};

USTRUCT(BlueprintType)
struct FSwimPlayerData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESwimState CurrentState = ESwimState::Land;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBreathState BreathState = EBreathState::Normal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EDiveDepth CurrentDepth = EDiveDepth::Surface;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentBreath = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxBreath = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SwimSpeed = 400.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DiveDepth = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float UnderwaterTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaDrain = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanSwim = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsDiving = false;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API USwimmingSystem : public UObject
{
    GENERATED_BODY()

public:
    USwimmingSystem();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static FSwimSkillData GetSwimSkill(FName SkillID);

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static void EnterWater(FWaterEnvironmentData WaterData);

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static void ExitWater();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static void StartSwimming();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static void StopSwimming();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static void StartDiving();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static void Surface();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static void HoldBreath();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static void ReleaseBreath();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static void TickSwimming(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static FSwimPlayerData GetPlayerSwimData();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static ESwimState GetSwimState();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static float GetSwimSpeed();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static float GetBreathPercentage();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static bool IsUnderwater();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static bool CanDiveTo(EDiveDepth TargetDepth);

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static float GetPressureDamage();

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static void ApplySwimSkill(FName SkillID);

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static void RecoverBreath(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Swimming")
    static FWaterEnvironmentData GetCurrentWaterData();

private:
    static FSwimPlayerData PlayerData;
    static FWaterEnvironmentData CurrentWater;
    static ESwimState SwimState;
    static EBreathState Breath;
    static float DiveStartTime;
    static float BreathRecoveryRate;
    static float SurfaceRecoveryDelay;
};
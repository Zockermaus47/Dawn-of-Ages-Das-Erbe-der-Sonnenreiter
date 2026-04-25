#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Stealth.generated.h"

UENUM(BlueprintType)
enum class EStealthState : uint8
{
    Visible     UMETA(DisplayName = "Visible"),
    Crouching  UMETA(DisplayName = "Crouching"),
    Sneaking   UMETA(DisplayName = "Sneaking"),
    Hidden     UMETA(DisplayName = "Hidden"),
    InCover    UMETA(DisplayName = "In Cover")
};

UENUM(BlueprintType)
enum class ECoverType : uint8
{
    None        UMETA(DisplayName = "None"),
    LowCover   UMETA(DisplayName = "Low Cover"),
    HighCover  UMETA(DisplayName = "High Cover"),
    FullCover  UMETA(DisplayName = "Full Cover"),
    DarkCorner UMETA(DisplayName = "Dark Corner")
};

USTRUCT(BlueprintType)
struct FStealthSkillData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SkillID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StealthBonus = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanSilentKill = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DetectionMod = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float NoiseMod = 1.0f;
};

USTRUCT(BlueprintType)
struct FStealthPlayerData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EStealthState StealthState = EStealthState::Visible;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StealthLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 NotorietyLevel = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DetectionRadius = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float NoiseLevel = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanHideInShadows = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanSilentKill = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> AwareEnemies;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UStealthSystem : public UObject
{
    GENERATED_BODY()

public:
    UStealthSystem();

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static FStealthSkillData GetStealthSkill(FName SkillID);

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static void EnterStealth();

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static void ExitStealth();

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static void StartSneaking();

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static void StopSneaking();

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static void MoveSilently();

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static FStealthPlayerData GetPlayerStealthData();

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static EStealthState GetStealthState();

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static float GetDetectionRadius();

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static float GetCurrentStealthValue();

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static float GetNoiseLevel();

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static void MakeNoise(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static bool CanBeDetected(float DetectorStealth, float Distance);

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static bool IsTargetAware(FName TargetID);

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static void MarkTargetAware(FName TargetID);

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static void MarkTargetUnaware(FName TargetID);

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static void AddNotoriety(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static void ReduceNotoriety(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static int32 GetNotorietyLevel();

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static void ApplyStealthSkill(FName SkillID);

    UFUNCTION(BlueprintCallable, Category = "Stealth")
    static void TickStealth(float DeltaTime);

private:
    static FStealthPlayerData PlayerStealthData;
    static float NoiseLevel;
    static bool bIsHidden;
    static bool bIsSneaking;
};
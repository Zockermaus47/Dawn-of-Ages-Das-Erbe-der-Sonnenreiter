#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HarvestComponent.generated.h"

UENUM(BlueprintType)
enum class EHarvestLevels : uint8
{
    Standing UMETA(DisplayName = "Stehend"),
    Falling UMETA(DisplayName = "Fallend"),
    LyingWithBranches UMETA(DisplayName = "Liegend mit Ästen"),
    LyingClean UMETA(DisplayName = "Liegend Sauber"),
    Destroyed UMETA(DisplayName = "Zerstört")
};

UENUM(BlueprintType)
enum class EHarvestTool : uint8
{
    None UMETA(DisplayName = "Keine"),
    Axe UMETA(DisplayName = "Axt"),
    Pickaxe UMETA(DisplayName = "Spitzhacke"),
    Sword UMETA(DisplayName = "Schwert"),
    Hands UMETA(DisplayName = "Hände")
};

USTRUCT(BlueprintType)
struct FHarvestLootDrop
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    FName ItemID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    int32 MinQuantity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    int32 MaxQuantity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    float DropChance = 100.0f;
};

USTRUCT(BlueprintType)
struct FHarvestStageData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    EHarvestStage Stage = EHarvestStage::Standing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    int32 HitsRequired = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    float DamagePerHit = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    TArray<FHarvestLootDrop> LootTable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    bool bSpawnLootOnHit = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    float WobbleAmount = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    FName NextStageItem = NAME_None;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEFFIS_DAWNOFAGES_API UHarvestComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UHarvestComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    EHarvestStage CurrentStage = EHarvestStage::Standing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    float CurrentHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    float MaxHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    TArray<FHarvestStageData> StageProgression;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    float GrowthProgress = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    bool bIsGrown = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvest")
    float RespawnTime = 600.0f;

    UFUNCTION(BlueprintCallable, Category = "Harvest")
    float ReceiveHit(float Damage, EHarvestTool Tool, FVector HitLocation, FVector HitDirection);

    UFUNCTION(BlueprintCallable, Category = "Harvest")
    void ProcessStageTransition();

    UFUNCTION(BlueprintCallable, Category = "Harvest")
    void SpawnLoot(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Harvest")
    void TriggerWobble(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Harvest")
    void Grow(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Harvest")
    void Respawn();

    UFUNCTION(BlueprintPure, Category = "Harvest")
    float GetHealthPercentage() const;

    UFUNCTION(BlueprintPure, Category = "Harvest")
    bool IsFullyGrown() const;

    UFUNCTION(BlueprintPure, Category = "Harvest")
    EHarvestStage GetCurrentStage() const;

private:
    void ApplyStageWobble();
    FHarvestStageData* GetCurrentStageData();
    TArray<FHarvestLootDrop> GetLootForCurrentStage();
};
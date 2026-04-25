#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatDepleted, FName, StatName);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_SPIEL_API UStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStatsComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void ModifyStat(FName StatName, float Delta);

    UFUNCTION(BlueprintCallable)
    void SetStat(FName StatName, float Value);

    UFUNCTION(BlueprintCallable)
    float GetStat(FName StatName) const;

    UFUNCTION(BlueprintCallable)
    float GetStatPercent(FName StatName) const;

    UFUNCTION(BlueprintCallable)
    bool HasStat(FName StatName) const;

    UFUNCTION(BlueprintCallable)
    void RestoreAllStats(float Amount);

    UFUNCTION(BlueprintCallable)
    void DrainAllStats(float Amount);

    UFUNCTION(BlueprintCallable)
    bool IsStarving() const;

    UFUNCTION(BlueprintCallable)
    bool IsDehydrated() const;

    UFUNCTION(BlueprintCallable)
    bool IsFreezing() const;

    UFUNCTION(BlueprintCallable)
    bool IsOverheating() const;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Hunger")
    float MaxHunger = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Hunger")
    float HungerDrainRate = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Hunger")
    float HungerDamageThreshold = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Hunger")
    float HungerDamagePerSecond = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Thirst")
    float MaxThirst = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Thirst")
    float ThirstDrainRate = 0.8f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Thirst")
    float ThirstDamageThreshold = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Thirst")
    float ThirstDamagePerSecond = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Health")
    float MaxHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Stamina")
    float MaxStamina = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Stamina")
    float StaminaDrainRate = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Stamina")
    float StaminaRegenRate = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Temperature")
    float MaxTemperature = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Temperature")
    float ComfortableMin = 40.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Temperature")
    float ComfortableMax = 60.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Regeneration")
    float HealthRegenRate = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Regeneration")
    float HealthRegenDelay = 5.0f;

    UPROPERTY(BlueprintAssignable)
    FOnStatChanged OnHungerChanged;

    UPROPERTY(BlueprintAssignable)
    FOnStatChanged OnThirstChanged;

    UPROPERTY(BlueprintAssignable)
    FOnStatChanged OnHealthChanged;

    UPROPERTY(BlueprintAssignable)
    FOnStatChanged OnStaminaChanged;

    UPROPERTY(BlueprintAssignable)
    FOnStatChanged OnTemperatureChanged;

    UPROPERTY(BlueprintAssignable)
    FOnStatDepleted OnHungerDepleted;

    UPROPERTY(BlueprintAssignable)
    FOnStatDepleted OnThirstDepleted;

    UPROPERTY(BlueprintAssignable)
    FOnStatDepleted OnHealthDepleted;

    UPROPERTY(BlueprintAssignable)
    FOnStatDepleted OnTemperatureDepleted;

protected:
    UPROPERTY(Replicated)
    float Hunger = 100.0f;

    UPROPERTY(Replicated)
    float Thirst = 100.0f;

    UPROPERTY(Replicated)
    float Health = 100.0f;

    UPROPERTY(Replicated)
    float Stamina = 100.0f;

    UPROPERTY(Replicated)
    float Temperature = 50.0f;

    UPROPERTY()
    float TimeSinceLastDamage = 0.0f;

    UPROPERTY()
    float TimeSinceLastRegen = 0.0f;

    float LastHungerValue = 100.0f;
    float LastThirstValue = 100.0f;
    float LastHealthValue = 100.0f;
    float LastStaminaValue = 100.0f;
    float LastTemperatureValue = 50.0f;

    void DrainStat(FName StatName, float DrainRate, float DeltaTime);
    void ApplyStatDamage(FName StatName, float Threshold, float DPS);
    void RegenStat(float& CurrentValue, float MaxValue, float RegenRate, float DeltaTime);

private:
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurvivalComponent.generated.h"

UENUM(BlueprintType)
enum class ESurvivalStat : uint8
{
    Hunger UMETA(DisplayName = "Hunger"),
    Thirst UMETA(DisplayName = "Durst"),
    Temperature UMETA(DisplayName = "Temperatur"),
    Stamina UMETA(DisplayName = "Ausdauer")
};

UENUM(BlueprintType)
enum class EHealthState : uint8
{
    Healthy UMETA(DisplayName = "Gesund"),
    Hungry UMETA(DisplayName = "Hungrig"),
    Starving UMETA(DisplayName = "Am Verhungern"),
    Thirsty UMETA(DisplayName = "Durstig"),
    Dehydrated UMETA(DisplayName = "Ausgetrocknet"),
    Dead UMETA(DisplayName = "Tot")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_DAWNOFAGES_API USurvivalComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    USurvivalComponent();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float MaxHunger = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float MaxThirst = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float MaxStamina = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float CurrentHunger = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float CurrentThirst = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float CurrentStamina = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float CurrentTemperature = 37.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float MinTemperature = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float MaxTemperature = 40.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float HungerDecreaseRate = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float ThirstDecreaseRate = 1.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float TemperatureDecreaseRate = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float StaminaRegenRate = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
    float StaminaDecreaseRate = 10.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Survival")
    EHealthState CurrentHealthState;

    UPROPERTY(BlueprintReadOnly, Category = "Survival")
    bool bIsDead = false;

    UFUNCTION(BlueprintCallable, Category = "Survival")
    void ModifyHunger(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Survival")
    void ModifyThirst(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Survival")
    void ModifyTemperature(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Survival")
    void ModifyStamina(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Survival")
    void UseStamina(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Survival")
    float GetHungerPercent() const;

    UFUNCTION(BlueprintCallable, Category = "Survival")
    float GetThirstPercent() const;

    UFUNCTION(BlueprintCallable, Category = "Survival")
    float GetStaminaPercent() const;

    UFUNCTION(BlueprintCallable, Category = "Survival")
    float GetTemperaturePercent() const;

    UFUNCTION(BlueprintPure, Category = "Survival")
    bool IsStarving() const;

    UFUNCTION(BlueprintPure, Category = "Survival")
    bool IsDehydrated() const;

    UFUNCTION(BlueprintPure, Category = "Survival")
    bool IsTooHot() const;

    UFUNCTION(BlueprintPure, Category = "Survival")
    bool IsTooCold() const;

    UFUNCTION(BlueprintCallable, Category = "Survival")
    void ConsumeFood(float FoodAmount);

    UFUNCTION(BlueprintCallable, Category = "Survival")
    void ConsumeWater(float WaterAmount);

private:
    void UpdateSurvivalStats(float DeltaTime);
    void UpdateHealthState();
    void ApplyHealthEffects(float DeltaTime);

    FTimerHandle HealthEffectTimer;
    
    UFUNCTION()
    void ApplyPeriodicHealthEffects();
};

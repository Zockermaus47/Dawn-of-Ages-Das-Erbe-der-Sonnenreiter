#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DawnGameState.generated.h"

UCLASS()
class STEFFIS_SPIEL_API ADawnGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    ADawnGameState();

    UFUNCTION(BlueprintPure)
    float GetGameTime() const { return GameTime; }

    UFUNCTION(BlueprintPure)
    float GetDayNightCycle() const { return DayNightCycle; }

    UFUNCTION(BlueprintPure)
    float GetDayNumber() const { return DayNumber; }

    UFUNCTION(BlueprintPure)
    bool IsDaytime() const;

    UFUNCTION(BlueprintPure)
    float GetWeatherIntensity() const { return WeatherIntensity; }

    UFUNCTION(BlueprintCallable)
    void SetWeatherIntensity(float NewIntensity);

    UFUNCTION(BlueprintCallable)
    void AdvanceDay();

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Time")
    float GameTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Time")
    float DayLength = 1200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Time")
    float DayNightCycle = 0.0f;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Time")
    int32 DayNumber = 1;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Weather")
    float WeatherIntensity = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
    float DayNightCycleSpeed = 1.0f;

protected:
    virtual void Tick(float DeltaSeconds) override;

private:
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
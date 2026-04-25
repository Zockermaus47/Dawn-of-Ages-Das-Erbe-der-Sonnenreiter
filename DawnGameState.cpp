#include "DawnGameState.h"
#include "Net/UnrealNetwork.h"

ADawnGameState::ADawnGameState()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
}

void ADawnGameState::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (HasAuthority())
    {
        GameTime += DeltaSeconds;
        
        DayNightCycle = FMath::Fmod(GameTime / DayLength, 1.0f);
        
        while (GameTime >= DayLength * DayNumber)
        {
            DayNumber++;
        }
    }
}

bool ADawnGameState::IsDaytime() const
{
    return DayNightCycle > 0.25f && DayNightCycle < 0.75f;
}

void ADawnGameState::SetWeatherIntensity(float NewIntensity)
{
    WeatherIntensity = FMath::Clamp(NewIntensity, 0.0f, 1.0f);
}

void ADawnGameState::AdvanceDay()
{
    DayNumber++;
}

void ADawnGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(ADawnGameState, GameTime);
    DOREPLIFETIME(ADawnGameState, DayNightCycle);
    DOREPLIFETIME(ADawnGameState, DayNumber);
    DOREPLIFETIME(ADawnGameState, WeatherIntensity);
}
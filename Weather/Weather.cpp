#include "Weather.h"

FTimeData UWeatherSystem::CurrentTime;
EWeatherType UWeatherSystem::CurrentWeather = EWeatherType::Clear;
FWindData UWeatherSystem::CurrentWind;
float UWeatherSystem::TemperatureCache = 20.0f;
float UWeatherSystem::WeatherTransition = 0.0f;

UWeatherSystem::UWeatherSystem()
{
    CurrentTime.GameHour = 8.0f;
    CurrentTime.DayOfYear = 1.0f;
    CurrentTime.TimeOfDay = ETimeOfDay::Morning;
    CurrentTime.CurrentSeason = ESeason::Spring;
}

FWeatherData UWeatherSystem::GetWeatherData(FName WeatherID)
{
    FWeatherData Data;
    Data.WeatherID = WeatherID;
    Data.WeatherType = CurrentWeather;
    Data.TemperatureMod = GetTemperature() / 20.0f;
    Data.Visibility = GetVisibilityRange() / 5000.0f;
    Data.MovementSpeedMod = GetPlayerMovementMod();
    Data.VisibilityRange = GetVisibilityRange();
    Data.CropGrowthMod = GetCropGrowthMod();
    Data.ResourceSpawnMod = 1.0f;
    return Data;
}

void UWeatherSystem::UpdateWeather(EWeatherType NewWeather)
{
    CurrentWeather = NewWeather;
    WeatherTransition = 0.0f;
}

TArray<FWeatherData> UWeatherSystem::GetAllWeatherTypes()
{
    TArray<FWeatherData> Types;
    return Types;
}

void UWeatherSystem::AdvanceTime(float DeltaHours)
{
    CurrentTime.GameHour += DeltaHours;
    
    if (CurrentTime.GameHour >= 24.0f)
    {
        CurrentTime.GameHour = FMath::Fmod(CurrentTime.GameHour, 24.0f);
        CurrentTime.DayOfYear += 1.0f;
        
        if (CurrentTime.DayOfYear > 365.0f)
        {
            CurrentTime.DayOfYear = 1.0f;
            int SeasonIndex = (int)(CurrentTime.DayOfYear / 91.25f) % 4;
            CurrentTime.CurrentSeason = (ESeason)SeasonIndex;
        }
    }
    
    UpdateTimeOfDay();
    UpdateTemperature();
}

void UWeatherSystem::UpdateTimeOfDay()
{
    if (CurrentTime.GameHour >= 0.0f && CurrentTime.GameHour < 4.0f)
        CurrentTime.TimeOfDay = ETimeOfDay::Midnight;
    else if (CurrentTime.GameHour >= 4.0f && CurrentTime.GameHour < 6.0f)
        CurrentTime.TimeOfDay = ETimeOfDay::EarlyDawn;
    else if (CurrentTime.GameHour >= 6.0f && CurrentTime.GameHour < 8.0f)
        CurrentTime.TimeOfDay = ETimeOfDay::Dawn;
    else if (CurrentTime.GameHour >= 8.0f && CurrentTime.GameHour < 10.0f)
        CurrentTime.TimeOfDay = ETimeOfDay::Morning;
    else if (CurrentTime.GameHour >= 10.0f && CurrentTime.GameHour < 14.0f)
        CurrentTime.TimeOfDay = ETimeOfDay::Noon;
    else if (CurrentTime.GameHour >= 14.0f && CurrentTime.GameHour < 17.0f)
        CurrentTime.TimeOfDay = ETimeOfDay::Afternoon;
    else if (CurrentTime.GameHour >= 17.0f && CurrentTime.GameHour < 19.0f)
        CurrentTime.TimeOfDay = ETimeOfDay::Evening;
    else if (CurrentTime.GameHour >= 19.0f && CurrentTime.GameHour < 21.0f)
        CurrentTime.TimeOfDay = ETimeOfDay::Dusk;
    else
        CurrentTime.TimeOfDay = ETimeOfDay::Night;
}

void UWeatherSystem::UpdateTemperature()
{
    FSeasonData SeasonInfo = GetSeasonData(CurrentTime.CurrentSeason);
    
    float BaseTemp = 15.0f + SeasonInfo.TemperatureOffset;
    float DayVariation = 0.0f;
    
    if (CurrentTime.GameHour >= 6.0f && CurrentTime.GameHour < 18.0f)
    {
        DayVariation = FMath::Sin((CurrentTime.GameHour - 6.0f) / 12.0f * 3.14159f) * 8.0f;
    }
    else if (CurrentTime.GameHour >= 18.0f || CurrentTime.GameHour < 6.0f)
    {
        DayVariation = -FMath::Sin((CurrentTime.GameHour < 6.0f ? CurrentTime.GameHour + 18.0f : CurrentTime.GameHour - 18.0f) / 12.0f * 3.14159f) * 4.0f;
    }
    
    switch (CurrentWeather)
    {
        case EWeatherType::Clear: case EWeatherType::Cloudy:
            break;
        case EWeatherType::Snow: case EWeatherType::HeavySnow: case EWeatherType::Blizard:
            BaseTemp -= 10.0f;
            break;
        case EWeatherType::HeatWave:
            BaseTemp += 15.0f;
            break;
        case EWeatherType::Rain: case EWeatherType::HeavyRain: case EWeatherType::Storm: case EWeatherType::Thunderstorm:
            BaseTemp -= 3.0f;
            break;
        case EWeatherType::Hail: case EWeatherType::Sleet:
            BaseTemp -= 5.0f;
            break;
        default:
            break;
    }
    
    TemperatureCache = BaseTemp + DayVariation;
}

FTimeData UWeatherSystem::GetTimeData()
{
    return CurrentTime;
}

void UWeatherSystem::SetTime(float GameHour, float DayOfYear)
{
    CurrentTime.GameHour = GameHour;
    CurrentTime.DayOfYear = DayOfYear;
    UpdateTimeOfDay();
    UpdateTemperature();
}

void UWeatherSystem::SetSeason(ESeason Season)
{
    CurrentTime.CurrentSeason = Season;
}

FSeasonData UWeatherSystem::GetSeasonData(ESeason Season)
{
    FSeasonData Data;
    Data.Season = Season;
    
    switch (Season)
    {
        case ESeason::Spring:
            Data.TemperatureOffset = 5.0f;
            Data.DayLength = 14.0f;
            Data.NightLength = 10.0f;
            Data.CommonWeather = { EWeatherType::Clear, EWeatherType::Cloudy, EWeatherType::Rain };
            Data.AmbientLight = FLinearColor(0.4f, 0.5f, 0.5f, 1.0f);
            Data.SkyColor = FLinearColor(0.5f, 0.7f, 0.9f, 1.0f);
            Data.SunLight = FLinearColor(1.0f, 0.95f, 0.8f, 1.0f);
            break;
        case ESeason::Summer:
            Data.TemperatureOffset = 10.0f;
            Data.DayLength = 16.0f;
            Data.NightLength = 8.0f;
            Data.CommonWeather = { EWeatherType::Clear, EWeatherType::Cloudy, EWeatherType::HeatWave };
            Data.AmbientLight = FLinearColor(0.5f, 0.55f, 0.5f, 1.0f);
            Data.SkyColor = FLinearColor(0.4f, 0.6f, 0.9f, 1.0f);
            Data.SunLight = FLinearColor(1.0f, 1.0f, 0.9f, 1.0f);
            break;
        case ESeason::Autumn:
            Data.TemperatureOffset = 0.0f;
            Data.DayLength = 12.0f;
            Data.NightLength = 12.0f;
            Data.CommonWeather = { EWeatherType::Clear, EWeatherType::Cloudy, EWeatherType::Rain, EWeatherType::Fog };
            Data.AmbientLight = FLinearColor(0.35f, 0.3f, 0.3f, 1.0f);
            Data.SkyColor = FLinearColor(0.7f, 0.5f, 0.4f, 1.0f);
            Data.SunLight = FLinearColor(1.0f, 0.7f, 0.5f, 1.0f);
            break;
        case ESeason::Winter:
            Data.TemperatureOffset = -10.0f;
            Data.DayLength = 8.0f;
            Data.NightLength = 16.0f;
            Data.CommonWeather = { EWeatherType::Clear, EWeatherType::Snow, EWeatherType::HeavySnow, EWeatherType::Blizard };
            Data.AmbientLight = FLinearColor(0.3f, 0.35f, 0.45f, 1.0f);
            Data.SkyColor = FLinearColor(0.7f, 0.75f, 0.85f, 1.0f);
            Data.SunLight = FLinearColor(0.9f, 0.95f, 1.0f, 1.0f);
            break;
    }
    
    return Data;
}

FWindData UWeatherSystem::GetWindData()
{
    return CurrentWind;
}

void UWeatherSystem::UpdateWind(EWindStrength Strength, FVector2D Direction)
{
    CurrentWind.Strength = Strength;
    CurrentWind.Direction = Direction;
    
    switch (Strength)
    {
        case EWindStrength::Calm:
            CurrentWind.Speed = 0.0f; CurrentWind.GustStrength = 0.0f; break;
        case EWindStrength::Light:
            CurrentWind.Speed = 5.0f; CurrentWind.GustStrength = 2.0f; break;
        case EWindStrength::Moderate:
            CurrentWind.Speed = 15.0f; CurrentWind.GustStrength = 5.0f; break;
        case EWindStrength::Strong:
            CurrentWind.Speed = 30.0f; CurrentWind.GustStrength = 10.0f; break;
        case EWindStrength::Gale:
            CurrentWind.Speed = 50.0f; CurrentWind.GustStrength = 20.0f; break;
        case EWindStrength::Storm:
            CurrentWind.Speed = 80.0f; CurrentWind.GustStrength = 35.0f; break;
    }
}

float UWeatherSystem::GetTemperature()
{
    return TemperatureCache;
}

float UWeatherSystem::GetVisibilityRange()
{
    float BaseVisibility = 5000.0f;
    
    switch (CurrentWeather)
    {
        case EWeatherType::Clear:
            BaseVisibility = 5000.0f; break;
        case EWeatherType::Cloudy:
            BaseVisibility = 4000.0f; break;
        case EWeatherType::Rain: case EWeatherType::HeavyRain:
            BaseVisibility = 3000.0f; break;
        case EWeatherType::Storm: case EWeatherType::Thunderstorm:
            BaseVisibility = 1500.0f; break;
        case EWeatherType::Snow: case EWeatherType::HeavySnow:
            BaseVisibility = 2000.0f; break;
        case EWeatherType::Blizard:
            BaseVisibility = 500.0f; break;
        case EWeatherType::Fog: case EWeatherType::DenseFog:
            BaseVisibility = 200.0f; break;
        case EWeatherType::HeatWave:
            BaseVisibility = 4500.0f; break;
        case EWeatherType::Hail: case EWeatherType::Sleet:
            BaseVisibility = 2500.0f; break;
        case EWeatherType::Sandstorm:
            BaseVisibility = 800.0f; break;
        default:
            BaseVisibility = 5000.0f; break;
    }
    
    switch (CurrentTime.TimeOfDay)
    {
        case ETimeOfDay::Night: case ETimeOfDay::Midnight:
            BaseVisibility *= 0.8f;
            break;
        case ETimeOfDay::EarlyDawn: case ETimeOfDay::Dawn: case ETimeOfDay::Dusk:
            BaseVisibility *= 0.9f;
            break;
        default:
            break;
    }
    
    return BaseVisibility;
}

float UWeatherSystem::GetPlayerMovementMod()
{
    float Mod = 1.0f;
    
    switch (CurrentWind.Strength)
    {
        case EWindStrength::Strong:
            Mod -= 0.15f; break;
        case EWindStrength::Gale:
            Mod -= 0.30f; break;
        case EWindStrength::Storm:
            Mod -= 0.50f; break;
        default:
            break;
    }
    
    switch (CurrentWeather)
    {
        case EWeatherType::Snow: case EWeatherType::HeavySnow:
            Mod -= 0.20f; break;
        case EWeatherType::Blizard:
            Mod -= 0.60f; break;
        case EWeatherType::HeatWave:
            Mod -= 0.25f; break;
        case EWeatherType::Thunderstorm:
            Mod -= 0.10f; break;
        default:
            break;
    }
    
    if (!IsDaytime())
    {
        Mod -= 0.10f;
    }
    
    return FMath::Max(0.1f, Mod);
}

float UWeatherSystem::GetCropGrowthMod()
{
    float Mod = 1.0f;
    
    switch (CurrentTime.CurrentSeason)
    {
        case ESeason::Spring:
            Mod = 1.2f; break;
        case ESeason::Summer:
            Mod = 1.5f; break;
        case ESeason::Autumn:
            Mod = 1.0f; break;
        case ESeason::Winter:
            Mod = 0.1f; break;
    }
    
    switch (CurrentWeather)
    {
        case EWeatherType::Rain: case EWeatherType::HeavyRain:
            Mod *= 1.3f; break;
        case EWeatherType::HeatWave:
            Mod *= 0.5f; break;
        case EWeatherType::Snow: case EWeatherType::HeavySnow:
            Mod *= 0.0f; break;
        case EWeatherType::Storm: case EWeatherType::Thunderstorm:
            Mod *= 0.7f; break;
        default:
            break;
    }
    
    return Mod;
}

bool UWeatherSystem::IsDaytime()
{
    return CurrentTime.TimeOfDay >= ETimeOfDay::Dawn && CurrentTime.TimeOfDay <= ETimeOfDay::Evening;
}

bool UWeatherSystem::IsPlayerVisible()
{
    return GetVisibilityRange() > 500.0f;
}

void UWeatherSystem::TickWeather(float DeltaTime)
{
    WeatherTransition += DeltaTime;
    
    if (WeatherTransition > 300.0f)
    {
        FSeasonData SeasonInfo = GetSeasonData(CurrentTime.CurrentSeason);
        
        float RandomWeather = FMath::FRand();
        
        if (CurrentWeather == EWeatherType::Clear && RandomWeather > 0.7f)
        {
            if (SeasonInfo.CommonWeather.Num() > 0)
            {
                int32 WeatherIndex = FMath::RandRange(0, SeasonInfo.CommonWeather.Num() - 1);
                UpdateWeather(SeasonInfo.CommonWeather[WeatherIndex]);
            }
        }
        else if (CurrentWeather != EWeatherType::Clear && RandomWeather > 0.8f)
        {
            UpdateWeather(EWeatherType::Clear);
        }
        
        WeatherTransition = 0.0f;
    }
    
    if (CurrentWind.Strength == EWindStrength::Calm && FMath::FRand() > 0.95f)
    {
        EWindStrength NewStrength = (EWindStrength)FMath::RandRange(0, 5);
        float WindDir = FMath::FRand() * 360.0f;
        FVector2D Direction = FVector2D(FMath::Cos(WindDir), FMath::Sin(WindDir));
        UpdateWind(NewStrength, Direction);
    }
    
    AdvanceTime(DeltaTime / 3600.0f);
}
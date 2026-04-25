#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Weather.generated.h"

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
    None          UMETA(DisplayName = "None"),
    Clear         UMETA(DisplayName = "Clear"),
    Cloudy        UMETA(DisplayName = "Cloudy"),
    Rain          UMETA(DisplayName = "Rain"),
    HeavyRain     UMETA(DisplayName = "Heavy Rain"),
    Storm         UMETA(DisplayName = "Storm"),
    Thunderstorm  UMETA(DisplayName = "Thunderstorm"),
    Snow          UMETA(DisplayName = "Snow"),
    HeavySnow     UMETA(DisplayName = "Heavy Snow"),
    Blizard       UMETA(DisplayName = "Blizzard"),
    Fog           UMETA(DisplayName = "Fog"),
    DenseFog      UMETA(DisplayName = "Dense Fog"),
    HeatWave      UMETA(DisplayName = "Heat Wave"),
    Hail          UMETA(DisplayName = "Hail"),
    Sleet         UMETA(DisplayName = "Sleet"),
    Sandstorm     UMETA(DisplayName = "Sandstorm")
};

UENUM(BlueprintType)
enum class EWeatherSeason : uint8
{
    Spring        UMETA(DisplayName = "Spring"),
    Summer        UMETA(DisplayName = "Summer"),
    Autumn        UMETA(DisplayName = "Autumn"),
    Winter        UMETA(DisplayName = "Winter")
};

UENUM(BlueprintType)
enum class ETimeOfDay : uint8
{
    Midnight  UMETA(DisplayName = "Midnight"),
    EarlyDawn UMETA(DisplayName = "Early Dawn"),
    Dawn      UMETA(DisplayName = "Dawn"),
    Morning   UMETA(DisplayName = "Morning"),
    Noon      UMETA(DisplayName = "Noon"),
    Afternoon UMETA(DisplayName = "Afternoon"),
    Evening   UMETA(DisplayName = "Evening"),
    Dusk      UMETA(DisplayName = "Dusk"),
    Night     UMETA(DisplayName = "Night")
};

UENUM(BlueprintType)
enum class EWindStrength : uint8
{
    Calm       UMETA(DisplayName = "Calm"),
    Light      UMETA(DisplayName = "Light"),
    Moderate   UMETA(DisplayName = "Moderate"),
    Strong     UMETA(DisplayName = "Strong"),
    Severe     UMETA(DisplayName = "Severe"),
    Hurricane  UMETA(DisplayName = "Hurricane")
};

UENUM(BlueprintType)
enum class EWindSpeed : uint8
{
    Calm       UMETA(DisplayName = "Calm"),
    Light      UMETA(DisplayName = "Light"),
    Moderate   UMETA(DisplayName = "Moderate"),
    Strong     UMETA(DisplayName = "Strong"),
    Gale       UMETA(DisplayName = "Gale"),
    Storm      UMETA(DisplayName = "Storm")
};

USTRUCT(BlueprintType)
struct FWeatherData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName WeatherID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWeatherType WeatherType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TemperatureMod = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Visibility = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MovementSpeedMod = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VisibilityRange = 5000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CropGrowthMod = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ResourceSpawnMod = 1.0f;
};

USTRUCT(BlueprintType)
struct FTimeData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GameHour = 6.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DayOfYear = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETimeOfDay TimeOfDay = ETimeOfDay::Morning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESeason CurrentSeason = ESeason::Spring;

    float GetSunAngle() const { return FMath::Sin((GameHour - 6.0f) * 15.0f) * 90.0f; }
};

USTRUCT(BlueprintType)
struct FWindData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWindStrength Strength = EWindStrength::Calm;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D Direction = FVector2D(1.0f, 0.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Speed = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GustStrength = 0.0f;
};

USTRUCT(BlueprintType)
struct FSeasonData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESeason Season;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TemperatureOffset = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DayLength = 24.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float NightLength = 12.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<EWeatherType> CommonWeather;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor AmbientLight = FLinearColor(0.5f, 0.5f, 0.5f, 1.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor SkyColor = FLinearColor(0.6f, 0.7f, 0.9f, 1.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor SunLight = FLinearColor(1.0f, 0.95f, 0.8f, 1.0f);
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UWeatherSystem : public UObject
{
    GENERATED_BODY()

public:
    UWeatherSystem();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static FWeatherData GetWeatherData(FName WeatherID);

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static void UpdateWeather(EWeatherType NewWeather);

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static TArray<FWeatherData> GetAllWeatherTypes();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static void AdvanceTime(float DeltaHours);

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static FTimeData GetTimeData();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static void SetTime(float GameHour, float DayOfYear);

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static void SetSeason(ESeason Season);

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static FSeasonData GetSeasonData(ESeason Season);

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static FWindData GetWindData();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static void UpdateWind(EWindStrength Strength, FVector2D Direction);

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static float GetTemperature();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static float GetVisibilityRange();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static float GetPlayerMovementMod();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static float GetCropGrowthMod();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static bool IsDaytime();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static bool IsPlayerVisible();

    UFUNCTION(BlueprintCallable, Category = "Weather")
    static void TickWeather(float DeltaTime);

private:
    static FTimeData CurrentTime;
    static EWeatherType CurrentWeather;
    static FWindData CurrentWind;
    static float TemperatureCache;
    static float WeatherTransition;
};
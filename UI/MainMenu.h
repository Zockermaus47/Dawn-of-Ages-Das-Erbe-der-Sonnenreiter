#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MainMenu.generated.h"

UENUM(BlueprintType)
enum class EMenuState : uint8
{
    MainMenu           UMETA(DisplayName = "Main Menu"),
    NewGame            UMETA(DisplayName = "New Game"),
    Continue           UMETA(DisplayName = "Continue"),
    Settings           UMETA(DisplayName = "Settings"),
    AudioSettings      UMETA(DisplayName = "Audio Settings"),
    VideoSettings     UMETA(DisplayName = "Video Settings"),
    GraphicsSettings  UMETA(DisplayName = "Graphics Settings"),
    GameSettings       UMETA(DisplayName = "Game Settings"),
    ControlsSettings   UMETA(DisplayName = "Controls Settings"),
    Credits            UMETA(DisplayName = "Credits"),
    Quit               UMETA(DisplayName = "Quit")
};

UENUM(BlueprintType)
enum class EGameDifficulty : uint8
{
    Story        UMETA(DisplayName = "Story"),
    Normal       UMETA(DisplayName = "Normal"),
    Hard         UMETA(DisplayName = "Hard"),
    Nightmare    UMETA(DisplayName = "Nightmare")
};

UENUM(BlueprintType)
enum class EGameWindowMode : uint8
{
    Fullscreen           UMETA(DisplayName = "Vollbild"),
    Borderless           UMETA(DisplayName = "Randlos"),
    Windowed             UMETA(DisplayName = "Fenstermodus")
};

UENUM(BlueprintType)
enum class EQualityPreset : uint8
{
    Low         UMETA(DisplayName = "Niedrig"),
    Medium      UMETA(DisplayName = "Mittel"),
    High        UMETA(DisplayName = "Hoch"),
    Epic        UMETA(DisplayName = "Episch"),
    Custom      UMETA(DisplayName = "Benutzerdefiniert")
};

UENUM(BlueprintType)
enum class EAntiAliasingMode : uint8
{
    Off         UMETA(DisplayName = "Aus"),
    FXAA        UMETA(DisplayName = "FXAA"),
    TAA         UMETA(DisplayName = "TAA"),
    MSAA        UMETA(DisplayName = "MSAA"),
    DLSS        UMETA(DisplayName = "DLSS"),
    FSR        UMETA(DisplayName = "FSR")
};

UENUM(BlueprintType)
enum class EVSyncMode : uint8
{
    Off         UMETA(DisplayName = "Aus"),
    On          UMETA(DisplayName = "An"),
    Adaptive    UMETA(DisplayName = "Adaptiv")
};

USTRUCT(BlueprintType)
struct FSoundSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MasterVolume = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MusicVolume = 0.8f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SFXVolume = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VoiceVolume = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AmbientVolume = 0.7f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bMuteAudio = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bSubtitlesEnabled = true;
};

USTRUCT(BlueprintType)
struct FVideoSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ResolutionX = 1920;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ResolutionY = 1080;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGameWindowMode WindowMode = EGameWindowMode::Fullscreen;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQualityPreset QualityPreset = EQualityPreset::High;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EVSyncMode VSyncMode = EVSyncMode::On;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FieldOfView = 90.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ViewDistanceScale = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ShadowQuality = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TextureQuality = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 EffectsQuality = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PostProcessQuality = 2;
};

USTRUCT(BlueprintType)
struct FGraphicsSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bMotionBlur = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MotionBlurStrength = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bBloom = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BloomIntensity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAmbientOcclusion = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AmbientOcclusionIntensity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bDepthOfField = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bLensFlares = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bLightShafts = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bDynamicSharpen = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SharpenIntensity = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bChromaticAberration = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bVignette = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bFilmGrain = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEyeAdaptation = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAntiAliasingMode AntiAliasingMode = EAntiAliasingMode::TAA;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AntiAliasingQuality = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bDLSSEnabled = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bFSREnabled = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FSRSharpness = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bRayTracing = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RayTracingQuality = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bGlobalIllumination = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ViewDistance = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ShadowCache = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bFoliageLOD = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bLumenGlobalIllumination = false;
};

USTRUCT(BlueprintType)
struct FControlSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MouseSensitivityX = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MouseSensitivityY = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bInvertMouseX = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bInvertMouseY = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bInvertController = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ControllerSensitivity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bToggleSprint = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bToggleCrouch = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bToggleAim = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MouseAcceleration = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bRawInput = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DeadZone = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bVibration = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VibrationIntensity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAimAssist = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AimAssistStrength = 0.5f;
};

USTRUCT(BlueprintType)
struct FGameSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGameDifficulty Difficulty = EGameDifficulty::Normal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bShowDamageNumbers = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bShowTutorials = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAutoLoot = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCameraShake = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bVibration = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MouseSensitivity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bInvertMouse = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bToggleSprint = false;
};

USTRUCT(BlueprintType)
struct FSaveGameData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SaveID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText SaveName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PlayerLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText CurrentLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PlayTimeMinutes = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Act = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDateTime SavedAt;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UMainMenuSystem : public UObject
{
    GENERATED_BODY()

public:
    UMainMenuSystem();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    static void OpenMainMenu();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    static void StartNewGame(EGameDifficulty Difficulty);

    UFUNCTION(BlueprintCallable, Category = "Menu")
    static void ContinueGame(FName SaveID);

    UFUNCTION(BlueprintCallable, Category = "Menu")
    static void SaveGame(FName SaveName);

    UFUNCTION(BlueprintCallable, Category = "Menu")
    static void LoadGame(FName SaveID);

    UFUNCTION(BlueprintCallable, Category = "Menu")
    static TArray<FSaveGameData> GetSaveGames();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    static void DeleteSave(FName SaveID);

    UFUNCTION(BlueprintCallable, Category = "Menu")
    static void QuitGame();

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static FSoundSettings GetAudioSettings();

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static void SetAudioSettings(FSoundSettings Settings);

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static void SetMasterVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static void SetMusicVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static void SetSFXVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static FVideoSettings GetVideoSettings();

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static void SetVideoSettings(FVideoSettings Settings);

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static void SetFullscreen(bool bFullscreen);

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static void SetResolution(int32 X, int32 Y);

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static FGameSettings GetGameSettings();

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static void SetGameSettings(FGameSettings Settings);

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static void SetDifficulty(EGameDifficulty Difficulty);

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static void SaveSettings();

    UFUNCTION(BlueprintCallable, Category = "Settings")
    static void LoadSettings();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    static void ShowCredits();

    UFUNCTION(BlueprintCallable, Category = "Menu")
    static bool HasExistingSave();
};
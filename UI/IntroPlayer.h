#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "IntroPlayer.generated.h"

UENUM(BlueprintType)
enum class EIntroStage : uint8
{
    Logo        UMETA(DisplayName = "Logo"),
    Prologue    UMETA(DisplayName = "Prologue"),
    Act1        UMETA(DisplayName = "Act 1"),
    Act2        UMETA(DisplayName = "Act 2"),
    Act3        UMETA(DisplayName = "Act 3"),
    Ending      UMETA(DisplayName = "Ending"),
    MainMenu    UMETA(DisplayName = "Main Menu")
};

UENUM(BlueprintType)
enum class EVoiceGender : uint8
{
    Male        UMETA(DisplayName = "Male"),
    Female      UMETA(DisplayName = "Female"),
    Narrator    UMETA(DisplayName = "Narrator")
};

USTRUCT(BlueprintType)
struct FIntroScene : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SceneID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText SceneTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText GermanText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText EnglishText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EVoiceGender SpeakerGender;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText SpeakerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName VideoAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BackgroundMusic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TextFadeIn = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TextFadeOut = 1.0f;
};

USTRUCT(BlueprintType)
struct FIntroSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bSkipEnabled = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TextSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MusicVolume = 0.8f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VoiceVolume = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bSubtitlesEnabled = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Language = "German";
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UIntroPlayer : public UObject
{
    GENERATED_BODY()

public:
    UIntroPlayer();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void StartIntro();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void SkipIntro();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void PauseIntro();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void ResumeIntro();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void NextScene();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void PreviousScene();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static FIntroScene GetCurrentScene();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static int32 GetCurrentSceneIndex();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static int32 GetTotalScenes();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static float GetProgress();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static EIntroPhase GetCurrentPhase();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void SetLanguage(FString Language);

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static FText GetCurrentSubtitle();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void TickIntro(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static bool IsIntroFinished();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void PlayVoiceOver(EVoiceGender Gender, FName AudioAsset);

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void StopVoiceOver();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void SetSettings(FIntroSettings NewSettings);

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static FIntroSettings GetSettings();

private:
    static TArray<FIntroScene> Scenes;
    static int32 CurrentSceneIndex;
    static float CurrentTime;
    static bool bIsPlaying;
    static bool bIsPaused;
    static EIntroPhase CurrentPhase;
    static FIntroSettings Settings;
    static FString CurrentLanguage;
    static bool bFinished;

    static void LoadIntroData();
    static void CalculatePhase();
    static void OnSceneChanged();
};
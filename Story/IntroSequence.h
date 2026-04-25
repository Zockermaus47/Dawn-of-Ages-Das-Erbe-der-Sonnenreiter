#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IntroSequence.generated.h"

UENUM(BlueprintType)
enum class EIntroPhase : uint8
{
    None              UMETA(DisplayName = "None"),
    Prologue        UMETA(DisplayName = "Prolog"),
    Awakening       UMETA(DisplayName = "Erwachen"),
    FirstHunger      UMETA(DisplayName = "Erster Hunger"),
    FlackeringWorld  UMETA(DisplayName = "Flackernde Welt"),
    HandMessage     UMETA(DisplayName = "Die Nachricht"),
    Act1Begin       UMETA(DisplayName = "Akt I Beginnt")
};

USTRUCT(BlueprintType)
struct FIntroLine
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Speaker;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Line;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration = 3.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsNarration = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bShowSpeaker = true;
};

USTRUCT(BlueprintType)
struct FIntroScreen
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Subtitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration = 4.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor TextColor = FLinearColor::White;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor BackgroundColor = FLinearColor::Black;
};

USTRUCT(BlueprintType)
struct FIntroSection
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EIntroPhase Phase;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FIntroScreen> Screens;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FIntroLine> Dialogs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasWhiteFlash = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WhiteFlashDuration = 0.5f;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UIntroSequence : public UObject
{
    GENERATED_BODY()

public:
    UIntroSequence();

    static TArray<FIntroSection> GetFullIntro();

    static FIntroSection GetPrologue();

    static FIntroSection GetAwakening();

    static FIntroSection GetFirstHunger();

    static FIntroSection GetFlackeringWorld();

    static FIntroSection GetHandMessage();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void StartIntro();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void SkipIntro();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static bool IsIntroComplete();

    UFUNCTION(BlueprintCallable, Category = "Intro")
    static void SetIntroComplete(bool bComplete);
};
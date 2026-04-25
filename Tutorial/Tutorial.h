#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tutorial.generated.h"

UENUM(BlueprintType)
enum class ETutorialStep : uint8
{
    NotStarted    UMETA(DisplayName = "Not Started"),
    Movement    UMETA(DisplayName = "Movement"),
    Inventory   UMETA(DisplayName = "Inventory"),
    Crafting    UMETA(DisplayName = "Crafting"),
    Harvesting  UMETA(DisplayName = "Harvesting"),
    Combat     UMETA(DisplayName = "Combat"),
    Farming    UMETA(DisplayName = "Farming"),
    Mount      UMETA(DisplayName = "Mount"),
    Magic      UMETA(DisplayName = "Magic"),
    Trading    UMETA(DisplayName = "Trading"),
    Building   UMETA(DisplayName = "Building"),
    Multiplayer UMETA(DisplayName = "Multiplayer"),
    Completed  UMETA(DisplayName = "Completed")
};

USTRUCT(BlueprintType)
struct FTutorialData
{
    GENERATED_BODY()
    FName TutorialID;
    FText Title;
    FText Description;
    FText GermanDescription;
    FText EnglishDescription;
    ETutorialStep Step;
    bool bRequired = false;
    int32 RequiredLevel = 1;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UTutorialSystem : public UObject
{
    GENERATED_BODY()
public:
    static void StartTutorial();
    static void CompleteStep(ETutorialStep Step);
    static bool CanStartStep(ETutorialStep Step);
    static ETutorialStep GetCurrentStep();
    static int32 GetCompletedSteps();
    static float GetProgress();
    static FTutorialData GetCurrentTutorial();
    static void SetSkipped(ETutorialStep Step, bool bSkipped);
    static bool IsSkipped(ETutorialStep Step);
    static void ShowHint(ETutorialStep Step);
    static bool IsTutorialComplete();
    static void ResetTutorial();
    static FText GetHintText();
private:
    static ETutorialStep CurrentStep;
    static TArray<ETutorialStep> CompletedSteps;
    static TArray<ETutorialStep> SkippedSteps;
};
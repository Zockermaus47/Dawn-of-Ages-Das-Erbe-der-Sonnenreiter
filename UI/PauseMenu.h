#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PauseMenu.generated.h"

UENUM(BlueprintType)
enum class EPauseMenuState : uint8
{
    None            UMETA(DisplayName = "None"),
    MainPause       UMETA(DisplayName = "Main Pause"),
    SaveGame        UMETA(DisplayName = "Save Game"),
    LoadGame        UMETA(DisplayName = "Load Game"),
    Settings        UMETA(DisplayName = "Settings"),
    Inventory       UMETA(DisplayName = "Inventory"),
    QuestLog        UMETA(DisplayName = "Quest Log"),
    Map             UMETA(DisplayName = "Map"),
    Character       UMETA(DisplayName = "Character"),
    Skills          UMETA(DisplayName = "Skills"),
    Journal         UMETA(DisplayName = "Journal"),
    Achievements    UMETA(DisplayName = "Achievements"),
    Crafting        UMETA(DisplayName = "Crafting"),
    Social          UMETA(DisplayName = "Social"),
    ReturnToMain    UMETA(DisplayName = "Return to Main")
};

UENUM(BlueprintType)
enum class ESaveSlot : uint8
{
    Slot1   UMETA(DisplayName = "Slot 1"),
    Slot2   UMETA(DisplayName = "Slot 2"),
    Slot3   UMETA(DisplayName = "Slot 3"),
    Slot4   UMETA(DisplayName = "Slot 4"),
    Slot5   UMETA(DisplayName = "Slot 5"),
    Slot6   UMETA(DisplayName = "Slot 6"),
    Slot7   UMETA(DisplayName = "Slot 7"),
    Slot8   UMETA(DisplayName = "Slot 8"),
    Slot9   UMETA(DisplayName = "Slot 9"),
    Slot10  UMETA(DisplayName = "Slot 10")
};

USTRUCT(BlueprintType)
struct FQuickSaveData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText PlayerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PlayerLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText CurrentBiome;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText CurrentQuest;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PlayTimeSeconds = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Gold = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HealthPercent = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ManaPercent = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Act = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDateTime SavedAt;
};

USTRUCT(BlueprintType)
struct FPauseMenuSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanSave = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanLoad = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bShowTimer = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsPaused = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GameTime = 0.0f;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UPauseMenuSystem : public UObject
{
    GENERATED_BODY()

public:
    UPauseMenuSystem();

    UFUNCTION(BlueprintCallable, Category = "Pause")
    static void OpenPauseMenu();

    UFUNCTION(BlueprintCallable, Category = "Pause")
    static void ClosePauseMenu();

    UFUNCTION(BlueprintCallable, Category = "Pause")
    static void TogglePauseMenu();

    UFUNCTION(BlueprintCallable, Category = "Pause")
    static bool IsPauseMenuOpen();

    UFUNCTION(BlueprintCallable, Category = "Pause")
    static void SetPauseMenuState(EPauseMenuState State);

    UFUNCTION(BlueprintCallable, Category = "Pause")
    static EPauseMenuState GetPauseMenuState();

    UFUNCTION(BlueprintCallable, Category = "Save")
    static void QuickSave();

    UFUNCTION(BlueprintCallable, Category = "Save")
    static void SaveToSlot(ESaveSlot Slot, FText SaveName);

    UFUNCTION(BlueprintCallable, Category = "Save")
    static bool CanSaveGame();

    UFUNCTION(BlueprintCallable, Category = "Save")
    static FQuickSaveData GetSaveData(ESaveSlot Slot);

    UFUNCTION(BlueprintCallable, Category = "Save")
    static TArray<FQuickSaveData> GetAllSaveData();

    UFUNCTION(BlueprintCallable, Category = "Save")
    static bool DeleteSave(ESaveSlot Slot);

    UFUNCTION(BlueprintCallable, Category = "Load")
    static void LoadFromSlot(ESaveSlot Slot);

    UFUNCTION(BlueprintCallable, Category = "Load")
    static bool HasSaveData(ESaveSlot Slot);

    UFUNCTION(BlueprintCallable, Category = "Pause")
    static void ReturnToMainMenu();

    UFUNCTION(BlueprintCallable, Category = "Pause")
    static void RestartFromCheckpoint();

    UFUNCTION(BlueprintCallable, Category = "Pause")
    static float GetGameTime();

    UFUNCTION(BlueprintCallable, Category = "Pause")
    static void SetGameTime(float Time);

    UFUNCTION(BlueprintCallable, Category = "Pause")
    static FText GetFormattedPlayTime();

    UFUNCTION(BlueprintCallable, Category = "Pause")
    static void ExitToDesktop();

    UFUNCTION(BlueprintCallable, Category = "Pause")
    static bool IsGameInProgress();
};
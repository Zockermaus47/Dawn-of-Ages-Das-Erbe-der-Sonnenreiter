#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "StoryIntegration.generated.h"

UENUM(BlueprintType)
enum class EStoryAct : uint8
{
    Act1_Anomalie  UMETA(DisplayName = "Akt I: Die Anomalie"),
    Act2_Begegnung UMETA(DisplayName = "Akt II: Die Begegnung"),
    Act3_Offenbarung UMETA(DisplayName = "Akt III: Die Offenbarung"),
    Endgame       UMETA(DisplayName = "Endgame"),
    Completed     UMETA(DisplayName = "Abgeschlossen")
};

UENUM(BlueprintType)
enum class EEnding : uint8
{
    None          UMETA(DisplayName = "Keines"),
    Imperfection UMETA(DisplayName = "Die Akzeptanz der Imperfektion"),
    Dissolution  UMETA(DisplayName = "Die Auflösung"),
    Reversal     UMETA(DisplayName = "Die Umkehrung"),
    Symbiosis    UMETA(DisplayName = "Die Symbiose")
};

UENUM(BlueprintType)
enum class EFragment : uint8
{
    None        UMETA(DisplayName = "Keiner"),
    Kael        UMETA(DisplayName = "Kael – Der Nihilist"),
    Lyra        UMETA(DisplayName = "Lyra – Die Suchende"),
    Theron     UMETA(DisplayName = "Theron – Der Eroberer"),
    Nyx         UMETA(DisplayName = "Nyx – Die Sterbliche"),
    Echo        UMETA(DisplayName = "Echo – Der Glitch")
};

USTRUCT(BlueprintType)
struct FMainQuest : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName QuestID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EStoryAct Act;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, int32> Objectives;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, int32> Rewards;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperienceGained = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RequiredQuest;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName NPCToTalk;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LocationID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LevelRequired = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsMainStory = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsRepeatable = false;
};

USTRUCT(BlueprintType)
struct FFragmentQuest : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName QuestID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName FragmentID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DialogStart;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DialogAccept;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DialogComplete;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, int32> Objectives;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, int32> Rewards;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEnding AssociatedEnding;
};

USTRUCT(BlueprintType)
struct FDiaryEntry : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EntryID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Content;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Author;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DayWritten;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsFromPreviousPlayer = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EStoryAct UnlockAfterAct;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LocationID;
};

USTRUCT(BlueprintType)
struct FAeonData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AeonID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Version;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 IterationCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText SpokenDialog;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> UnlockedEndings;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UStoryIntegration : public UObject
{
    GENERATED_BODY()

public:
    UStoryIntegration();

    UFUNCTION(BlueprintCallable, Category = "Story")
    static FMainQuest GetMainQuest(FName QuestID);

    UFUNCTION(BlueprintCallable, Category = "Story")
    static TArray<FMainQuest> GetQuestsByAct(EStoryAct Act);

    UFUNCTION(BlueprintCallable, Category = "Story")
    static bool StartMainQuest(FName QuestID);

    UFUNCTION(BlueprintCallable, Category = "Story")
    static bool CompleteMainQuest(FName QuestID);

    UFUNCTION(BlueprintCallable, Category = "Story")
    static EStoryAct GetCurrentAct();

    UFUNCTION(BlueprintCallable, Category = "Story")
    static void AdvanceToAct(EStoryAct NewAct);

    UFUNCTION(BlueprintCallable, Category = "Story")
    static FFragmentQuest GetFragmentQuest(FName FragmentID);

    UFUNCTION(BlueprintCallable, Category = "Story")
    static TArray<FFragmentQuest> GetFragmentQuests(EFragment Fragment);

    UFUNCTION(BlueprintCallable, Category = "Story")
    static FDiaryEntry GetDiaryEntry(FName EntryID);

    UFUNCTION(BlueprintCallable, Category = "Story")
    static TArray<FDiaryEntry> GetDiaryEntriesByLocation(FName LocationID);

    UFUNCTION(BlueprintCallable, Category = "Story")
    static TArray<FDiaryEntry> GetAllDiaryEntries();

    UFUNCTION(BlueprintCallable, Category = "Story")
    static bool UnlockEnding(EEnding Ending);

    UFUNCTION(BlueprintCallable, Category = "Story")
    static TArray<EEnding> GetUnlockedEndings();

    UFUNCTION(BlueprintCallable, Category = "Story")
    static EEnding GetCurrentEnding();

    UFUNCTION(BlueprintCallable, Category = "Story")
    static FText GetAeonDialog();

    UFUNCTION(BlueprintCallable, Category = "Story")
    static void SetAeonDialog(FText NewDialog);

    UFUNCTION(BlueprintCallable, Category = "Story")
    static bool IsEchoFound();

    UFUNCTION(BlueprintCallable, Category = "Story")
    static void SetEchoFound(bool bFound);

    UFUNCTION(BlueprintCallable, Category = "Story")
    static int32 GetIterationCount();

    UFUNCTION(BlueprintCallable, Category = "Story")
    static void IncrementIterationCount();

    UFUNCTION(BlueprintCallable, Category = "Story")
    static void SetCreatorModeEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Story")
    static bool IsCreatorModeEnabled();
};
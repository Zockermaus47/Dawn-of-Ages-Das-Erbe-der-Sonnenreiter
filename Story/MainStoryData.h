#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "MainStoryData.generated.h"

USTRUCT(BlueprintType)
struct FMainQuestData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName QuestID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Act;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText ShortDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText FullDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName NPCToMeet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LocationToGo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ObjectiveCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 XP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName NextQuest;
};

USTRUCT(BlueprintType)
struct FFragmentData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName FragmentID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText PhilosophyType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText SpawnDialog;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText QuestDialog;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText EndingOffer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LocationID;
};

USTRUCT(BlueprintType)
struct FDiaryData : public FTableRowBase
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
    int32 Act;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinPlayerLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LocationID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsGlitchEntry;
};

USTRUCT(BlueprintType)
struct FEndingData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EndingID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText GameplayEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUnlocksCreatorMode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsTrueEnding;
};
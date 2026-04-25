#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Religion.generated.h"

UENUM(BlueprintType)
enum class EGodName : uint8
{
    None        UMETA(DisplayName = "None"),
    Ares        UMETA(DisplayName = "Ares"),
    Gaia        UMETA(DisplayName = "Gaia"),
    Athena      UMETA(DisplayName = "Athena"),
    Tyche       UMETA(DisplayName = "Tyche"),
    Hades       UMETA(DisplayName = "Hades"),
    Hephaestus  UMETA(DisplayName = "Hephaestus"),
    Poseidon    UMETA(DisplayName = "Poseidon"),
    Aeon       UMETA(DisplayName = "Aeon – Der Schöpfer")
};

USTRUCT(BlueprintType)
struct FGodData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName GodID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGodName GodName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Blessings;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Rituals;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DevotionRequired = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsHidden = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsStoryGod = false;
};

USTRUCT(BlueprintType)
struct FAeonReligionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 IterationCount = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PlayerDevotion = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText LastPrayed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bKnowsTruth = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<EEnding> AcceptedEndings;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UReligionSystem : public UObject
{
    GENERATED_BODY()

public:
    UReligionSystem();

    UFUNCTION(BlueprintCallable, Category = "Religion")
    static FGodData GetGodData(FName GodID);

    UFUNCTION(BlueprintCallable, Category = "Religion")
    static void Pray(FName GodID);

    UFUNCTION(BlueprintCallable, Category = "Religion")
    static void PerformRitual(FName GodID, FName RitualID);

    UFUNCTION(BlueprintCallable, Category = "Religion")
    static TArray<FGodData> GetAllGods();

    UFUNCTION(BlueprintCallable, Category = "Religion")
    static FGodData GetAeonData();

    UFUNCTION(BlueprintCallable, Category = "Religion")
    static bool IsAeonKnown();

    UFUNCTION(BlueprintCallable, Category = "Religion")
    static void RevealAeon();

    UFUNCTION(BlueprintCallable, Category = "Religion")
    static FAeonReligionData GetAeonReligionData();
};
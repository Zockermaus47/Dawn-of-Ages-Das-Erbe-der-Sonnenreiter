#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Trophy.generated.h"

UENUM(BlueprintType)
enum class ETrophyType : uint8
{
    Beast     UMETA(DisplayName = "Beast"),
    Boss      UMETA(DisplayName = "Boss"),
    Rare     UMETA(DisplayName = "Rare"),
    Artifact UMETA(DisplayName = "Artifact"),
    Champion UMETA(DisplayName = "Champion"),
    Dragon   UMETA(DisplayName = "Dragon"),
    God      UMETA(DisplayName = "God")
};

USTRUCT(BlueprintType)
struct FTrophyData
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere) FName TrophyID;
    UPROPERTY(EditAnywhere) FText DisplayName;
    UPROPERTY(EditAnywhere) ETrophyType Type;
    UPROPERTY(EditAnywhere) int32 Rarity = 1;
    UPROPERTY(EditAnywhere) FName DropSource;
    UPROPERTY(EditAnywhere) float DropChance = 0.01f;
    UPROPERTY(EditAnywhere) int32 Points = 10;
};

USTRUCT(BlueprintType)
struct FCollectionData
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere) FName CollectionID;
    UPROPERTY(EditAnywhere) FText DisplayName;
    UPROPERTY(EditAnywhere) TArray<FName> RequiredTrophies;
    UPROPERTY(EditAnywhere) int32 TotalPoints = 0;
    UPROPERTY(EditAnywhere) bool bCompleted = false;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UTrophySystem : public UObject
{
    GENERATED_BODY()
public:
    static FTrophyData GetTrophy(FName TrophyID);
    static bool CollectTrophy(FName TrophyID);
    static TArray<FTrophyData> GetCollected();
    static TArray<FTrophyData> GetUncollected();
    static int32 GetTotalPoints();
    static int32 GetCompletionPercentage();
    static bool CompleteCollection(FName CollectionID);
    static TArray<FCollectionData> GetCollections();
    static FName GetRarestTrophy();
private:
    static TArray<FName> CollectedTrophies;
    static int32 TotalPoints;
};
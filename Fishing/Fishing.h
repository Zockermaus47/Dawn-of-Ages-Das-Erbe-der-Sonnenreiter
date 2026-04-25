#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Fishing.generated.h"

UENUM(BlueprintType)
enum class EFishType : uint8
{
    Small     UMETA(DisplayName = "Klein"),
    Medium    UMETA(DisplayName = "Mittel"),
    Large     UMETA(DisplayName = "Groß"),
    Legendary UMETA(DisplayName = "Legendär"),
    Rare      UMETA(DisplayName = "Selten")
};

UENUM(BlueprintType)
enum class EFishingZone : uint8
{
    River      UMETA(DisplayName = "Fluss"),
    Lake       UMETA(DisplayName = "See"),
    Ocean      UMETA(DisplayName = "Ozean"),
    Swamp      UMETA(DisplayName = "Sumpf"),
    Underground UMETA(DisplayName = "Unterwelt")
};

USTRUCT(BlueprintType)
struct FFishData
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName FishID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EFishType Type;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float Weight;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Value;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> BiomeIDs;
};

USTRUCT(BlueprintType)
struct FFishingSpot
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector Location;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) EFishingZone Zone;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float FishPopulation;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UFishingSystem : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable) static FFishData CatchFish(EFishingZone Zone);
    UFUNCTION(BlueprintCallable) static bool HasBait(FName BaitID);
    UFUNCTION(BlueprintCallable) static float CalculateCatchChance(FFishData Fish, float Skill);
    UFUNCTION(BlueprintCallable) static TArray<FFishData> GetFishInZone(EFishingZone Zone);
    UFUNCTION(BlueprintCallable) static int32 SellFish(FFishData Fish);
};

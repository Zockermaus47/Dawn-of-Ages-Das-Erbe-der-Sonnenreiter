#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Racing.generated.h"

UENUM(BlueprintType)
enum class ERaceType : uint8
{
    Sprint   UMETA(DisplayName = "Sprint"),
    Marathon UMETA(DisplayName = "Marathon"),
    CrossCountry UMETA(DisplayName = "Geländerennen"),
    Mount     UMETA(DisplayName = "Reitrennen")
};

USTRUCT(BlueprintType)
struct FRaceCheckpoint
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector Location;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float Radius;
};

USTRUCT(BlueprintType)
struct FRace
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName RaceID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ERaceType Type;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FRaceCheckpoint> Checkpoints;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float Distance;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 RewardGold;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> RewardItems;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API URacingSystem : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable) static FRace StartRace(FName RaceID);
    UFUNCTION(BlueprintCallable) static bool PassCheckpoint(int32 Index);
    UFUNCTION(BlueprintCallable) static float GetRaceTime();
    UFUNCTION(BlueprintCallable) static int32 GetLeaderboardPosition(FName RaceID);
};
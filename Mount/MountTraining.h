#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MountTraining.generated.h"

UENUM(BlueprintType)
enum class EMountCommand : uint8
{
    Follow      UMETA(DisplayName = "Follow"),
    Stay       UMETA(DisplayName = "Stay"),
    Charge     UMETA(DisplayName = "Charge"),
    Gallop     UMETA(DisplayName = "Gallop"),
    Trot       UMETA(DisplayName = "Trot"),
    Walk       UMETA(DisplayName = "Walk"),
    Rear       UMETA(DisplayName = "Rear"),
   gra      UMETA(DisplayName = "gra"),
    Swim       UMETA(DisplayName = "Swim"),
    Fly        UMETA(DisplayName = "Fly")
};

USTRUCT(BlueprintType)
struct FMountTrainingData
{
    GENERATED_BODY()
    EMountCommand Command;
    int32 Difficulty = 1;
    int32 TrainingPoints = 15;
    int32 RequiredBond = 30;
    float SpeedBonus = 0.0f;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UMountTrainingSystem : public UObject
{
    GENERATED_BODY()
public:
    static bool TrainCommand(EMountCommand Command);
    static void AddTrainingPoints(int32 Amount);
    static int32 GetTrainingPoints();
    static TArray<EMountCommand> GetKnownCommands();
    static void IncreaseBond(int32 Amount);
    static int32 GetBond();
    static void SetTamed(bool bTamed);
    static bool IsTamed();
    static void Mount();
    static void Dismount();
    static bool IsMounted();
};
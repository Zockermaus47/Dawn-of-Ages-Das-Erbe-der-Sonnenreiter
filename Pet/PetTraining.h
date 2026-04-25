#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PetTraining.generated.h"

UENUM(BlueprintType)
enum class EPetTrick : uint8
{
    Sit         UMETA(DisplayName = "Sit"),
    Stay       UMETA(DisplayName = "Stay"),
    Come       UMETA(DisplayName = "Come"),
    Heel       UMETA(DisplayName = "Heel"),
    Fetch      UMETA(DisplayName = "Fetch"),
    Guard      UMETA(DisplayName = "Guard"),
    Hunt       UMETA(DisplayName = "Hunt"),
    Track      UMETA(DisplayName = "Track"),
    Attack     UMETA(DisplayName = "Attack"),
    Rescue     UMETA(DisplayName = "Rescue")
};

USTRUCT(BlueprintType)
struct FPetTrickData
{
    GENERATED_BODY()
    EPetTrick Trick;
    int32 Difficulty = 1;
    int32 TrainingPoints = 10;
    int32 RequiredBond = 50;
    float SuccessChance = 0.5f;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UPetTrainingSystem : public UObject
{
    GENERATED_BODY()
public:
    static bool TrainTrick(EPetTrick Trick, int32 PlayerSkill);
    static void AddTrainingPoints(int32 Amount);
    static int32 GetTrainingPoints();
    static TArray<EPetTrick> GetKnownTricks();
    static bool CanLearnTrick(EPetTrick Trick);
    static void IncreaseBond(int32 Amount);
    static int32 GetBond();
    static float GetLoyalty();
    static void SetAggressive(bool bAggressive);
    static bool IsAggressive();
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillMastery.generated.h"

UENUM(BlueprintType)
enum class ESkillCategory : uint8
{
    Combat   UMETA(DisplayName = "Kampf"),
    Crafting UMETA(DisplayName = "Handwerk"),
    Gathering UMETA(DisplayName = "Sammeln"),
    Survival UMETA(DisplayName = "Überleben")
};

USTRUCT(BlueprintType)
struct FMasteryLevel
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ESkillCategory Category;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName SkillName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Level;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 XP;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API USkillMasterySystem : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable) static bool AddXP(FName SkillName, int32 Amount);
    UFUNCTION(BlueprintCallable) static int32 GetLevel(FName SkillName);
    UFUNCTION(BlueprintCallable) static float GetMasteryBonus(FName SkillName);
};
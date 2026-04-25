#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Achievement.generated.h"

USTRUCT(BlueprintType)
struct FAchievementData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AchievementID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Points = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Rewards;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsSecret = false;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UAchievementSystem : public UObject
{
    GENERATED_BODY()

public:
    UAchievementSystem();

    UFUNCTION(BlueprintCallable, Category = "Achievement")
    static FAchievementData GetAchievementData(FName AchievementID);

    UFUNCTION(BlueprintCallable, Category = "Achievement")
    static bool UnlockAchievement(FName AchievementID);

    UFUNCTION(BlueprintCallable, Category = "Achievement")
    static TArray<FAchievementData> GetAllAchievements();
};
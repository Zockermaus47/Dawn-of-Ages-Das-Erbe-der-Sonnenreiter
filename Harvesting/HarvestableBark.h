#pragma once

#include "CoreMinimal.h"
#include "Harvesting/HarvestableObject.h"
#include "HarvestableBark.generated.h"

UCLASS()
class STEFFIS_DAWNOFAGES_API AHarvestableBark : public AHarvestableObject
{
    GENERATED_BODY()

public:
    AHarvestableBark();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bark")
    bool bFromLivingTree = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bark")
    float RegrowthTime = 600.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bark")
    float BarkAmount = 2.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Bark")
    bool bIsDepleted = false;

    virtual void OnHit(AActor* Attacker, float Damage, FName ToolType) override;

    UFUNCTION(BlueprintCallable, Category = "Bark")
    void HarvestBark();

    UFUNCTION(BlueprintCallable, Category = "Bark")
    void StartRegrowth();

protected:
    FTimerHandle RegrowthTimer;

    UFUNCTION()
    void CompleteRegrowth();
};

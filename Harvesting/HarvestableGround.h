#pragma once

#include "CoreMinimal.h"
#include "Harvesting/HarvestableObject.h"
#include "HarvestableGround.generated.h"

UENUM(BlueprintType)
enum class EGroundType : uint8
{
    Clay UMETA(DisplayName = "Lehm"),
    Sand UMETA(DisplayName = "Sand"),
    Gravel UMETA(DisplayName = "Kies"),
    Dirt UMETA(DisplayName = "Erde"),
    ClayDeposit UMETA(DisplayName = "Lehmgrube")
};

UCLASS()
class STEFFIS_DAWNOFAGES_API AHarvestableGround : public AHarvestableObject
{
    GENERATED_BODY()

public:
    AHarvestableGround();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground")
    EGroundType GroundType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground")
    float DepletionRate = 0.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground")
    float RegenerationTime = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground")
    bool bCanRegenerate = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground")
    int32 MaxHarvests = 10;

    UPROPERTY(BlueprintReadOnly, Category = "Ground")
    int32 CurrentHarvests = 0;

    virtual void OnHit(AActor* Attacker, float Damage, FName ToolType) override;

    UFUNCTION(BlueprintCallable, Category = "Ground")
    void Harvest();

    UFUNCTION(BlueprintCallable, Category = "Ground")
    void StartRegeneration();

    UFUNCTION(BlueprintCallable, Category = "Ground")
    bool IsDepleted() const;

protected:
    FTimerHandle RegenerationTimer;
    
    UFUNCTION()
    void Regenerate();

    void SetupResourceDrops();
};

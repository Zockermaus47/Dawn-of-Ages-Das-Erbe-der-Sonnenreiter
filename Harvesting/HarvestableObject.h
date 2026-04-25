#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ResourceTypes.h"
#include "HarvestableObject.generated.h"

UCLASS()
class STEFFIS_DAWNOFAGES_API AHarvestableObject : public AActor
{
    GENERATED_BODY()
    
public:    
    AHarvestableObject();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* InteractionBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvesting")
    float MaxHealth = 100.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Harvesting")
    float CurrentHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvesting")
    EHarvestStage CurrentStage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvesting")
    TArray<FResourceDrop> ResourceDrops;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvesting")
    FName RequiredToolType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvesting")
    float DamagePerHit = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Harvesting")
    EEpoch AvailableEpoch = EEpoch::StoneAge;

    UFUNCTION(BlueprintCallable, Category = "Harvesting")
    virtual void OnHit(AActor* Attacker, float Damage, FName ToolType);

    UFUNCTION(BlueprintPure, Category = "Harvesting")
    bool IsCorrectTool(FName ToolType) const;

    UFUNCTION(BlueprintCallable, Category = "Harvesting")
    void UpdateHarvestStage();

    UFUNCTION(BlueprintCallable, Category = "Harvesting")
    virtual void SpawnResources();

    UFUNCTION(BlueprintNativeEvent, Category = "Harvesting")
    void PlayHitEffect();

    UFUNCTION(BlueprintNativeEvent, Category = "Harvesting")
    void OnDestroyed();

protected:
    FTimerHandle ShakeTimerHandle;
    
    UFUNCTION()
    void StopShaking();

    int32 CalculateDropAmount(const FResourceDrop& Drop) const;
};

#pragma once

#include "CoreMinimal.h"
#include "Harvesting/HarvestableObject.h"
#include "HarvestableTree.generated.h"

UENUM(BlueprintType)
enum class ETreeState : uint8
{
    Standing UMETA(DisplayName = "Stehend"),
    Falling UMETA(DisplayName = "Fällt"),
    Fallen UMETA(DisplayName = "Gefallen"),
    LogOnly UMETA(DisplayName = "Nur Stamm"),
    Harvested UMETA(DisplayName = "Geerntet")
};

UENUM(BlueprintType)
enum class ETreeType : uint8
{
    Oak UMETA(DisplayName = "Eiche"),
    Birch UMETA(DisplayName = "Birche"),
    Pine UMETA(DisplayName = "Kiefer")
};

UCLASS()
class STEFFIS_DAWNOFAGES_API AHarvestableTree : public AHarvestableObject
{
    GENERATED_BODY()

public:
    AHarvestableTree();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree")
    ETreeState TreeState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree")
    ETreeType TreeType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree")
    UStaticMeshComponent* TrunkMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree")
    UStaticMeshComponent* BranchesMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree")
    float FallDuration = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree")
    int32 BranchCount = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree")
    TSubclassOf<AActor> BranchActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree")
    TSubclassOf<AActor> StickActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree")
    float WoodAmount = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree")
    float StickAmount = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tree")
    float BarkAmount = 3.0f;

    virtual void OnDestroyed_Implementation() override;

    UFUNCTION(BlueprintCallable, Category = "Tree")
    void StartFalling();

    UFUNCTION(BlueprintCallable, Category = "Tree")
    void RemoveBranches();

    UFUNCTION(BlueprintCallable, Category = "Tree")
    void SplitLog();

    UFUNCTION(BlueprintCallable, Category = "Tree")
    bool CanRemoveBranches() const;

    UFUNCTION(BlueprintCallable, Category = "Tree")
    bool CanSplitLog() const;

private:
    FTimerHandle FallTimerHandle;
    
    UFUNCTION()
    void CompleteFall();

    void SetupResourceDrops();
};

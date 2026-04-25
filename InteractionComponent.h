#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class IInteractable;

USTRUCT(BlueprintType)
struct FInteractionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* TargetActor = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector TargetLocation = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Distance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimeRequired = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimeRemaining = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsInteractionAvailable = false;

    FInteractionData()
    {
        TargetActor = nullptr;
        Distance = 0.0f;
        TimeRequired = 0.0f;
        TimeRemaining = 0.0f;
        bIsInteractionAvailable = false;
    }
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_SPIEL_API UInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInteractionComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void Interact();

    UFUNCTION(BlueprintCallable)
    void StartInteraction();

    UFUNCTION(BlueprintCallable)
    void CancelInteraction();

    UFUNCTION(BlueprintCallable)
    void UpdateInteractionTarget();

    UFUNCTION(BlueprintCallable)
    bool CanInteract(AActor* Actor) const;

    UFUNCTION(BlueprintCallable)
    void SetInteractionBlocked(bool bBlocked);

    UFUNCTION(BlueprintPure)
    FInteractionData GetCurrentInteractionData() const { return CurrentInteractionData; }

    UFUNCTION(BlueprintPure)
    bool IsInteracting() const { return bIsInteracting; }

    UFUNCTION(BlueprintPure)
    float GetInteractionProgress() const;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float InteractionTraceDistance = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float InteractionRadius = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    TArray<TEnumAsByte<EObjectTypeQuery>> InteractionTraceObjectTypes;

    UPROPERTY(BlueprintAssignable)
    FOnInteractionStarted OnInteractionStarted;

    UPROPERTY(BlueprintAssignable)
    FOnInteractionCompleted OnInteractionCompleted;

    UPROPERTY(BlueprintAssignable)
    FOnInteractionCancelled OnInteractionCancelled;

    UPROPERTY(BlueprintAssignable)
    FOnTargetChanged OnTargetChanged;

    UFUNCTION(BlueprintImplementableEvent)
    void OnTargetChangedBP(AActor* OldTarget, AActor* NewTarget);

protected:
    UPROPERTY()
    FInteractionData CurrentInteractionData;

    UPROPERTY()
    AActor* CurrentTarget = nullptr;

    UPROPERTY()
    bool bIsInteracting = false;

    UPROPERTY()
    bool bInteractionBlocked = false;

    UPROPERTY()
    float InteractionTimeElapsed = 0.0f;

    UPROPERTY()
    bool bWasInteracting = false;

    void FindInteractableTarget();
    void ClearInteraction();
};

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnInteractionStarted, AActor*, TargetActor, float, Duration, FText, InteractionText);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnInteractionCompleted, AActor*, TargetActor, bool, bSuccess);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnInteractionCancelled, AActor*, TargetActor);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnTargetChanged, AActor*, OldTarget, AActor*, NewTarget);
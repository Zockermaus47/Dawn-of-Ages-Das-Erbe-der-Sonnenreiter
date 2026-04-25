#include "InteractionComponent.h"
#include "Interactable.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"

UInteractionComponent::UInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    InteractionTraceDistance = 300.0f;
    InteractionRadius = 50.0f;

    InteractionTraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
    InteractionTraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bInteractionBlocked)
    {
        if (CurrentTarget != nullptr)
        {
            AActor* OldTarget = CurrentTarget;
            ClearInteraction();
        }
        return;
    }

    if (bIsInteracting && CurrentTarget != nullptr)
    {
        IInteractable* Interactable = Cast<IInteractable>(CurrentTarget);
        if (Interactable)
        {
            FText InteractionText;
            float InteractionDuration;
            Interactable->GetInteractionData(InteractionText, InteractionDuration);

            if (InteractionDuration > 0.0f)
            {
                InteractionTimeElapsed += DeltaTime;
                CurrentInteractionData.TimeRemaining = InteractionDuration - InteractionTimeElapsed;

                if (InteractionTimeElapsed >= InteractionDuration)
                {
                    Interactable->CompleteInteraction(Cast<APawn>(GetOwner()));
                    OnInteractionCompleted.Broadcast(CurrentTarget, true);
                    bIsInteracting = false;
                    ClearInteraction();
                }
            }
        }
    }
    else
    {
        FindInteractableTarget();
    }

    bWasInteracting = bIsInteracting;
}

void UInteractionComponent::FindInteractableTarget()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;

    FVector CameraLocation;
    FRotator CameraRotation;
    Owner->GetActorEyesViewPoint(CameraLocation, CameraRotation);

    FVector TraceEnd = CameraLocation + (CameraRotation.Vector() * InteractionTraceDistance);

    FCollisionShape Shape;
    Shape.SetSphere(InteractionRadius);

    TArray<FHitResult> Hits;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(Owner);

    bool bHit = GetWorld()->SweepSingleByObjectType(
        Hits,
        CameraLocation,
        TraceEnd,
        FQuat::Identity,
        FCollisionObjectQueryParams(InteractionTraceObjectTypes),
        Shape,
        QueryParams
    );

    AActor* OldTarget = CurrentTarget;
    CurrentTarget = nullptr;

    if (bHit)
    {
        for (const FHitResult& Hit : Hits)
        {
            AActor* HitActor = Hit.GetActor();
            if (HitActor && Cast<IInteractable>(HitActor))
            {
                if (CanInteract(HitActor))
                {
                    CurrentTarget = HitActor;
                    CurrentInteractionData.TargetActor = CurrentTarget;
                    CurrentInteractionData.TargetLocation = Hit.ImpactPoint;
                    CurrentInteractionData.Distance = Hit.Distance;
                    CurrentInteractionData.bIsInteractionAvailable = true;

                    IInteractable* Interactable = Cast<IInteractable>(CurrentTarget);
                    if (Interactable)
                    {
                        FText Text;
                        float Duration;
                        Interactable->GetInteractionData(Text, Duration);
                        CurrentInteractionData.TimeRequired = Duration;
                        CurrentInteractionData.TimeRemaining = Duration;
                    }
                    break;
                }
            }
        }
    }

    if (OldTarget != CurrentTarget)
    {
        OnTargetChanged.Broadcast(OldTarget, CurrentTarget);
        OnTargetChangedBP(OldTarget, CurrentTarget);
    }
}

void UInteractionComponent::Interact()
{
    if (bInteractionBlocked)
    {
        return;
    }

    if (CurrentTarget == nullptr)
    {
        UpdateInteractionTarget();
    }

    if (CurrentTarget)
    {
        IInteractable* Interactable = Cast<IInteractable>(CurrentTarget);
        if (Interactable && Interactable->CanInteract(Cast<APawn>(GetOwner())))
        {
            FText InteractionText;
            float InteractionDuration;
            Interactable->GetInteractionData(InteractionText, InteractionDuration);

            if (InteractionDuration > 0.0f)
            {
                StartInteraction();
            }
            else
            {
                Interactable->CompleteInteraction(Cast<APawn>(GetOwner()));
                OnInteractionCompleted.Broadcast(CurrentTarget, true);
            }
        }
    }
}

void UInteractionComponent::StartInteraction()
{
    if (!CurrentTarget || bIsInteracting)
    {
        return;
    }

    bIsInteracting = true;
    InteractionTimeElapsed = 0.0f;

    IInteractable* Interactable = Cast<IInteractable>(CurrentTarget);
    if (Interactable)
    {
        FText InteractionText;
        float InteractionDuration;
        Interactable->GetInteractionData(InteractionText, InteractionDuration);

        OnInteractionStarted.Broadcast(CurrentTarget, InteractionDuration, InteractionText);
    }
}

void UInteractionComponent::CancelInteraction()
{
    if (bIsInteracting)
    {
        bIsInteracting = false;
        InteractionTimeElapsed = 0.0f;
        OnInteractionCancelled.Broadcast(CurrentTarget);
        ClearInteraction();
    }
}

void UInteractionComponent::UpdateInteractionTarget()
{
    FindInteractableTarget();
}

bool UInteractionComponent::CanInteract(AActor* Actor) const
{
    if (!Actor) return false;
    
    IInteractable* Interactable = Cast<IInteractable>(Actor);
    if (!Interactable) return false;

    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (!OwnerPawn) return false;

    float Distance = Actor->GetDistanceTo(OwnerPawn);
    if (Distance > InteractionTraceDistance)
    {
        return false;
    }

    return Interactable->CanInteract(OwnerPawn);
}

void UInteractionComponent::SetInteractionBlocked(bool bBlocked)
{
    bInteractionBlocked = bBlocked;
    
    if (bBlocked)
    {
        CancelInteraction();
    }
}

float UInteractionComponent::GetInteractionProgress() const
{
    if (CurrentInteractionData.TimeRequired > 0.0f)
    {
        return InteractionTimeElapsed / CurrentInteractionData.TimeRequired;
    }
    return 0.0f;
}

void UInteractionComponent::ClearInteraction()
{
    CurrentTarget = nullptr;
    CurrentInteractionData = FInteractionData();
    bIsInteracting = false;
    InteractionTimeElapsed = 0.0f;
}
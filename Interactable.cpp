#include "Interactable.h"

void IInteractable::GetInteractionData_Implementation(FText& InteractionText, float& InteractionDuration)
{
    InteractionText = FText::FromString("Interact");
    InteractionDuration = 0.0f;
}

bool IInteractable::CanInteract_Implementation(APawn* Instigator)
{
    return true;
}

void IInteractable::StartInteraction_Implementation(APawn* Instigator)
{
}

void IInteractable::CompleteInteraction_Implementation(APawn* Instigator)
{
}

void IInteractable::CancelInteraction_Implementation(APawn* Instigator)
{
}

bool IInteractable::IsInteractionAvailable_Implementation(APawn* Instigator)
{
    return true;
}

FLinearColor IInteractable::GetInteractionIndicatorColor_Implementation()
{
    return FLinearColor::White;
}
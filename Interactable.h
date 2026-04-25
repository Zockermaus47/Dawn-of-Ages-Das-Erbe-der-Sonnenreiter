#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class APawn;

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
    GENERATED_BODY()
};

class STEFFIS_SPIEL_API IInteractable
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    void GetInteractionData(FText& InteractionText, float& InteractionDuration);

    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    bool CanInteract(APawn* Instigator);

    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    void StartInteraction(APawn* Instigator);

    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    void CompleteInteraction(APawn* Instigator);

    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    void CancelInteraction(APawn* Instigator);

    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    bool IsInteractionAvailable(APawn* Instigator);

    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    FLinearColor GetInteractionIndicatorColor();
};
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DawnPlayerController.generated.h"

class ADawnPlayerState;
class ADawnGameMode;

UCLASS()
class STEFFIS_SPIEL_API ADawnPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ADawnPlayerController();

    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    UFUNCTION(Client, Reliable)
    void ClientShowNotification(const FString& Message);

    UFUNCTION(Client, Reliable)
    void ClientShowError(const FString& ErrorMessage);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerRequestRespawn();

    UFUNCTION(BlueprintPure)
    ADawnPlayerState* GetDawnPlayerState() const;

    UFUNCTION(BlueprintPure)
    ADawnGameMode* GetDawnGameMode() const;

    UFUNCTION(BlueprintCallable)
    void RequestServerTravel(const FString& URL);

protected:
    UPROPERTY()
    bool bIsMenuOpen = false;

    UFUNCTION()
    void ToggleMenu();

    UFUNCTION()
    void ToggleInventory();

    UFUNCTION()
    void ToggleCrafting();

private:
    void SetupPlayerInputComponent() override;
};
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DawnGameMode.generated.h"

class ADawnPlayerState;
class UCraftingComponent;

UCLASS()
class STEFFIS_SPIEL_API ADawnGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ADawnGameMode();

    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void Logout(AController* Exiting) override;
    virtual void HandleMatchHasStarted() override;

    UFUNCTION(BlueprintCallable)
    void StartGame();

    UFUNCTION(BlueprintCallable)
    void EndGame(APlayerController* Winner);

    UFUNCTION(BlueprintCallable)
    int32 GetConnectedPlayerCount() const;

    UFUNCTION(BlueprintPure)
    bool IsGameActive() const { return bIsGameActive; }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
    int32 MaxPlayers = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
    int32 MinPlayersToStart = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Settings")
    float TimeToStartAfterMinPlayers = 30.0f;

    UPROPERTY(BlueprintAssignable)
    FOnGameStateChanged OnGameStarted;

    UPROPERTY(BlueprintAssignable)
    FOnGameStateChanged OnGameEnded;

protected:
    UPROPERTY(Replicated)
    bool bIsGameActive = false;

    UPROPERTY()
    float TimeSinceMinPlayersReached = 0.0f;

    UFUNCTION()
    void OnPlayerCountChanged(int32 NewCount);

private:
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
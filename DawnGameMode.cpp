#include "DawnGameMode.h"
#include "DawnPlayerController.h"
#include "DawnPlayerState.h"
#include "DawnGameState.h"
#include "Net/UnrealNetwork.h"

ADawnGameMode::ADawnGameMode()
{
    bPauseable = false;
    PlayerControllerClass = ADawnPlayerController::StaticClass();
}

void ADawnGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if (HasAuthority())
    {
        UE_LOG(LogTemp, Log, TEXT("Player %s has joined"), *NewPlayer->GetName());
    }
}

void ADawnGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);

    if (HasAuthority())
    {
        UE_LOG(LogTemp, Log, TEXT("Player %s has left"), *Exiting->GetName());
    }
}

void ADawnGameMode::HandleMatchHasStarted()
{
    Super::HandleMatchHasStarted();
    
    if (HasAuthority())
    {
        bIsGameActive = true;
        OnGameStarted.Broadcast();
    }
}

void ADawnGameMode::StartGame()
{
    if (!HasAuthority()) return;

    bIsGameActive = true;
    OnGameStarted.Broadcast();
}

void ADawnGameMode::EndGame(APlayerController* Winner)
{
    if (!HasAuthority()) return;

    bIsGameActive = false;
    OnGameEnded.Broadcast();
}

int32 ADawnGameMode::GetConnectedPlayerCount() const
{
    return GetWorld()->GetGameState()->PlayerArray.Num();
}

void ADawnGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(ADawnGameMode, bIsGameActive);
}

DECLARE_DYNAMIC_DELEGATE(FOnGameStateChanged);
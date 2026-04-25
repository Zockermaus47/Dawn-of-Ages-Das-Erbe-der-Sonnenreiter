#include "DawnPlayerController.h"
#include "DawnPlayerState.h"
#include "DawnGameMode.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ADawnPlayerController::ADawnPlayerController()
{
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;
}

void ADawnPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (IsLocalController())
    {
    }
}

void ADawnPlayerController::ClientShowNotification_Implementation(const FString& Message)
{
}

void ADawnPlayerController::ClientShowError_Implementation(const FString& ErrorMessage)
{
}

void ADawnPlayerController::ServerRequestRespawn_Implementation()
{
    if (GetPawn())
    {
        GetPawn()->Destroy();
    }

    if (GetWorld())
    {
        FRotator StartRotation(0.0f, 0.0f, 0.0f);
        FVector StartLocation(0.0f, 0.0f, 100.0f);
        RestartPlayerAtTransform(GetWorld()->GetAuthGameMode(), StartLocation, StartRotation);
    }
}

bool ADawnPlayerController::ServerRequestRespawn_Validate()
{
    return true;
}

ADawnPlayerState* ADawnPlayerController::GetDawnPlayerState() const
{
    return Cast<ADawnPlayerState>(PlayerState);
}

ADawnGameMode* ADawnPlayerController::GetDawnGameMode() const
{
    return Cast<ADawnGameMode>(GetWorld()->GetAuthGameMode());
}

void ADawnPlayerController::RequestServerTravel(const FString& URL)
{
    ClientTravel(URL, TRAVEL_Absolute);
}
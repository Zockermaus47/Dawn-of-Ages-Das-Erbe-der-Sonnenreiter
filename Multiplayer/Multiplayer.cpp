#include "Multiplayer.h"

UMultiplayerSystem::UMultiplayerSystem()
{
}

bool UMultiplayerSystem::CreateServer(FText ServerName, int32 MaxPlayers)
{
    return false;
}

bool UMultiplayerSystem::JoinServer(FName ServerID)
{
    return false;
}

void UMultiplayerSystem::LeaveServer()
{
}

TArray<FPlayerSettings> UMultiplayerSystem::GetConnectedPlayers()
{
    return TArray<FPlayerSettings>();
}

void UMultiplayerSystem::SetPlayerReady(bool bReady)
{
}
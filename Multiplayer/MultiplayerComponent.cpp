#include "Multiplayer/MultiplayerComponent.h"
#include "Net/UnrealNetwork.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Common/UdpSocketBuilder.h"

UMultiplayerComponent::UMultiplayerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UMultiplayerComponent::BeginPlay()
{
	Super::BeginPlay();
	bIsConnected = false;
}

void UMultiplayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdatePlayerList();
}

void UMultiplayerComponent::UpdatePlayerList()
{
	if (!GetOwner()->HasAuthority())
		return;
	
	for (int32 i = ConnectedPlayers.Num() - 1; i >= 0; i--)
	{
		if (ConnectedPlayers[i].PlayerID == 0)
		{
			ConnectedPlayers.RemoveAt(i);
		}
	}
}

bool UMultiplayerComponent::HostServer(FString InServerName, int32 InMaxPlayers)
{
	ServerName = InServerName;
	MaxPlayers = InMaxPlayers;
	bIsHost = true;
	bIsConnected = true;
	
	FPlayerInfo LocalPlayer;
	LocalPlayer.PlayerName = "Host";
	LocalPlayer.PlayerID = 0;
	LocalPlayer.Role = EPlayerRole::Admin;
	LocalPlayer.bIsReady = true;
	LocalPlayer.Ping = 0;
	ConnectedPlayers.Add(LocalPlayer);
	LocalPlayerID = 0;
	
	return true;
}

bool UMultiplayerComponent::JoinServer(FString IPAddress, int32 Port)
{
	if (bIsConnected)
		return false;
	
	bIsConnected = true;
	
	FPlayerInfo NewPlayer;
	NewPlayer.PlayerName = "Player";
	NewPlayer.PlayerID = ConnectedPlayers.Num();
	NewPlayer.Role = EPlayerRole::Player;
	NewPlayer.bIsReady = false;
	NewPlayer.Ping = 0;
	ConnectedPlayers.Add(NewPlayer);
	LocalPlayerID = NewPlayer.PlayerID;
	
	return true;
}

void UMultiplayerComponent::Disconnect()
{
	if (!GetOwner()->HasAuthority() && !bIsHost)
		return;
	
	bIsHost = false;
	bIsConnected = false;
	ConnectedPlayers.Empty();
}

bool UMultiplayerComponent::KickPlayer(int32 PlayerID)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	for (int32 i = 0; i < ConnectedPlayers.Num(); i++)
	{
		if (ConnectedPlayers[i].PlayerID == PlayerID)
		{
			ConnectedPlayers.RemoveAt(i);
			return true;
		}
	}
	return false;
}

bool UMultiplayerComponent::BanPlayer(int32 PlayerID)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	KickPlayer(PlayerID);
	return true;
}

bool UMultiplayerComponent::SendMessageToPlayer(int32 PlayerID, FString Message)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	for (FPlayerInfo& Player : ConnectedPlayers)
	{
		if (Player.PlayerID == PlayerID)
		{
			return true;
		}
	}
	return false;
}

void UMultiplayerComponent::SendMessageToAll(FString Message)
{
}

int32 UMultiplayerComponent::GetPlayerCount() const
{
	return ConnectedPlayers.Num();
}

bool UMultiplayerComponent::IsHost() const
{
	return bIsHost;
}

void UMultiplayerComponent::SetPlayerReady(bool bReady)
{
	for (FPlayerInfo& Player : ConnectedPlayers)
	{
		if (Player.PlayerID == LocalPlayerID)
		{
			Player.bIsReady = bReady;
			break;
		}
	}
}

bool UMultiplayerComponent::SaveGameState()
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	return true;
}

bool UMultiplayerComponent::LoadGameState()
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	return true;
}
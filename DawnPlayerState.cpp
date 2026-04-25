#include "DawnPlayerState.h"
#include "Net/UnrealNetwork.h"

ADawnPlayerState::ADawnPlayerState()
{
    bReplicates = true;
}

void ADawnPlayerState::BeginPlay()
{
    Super::BeginPlay();
}

void ADawnPlayerState::SetPlayerName(const FString& NewName)
{
    PlayerNickname = NewName;
    Super::SetPlayerName(NewName);
}

void ADawnPlayerState::SetTeamID(int32 NewTeamID)
{
    TeamID = NewTeamID;
}

void ADawnPlayerState::AddKill()
{
    Kills++;
    Score += 100;
}

void ADawnPlayerState::AddDeath()
{
    Deaths++;
}

void ADawnPlayerState::AddScore(int32 ScoreToAdd)
{
    Score += ScoreToAdd;
}

float ADawnPlayerState::GetKDRatio() const
{
    if (Deaths == 0) return static_cast<float>(Kills);
    return static_cast<float>(Kills) / static_cast<float>(Deaths);
}

void ADawnPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(ADawnPlayerState, TeamID);
    DOREPLIFETIME(ADawnPlayerState, Kills);
    DOREPLIFETIME(ADawnPlayerState, Deaths);
    DOREPLIFETIME(ADawnPlayerState, Score);
    DOREPLIFETIME(ADawnPlayerState, PlayerNickname);
    DOREPLIFETIME(ADawnPlayerState, PlayerColor);
}
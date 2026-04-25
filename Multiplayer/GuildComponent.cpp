#include "Multiplayer/MultiplayerComponent.h"

UGuildComponent::UGuildComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGuildComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGuildComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UGuildComponent::CreateGuild(FString InName)
{
	if (GuildID != NAME_None) return false;
	
	GuildName = InName;
	GuildID = FName(*FString::Printf(TEXT("Guild_%s"), *InName));
	GuildLevel = 1;
	MemberCount = 1;
	GuildBankGold = 0;
	
	return true;
}

bool UGuildComponent::JoinGuild(FName InGuildID)
{
	if (GuildID != NAME_None) return false;
	
	GuildID = InGuildID;
	MemberIDs.Add(GetOwner()->GetFName());
	MemberCount = MemberIDs.Num();
	
	return true;
}

bool UGuildComponent::LeaveGuild()
{
	if (GuildID == NAME_None) return false;
	
	MemberIDs.Remove(GetOwner()->GetFName());
	MemberCount = MemberIDs.Num();
	
	if (MemberCount <= 0)
	{
		GuildID = NAME_None;
		GuildName = "";
	}
	
	return true;
}

bool UGuildComponent::InvitePlayer(FName PlayerID)
{
	if (GuildID == NAME_None) return false;
	return true;
}

bool UGuildComponent::KickMember(FName MemberID)
{
	if (GuildID == NAME_None) return false;
	
	MemberIDs.Remove(MemberID);
	MemberCount = MemberIDs.Num();
	return true;
}

bool UGuildComponent::DeclareWar(FName EnemyGuildID)
{
	if (GuildID == NAME_None) return false;
	EnemyGuilds.Add(EnemyGuildID);
	return true;
}

bool UGuildComponent::DeclarePeace(FName AllyGuildID)
{
	if (GuildID == NAME_None) return false;
	EnemyGuilds.Remove(AllyGuildID);
	AllyGuilds.Add(AllyGuildID);
	return true;
}

bool UGuildComponent::DepositGold(int32 Amount)
{
	if (GuildID == NAME_None) return false;
	GuildBankGold += Amount;
	return true;
}

bool UGuildComponent::WithdrawGold(int32 Amount)
{
	if (GuildID == NAME_None) return false;
	if (GuildBankGold < Amount) return false;
	
	GuildBankGold -= Amount;
	return true;
}

bool UGuildComponent::HasPermission(FName PlayerID) const
{
	return MemberIDs.Contains(PlayerID);
}

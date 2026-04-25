#include "Mount/MountComponent.h"

UMountComponent::UMountComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMountComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMountComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateStamina(DeltaTime);
}

bool UMountComponent::TameMount(AActor* WildMount)
{
	if (!WildMount || !GetOwner()->HasAuthority())
		return false;
	
	FMountData NewMount;
	NewMount.MountID = WildMount->GetFName();
	NewMount.MountName = WildMount->GetFName();
	NewMount.Type = EMountType::Horse;
	NewMount.Speed = 600.0f;
	NewMount.TrotSpeed = 1200.0f;
	NewMount.GallopSpeed = 2000.0f;
	NewMount.Stamina = 100.0f;
	NewMount.MaxStamina = 100.0f;
	NewMount.BreedTier = 1;
	NewMount.bIsTamed = true;
	NewMount.OwnerID = GetOwner()->GetFName();
	
	OwnedMounts.Add(NewMount);
	return true;
}

bool UMountComponent::Mount(FName MountID)
{
	for (FMountData& Mount : OwnedMounts)
	{
		if (Mount.MountID == MountID && Mount.bIsTamed)
		{
			ActiveMount = Mount;
			MountActor = nullptr;
			CurrentState = EMountState::Riding;
			UE_LOG(LogTemp, Log, TEXT("Mounted: %s"), *MountID.ToString());
			return true;
		}
	}
	return false;
}

bool UMountComponent::Dismount()
{
	if (ActiveMount.MountID == NAME_None)
		return false;
	
	CurrentState = EMountState::Idle;
	MountActor = nullptr;
	UE_LOG(LogTemp, Log, TEXT("Dismounted"));
	return true;
}

bool UMountComponent::AddMount(FMountData MountData)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	OwnedMounts.Add(MountData);
	return true;
}

bool UMountComponent::RemoveMount(FName MountID)
{
	for (int32 i = 0; i < OwnedMounts.Num(); i++)
	{
		if (OwnedMounts[i].MountID == MountID)
		{
			if (ActiveMount.MountID == MountID)
			{
				Dismount();
			}
			OwnedMounts.RemoveAt(i);
			return true;
		}
	}
	return false;
}

FMountData UMountComponent::GetMount(FName MountID)
{
	for (FMountData& Mount : OwnedMounts)
	{
		if (Mount.MountID == MountID)
			return Mount;
	}
	return FMountData();
}

void UMountComponent::SetMovementState(EMountState NewState)
{
	CurrentState = NewState;
	
	switch (NewState)
	{
	case EMountState::Idle:
		CurrentSpeed = 0.0f;
		break;
	case EMountState::Walking:
		CurrentSpeed = ActiveMount.Speed;
		break;
	case EMountState::Trotting:
		CurrentSpeed = ActiveMount.TrotSpeed;
		break;
	case EMountState::Galloping:
		CurrentSpeed = ActiveMount.GallopSpeed;
		break;
	}
}

float UMountComponent::GetCurrentSpeed() const
{
	return CurrentSpeed * MountSpeedMultiplier;
}

int32 UMountComponent::GetMountCount() const
{
	return OwnedMounts.Num();
}

void UMountComponent::UpdateStamina(float DeltaTime)
{
	if (ActiveMount.MountID == NAME_None)
		return;
	
	bool IsMoving = (CurrentState == EMountState::Walking || CurrentState == EMountState::Trotting || CurrentState == EMountState::Galloping);
	
	if (IsMoving)
	{
		float StaminaDrain = 1.0f;
		if (CurrentState == EMountState::Trotting) StaminaDrain = 2.0f;
		if (CurrentState == EMountState::Galloping) StaminaDrain = 4.0f;
		
		ActiveMount.Stamina = FMath::Clamp(ActiveMount.Stamina - (DeltaTime * StaminaDrain), 0.0f, ActiveMount.MaxStamina);
	}
	else
	{
		ActiveMount.Stamina = FMath::Clamp(ActiveMount.Stamina + (DeltaTime * 0.5f), 0.0f, ActiveMount.MaxStamina);
	}
}
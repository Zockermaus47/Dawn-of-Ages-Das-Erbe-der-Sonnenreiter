#include "Harvesting/HarvestComponent.h"

UHarvestComponent::UHarvestComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHarvestComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (StageProgression.Num() == 0)
	{
		FHarvestStageData Standing;
		Standing.Stage = EHarvestStage::Standing;
		Standing.HitsRequired = 3;
		Standing.DamagePerHit = 1.0f;
		Standing.WobbleAmount = 5.0f;
		StageProgression.Add(Standing);
		
		FHarvestStageData Falling;
		Falling.Stage = EHarvestStage::Falling;
		Falling.HitsRequired = 0;
		StageProgression.Add(Falling);
		
		FHarvestStageData LyingBranches;
		LyingBranches.Stage = EHarvestStage::LyingWithBranches;
		LyingBranches.HitsRequired = 3;
		LyingBranches.bSpawnLootOnHit = true;
		StageProgression.Add(LyingBranches);
		
		FHarvestStageData LyingClean;
		LyingClean.Stage = EHarvestStage::LyingClean;
		LyingClean.HitsRequired = 2;
		LyingClean.bSpawnLootOnHit = true;
		StageProgression.Add(LyingClean);
		
		FHarvestStageData Destroyed;
		Destroyed.Stage = EHarvestStage::Destroyed;
		Destroyed.HitsRequired = 0;
		StageProgression.Add(Destroyed);
	}
}

void UHarvestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!bIsGrown)
	{
		Grow(DeltaTime);
	}
}

float UHarvestComponent::ReceiveHit(float Damage, EHarvestTool Tool, FVector HitLocation, FVector HitDirection)
{
	FHarvestStageData* StageData = GetCurrentStageData();
	if (!StageData)
		return 0.0f;
	
	float DamageMultiplier = 1.0f;
	switch (Tool)
	{
	case EHarvestTool::Axe:
		DamageMultiplier = 2.0f;
		break;
	case EHarvestTool::Pickaxe:
		DamageMultiplier = 1.5f;
		break;
	case EHarvestTool::Sword:
		DamageMultiplier = 1.2f;
		break;
	case EHarvestTool::Hands:
		DamageMultiplier = 0.5f;
		break;
	}
	
	float ActualDamage = Damage * DamageMultiplier * StageData->DamagePerHit;
	CurrentHealth -= ActualDamage;
	
	TriggerWobble(StageData->WobbleAmount);
	
	if (StageData->bSpawnLootOnHit)
	{
		TArray<FHarvestLootDrop> Loot = GetLootForCurrentStage();
		for (const FHarvestLootDrop& Drop : Loot)
		{
			if (FMath::RandRange(0.0f, 100.0f) <= Drop.DropChance)
			{
				SpawnLoot(HitLocation);
			}
		}
	}
	
	if (CurrentHealth <= 0.0f)
	{
		ProcessStageTransition();
	}
	
	return ActualDamage;
}

void UHarvestComponent::ProcessStageTransition()
{
	int32 CurrentIndex = -1;
	for (int32 i = 0; i < StageProgression.Num(); i++)
	{
		if (StageProgression[i].Stage == CurrentStage)
		{
			CurrentIndex = i;
			break;
		}
	}
	
	if (CurrentIndex >= 0 && CurrentIndex < StageProgression.Num() - 1)
	{
		CurrentStage = StageProgression[CurrentIndex + 1].Stage;
		
		FHarvestStageData* NextStageData = GetCurrentStageData();
		if (NextStageData)
		{
			CurrentHealth = NextStageData->HitsRequired * 10.0f;
			MaxHealth = CurrentHealth;
		}
		
		UE_LOG(LogTemp, Log, TEXT("Stage transition to: %d"), (int32)CurrentStage);
		
		if (CurrentStage == EHarvestStage::Standing)
		{
		}
		else if (CurrentStage == EHarvestStage::Falling)
		{
			ApplyStageWobble();
		}
		else if (CurrentStage == EHarvestStage::Destroyed)
		{
			Respawn();
		}
	}
}

void UHarvestComponent::SpawnLoot(FVector Location)
{
	UWorld* World = GetWorld();
	if (!World)
		return;
	
	TArray<FHarvestLootDrop> Loot = GetLootForCurrentStage();
	for (const FHarvestLootDrop& Drop : Loot)
	{
		int32 Quantity = FMath::RandRange(Drop.MinQuantity, Drop.MaxQuantity);
		for (int32 i = 0; i < Quantity; i++)
		{
			FVector SpawnLocation = Location + FVector(FMath::RandRange(-50.0f, 50.0f), FMath::RandRange(-50.0f, 50.0f), 0.0f);
			UE_LOG(LogTemp, Log, TEXT("Spawning loot: %s at %s"), *Drop.ItemID.ToString(), *SpawnLocation.ToString());
		}
	}
}

void UHarvestComponent::TriggerWobble(float Amount)
{
	ApplyStageWobble();
}

void UHarvestComponent::Grow(float DeltaTime)
{
	if (GrowthProgress < 100.0f)
	{
		GrowthProgress += DeltaTime * (100.0f / RespawnTime);
		bIsGrown = GrowthProgress >= 100.0f;
		
		if (bIsGrown)
		{
			CurrentHealth = MaxHealth;
			CurrentStage = EHarvestStage::Standing;
		}
	}
}

void UHarvestComponent::Respawn()
{
	bIsGrown = false;
	GrowthProgress = 0.0f;
	CurrentStage = EHarvestStage::Standing;
	CurrentHealth = MaxHealth;
	
	UE_LOG(LogTemp, Log, TEXT("Resource will respawn in %f seconds"), RespawnTime);
}

float UHarvestComponent::GetHealthPercentage() const
{
	if (MaxHealth <= 0.0f)
		return 0.0f;
	return (CurrentHealth / MaxHealth) * 100.0f;
}

bool UHarvestComponent::IsFullyGrown() const
{
	return bIsGrown;
}

EHarvestStage UHarvestComponent::GetCurrentStage() const
{
	return CurrentStage;
}

void UHarvestComponent::ApplyStageWobble()
{
	AActor* Owner = GetOwner();
	if (!Owner)
		return;
	
	FVector CurrentRotation = Owner->GetActorRotation().Vector();
	float Wobble = FMath::RandRange(-5.0f, 5.0f);
	FRotator NewRotation = FRotator(CurrentRotation.X + Wobble, CurrentRotation.Y, CurrentRotation.Z);
	Owner->SetActorRotation(NewRotation);
}

FHarvestStageData* UHarvestComponent::GetCurrentStageData()
{
	for (FHarvestStageData& Data : StageProgression)
	{
		if (Data.Stage == CurrentStage)
			return &Data;
	}
	return nullptr;
}

TArray<FHarvestLootDrop> UHarvestComponent::GetLootForCurrentStage()
{
	TArray<FHarvestLootDrop> Result;
	FHarvestStageData* Data = GetCurrentStageData();
	if (Data)
	{
		Result = Data->LootTable;
	}
	return Result;
}
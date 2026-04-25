#include "Farming/FarmingComponent.h"
#include "Net/UnrealNetwork.h"
#include "Inventory/InventoryComponent.h"

TMap<EFarmCropType, FName> UFarmingComponent::SeedItemMap;

UFarmingComponent::UFarmingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);

	SeedItemMap.Add(EFarmCropType::Wheat, TEXT("Seed_Wheat"));
	SeedItemMap.Add(EFarmCropType::Corn, TEXT("Seed_Corn"));
	SeedItemMap.Add(EFarmCropType::Carrot, TEXT("Seed_Carrot"));
	SeedItemMap.Add(EFarmCropType::Potato, TEXT("Seed_Potato"));
	SeedItemMap.Add(EFarmCropType::Berry, TEXT("Seed_Berry"));
	SeedItemMap.Add(EFarmCropType::Flax, TEXT("Seed_Flax"));
	SeedItemMap.Add(EFarmCropType::Hemp, TEXT("Seed_Hemp"));
}

void UFarmingComponent::BeginPlay()
{
	Super::BeginPlay();
	PlantedCrops.SetNum(NumPlots);
	for (int32 i = 0; i < NumPlots; i++)
	{
		PlantedCrops[i].PlotIndex = i;
		PlantedCrops[i].State = ECropState::Seeded;
		PlantedCrops[i].CurrentGrowth = 0.0f;
		PlantedCrops[i].WaterLevel = 50.0f;
		PlantedCrops[i].FertilizerLevel = 0.0f;
	}
}

void UFarmingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateCrops(DeltaTime);
	UpdateAnimals(DeltaTime);
}

void UFarmingComponent::UpdateCrops(float DeltaTime)
{
	if (!GetOwner()->HasAuthority())
		return;
	
	for (FPlantedCrop& Crop : PlantedCrops)
	{
		if (Crop.State == ECropState::Growing)
		{
			float GrowthMultiplier = 1.0f;
			if (Crop.WaterLevel > 30.0f)
				GrowthMultiplier += 0.5f;
			if (Crop.FertilizerLevel > 0.0f)
				GrowthMultiplier += (Crop.FertilizerLevel / 100.0f) * 0.5f;
			
			Crop.CurrentGrowth += (DeltaTime * GrowthMultiplier);
			
			if (Crop.CurrentGrowth >= 100.0f)
			{
				Crop.State = ECropState::Ready;
				Crop.CurrentGrowth = 100.0f;
			}
		}
	}
}

void UFarmingComponent::UpdateAnimals(float DeltaTime)
{
	if (!GetOwner()->HasAuthority())
		return;
	
	for (FFarmAnimalData& Animal : Animals)
	{
		Animal.Hunger = FMath::Clamp(Animal.Hunger - (DeltaTime * 0.5f), 0.0f, 100.0f);
		
		if (Animal.Health <= 0.0f)
			continue;
		
		if (!Animal.bIsAdult)
		{
			Animal.GrowthProgress += DeltaTime;
			if (Animal.GrowthProgress >= 100.0f)
			{
				Animal.bIsAdult = true;
				Animal.GrowthProgress = 100.0f;
			}
		}
	}
}

bool UFarmingComponent::PlantCrop(int32 PlotIndex, FName SeedItemID)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	if (PlotIndex < 0 || PlotIndex >= NumPlots)
		return false;
	
	if (PlantedCrops[PlotIndex].State != ECropState::Seeded)
		return false;

	UInventoryComponent* Inventory = Cast<UInventoryComponent>(GetOwner()->GetComponentByClass(UInventoryComponent::StaticClass()));
	if (!Inventory)
		return false;
	
	if (!Inventory->HasItem(SeedItemID, 1))
		return false;
	
	Inventory->RemoveItem(SeedItemID, 1);
	
	for (auto& KVP : SeedItemMap)
	{
		if (KVP.Value == SeedItemID)
		{
			PlantedCrops[PlotIndex].CropID = KVP.Key;
			break;
		}
	}
	
	if (PlantedCrops[PlotIndex].CropID == NAME_None)
	{
		PlantedCrops[PlotIndex].CropID = SeedItemID;
	}
	
	PlantedCrops[PlotIndex].State = ECropState::Growing;
	PlantedCrops[PlotIndex].CurrentGrowth = 0.0f;
	PlantedCrops[PlotIndex].WaterLevel = 50.0f;
	PlantedCrops[PlotIndex].FertilizerLevel = 0.0f;
	
	return true;
}

FName UFarmingComponent::GetSeedForCrop(EFarmCropType CropType) const
{
	return SeedItemMap.FindRef(CropType);
}

bool UFarmingComponent::HasSeeds(EFarmCropType CropType) const
{
	FName SeedID = GetSeedForCrop(CropType);
	if (SeedID == NAME_None)
		return false;
	
	UInventoryComponent* Inventory = Cast<UInventoryComponent>(GetOwner()->GetComponentByClass(UInventoryComponent::StaticClass()));
	if (!Inventory)
		return false;
	
	return Inventory->HasItem(SeedID, 1);
}

bool UFarmingComponent::WaterCrop(int32 PlotIndex, float Amount)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	if (PlotIndex < 0 || PlotIndex >= NumPlots)
		return false;
	
	PlantedCrops[PlotIndex].WaterLevel = FMath::Clamp(PlantedCrops[PlotIndex].WaterLevel + Amount, 0.0f, 100.0f);
	return true;
}

bool UFarmingComponent::Fertilize(int32 PlotIndex, float Amount)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	if (PlotIndex < 0 || PlotIndex >= NumPlots)
		return false;
	
	PlantedCrops[PlotIndex].FertilizerLevel = FMath::Clamp(PlantedCrops[PlotIndex].FertilizerLevel + Amount, 0.0f, 100.0f);
	return true;
}

bool UFarmingComponent::HarvestCrop(int32 PlotIndex)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	if (PlotIndex < 0 || PlotIndex >= NumPlots)
		return false;
	
	if (PlantedCrops[PlotIndex].State != ECropState::Ready)
		return false;
	
	FName CropID = PlantedCrops[PlotIndex].CropID;
	int32 YieldAmount = 1;
	if (HarvestYields.IsValidIndex(PlotIndex))
	{
		YieldAmount = HarvestYields[PlotIndex];
	}
	
	UInventoryComponent* Inventory = Cast<UInventoryComponent>(GetOwner()->GetComponentByClass(UInventoryComponent::StaticClass()));
	if (Inventory)
	{
		FName HarvestItemID = CropID;
		Inventory->AddItem(HarvestItemID, YieldAmount);
	}
	
	PlantedCrops[PlotIndex].State = ECropState::Seeded;
	PlantedCrops[PlotIndex].CropID = NAME_None;
	PlantedCrops[PlotIndex].CurrentGrowth = 0.0f;
	PlantedCrops[PlotIndex].WaterLevel = 50.0f;
	PlantedCrops[PlotIndex].FertilizerLevel = 0.0f;
	
	return true;
}

bool UFarmingComponent::AddAnimal(FFarmAnimalData Animal)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	Animals.Add(Animal);
	return true;
}

bool UFarmingComponent::BreedAnimals(FName Parent1, FName Parent2)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	FFarmAnimalData* Animal1 = nullptr;
	FFarmAnimalData* Animal2 = nullptr;
	
	for (FFarmAnimalData& Animal : Animals)
	{
		if (Animal.AnimalID == Parent1) Animal1 = &Animal;
		if (Animal.AnimalID == Parent2) Animal2 = &Animal;
	}
	
	if (!Animal1 || !Animal2)
		return false;
	
	if (!Animal1->bIsAdult || !Animal2->bIsAdult)
		return false;
	
	FFarmAnimalData Child;
	Child.AnimalID = FName(*FString::Printf(TEXT("Child_%s_%s"), *Parent1.ToString(), *Parent2.ToString()));
	Child.AnimalName = Animal1->AnimalName;
	Child.BreedTier = FMath::Max(Animal1->BreedTier, Animal2->BreedTier) + 1;
	Child.Health = 100.0f;
	Child.Hunger = 50.0f;
	Child.GrowthProgress = 0.0f;
	Child.bIsAdult = false;
	Child.Parent1 = Parent1;
	Child.Parent2 = Parent2;
	
	Animals.Add(Child);
	return true;
}

bool UFarmingComponent::FeedAnimal(FName AnimalID, float FoodAmount)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	FFarmAnimalData* FoundAnimal = nullptr;
	for (FFarmAnimalData& Animal : Animals)
	{
		if (Animal.AnimalID == AnimalID)
		{
			FoundAnimal = &Animal;
			break;
		}
	}
	
	if (!FoundAnimal)
		return false;
	
	FoundAnimal->Hunger = FMath::Clamp(FoundAnimal->Hunger + FoodAmount, 0.0f, 100.0f);
	FoundAnimal->Health = FMath::Clamp(FoundAnimal->Health + 5.0f, 0.0f, 100.0f);
	return true;
}

TArray<FFarmAnimalData> UFarmingComponent::GetAnimalsByType(FName AnimalType) const
{
	TArray<FFarmAnimalData> Result;
	for (const FFarmAnimalData& Animal : Animals)
	{
		if (Animal.AnimalName == AnimalType)
			Result.Add(Animal);
	}
	return Result;
}

int32 UFarmingComponent::GetTotalAnimals() const
{
	return Animals.Num();
}

TArray<EGeneticTrait> UFarmingComponent::InheritTraits(FFarmAnimalData Parent1, FFarmAnimalData Parent2)
{
	TArray<EGeneticTrait> ChildTraits;
	
	if (FMath::RandRange(0, 100) < 50 && Parent1.InheritedTraits.Num() > 0)
	{
		ChildTraits.Add(Parent1.InheritedTraits[FMath::RandRange(0, Parent1.InheritedTraits.Num() - 1)]);
	}
	if (FMath::RandRange(0, 100) < 50 && Parent2.InheritedTraits.Num() > 0)
	{
		ChildTraits.Add(Parent2.InheritedTraits[FMath::RandRange(0, Parent2.InheritedTraits.Num() - 1)]);
	}
	
	return ChildTraits;
}

float UFarmingComponent::CalculateGeneticPotency(FFarmAnimalData Parent1, FFarmAnimalData Parent2)
{
	float Potency = 1.0f;
	Potency += Parent1.GeneticPotency * 0.4f;
	Potency += Parent2.GeneticPotency * 0.4f;
	if (Parent1.BreedTier == Parent2.BreedTier && Parent1.BreedTier > 1)
	{
		Potency += 0.2f;
	}
	return FMath::Clamp(Potency, 0.5f, 2.0f);
}

bool UFarmingComponent::BreedWithGenetics(FName Parent1ID, FName Parent2ID)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	FFarmAnimalData* Parent1 = nullptr;
	FFarmAnimalData* Parent2 = nullptr;
	
	for (FFarmAnimalData& Animal : Animals)
	{
		if (Animal.AnimalID == Parent1ID) Parent1 = &Animal;
		if (Animal.AnimalID == Parent2ID) Parent2 = &Animal;
	}
	
	if (!Parent1 || !Parent2)
		return false;
	
	if (!Parent1->bIsAdult || !Parent2->bIsAdult)
		return false;
	
	FFarmAnimalData Child;
	Child.AnimalID = FName(*FString::Printf(TEXT("Child_%s_%s"), *Parent1ID.ToString(), *Parent2ID.ToString()));
	Child.AnimalName = Parent1->AnimalName;
	Child.BreedTier = FMath::Max(Parent1->BreedTier, Parent2->BreedTier) + 1;
	Child.Health = 100.0f;
	Child.Hunger = 50.0f;
	Child.GrowthProgress = 0.0f;
	Child.bIsAdult = false;
	Child.Parent1 = Parent1ID;
	Child.Parent2 = Parent2ID;
	Child.InheritedTraits = InheritTraits(*Parent1, *Parent2);
	Child.GeneticPotency = CalculateGeneticPotency(*Parent1, *Parent2);
	
	Animals.Add(Child);
	return true;
}

bool UFarmingComponent::ApplyTraitToAnimal(FName AnimalID, EGeneticTrait Trait)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	for (FFarmAnimalData& Animal : Animals)
	{
		if (Animal.AnimalID == AnimalID)
		{
			Animal.InheritedTraits.Add(Trait);
			return true;
		}
	}
	return false;
}

TArray<EGeneticTrait> UFarmingComponent::GetAnimalTraits(FName AnimalID) const
{
	for (const FFarmAnimalData& Animal : Animals)
	{
		if (Animal.AnimalID == AnimalID)
		{
			return Animal.InheritedTraits;
		}
	}
	return TArray<EGeneticTrait>();
}

float UFarmingComponent::GetGeneticPotency(FName AnimalID) const
{
	for (const FFarmAnimalData& Animal : Animals)
	{
		if (Animal.AnimalID == AnimalID)
		{
			return Animal.GeneticPotency;
		}
	}
	return 1.0f;
}
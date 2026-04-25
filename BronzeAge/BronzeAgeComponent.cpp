#include "BronzeAge/BronzeAgeComponent.h"

UBronzeAgeComponent::UBronzeAgeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBronzeAgeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBronzeAgeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UBronzeAgeComponent::UnlockTech(EBronzeAgeTech Tech)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	if (!UnlockedTechs.Contains(Tech))
	{
		UnlockedTechs.Add(Tech);
		UE_LOG(LogTemp, Log, TEXT("Unlocked Bronze Age Tech: %d"), (int32)Tech);
		return true;
	}
	return false;
}

bool UBronzeAgeComponent::HasTech(EBronzeAgeTech Tech) const
{
	return UnlockedTechs.Contains(Tech);
}

bool UBronzeAgeComponent::CanCraft(FBronzeRecipe Recipe) const
{
	if (!HasTech(Recipe.RequiredTech))
		return false;
	
	if (Recipe.RequiredMaterials.Num() != Recipe.RequiredQuantities.Num())
		return false;
	
	return true;
}

bool UBronzeAgeComponent::CraftBronzeItem(FBronzeRecipe Recipe)
{
	if (!CanCraft(Recipe))
		return false;
	
	if (!GetOwner()->HasAuthority())
		return false;
	
	UE_LOG(LogTemp, Log, TEXT("Crafted: %s"), *Recipe.OutputItemID.ToString());
	return true;
}

bool UBronzeAgeComponent::AddOre(EMetalType MetalType, int32 Amount)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	switch (MetalType)
	{
	case EMetalType::Copper:
		CopperOre += Amount;
		break;
	case EMetalType::Tin:
		TinOre += Amount;
		break;
	default:
		return false;
	}
	return true;
}

int32 UBronzeAgeComponent::GetOre(EMetalType MetalType) const
{
	switch (MetalType)
	{
	case EMetalType::Copper:
		return CopperOre;
	case EMetalType::Tin:
		return TinOre;
	case EMetalType::Bronze:
		return BronzeIngots;
	default:
		return 0;
	}
}

bool UBronzeAgeComponent::SmeltBronze()
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	int32 RequiredCopper = 2;
	int32 RequiredTin = 1;
	
	if (CopperOre < RequiredCopper || TinOre < RequiredTin)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough ore for bronze!"));
		return false;
	}
	
	int32 Output = CalculateBronzeOutput(CopperOre, TinOre, 0.8f);
	BronzeIngots += Output;
	CopperOre -= RequiredCopper;
	TinOre -= RequiredTin;
	
	UE_LOG(LogTemp, Log, TEXT("Smelted %d Bronze Ingots"), Output);
	return true;
}

int32 UBronzeAgeComponent::CalculateBronzeOutput(int32 Copper, int32 Tin, float Purity)
{
	int32 Ratio = Copper / 2;
	int32 Output = FMath::Min(Ratio, Tin);
	return FMath::FloorToInt(Output * Purity);
}

TArray<EBronzeAgeTech> UBronzeAgeComponent::GetAvailableTechs() const
{
	return UnlockedTechs;
}

float UBronzeAgeComponent::GetTechProgress(EBronzeAgeTech Tech) const
{
	if (HasTech(Tech))
		return 1.0f;
	return 0.0f;
}
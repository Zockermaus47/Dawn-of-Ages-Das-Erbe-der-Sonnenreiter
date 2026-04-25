#include "Dynasty/DynastyComponent.h"

UDynastyComponent::UDynastyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDynastyComponent::BeginPlay()
{
	Super::BeginPlay();
	CalculateLegacyBonuses();
}

void UDynastyComponent::CreateFounder(FName FounderName, TArray<ECharacterTrait> StartingTraits)
{
	if (!GetOwner()->HasAuthority())
		return;
	
	FFamilyMember Founder;
	Founder.MemberID = FounderName;
	Founder.Name = FounderName.ToString();
	Founder.Generation = 1;
	Founder.Age = 18;
	Founder.Traits = StartingTraits;
	Founder.bIsAlive = true;
	Founder.Health = 100.0f;
	Founder.XPBonusMultiplier = 1.0f;
	
	FamilyTree.Add(Founder);
	CurrentHeirID = FounderName;
	
	UE_LOG(LogTemp, Log, TEXT("Dynasty founded: %s"), *FounderName.ToString());
}

bool UDynastyComponent::HaveChild(FName ChildName, FName ParentID)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	FFamilyMember Parent = FindMember(ParentID);
	if (Parent.MemberID == NAME_None || !Parent.bIsAlive)
		return false;
	
	FFamilyMember Child;
	Child.MemberID = ChildName;
	Child.Name = ChildName.ToString();
	Child.Generation = Parent.Generation + 1;
	Child.Age = 0;
	Child.Traits = InheritTraitsFrom(Parent.Traits);
	Child.ParentID = ParentID;
	Child.bIsAlive = true;
	Child.Health = 100.0f;
	Child.XPBonusMultiplier = 1.0f + (Parent.XPBonusMultiplier - 1.0f) * 0.5f;
	
	FamilyTree.Add(Child);
	
	UE_LOG(LogTemp, Log, TEXT("Child born: %s"), *ChildName.ToString());
	return true;
}

bool UDynastyComponent::PassDownGeneration(FName HeirName)
{
	if (!GetOwner()->HasAuthority())
		return false;
	
	FFamilyMember Heir = FindMember(HeirName);
	if (Heir.MemberID == NAME_None || !Heir.bIsAlive)
		return false;
	
	for (FFamilyMember& Prev : FamilyTree)
	{
		if (Prev.MemberID == CurrentHeirID)
		{
			Prev.bIsAlive = false;
			break;
		}
	}
	
	CurrentHeirID = HeirName;
	CurrentGeneration++;
	
	CalculateLegacyBonuses();
	
	UE_LOG(LogTemp, Log, TEXT("Passed to generation %d: %s"), CurrentGeneration, *HeirName.ToString());
	return true;
}

void UDynastyComponent::CalculateLegacyBonuses()
{
	LegacyBonuses = FLegacyBonus();
	
	int32 MaxTier = 0;
	int32 TotalTraits = 0;
	
	for (const FFamilyMember& Member : FamilyTree)
	{
		if (Member.bIsAlive)
		{
			int32 Tier = Member.Generation;
			if (Tier > MaxTier) MaxTier = Tier;
			
			TotalTraits += Member.Traits.Num();
		}
	}
	
	float GenerationMultiplier = MaxTier * 0.1f;
	float TraitMultiplier = TotalTraits * 0.05f;
	
	LegacyBonuses.XPBonus = GenerationMultiplier + TraitMultiplier;
	LegacyBonuses.GoldBonus = GenerationMultiplier * 0.5f;
	LegacyBonuses.CraftingSpeedBonus = GenerationMultiplier * 0.1f;
	LegacyBonuses.DamageBonus = GenerationMultiplier * 0.1f;
	LegacyBonuses.TradeBonus = TraitMultiplier;
	
	UE_LOG(LogTemp, Log, TEXT("Legacy Bonuses: XP=%.2f, Gold=%.2f"), LegacyBonuses.XPBonus, LegacyBonuses.GoldBonus);
}

void UDynastyComponent::AddFamilyMember(FFamilyMember NewMember)
{
	if (!GetOwner()->HasAuthority())
		return;
	
	FamilyTree.Add(NewMember);
}

TArray<ECharacterTrait> UDynastyComponent::GetInheritedTraits(FName ParentID) const
{
	for (const FFamilyMember& Member : FamilyTree)
	{
		if (Member.MemberID == ParentID)
			return Member.Traits;
	}
	return TArray<ECharacterTrait>();
}

FFamilyMember UDynastyComponent::FindMember(FName MemberID)
{
	for (const FFamilyMember& Member : FamilyTree)
	{
		if (Member.MemberID == MemberID)
			return Member;
	}
	return FFamilyMember();
}

bool UDynastyComponent::SetHeir(FName MemberID)
{
	for (FFamilyMember& Member : FamilyTree)
	{
		if (Member.MemberID == MemberID)
		{
			CurrentHeirID = MemberID;
			return true;
		}
	}
	return false;
}

float UDynastyComponent::GetTraitBonus(ECharacterTrait Trait) const
{
	float Bonus = 0.0f;
	
	switch (Trait)
	{
	case ECharacterTrait::Strong:
		Bonus = 0.1f;
		break;
	case ECharacterTrait::Intelligent:
		Bonus = 0.1f;
		break;
	case ECharacterTrait::Lucky:
		Bonus = 0.05f;
		break;
	case ECharacterTrait::Healthy:
		Bonus = 20.0f;
		break;
	case ECharacterTrait::Fast:
		Bonus = 0.1f;
		break;
	case ECharacterTrait::Charismatic:
		Bonus = 0.1f;
		break;
	}
	
	int32 LivingGenerations = GetLivingGenerations();
	return Bonus * (1.0f + LivingGenerations * 0.1f);
}

void UDynastyComponent::AgeFamily(float DeltaTime)
{
	if (!GetOwner()->HasAuthority())
		return;
	
	float AgeAmount = DeltaTime * AgeSpeed;
	
	for (FFamilyMember& Member : FamilyTree)
	{
		if (Member.bIsAlive)
		{
			Member.Age += FMath::FloorToInt(AgeAmount);
		}
	}
}

int32 UDynastyComponent::GetLivingGenerations() const
{
	TSet<int32> LivingGen;
	for (const FFamilyMember& Member : FamilyTree)
	{
		if (Member.bIsAlive)
		{
			LivingGen.Add(Member.Generation);
		}
	}
	return LivingGen.Num();
}

TArray<ECharacterTrait> UDynastyComponent::InheritTraitsFrom(const TArray<ECharacterTrait>& ParentTraits)
{
	TArray<ECharacterTrait> ChildTraits;
	
	for (const ECharacterTrait& Trait : ParentTraits)
	{
		if (FMath::RandRange(0, 100) < 30)
		{
			ChildTraits.Add(Trait);
		}
	}
	
	if (ChildTraits.Num() == 0 && ParentTraits.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, ParentTraits.Num() - 1);
		ChildTraits.Add(ParentTraits[RandomIndex]);
	}
	
	return ChildTraits;
}

float UDynastyComponent::CalculateTraitValue(ECharacterTrait Trait, int32 GenerationCount)
{
	float BaseValue = GetTraitBonus(Trait);
	return BaseValue * (1.0f + GenerationCount * 0.1f);
}
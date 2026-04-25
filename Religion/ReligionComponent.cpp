#include "Religion/ReligionComponent.h"

UReligionComponent::UReligionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UReligionComponent::BeginPlay()
{
	Super::BeginPlay();

	GodFavor.Add(EGod::Ares, 50.0f);
	GodFavor.Add(EGod::Gaia, 50.0f);
	GodFavor.Add(EGod::Athena, 50.0f);
	GodFavor.Add(EGod::Tyche, 50.0f);
	GodFavor.Add(EGod::Hades, 50.0f);
	GodFavor.Add(EGod::Hephaestus, 50.0f);
	GodFavor.Add(EGod::Poseidon, 50.0f);
}

void UReligionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateBlessings(DeltaTime);
}

void UReligionComponent::MakeOffering(EGod God, int32 OfferingValue)
{
	float* Favor = GodFavor.Find(God);
	if (Favor)
	{
		float FavorGain = OfferingValue * 0.1f;
		*Favor = FMath::Clamp(*Favor + FavorGain, 0.0f, 100.0f);
	}
}

bool UReligionComponent::RequestBlessing(EGod God)
{
	float CurrentFavor = GetFavorWithGod(God);

	if (CurrentFavor >= 60.0f)
	{
		FDivineBlessing NewBlessing = CreateBlessing(God);
		NewBlessing.bIsActive = true;
		ActiveBlessings.Add(NewBlessing);

		float* Favor = GodFavor.Find(God);
		if (Favor)
		{
			*Favor -= 30.0f;
		}

		return true;
	}

	return false;
}

void UReligionComponent::BuildTemple(EGod God, FVector Location)
{
	FTempleData NewTemple;
	NewTemple.DedicatedGod = God;
	NewTemple.Location = Location;
	NewTemple.TempleLevel = 1;
	NewTemple.Devotion = 0.0f;

	Temples.Add(NewTemple);

	MakeOffering(God, 100);
}

void UReligionComponent::PrayAtTemple(int32 TempleIndex)
{
	if (Temples.IsValidIndex(TempleIndex))
	{
		FTempleData& Temple = Temples[TempleIndex];
		Temple.Devotion = FMath::Clamp(Temple.Devotion + 5.0f, 0.0f, 100.0f);

		MakeOffering(Temple.DedicatedGod, 10);
	}
}

float UReligionComponent::GetFavorWithGod(EGod God) const
{
	const float* Favor = GodFavor.Find(God);
	if (Favor)
	{
		return *Favor;
	}
	return 0.0f;
}

FString UReligionComponent::GetGodName(EGod God) const
{
	switch (God)
	{
	case EGod::Ares: return TEXT("Ares");
	case EGod::Gaia: return TEXT("Gaia");
	case EGod::Athena: return TEXT("Athena");
	case EGod::Tyche: return TEXT("Tyche");
	case EGod::Hades: return TEXT("Hades");
	case EGod::Hephaestus: return TEXT("Hephaestus");
	case EGod::Poseidon: return TEXT("Poseidon");
	default: return TEXT("Unknown");
	}
}

FString UReligionComponent::GetGodDomain(EGod God) const
{
	switch (God)
	{
	case EGod::Ares: return TEXT("Krieg");
	case EGod::Gaia: return TEXT("Natur");
	case EGod::Athena: return TEXT("Weisheit");
	case EGod::Tyche: return TEXT("Glück");
	case EGod::Hades: return TEXT("Tod");
	case EGod::Hephaestus: return TEXT("Handwerk");
	case EGod::Poseidon: return TEXT("Meer");
	default: return TEXT("Unknown");
	}
}

void UReligionComponent::UpdateBlessings(float DeltaTime)
{
	for (int32 i = ActiveBlessings.Num() - 1; i >= 0; i--)
	{
		ActiveBlessings[i].Duration -= DeltaTime;

		if (ActiveBlessings[i].Duration <= 0.0f)
		{
			ActiveBlessings[i].bIsActive = false;
			ActiveBlessings.RemoveAt(i);
		}
	}
}

FDivineBlessing UReligionComponent::CreateBlessing(EGod God)
{
	FDivineBlessing Blessing;
	Blessing.God = God;
	Blessing.Duration = 300.0f;

	switch (God)
	{
	case EGod::Ares:
		Blessing.BlessingName = TEXT("Kriegssegen");
		Blessing.BuffStrength = 25.0f;
		break;
	case EGod::Gaia:
		Blessing.BlessingName = TEXT("Natursegen");
		Blessing.BuffStrength = 30.0f;
		break;
	case EGod::Athena:
		Blessing.BlessingName = TEXT("Weisheitssegen");
		Blessing.BuffStrength = 50.0f;
		break;
	case EGod::Tyche:
		Blessing.BlessingName = TEXT("Glückssegen");
		Blessing.BuffStrength = 15.0f;
		break;
	case EGod::Hades:
		Blessing.BlessingName = TEXT("Todessegen");
		Blessing.BuffStrength = 20.0f;
		break;
	case EGod::Hephaestus:
		Blessing.BlessingName = TEXT("Schmiedesegen");
		Blessing.BuffStrength = 40.0f;
		break;
	case EGod::Poseidon:
		Blessing.BlessingName = TEXT("Meeressegen");
		Blessing.BuffStrength = 100.0f;
		break;
	}

	return Blessing;
}

TArray<FDivineBlessing> UReligionComponent::GetActiveBlessings() const
{
	return ActiveBlessings;
}

float UReligionComponent::GetTotalBuffStrength() const
{
	float Total = 0.0f;
	for (const FDivineBlessing& Blessing : ActiveBlessings)
	{
		if (Blessing.bIsActive)
		{
			Total += Blessing.BuffStrength;
		}
	}
	return Total;
}
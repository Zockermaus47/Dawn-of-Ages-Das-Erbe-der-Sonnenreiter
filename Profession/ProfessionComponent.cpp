#include "Profession/ProfessionComponent.h"

UProfessionComponent::UProfessionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryProfession = EProfession::None;
}

void UProfessionComponent::BeginPlay()
{
    Super::BeginPlay();
    
    if (PrimaryProfession != EProfession::None)
    {
        InitializeProfession(PrimaryProfession, PrimaryStats);
    }
    
    SecondaryStats.SetNum(SecondaryProfessions.Num());
    for (int32 i = 0; i < SecondaryProfessions.Num(); i++)
    {
        InitializeProfession(SecondaryProfessions[i], SecondaryStats[i]);
    }
}

void UProfessionComponent::InitializeProfession(EProfession Profession, FProfessionStats& Stats)
{
    Stats.Profession = Profession;
    Stats.Level = 1;
    Stats.CurrentXP = 0;
    Stats.RequiredXP = 100;
    Stats.SkillBonus = 1.0f;
    Stats.TotalActions = 0;
}

void UProfessionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 UProfessionComponent::CalculateRequiredXP(int32 Level) const
{
    return FMath::RoundToInt(100.0f * FMath::Pow(1.5f, Level - 1));
}

void UProfessionComponent::SetPrimaryProfession(EProfession NewProfession)
{
    if (NewProfession == EProfession::None) return;
    
    PrimaryProfession = NewProfession;
    InitializeProfession(NewProfession, PrimaryStats);
    UE_LOG(LogTemp, Log, TEXT("Hauptberuf gesetzt: %d"), (int32)NewProfession);
}

void UProfessionComponent::AddSecondaryProfession(EProfession Profession)
{
    if (Profession == EProfession::None) return;
    if (HasProfession(Profession)) return;

    SecondaryProfessions.Add(Profession);
    
    FProfessionStats NewStats;
    InitializeProfession(Profession, NewStats);
    SecondaryStats.Add(NewStats);
    
    UE_LOG(LogTemp, Log, TEXT("Nebenberuf hinzugefügt: %d"), (int32)Profession);
}

void UProfessionComponent::RemoveProfession(EProfession Profession)
{
    if (PrimaryProfession == Profession)
    {
        PrimaryProfession = EProfession::None;
        return;
    }

    for (int32 i = 0; i < SecondaryProfessions.Num(); i++)
    {
        if (SecondaryProfessions[i] == Profession)
        {
            SecondaryProfessions.RemoveAt(i);
            if (i < SecondaryStats.Num())
            {
                SecondaryStats.RemoveAt(i);
            }
            return;
        }
    }
}

bool UProfessionComponent::HasProfession(EProfession Profession) const
{
    if (PrimaryProfession == Profession) return true;
    
    for (EProfession P : SecondaryProfessions)
    {
        if (P == Profession) return true;
    }
    return false;
}

int32 UProfessionComponent::GetProfessionLevel(EProfession Profession) const
{
    if (PrimaryProfession == Profession) return PrimaryStats.Level;
    
    for (int32 i = 0; i < SecondaryProfessions.Num(); i++)
    {
        if (SecondaryProfessions[i] == Profession) 
        {
            return SecondaryStats[i].Level;
        }
    }
    return 0;
}

void UProfessionComponent::AddXP(EProfession Profession, int32 XPAmount)
{
    if (PrimaryProfession != Profession) return;
    
    PrimaryStats.CurrentXP += XPAmount;
    UE_LOG(LogTemp, Log, TEXT("XP erhalten: %d für Beruf %d"), XPAmount, (int32)Profession);

    while (PrimaryStats.CurrentXP >= PrimaryStats.RequiredXP)
    {
        LevelUp(Profession);
    }
}

bool UProfessionComponent::LevelUp(EProfession Profession)
{
    if (PrimaryProfession != Profession) return false;

    PrimaryStats.CurrentXP -= PrimaryStats.RequiredXP;
    PrimaryStats.Level++;
    PrimaryStats.RequiredXP = CalculateRequiredXP(PrimaryStats.Level);
    PrimaryStats.SkillBonus = 1.0f + (PrimaryStats.Level * 0.1f);
    
    UE_LOG(LogTemp, Log, TEXT("Level Up! %d jetzt Level %d"), (int32)Profession, PrimaryStats.Level);
    return true;
}

float UProfessionComponent::GetSkillBonus(EProfession Profession) const
{
    if (PrimaryProfession == Profession) return PrimaryStats.SkillBonus;
    
    for (int32 i = 0; i < SecondaryProfessions.Num(); i++)
    {
        if (SecondaryProfessions[i] == Profession) 
        {
            return SecondaryStats[i].SkillBonus;
        }
    }
    return 1.0f;
}

int32 UProfessionComponent::GetTotalLevel() const
{
    int32 Total = PrimaryStats.Level;
    for (const FProfessionStats& Stats : SecondaryStats)
    {
        Total += Stats.Level;
    }
    return Total;
}

FProfessionStats UProfessionComponent::GetProfessionStats(EProfession Profession) const
{
	if (PrimaryProfession == Profession) return PrimaryStats;
    
	for (int32 i = 0; i < SecondaryProfessions.Num(); i++)
	{
		if (SecondaryProfessions[i] == Profession) 
		{
			return SecondaryStats[i];
		}
	}
	return FProfessionStats();
}

TArray<EProfession> UProfessionComponent::GetAllProfessions() const
{
    TArray<EProfession> Result;
    Result.Add(PrimaryProfession);
    Result.Append(SecondaryProfessions);
    return Result;
}
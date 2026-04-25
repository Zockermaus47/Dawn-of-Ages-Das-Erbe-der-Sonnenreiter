#include "EpochSystemComponent.h"
#include "DawnOfAgesGameData.h"
#include "Net/UnrealNetwork.h"

UEpochSystemComponent::UEpochSystemComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicated(true);
}

void UEpochSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEpochSystemComponent::AdvanceTime(float DeltaHours)
{
    if (!HasAuthority())
    {
        return;
    }

    GameTimeHours += DeltaHours;
    OnEpochProgress.Broadcast(GetEpochProgress());
    CheckEpochTransition();
}

void UEpochSystemComponent::SetEpoch(EEpoch NewEpoch)
{
    if (CurrentEpoch != NewEpoch)
    {
        EEpoch OldEpoch = CurrentEpoch;
        CurrentEpoch = NewEpoch;
        OnEpochChanged.Broadcast(NewEpoch);
    }
}

void UEpochSystemComponent::CheckEpochTransition()
{
    EEpoch NewEpoch = EEpoch::StoneAge;

    if (GameTimeHours >= HoursToMedievalAge)
    {
        NewEpoch = EEpoch::MedievalAge;
    }
    else if (GameTimeHours >= HoursToBronzeAge)
    {
        NewEpoch = EEpoch::BronzeAge;
    }

    if (NewEpoch != CurrentEpoch)
    {
        SetEpoch(NewEpoch);
    }
}

float UEpochSystemComponent::GetEpochProgress() const
{
    if (CurrentEpoch == EEpoch::StoneAge)
    {
        return FMath::Clamp(GameTimeHours / HoursToBronzeAge, 0.0f, 1.0f);
    }
    else if (CurrentEpoch == EEpoch::BronzeAge)
    {
        return FMath::Clamp((GameTimeHours - HoursToBronzeAge) / (HoursToMedievalAge - HoursToBronzeAge), 0.0f, 1.0f);
    }
    return 1.0f;
}

FString UEpochSystemComponent::GetEpochDisplayName() const
{
    switch (CurrentEpoch)
    {
        case EEpoch::StoneAge: return "Steinzeit";
        case EEpoch::BronzeAge: return "Bronzezeit";
        case EEpoch::MedievalAge: return "Mittelalter";
        default: return "Unbekannt";
    }
}

bool UEpochSystemComponent::IsItemAvailableInEpoch(FName ItemID) const
{
    return true;
}

bool UEpochSystemComponent::CanCraftRecipeInCurrentEpoch(FName RecipeID) const
{
    return true;
}

void UEpochSystemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UEpochSystemComponent, CurrentEpoch);
    DOREPLIFETIME(UEpochSystemComponent, GameTimeHours);
}
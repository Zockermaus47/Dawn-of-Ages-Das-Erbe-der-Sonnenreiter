#include "Harvesting/HarvestableStick.h"

AHarvestableStick::AHarvestableStick()
{
    RequiredToolType = FName("Hand");
    MaxHealth = 10.0f;
    StickType = EStickType::SmallStick;
    bIsPickupOnly = true;
    AvailableEpoch = EEpoch::StoneAge;

    SetupResourceDrops();
}

void AHarvestableStick::SetupResourceDrops()
{
    EResourceType Resource = EResourceType::Stick;
    switch (StickType)
    {
        case EStickType::SmallStick:
            Resource = EResourceType::Stick;
            StickAmount = 1.0f;
            break;
        case EStickType::MediumStick:
            Resource = EResourceType::Stick;
            StickAmount = 2.0f;
            break;
        case EStickType::LargeBranch:
        case EStickType::FallenBranch:
            Resource = EResourceType::Branch;
            StickAmount = 3.0f;
            break;
    }

    FResourceDrop Drop;
    Drop.ResourceType = Resource;
    Drop.MinAmount = FMath::RoundToInt(StickAmount);
    Drop.MaxAmount = FMath::RoundToInt(StickAmount * 1.5f);
    Drop.DropChance = 1.0f;
    ResourceDrops.Add(Drop);
}

void AHarvestableStick::BeginPlay()
{
    Super::BeginPlay();
    
    if (bIsPickupOnly)
    {
        MaxHealth = 1.0f;
        CurrentHealth = 1.0f;
    }
}

bool AHarvestableStick::CanPickup() const
{
    return bIsPickupOnly;
}

void AHarvestableStick::Pickup()
{
    if (!CanPickup())
    {
        UE_LOG(LogTemp, Warning, TEXT("Kann nicht aufgehoben werden!"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Stock aufgehoben!"));
    
    SpawnResources();
    Destroy();
}
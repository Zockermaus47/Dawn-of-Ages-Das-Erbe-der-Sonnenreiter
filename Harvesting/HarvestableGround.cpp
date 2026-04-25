#include "Harvesting/HarvestableGround.h"

AHarvestableGround::AHarvestableGround()
{
    RequiredToolType = FName("Shovel");
    MaxHealth = 50.0f;
    GroundType = EGroundType::Clay;
    AvailableEpoch = EEpoch::StoneAge;

    SetupResourceDrops();
}

void AHarvestableGround::SetupResourceDrops()
{
    EResourceType Resource = EResourceType::Clay;
    switch (GroundType)
    {
        case EGroundType::Clay:
        case EGroundType::ClayDeposit:
            Resource = EResourceType::Clay;
            break;
        case EGroundType::Sand:
            Resource = EResourceType::Sand;
            break;
        case EGroundType::Gravel:
            Resource = EResourceType::Gravel;
            break;
        case EGroundType::Dirt:
            Resource = EResourceType::Clay;
            break;
    }

    FResourceDrop Drop;
    Drop.ResourceType = Resource;
    Drop.MinAmount = 2;
    Drop.MaxAmount = 4;
    Drop.DropChance = 1.0f;
    ResourceDrops.Add(Drop);
}

void AHarvestableGround::OnHit(AActor* Attacker, float Damage, FName ToolType)
{
    if (ToolType == FName("Hand"))
    {
        Damage *= 0.5f;
    }

    Super::OnHit(Attacker, Damage, ToolType);
}

bool AHarvestableGround::IsDepleted() const
{
    return CurrentHarvests >= MaxHarvests;
}

void AHarvestableGround::Harvest()
{
    if (IsDepleted())
    {
        UE_LOG(LogTemp, Warning, TEXT("Ressource erschöpft!"));
        
        if (bCanRegenerate)
        {
            StartRegeneration();
        }
        else
        {
            Destroy();
        }
        return;
    }

    CurrentHarvests++;
    SpawnResources();

    UE_LOG(LogTemp, Log, TEXT("Gesammelt! %d / %d"), CurrentHarvests, MaxHarvests);

    PlayHitEffect();

    if (IsDepleted())
    {
        if (bCanRegenerate)
        {
            StartRegeneration();
        }
        else
        {
            Destroy();
        }
    }
}

void AHarvestableGround::StartRegeneration()
{
    UE_LOG(LogTemp, Log, TEXT("Regeneration startet in %.0f Sekunden"), RegenerationTime);

    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);

    GetWorld()->GetTimerManager().SetTimer(
        RegenerationTimer,
        this,
        &AHarvestableGround::Regenerate,
        RegenerationTime,
        false
    );
}

void AHarvestableGround::Regenerate()
{
    UE_LOG(LogTemp, Log, TEXT("Ressource regeneriert!"));

    CurrentHarvests = 0;
    CurrentHealth = MaxHealth;

    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
}
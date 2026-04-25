#include "Harvesting/HarvestableBark.h"

AHarvestableBark::AHarvestableBark()
{
    RequiredToolType = FName("Knife");
    MaxHealth = 30.0f;
    AvailableEpoch = EEpoch::StoneAge;

    FResourceDrop BarkDrop;
    BarkDrop.ResourceType = EResourceType::Bark;
    BarkDrop.MinAmount = FMath::RoundToInt(BarkAmount);
    BarkDrop.MaxAmount = FMath::RoundToInt(BarkAmount * 1.5f);
    BarkDrop.DropChance = 1.0f;
    ResourceDrops.Add(BarkDrop);
}

void AHarvestableBark::OnHit(AActor* Attacker, float Damage, FName ToolType)
{
    if (!IsCorrectTool(ToolType))
    {
        UE_LOG(LogTemp, Warning, TEXT("Benötigt Messer!"));
        return;
    }

    Super::OnHit(Attacker, Damage, ToolType);

    if (CurrentHealth <= 0.0f && !bIsDepleted)
    {
        HarvestBark();
    }
}

void AHarvestableBark::HarvestBark()
{
    if (bIsDepleted)
    {
        UE_LOG(LogTemp, Warning, TEXT("Rinde bereits gesammelt!"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Sammle Rinde..."));

    bIsDepleted = true;
    SpawnResources();

    if (bFromLivingTree)
    {
        StartRegrowth();
    }
    else
    {
        Destroy();
    }
}

void AHarvestableBark::StartRegrowth()
{
    UE_LOG(LogTemp, Log, TEXT("Rinde wächst nach in %.0f Sekunden"), RegrowthTime);

    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);

    GetWorld()->GetTimerManager().SetTimer(
        RegrowthTimer,
        this,
        &AHarvestableBark::CompleteRegrowth,
        RegrowthTime,
        false
    );
}

void AHarvestableBark::CompleteRegrowth()
{
    UE_LOG(LogTemp, Log, TEXT("Rinde nachgewachsen!"));

    bIsDepleted = false;
    CurrentHealth = MaxHealth;

    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
}
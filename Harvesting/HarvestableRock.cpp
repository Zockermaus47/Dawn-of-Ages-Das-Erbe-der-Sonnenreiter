#include "Harvesting/HarvestableRock.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AHarvestableRock::AHarvestableRock()
{
    RequiredToolType = FName("Pickaxe");
    MaxHealth = 200.0f;
    RockState = ERockState::Large;
    RockType = ERockType::Granite;
    PrimaryResource = EResourceType::Stone_Granite;
    AvailableEpoch = EEpoch::StoneAge;

    SetupResourceDrops();
}

void AHarvestableRock::SetupResourceDrops()
{
    FResourceDrop StoneDrop;
    StoneDrop.ResourceType = PrimaryResource;
    StoneDrop.MinAmount = 3;
    StoneDrop.MaxAmount = 6;
    StoneDrop.DropChance = 1.0f;
    ResourceDrops.Add(StoneDrop);
}

void AHarvestableRock::BeginPlay()
{
    Super::BeginPlay();
    UpdateMesh();

    if (bIsOreVein)
    {
        RockType = ERockType::OreVein;
        OreVisibility = 0.0f;
    }
}

void AHarvestableRock::OnHit(AActor* Attacker, float Damage, FName ToolType)
{
    if (!IsCorrectTool(ToolType))
    {
        UE_LOG(LogTemp, Warning, TEXT("Benötigt Spitzhacke!"));
        return;
    }

    if (bIsOreVein && OreVisibility < 1.0f)
    {
        OreVisibility += 0.1f;
        OreVisibility = FMath::Clamp(OreVisibility, 0.0f, 1.0f);
        
        if (OreVisibility >= 1.0f)
        {
            RevealOre();
        }
    }

    Super::OnHit(Attacker, Damage, ToolType);

    float HealthPercent = CurrentHealth / MaxHealth;
    
    if (HealthPercent <= 0.66f && RockState == ERockState::Large)
    {
        BreakIntoSmaller();
    }
    else if (HealthPercent <= 0.33f && RockState == ERockState::Medium)
    {
        BreakIntoSmaller();
    }
}

void AHarvestableRock::BreakIntoSmaller()
{
    UE_LOG(LogTemp, Log, TEXT("Stein zerbricht in kleinere Teile!"));

    if (RockState == ERockState::Large)
    {
        RockState = ERockState::Medium;
    }
    else if (RockState == ERockState::Medium)
    {
        RockState = ERockState::Small;
    }
    else if (RockState == ERockState::Small)
    {
        RockState = ERockState::Fragments;
    }

    UpdateMesh();

    int32 FragmentCount = FMath::RandRange(2, 4);
    for (int32 i = 0; i < FragmentCount; i++)
    {
        FVector SpawnLocation = GetActorLocation() + FVector(
            FMath::RandRange(-150.0f, 150.0f),
            FMath::RandRange(-150.0f, 150.0f),
            50.0f
        );
    }
}

void AHarvestableRock::RevealOre()
{
    UE_LOG(LogTemp, Log, TEXT("Erzader freigelegt!"));

    if (MeshComponent)
    {
    }

    bIsOreVein = true;
}

bool AHarvestableRock::CanMineOre() const
{
    return bIsOreVein && OreVisibility >= 1.0f;
}

void AHarvestableRock::UpdateMesh()
{
    if (!MeshComponent) return;

    UStaticMesh* NewMesh = nullptr;

    switch (RockState)
    {
        case ERockState::Large:
            NewMesh = LargeMesh;
            break;
        case ERockState::Medium:
            NewMesh = MediumMesh;
            break;
        case ERockState::Small:
            NewMesh = SmallMesh;
            break;
        case ERockState::Fragments:
            OnDestroyed();
            return;
    }

    if (NewMesh)
    {
        MeshComponent->SetStaticMesh(NewMesh);
        
        float Scale = 1.0f;
        switch (RockState)
        {
            case ERockState::Medium: Scale = 0.6f; break;
            case ERockState::Small: Scale = 0.3f; break;
        }
        MeshComponent->SetWorldScale3D(FVector(Scale));
    }
}

void AHarvestableRock::OnDestroyed_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("Stein komplett zerstört!"));
    SpawnResources();
    Destroy();
}
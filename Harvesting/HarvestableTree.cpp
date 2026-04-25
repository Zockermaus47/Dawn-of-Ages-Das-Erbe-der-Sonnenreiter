#include "Harvesting/HarvestableTree.h"
#include "Components/StaticMeshComponent.h"

AHarvestableTree::AHarvestableTree()
{
    RequiredToolType = FName("Axe");
    MaxHealth = 150.0f;
    TreeState = ETreeState::Standing;
    TreeType = ETreeType::Oak;
    AvailableEpoch = EEpoch::StoneAge;

    TrunkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trunk"));
    TrunkMesh->SetupAttachment(RootComponent);

    BranchesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Branches"));
    BranchesMesh->SetupAttachment(TrunkMesh);

    SetupResourceDrops();
}

void AHarvestableTree::SetupResourceDrops()
{
    EResourceType WoodType = EResourceType::Wood_Oak;
    switch (TreeType)
    {
        case ETreeType::Oak: WoodType = EResourceType::Wood_Oak; break;
        case ETreeType::Birch: WoodType = EResourceType::Wood_Birch; break;
        case ETreeType::Pine: WoodType = EResourceType::Wood_Pine; break;
    }

    FResourceDrop WoodDrop;
    WoodDrop.ResourceType = WoodType;
    WoodDrop.MinAmount = FMath::RoundToInt(WoodAmount);
    WoodDrop.MaxAmount = FMath::RoundToInt(WoodAmount * 1.5f);
    WoodDrop.DropChance = 1.0f;
    ResourceDrops.Add(WoodDrop);

    FResourceDrop StickDrop;
    StickDrop.ResourceType = EResourceType::Stick;
    StickDrop.MinAmount = FMath::RoundToInt(StickAmount);
    StickDrop.MaxAmount = FMath::RoundToInt(StickAmount * 1.5f);
    StickDrop.DropChance = 0.8f;
    StickDrop.DropActorClass = StickActorClass;
    ResourceDrops.Add(StickDrop);

    FResourceDrop BarkDrop;
    BarkDrop.ResourceType = EResourceType::Bark;
    BarkDrop.MinAmount = FMath::RoundToInt(BarkAmount);
    BarkDrop.MaxAmount = FMath::RoundToInt(BarkAmount * 1.5f);
    BarkDrop.DropChance = 0.6f;
    ResourceDrops.Add(BarkDrop);
}

void AHarvestableTree::OnDestroyed_Implementation()
{
    if (TreeState == ETreeState::Standing)
    {
        StartFalling();
    }
    else if (TreeState == ETreeState::Fallen || TreeState == ETreeState::LogOnly)
    {
        Super::OnDestroyed_Implementation();
    }
}

void AHarvestableTree::StartFalling()
{
    UE_LOG(LogTemp, Log, TEXT("Baum fällt!"));
    
    TreeState = ETreeState::Falling;

    if (TrunkMesh)
    {
        TrunkMesh->SetSimulatePhysics(true);
        TrunkMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

        FVector FallDirection = FVector(
            FMath::RandRange(-1.0f, 1.0f),
            FMath::RandRange(-1.0f, 1.0f),
            0.0f
        ).GetSafeNormal();

        TrunkMesh->AddImpulseAtLocation(
            FallDirection * 50000.0f,
            GetActorLocation() + FVector(0, 0, 500.0f)
        );
    }

    GetWorld()->GetTimerManager().SetTimer(
        FallTimerHandle,
        this,
        &AHarvestableTree::CompleteFall,
        FallDuration,
        false
    );
}

void AHarvestableTree::CompleteFall()
{
    UE_LOG(LogTemp, Log, TEXT("Baum ist gefallen!"));
    
    TreeState = ETreeState::Fallen;

    if (TrunkMesh)
    {
        TrunkMesh->SetSimulatePhysics(false);
    }

    for (int32 i = 0; i < BranchCount; i++)
    {
        if (BranchActorClass)
        {
            FVector SpawnLocation = GetActorLocation() + FVector(
                FMath::RandRange(-300.0f, 300.0f),
                FMath::RandRange(-300.0f, 300.0f),
                20.0f
            );

            GetWorld()->SpawnActor<AActor>(
                BranchActorClass,
                SpawnLocation,
                FRotator::ZeroRotator
            );
        }
    }
}

bool AHarvestableTree::CanRemoveBranches() const
{
    return TreeState == ETreeState::Fallen;
}

bool AHarvestableTree::CanSplitLog() const
{
    return TreeState == ETreeState::LogOnly;
}

void AHarvestableTree::RemoveBranches()
{
    if (!CanRemoveBranches())
    {
        UE_LOG(LogTemp, Warning, TEXT("Baum muss erst gefällt sein!"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Entferne Äste..."));

    if (BranchesMesh)
    {
        BranchesMesh->SetVisibility(false);
    }

    TreeState = ETreeState::LogOnly;
}

void AHarvestableTree::SplitLog()
{
    if (!CanSplitLog())
    {
        UE_LOG(LogTemp, Warning, TEXT("Äste müssen erst entfernt werden!"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Zerlege Stamm..."));

    TreeState = ETreeState::Harvested;
    SpawnResources();
    Destroy();
}
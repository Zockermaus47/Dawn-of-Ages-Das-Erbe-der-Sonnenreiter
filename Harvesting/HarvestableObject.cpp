#include "Harvesting/HarvestableObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AHarvestableObject::AHarvestableObject()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetSimulatePhysics(false);
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
    InteractionBox->SetupAttachment(RootComponent);
    InteractionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
    InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    CurrentHealth = MaxHealth;
    CurrentStage = EHarvestStage::Intact;
    RequiredToolType = FName("Axe");
}

void AHarvestableObject::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = MaxHealth;
}

void AHarvestableObject::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AHarvestableObject::OnHit(AActor* Attacker, float Damage, FName ToolType)
{
    if (!IsCorrectTool(ToolType))
    {
        UE_LOG(LogTemp, Warning, TEXT("Falsches Werkzeug! Benötigt: %s"), *RequiredToolType.ToString());
        return;
    }

    CurrentHealth -= Damage;
    CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);

    UE_LOG(LogTemp, Log, TEXT("Hit! Health: %f / %f"), CurrentHealth, MaxHealth);

    UpdateHarvestStage();
    PlayHitEffect();

    if (CurrentHealth <= 0.0f)
    {
        OnDestroyed();
    }
}

bool AHarvestableObject::IsCorrectTool(FName ToolType) const
{
    if (ToolType == FName("Hand"))
        return true;

    return ToolType == RequiredToolType;
}

void AHarvestableObject::UpdateHarvestStage()
{
    float HealthPercent = CurrentHealth / MaxHealth;

    if (HealthPercent > 0.66f)
    {
        CurrentStage = EHarvestStage::Intact;
    }
    else if (HealthPercent > 0.33f)
    {
        CurrentStage = EHarvestStage::Damaged;
    }
    else if (HealthPercent > 0.0f)
    {
        CurrentStage = EHarvestStage::Critical;
    }
    else
    {
        CurrentStage = EHarvestStage::Destroyed;
    }
}

int32 AHarvestableObject::CalculateDropAmount(const FResourceDrop& Drop) const
{
    if (Drop.MinAmount >= Drop.MaxAmount)
        return Drop.MinAmount;

    return FMath::RandRange(Drop.MinAmount, Drop.MaxAmount);
}

void AHarvestableObject::SpawnResources()
{
    for (const FResourceDrop& Drop : ResourceDrops)
    {
        if (FMath::FRand() > Drop.DropChance)
            continue;

        int32 Amount = CalculateDropAmount(Drop);

        for (int32 i = 0; i < Amount; i++)
        {
            if (Drop.DropActorClass)
            {
                FVector SpawnLocation = GetActorLocation() + FVector(
                    FMath::RandRange(-100.0f, 100.0f),
                    FMath::RandRange(-100.0f, 100.0f),
                    50.0f
                );

                FRotator SpawnRotation = FRotator::ZeroRotator;

                AActor* DroppedResource = GetWorld()->SpawnActor<AActor>(
                    Drop.DropActorClass,
                    SpawnLocation,
                    SpawnRotation
                );

                if (DroppedResource)
                {
                    UStaticMeshComponent* DropMesh = DroppedResource->FindComponentByClass<UStaticMeshComponent>();
                    if (DropMesh && DropMesh->IsSimulatingPhysics())
                    {
                        FVector Impulse = FVector(
                            FMath::RandRange(-200.0f, 200.0f),
                            FMath::RandRange(-200.0f, 200.0f),
                            FMath::RandRange(100.0f, 300.0f)
                        );
                        DropMesh->AddImpulse(Impulse, NAME_None, true);
                    }
                }
            }
        }
    }
}

void AHarvestableObject::PlayHitEffect_Implementation()
{
    if (MeshComponent)
    {
        FRotator CurrentRotation = MeshComponent->GetRelativeRotation();
        float ShakeAmount = 5.0f;
        
        FRotator ShakeRotation = FRotator(
            FMath::RandRange(-ShakeAmount, ShakeAmount),
            0.0f,
            FMath::RandRange(-ShakeAmount, ShakeAmount)
        );

        MeshComponent->SetRelativeRotation(CurrentRotation + ShakeRotation);

        GetWorld()->GetTimerManager().SetTimer(
            ShakeTimerHandle,
            this,
            &AHarvestableObject::StopShaking,
            0.2f,
            false
        );
    }
}

void AHarvestableObject::StopShaking()
{
    if (MeshComponent)
    {
        MeshComponent->SetRelativeRotation(FRotator::ZeroRotator);
    }
}

void AHarvestableObject::OnDestroyed_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("Objekt zerstört! Spawne Ressourcen..."));
    SpawnResources();
    Destroy();
}
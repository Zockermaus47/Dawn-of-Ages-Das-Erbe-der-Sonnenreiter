#include "Building/BuildingComponent.h"
#include "Inventory/InventoryComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UBuildingComponent::UBuildingComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    BuildingRange = 500.0f;
}

void UBuildingComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

const FBuildingPiece* UBuildingComponent::GetBuildingRecipe(FName BuildingID) const
{
    for (const FBuildingPiece& Piece : BuildingRecipes)
    {
        if (Piece.BuildingID == BuildingID) return &Piece;
    }
    return nullptr;
}

bool UBuildingComponent::CanBuild(FName BuildingID) const
{
    const FBuildingPiece* Recipe = GetBuildingRecipe(BuildingID);
    if (!Recipe) return false;

    UInventoryComponent* Inventory = GetOwner()->FindComponentByClass<UInventoryComponent>();
    if (!Inventory) return false;

    return Inventory->HasItem(Recipe->RequiredItemID, Recipe->RequiredQuantity);
}

AActor* UBuildingComponent::Build(FName BuildingID, FVector Location, FRotator Rotation)
{
    const FBuildingPiece* Recipe = GetBuildingRecipe(BuildingID);
    if (!Recipe)
    {
        UE_LOG(LogTemp, Warning, TEXT("Building recipe not found: %s"), *BuildingID.ToString());
        return nullptr;
    }

    UInventoryComponent* Inventory = GetOwner()->FindComponentByClass<UInventoryComponent>();
    if (!Inventory || !Inventory->RemoveItem(Recipe->RequiredItemID, Recipe->RequiredQuantity))
    {
        UE_LOG(LogTemp, Warning, TEXT("Not enough materials!"));
        return nullptr;
    }

    UE_LOG(LogTemp, Log, TEXT("Building: %s"), *Recipe->BuildingName.ToString());
    
    FActorBuilding NewBuilding;
    NewBuilding.BuildingID = BuildingID;
    NewBuilding.CurrentHealth = Recipe->Health;
    NewBuilding.OwnerID = GetOwner()->GetFName();
    NewBuilding.bIsDamaged = false;
    PlacedBuildings.Add(NewBuilding);

    return nullptr;
}

bool UBuildingComponent::Demolish(AActor* Building)
{
    for (int32 i = 0; i < PlacedBuildings.Num(); i++)
    {
        if (PlacedBuildings[i].BuildingActor == Building)
        {
            const FBuildingPiece* Recipe = GetBuildingRecipe(PlacedBuildings[i].BuildingID);
            if (Recipe)
            {
                UInventoryComponent* Inventory = GetOwner()->FindComponentByClass<UInventoryComponent>();
                if (Inventory)
                {
                    Inventory->AddItem(Recipe->RequiredItemID, Recipe->RequiredQuantity);
                }
            }
            PlacedBuildings.RemoveAt(i);
            Building->Destroy();
            return true;
        }
    }
    return false;
}

bool UBuildingComponent::Repair(AActor* Building, int32 RepairAmount)
{
    for (FActorBuilding& Placed : PlacedBuildings)
    {
        if (Placed.BuildingActor == Building)
        {
            const FBuildingPiece* Recipe = GetBuildingRecipe(Placed.BuildingID);
            if (!Recipe) return false;

            Placed.CurrentHealth = FMath::Clamp(Placed.CurrentHealth + RepairAmount, 0, Recipe->Health);
            Placed.bIsDamaged = Placed.CurrentHealth < Recipe->Health;
            return true;
        }
    }
    return false;
}

void UBuildingComponent::DamageBuilding(AActor* Building, int32 Damage)
{
    for (FActorBuilding& Placed : PlacedBuildings)
    {
        if (Placed.BuildingActor == Building)
        {
            Placed.CurrentHealth -= Damage;
            Placed.bIsDamaged = Placed.CurrentHealth < 0;

            if (Placed.CurrentHealth <= 0)
            {
                Demolish(Building);
            }
            break;
        }
    }
}

bool UBuildingComponent::UpgradeBuilding(AActor* Building)
{
    return false;
}

TArray<FActorBuilding> UBuildingComponent::GetBuildingsInRadius(FVector Location, float Radius) const
{
    TArray<FActorBuilding> Results;
    for (const FActorBuilding& Placed : PlacedBuildings)
    {
        if (Placed.BuildingActor)
        {
            float Distance = FVector::Dist(Location, Placed.BuildingActor->GetActorLocation());
            if (Distance <= Radius) Results.Add(Placed);
        }
    }
    return Results;
}

int32 UBuildingComponent::GetBuildingCount() const
{
    return PlacedBuildings.Num();
}

USiegeComponent::USiegeComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bIsFiring = false;
}

void USiegeComponent::BeginPlay()
{
    Super::BeginPlay();
}

void USiegeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USiegeComponent::FireAt(AActor* Target)
{
    if (!Target || !bIsFiring) return;
    if (!Target->IsValidLowLevel()) return;

    float Distance = FVector::Dist(GetOwner()->GetActorLocation(), Target->GetActorLocation());
    if (Distance > CurrentWeapon.Range)
    {
        UE_LOG(LogTemp, Warning, TEXT("Target out of range!"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Siege weapon firing at target!"));

    UBuildingComponent* BuildingComp = GetOwner()->FindComponentByClass<UBuildingComponent>();
    if (BuildingComp)
    {
        BuildingComp->DamageBuilding(Target, CurrentWeapon.Damage);
    }
}

void USiegeComponent::SelectWeapon(FSiegeWeapon Weapon)
{
    CurrentWeapon = Weapon;
    UE_LOG(LogTemp, Log, TEXT("Selected weapon: %s"), *Weapon.WeaponName.ToString());
}

TArray<AActor*> USiegeComponent::GetTargetsInRange() const
{
    TArray<AActor*> Results;
    UWorld* World = GetWorld();
    if (!World) return Results;

    FVector Location = GetOwner()->GetActorLocation();
    TArray<AActor*> OutActors;
    UKismetSystemLibrary::SphereOverlapActors(World, Location, CurrentWeapon.Range, {}, AActor::StaticClass(), {}, OutActors);

    for (AActor* Actor : OutActors)
    {
        if (Actor && Actor != GetOwner())
        {
            Results.Add(Actor);
        }
    }
    return Results;
}
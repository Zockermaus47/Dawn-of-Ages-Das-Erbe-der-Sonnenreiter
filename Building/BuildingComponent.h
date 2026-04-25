#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"

UENUM(BlueprintType)
enum class EBuildCategory : uint8
{
    Wall UMETA(DisplayName = "Mauer"),
    Floor UMETA(DisplayName = "Boden"),
    Roof UMETA(DisplayName = "Dach"),
    Door UMETA(DisplayName = "Tür"),
    Window UMETA(DisplayName = "Fenster"),
    Tower UMETA(DisplayName = "Turm"),
    Gate UMETA(DisplayName = "Tor"),
    Stairs UMETA(DisplayName = "Treppe"),
    Furniture UMETA(DisplayName = "Möbel"),
    Trap UMETA(DisplayName = "Falle")
};

UENUM(BlueprintType)
enum class EBuildingPermission : uint8
{
    Owner UMETA(DisplayName = "Eigentümer"),
    Guild UMETA(DisplayName = "Gilde"),
    Anyone UMETA(DisplayName = "Jeder")
};

USTRUCT(BlueprintType)
struct FBuildingPiece
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BuildingID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BuildingName = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBuildingCategory Category = EBuildingCategory::Wall;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RequiredItemID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredQuantity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Health = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BuildTime = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredLevel = 1;
};

USTRUCT(BlueprintType)
struct FActorBuilding
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* BuildingActor = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BuildingID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentHealth = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName OwnerID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsDamaged = false;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_DAWNOFAGES_API UBuildingComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UBuildingComponent();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
    TArray<FBuildingPiece> BuildingRecipes;

    UPROPERTY(BlueprintReadOnly, Category = "Building")
    TArray<FActorBuilding> PlacedBuildings;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
    float BuildingRange = 500.0f;

    UFUNCTION(BlueprintCallable, Category = "Building")
    bool CanBuild(FName BuildingID) const;

    UFUNCTION(BlueprintCallable, Category = "Building")
    AActor* Build(FName BuildingID, FVector Location, FRotator Rotation);

    UFUNCTION(BlueprintCallable, Category = "Building")
    bool Demolish(AActor* Building);

    UFUNCTION(BlueprintCallable, Category = "Building")
    bool Repair(AActor* Building, int32 RepairAmount);

    UFUNCTION(BlueprintCallable, Category = "Building")
    void DamageBuilding(AActor* Building, int32 Damage);

    UFUNCTION(BlueprintCallable, Category = "Building")
    bool UpgradeBuilding(AActor* Building);

    UFUNCTION(BlueprintCallable, Category = "Building")
    TArray<FActorBuilding> GetBuildingsInRadius(FVector Location, float Radius) const;

    UFUNCTION(BlueprintCallable, Category = "Building")
    int32 GetBuildingCount() const;

private:
    const FBuildingPiece* GetBuildingRecipe(FName BuildingID) const;
};

USTRUCT(BlueprintType)
struct FSiegeWeapon
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName WeaponName = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Damage = 50;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FireRate = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Range = 1000.0f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_DAWNOFAGES_API USiegeComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    USiegeComponent();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Siege")
    TArray<FSiegeWeapon> AvailableWeapons;

    UPROPERTY(BlueprintReadOnly, Category = "Siege")
    FSiegeWeapon CurrentWeapon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Siege")
    bool bIsFiring = false;

    UFUNCTION(BlueprintCallable, Category = "Siege")
    void FireAt(AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "Siege")
    void SelectWeapon(FSiegeWeapon Weapon);

    UFUNCTION(BlueprintCallable, Category = "Siege")
    TArray<AActor*> GetTargetsInRange() const;
};
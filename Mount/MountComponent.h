#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MountComponent.generated.h"

UENUM(BlueprintType)
enum class EMountCategory : uint8
{
    Horse UMETA(DisplayName = "Pferd"),
    Donkey UMETA(DisplayName = "Esel"),
    Ox UMETA(DisplayName = "Ochse"),
    Cow UMETA(DisplayName = "Kuh")
};

UENUM(BlueprintType)
enum class EMountState : uint8
{
    Idle UMETA(DisplayName = "Stehend"),
    Walking UMETA(DisplayName = "Gehend"),
    Trotting UMETA(DisplayName = "Trabend"),
    Galloping UMETA(DisplayName = "Galoppierend"),
    Riding UMETA(DisplayName = "Geritten")
};

USTRUCT(BlueprintType)
struct FMountInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MountID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MountName = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMountType Type = EMountType::Horse;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Speed = 600.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TrotSpeed = 1200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GallopSpeed = 2000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Stamina = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxStamina = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BreedTier = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsTamed = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName OwnerID = NAME_None;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_DAWNOFAGES_API UMountComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UMountComponent();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mount")
    TArray<FMountData> OwnedMounts;

    UPROPERTY(BlueprintReadOnly, Category = "Mount")
    FMountData ActiveMount;

    UPROPERTY(BlueprintReadOnly, Category = "Mount")
    AActor* MountActor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mount")
    float MountSpeedMultiplier = 1.0f;

    UFUNCTION(BlueprintCallable, Category = "Mount")
    bool TameMount(AActor* WildMount);

    UFUNCTION(BlueprintCallable, Category = "Mount")
    bool Mount(FName MountID);

    UFUNCTION(BlueprintCallable, Category = "Mount")
    bool Dismount();

    UFUNCTION(BlueprintCallable, Category = "Mount")
    bool AddMount(FMountData MountData);

    UFUNCTION(BlueprintCallable, Category = "Mount")
    bool RemoveMount(FName MountID);

    UFUNCTION(BlueprintCallable, Category = "Mount")
    FMountData GetMount(FName MountID);

    UFUNCTION(BlueprintCallable, Category = "Mount")
    void SetMovementState(EMountState NewState);

    UFUNCTION(BlueprintPure, Category = "Mount")
    float GetCurrentSpeed() const;

    UFUNCTION(BlueprintPure, Category = "Mount")
    int32 GetMountCount() const;

    UFUNCTION(BlueprintCallable, Category = "Mount")
    void UpdateStamina(float DeltaTime);

private:
    EMountState CurrentState = EMountState::Idle;
    float CurrentSpeed = 0.0f;
};
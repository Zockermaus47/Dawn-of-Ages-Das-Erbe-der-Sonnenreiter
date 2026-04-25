#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DawnPlayerCharacter.generated.h"

class UInventorySystemComponent;
class UStatsComponent;
class UInteractionComponent;

UCLASS()
class STEFFIS_SPIEL_API ADawnPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ADawnPlayerCharacter();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;

protected:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void TurnAtRate(float Rate);
    void LookUpAtRate(float Rate);
    void SprintStart();
    void SprintEnd();
    void CrouchStart();
    void CrouchEnd();
    void Interact();
    void OpenInventory();
    void OpenCrafting();
    void ToggleFlashlight();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UInventorySystemComponent* InventoryComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStatsComponent* StatsComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UInteractionComponent* InteractionComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed = 600.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float SprintSpeed = 900.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float CrouchSpeed = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float TurnRate = 90.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float LookUpRate = 90.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float BaseArmLength = 400.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    FVector CameraOffset = FVector(0.0f, 0.0f, 50.0f);

    UFUNCTION(BlueprintCallable)
    void ApplyDamage(float Damage, FName DamageType);

    UFUNCTION(BlueprintCallable)
    void Die();

    UFUNCTION(BlueprintPure)
    bool IsSprinting() const { return bIsSprinting; }

    UFUNCTION(BlueprintPure)
    bool IsCrouching() const { return bIsCrouching; }

    UFUNCTION(BlueprintPure)
    bool IsDead() const { return bIsDead; }

protected:
    UPROPERTY(Replicated)
    bool bIsSprinting = false;

    UPROPERTY(Replicated)
    bool bIsCrouching = false;

    UPROPERTY(Replicated)
    bool bIsDead = false;

    UPROPERTY(ReplicatedUsing = OnRep_Health)
    float Health = 100.0f;

    UFUNCTION()
    void OnRep_Health();

    float MaxHealth = 100.0f;

    bool bFlashlightOn = false;

private:
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
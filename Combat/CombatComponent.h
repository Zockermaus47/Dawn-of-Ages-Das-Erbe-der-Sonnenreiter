#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UENUM(BlueprintType)
enum class EAttackType : uint8
{
    Light UMETA(DisplayName = "Leicht"),
    Heavy UMETA(DisplayName = "Schwer"),
    Charged UMETA(DisplayName = "Aufgeladen"),
    Ranged UMETA(DisplayName = "Fernkampf")
};

UENUM(BlueprintType)
enum class ECombatWeaponType : uint8
{
    None UMETA(DisplayName = "Keine"),
    Melee UMETA(DisplayName = "Nahkampf"),
    Ranged UMETA(DisplayName = "Fernkampf"),
    Shield UMETA(DisplayName = "Schild")
};

UENUM(BlueprintType)
enum class ECombatDamageType : uint8
{
    Physical UMETA(DisplayName = "Physisch"),
    Fire UMETA(DisplayName = "Feuer"),
    Ice UMETA(DisplayName = "Eis"),
    Poison UMETA(DisplayName = "Gift")
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseDamage = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Range = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CritChance = 0.05f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CritMultiplier = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EDamageType DamageType = EDamageType::Physical;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_DAWNOFAGES_API UCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UCombatComponent();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float MaxHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float CurrentHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float BaseDamage = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float BlockChance = 0.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float DodgeChance = 0.15f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat|Weapons")
    FWeaponStats EquippedMeleeWeapon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat|Weapons")
    FWeaponStats EquippedRangedWeapon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat|Weapons")
    EWeaponType CurrentWeaponType = EWeaponType::Melee;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    bool bIsAttacking = false;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    bool bIsBlocking = false;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    bool bIsDead = false;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    float LastAttackTime = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    int32 ComboCount = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    int32 MaxComboCount = 3;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void PerformLightAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void PerformHeavyAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void PerformRangedAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void StartBlocking();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void StopBlocking();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Dodge();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    float TakeDamage(float DamageAmount, EDamageType DamageType = EDamageType::Physical);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Heal(float HealAmount);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void EquipMeleeWeapon(FWeaponStats Weapon);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void EquipRangedWeapon(FWeaponStats Weapon);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void UnequipWeapons();

    UFUNCTION(BlueprintPure, Category = "Combat")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool CanAttack() const;

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool CanBlock() const;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ResetCombo();

private:
    float AttackCooldown = 0.0f;
    float LastDodgeTime = 0.0f;
    float DodgeCooldown = 1.0f;

    void ExecuteAttack(EAttackType AttackType);
    float CalculateDamage(EDamageType DamageType, bool& bIsCritical);
    bool CheckBlock();
    bool CheckDodge();
    bool CheckCrit();
    
    TArray<AActor*> GetActorsInAttackRange(float Range) const;
    void DealDamageToActor(AActor* Target, float Damage, EDamageType DamageType);
};
#include "Combat/CombatComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UCombatComponent::UCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    MaxHealth = 100.0f;
    CurrentHealth = 100.0f;
    BaseDamage = 10.0f;
    AttackSpeed = 1.0f;
    BlockChance = 0.2f;
    DodgeChance = 0.15f;

    CurrentWeaponType = EWeaponType::Melee;
    bIsAttacking = false;
    bIsBlocking = false;
    bIsDead = false;
    LastAttackTime = 0.0f;
    ComboCount = 0;
    MaxComboCount = 3;

    EquippedMeleeWeapon.BaseDamage = 10.0f;
    EquippedMeleeWeapon.AttackSpeed = 1.0f;
    EquippedMeleeWeapon.Range = 150.0f;
    EquippedMeleeWeapon.CritChance = 0.05f;
    EquippedMeleeWeapon.CritMultiplier = 2.0f;

    EquippedRangedWeapon.BaseDamage = 15.0f;
    EquippedRangedWeapon.AttackSpeed = 0.8f;
    EquippedRangedWeapon.Range = 1000.0f;
    EquippedRangedWeapon.CritChance = 0.1f;
    EquippedRangedWeapon.CritMultiplier = 2.0f;

    AttackCooldown = 0.0f;
    LastDodgeTime = 0.0f;
    DodgeCooldown = 1.0f;
}

void UCombatComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bIsDead) return;

    if (AttackCooldown > 0.0f)
    {
        AttackCooldown -= DeltaTime;
    }

    if (LastDodgeTime > 0.0f)
    {
        LastDodgeTime -= DeltaTime;
    }
}

bool UCombatComponent::CanAttack() const
{
    return !bIsAttacking && !bIsBlocking && AttackCooldown <= 0.0f && !bIsDead;
}

bool UCombatComponent::CanBlock() const
{
    return !bIsAttacking && !bIsDead;
}

void UCombatComponent::PerformLightAttack()
{
    if (!CanAttack()) return;

    ExecuteAttack(EAttackType::Light);
}

void UCombatComponent::PerformHeavyAttack()
{
    if (!CanAttack()) return;

    ExecuteAttack(EAttackType::Heavy);
}

void UCombatComponent::PerformRangedAttack()
{
    if (!CanAttack()) return;
    if (CurrentWeaponType != EWeaponType::Ranged) return;

    ExecuteAttack(EAttackType::Ranged);
}

void UCombatComponent::ExecuteAttack(EAttackType AttackType)
{
    bIsAttacking = true;
    LastAttackTime = GetWorld()->GetTimeSeconds();

    float DamageMultiplier = 1.0f;
    switch (AttackType)
    {
        case EAttackType::Light:
            DamageMultiplier = 0.7f;
            break;
        case EAttackType::Heavy:
            DamageMultiplier = 1.5f;
            break;
        case EAttackType::Charged:
            DamageMultiplier = 2.0f;
            break;
        case EAttackType::Ranged:
            DamageMultiplier = 1.0f;
            break;
    }

    FWeaponStats* Weapon = (CurrentWeaponType == EWeaponType::Ranged) ? &EquippedRangedWeapon : &EquippedMeleeWeapon;
    float Damage = Weapon->BaseDamage * DamageMultiplier;
    float Range = Weapon->Range;

    TArray<AActor*> Targets = GetActorsInAttackRange(Range);
    for (AActor* Target : Targets)
    {
        if (Target == GetOwner()) continue;
        
        bool bIsCritical = false;
        float FinalDamage = CalculateDamage(Weapon->DamageType, bIsCritical);
        FinalDamage *= DamageMultiplier;

        DealDamageToActor(Target, FinalDamage, Weapon->DamageType);

        if (bIsCritical)
        {
            UE_LOG(LogTemp, Log, TEXT("CRITICAL HIT! %f"), FinalDamage);
        }
    }

    ComboCount++;
    if (ComboCount >= MaxComboCount)
    {
        ComboCount = 0;
    }

    AttackCooldown = 1.0f / Weapon->AttackSpeed;
    bIsAttacking = false;
}

float UCombatComponent::CalculateDamage(EDamageType DamageType, bool& bIsCritical)
{
    bIsCritical = CheckCrit();
    
    float Damage = BaseDamage;
    
    if (bIsCritical)
    {
        Damage *= EquippedMeleeWeapon.CritMultiplier;
    }

    return Damage;
}

bool UCombatComponent::CheckCrit()
{
    float Roll = FMath::FRand();
    return Roll <= EquippedMeleeWeapon.CritChance;
}

bool UCombatComponent::CheckBlock()
{
    if (!bIsBlocking) return false;
    
    float Roll = FMath::FRand();
    return Roll <= BlockChance;
}

bool UCombatComponent::CheckDodge()
{
    float Roll = FMath::FRand();
    return Roll <= DodgeChance;
}

void UCombatComponent::DealDamageToActor(AActor* Target, float Damage, EDamageType DamageType)
{
    if (!Target) return;

    UCombatComponent* TargetCombat = Target->FindComponentByClass<UCombatComponent>();
    if (TargetCombat)
    {
        TargetCombat->TakeDamage(Damage, DamageType);
    }
}

TArray<AActor*> UCombatComponent::GetActorsInAttackRange(float Range) const
{
    TArray<AActor*> Actors;
    TArray<AActor*> OutActors;
    TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
    
    UWorld* World = GetWorld();
    if (!World) return Actors;

    FVector OwnerLocation = GetOwner()->GetActorLocation();
    
    UKismetSystemLibrary::SphereOverlapActors(
        World,
        OwnerLocation,
        Range,
        ObjectTypes,
        AActor::StaticClass(),
        OutActors,
        OutActors
    );

    for (AActor* Actor : OutActors)
    {
        if (Actor && Actor != GetOwner())
        {
            Actors.Add(Actor);
        }
    }

    return Actors;
}

void UCombatComponent::StartBlocking()
{
    if (!CanBlock()) return;
    bIsBlocking = true;
}

void UCombatComponent::StopBlocking()
{
    bIsBlocking = false;
}

void UCombatComponent::Dodge()
{
    if (bIsDead) return;
    if (LastDodgeTime > 0.0f) return;

    AActor* Owner = GetOwner();
    if (!Owner) return;

    FVector Forward = Owner->GetActorForwardVector();
    FVector DodgeLocation = Owner->GetActorLocation() + (Forward * 200.0f);

    Owner->SetActorLocation(DodgeLocation, false, nullptr, ETeleportType::TeleportPhysics);

    LastDodgeTime = DodgeCooldown;
    UE_LOG(LogTemp, Log, TEXT("Dodge!"));
}

float UCombatComponent::TakeDamage(float DamageAmount, EDamageType DamageType)
{
    if (bIsDead) return 0.0f;

    float ActualDamage = DamageAmount;

    if (CheckBlock())
    {
        ActualDamage *= 0.5f;
        UE_LOG(LogTemp, Log, TEXT("Blocked! Damage reduced to %f"), ActualDamage);
    }
    else if (CheckDodge())
    {
        ActualDamage = 0.0f;
        UE_LOG(LogTemp, Log, TEXT("Dodged!"));
    }

    CurrentHealth = FMath::Clamp(CurrentHealth - ActualDamage, 0.0f, MaxHealth);

    if (CurrentHealth <= 0.0f)
    {
        bIsDead = true;
        UE_LOG(LogTemp, Log, TEXT("Character died!"));
    }

    return ActualDamage;
}

void UCombatComponent::Heal(float HealAmount)
{
    if (bIsDead) return;

    CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
    UE_LOG(LogTemp, Log, TEXT("Healed: %f"), HealAmount);
}

void UCombatComponent::EquipMeleeWeapon(FWeaponStats Weapon)
{
    EquippedMeleeWeapon = Weapon;
    CurrentWeaponType = EWeaponType::Melee;
    UE_LOG(LogTemp, Log, TEXT("Melee weapon equipped!"));
}

void UCombatComponent::EquipRangedWeapon(FWeaponStats Weapon)
{
    EquippedRangedWeapon = Weapon;
    CurrentWeaponType = EWeaponType::Ranged;
    UE_LOG(LogTemp, Log, TEXT("Ranged weapon equipped!"));
}

void UCombatComponent::UnequipWeapons()
{
    CurrentWeaponType = EWeaponType::None;
    UE_LOG(LogTemp, Log, TEXT("Weapons unequipped!"));
}

float UCombatComponent::GetHealthPercent() const
{
    return MaxHealth > 0.0f ? (CurrentHealth / MaxHealth) * 100.0f : 0.0f;
}

void UCombatComponent::ResetCombo()
{
    ComboCount = 0;
}
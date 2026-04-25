#include "DawnPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Net/UnrealNetwork.h"
#include "InventorySystemComponent.h"
#include "StatsComponent.h"
#include "InteractionComponent.h"

ADawnPlayerCharacter::ADawnPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -97.0f));
    GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 600.0f;
    GetCharacterMovement()->CrouchDecelerationWalk = 300.0f;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = BaseArmLength;
    CameraBoom->SocketOffset = CameraOffset;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    InventoryComp = CreateDefaultSubobject<UInventorySystemComponent>(TEXT("InventoryComp"));
    StatsComp = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComp"));
    InteractionComp = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComp"));
}

void ADawnPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    }
}

void ADawnPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ADawnPlayerCharacter::SprintStart);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ADawnPlayerCharacter::SprintEnd);
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ADawnPlayerCharacter::CrouchStart);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ADawnPlayerCharacter::CrouchEnd);
    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ADawnPlayerCharacter::Interact);
    PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ADawnPlayerCharacter::OpenInventory);
    PlayerInputComponent->BindAction("Crafting", IE_Pressed, this, &ADawnPlayerCharacter::OpenCrafting);
    PlayerInputComponent->BindAction("Flashlight", IE_Pressed, this, &ADawnPlayerCharacter::ToggleFlashlight);

    PlayerInputComponent->BindAxis("MoveForward", this, &ADawnPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ADawnPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &ADawnPlayerCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUpRate", this, &ADawnPlayerCharacter::LookUpAtRate);
}

void ADawnPlayerCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.0f && !bIsDead)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ADawnPlayerCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.0f && !bIsDead)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void ADawnPlayerCharacter::TurnAtRate(float Rate)
{
    AddControllerYawInput(Rate * TurnRate * GetWorld()->GetDeltaSeconds());
}

void ADawnPlayerCharacter::LookUpAtRate(float Rate)
{
    AddControllerPitchInput(Rate * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADawnPlayerCharacter::SprintStart()
{
    if (!bIsCrouching && !bIsDead)
    {
        bIsSprinting = true;
        GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
    }
}

void ADawnPlayerCharacter::SprintEnd()
{
    bIsSprinting = false;
    GetCharacterMovement()->MaxWalkSpeed = bIsCrouching ? CrouchSpeed : WalkSpeed;
}

void ADawnPlayerCharacter::CrouchStart()
{
    if (!bIsDead)
    {
        bIsCrouching = true;
        Crouch();
        GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
    }
}

void ADawnPlayerCharacter::CrouchEnd()
{
    bIsCrouching = false;
    UnCrouch();
    GetCharacterMovement()->MaxWalkSpeed = bIsSprinting ? SprintSpeed : WalkSpeed;
}

void ADawnPlayerCharacter::Interact()
{
    if (InteractionComp && !bIsDead)
    {
        InteractionComp->Interact();
    }
}

void ADawnPlayerCharacter::OpenInventory()
{
}

void ADawnPlayerCharacter::OpenCrafting()
{
}

void ADawnPlayerCharacter::ToggleFlashlight()
{
    bFlashlightOn = !bFlashlightOn;
}

void ADawnPlayerCharacter::ApplyDamage(float Damage, FName DamageType)
{
    if (HasAuthority())
    {
        Health -= Damage;
        
        if (Health <= 0.0f)
        {
            Health = 0.0f;
            Die();
        }
    }
}

void ADawnPlayerCharacter::Die()
{
    bIsDead = true;
    GetMovementComponent()->StopMovementImmediately();
    DisableInput(nullptr);
    
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
    GetMesh()->SetAllBodiesSimulatePhysics(true);
}

void ADawnPlayerCharacter::OnRep_Health()
{
}

void ADawnPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(ADawnPlayerCharacter, bIsSprinting);
    DOREPLIFETIME(ADawnPlayerCharacter, bIsCrouching);
    DOREPLIFETIME(ADawnPlayerCharacter, bIsDead);
    DOREPLIFETIME(ADawnPlayerCharacter, Health);
}
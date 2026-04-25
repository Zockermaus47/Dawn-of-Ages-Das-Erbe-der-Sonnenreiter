#pragma once

#include "CoreMinimal.h"
#include "ResourceTypes.generated.h"

UENUM(BlueprintType)
enum class EEpoch : uint8
{
    StoneAge UMETA(DisplayName = "Steinzeit"),
    BronzeAge UMETA(DisplayName = "Bronzezeit"),
    Medieval UMETA(DisplayName = "Mittelalter")
};

UENUM(BlueprintType)
enum class EResourceType : uint8
{
    // === HOLZ ===
    Wood_Oak UMETA(DisplayName = "Eichenholz"),
    Wood_Birch UMETA(DisplayName = "Birkenholz"),
    Wood_Pine UMETA(DisplayName = "Kiefernholz"),
    
    // === ORGANISCH ===
    Bark UMETA(DisplayName = "Rinde"),
    Stick UMETA(DisplayName = "Stock"),
    Branch UMETA(DisplayName = "Ast"),
    
    // === STEIN (Steinzeit) ===
    Stone_Flint UMETA(DisplayName = "Feuerstein"),
    Stone_Granite UMETA(DisplayName = "Granit"),
    Stone_Limestone UMETA(DisplayName = "Kalkstein"),
    Stone_Sandstone UMETA(DisplayName = "Sandstein"),
    
    // === ERZE (Bronzezeit) ===
    Ore_Copper UMETA(DisplayName = "Kupfererz"),
    Ore_Tin UMETA(DisplayName = "Zinnerz"),
    
    // === ERZE (Mittelalter) ===
    Ore_Iron UMETA(DisplayName = "Eisenerz"),
    Ore_Silver UMETA(DisplayName = "Silbererz"),
    Ore_Gold UMETA(DisplayName = "Golderz"),
    
    // === KOHLE ===
    Coal_Brown UMETA(DisplayName = "Braunkohle"),
    Coal_Stone UMETA(DisplayName = "Steinkohle"),
    
    // === BODEN-RESSOURCEN ===
    Clay UMETA(DisplayName = "Lehm"),
    Sand UMETA(DisplayName = "Sand"),
    Gravel UMETA(DisplayName = "Kies"),
    
    // === SPEZIAL (Mittelalter) ===
    Sulfur UMETA(DisplayName = "Schwefel"),
    Saltpeter UMETA(DisplayName = "Salpeter")
};

UENUM(BlueprintType)
enum class EToolType : uint8
{
    Hand UMETA(DisplayName = "Hand"),
    
    // Steinzeit
    StoneAxe UMETA(DisplayName = "Steinaxt"),
    StonePickaxe UMETA(DisplayName = "Steinspitzhacke"),
    StoneKnife UMETA(DisplayName = "Steinmesser"),
    
    // Bronzezeit
    BronzeAxe UMETA(DisplayName = "Bronzeaxt"),
    BronzePickaxe UMETA(DisplayName = "Bronzespitzhacke"),
    BronzeShovel UMETA(DisplayName = "Bronzeschaufel"),
    
    // Mittelalter
    IronAxe UMETA(DisplayName = "Eisenaxt"),
    IronPickaxe UMETA(DisplayName = "Eisenspitzhacke"),
    IronShovel UMETA(DisplayName = "Eisenschaufel"),
    SteelAxe UMETA(DisplayName = "Stahlaxt"),
    SteelPickaxe UMETA(DisplayName = "Stahlspitzhacke")
};

UENUM(BlueprintType)
enum class EResourceQuality : uint8
{
    Poor UMETA(DisplayName = "Schlecht"),
    Common UMETA(DisplayName = "Normal"),
    Good UMETA(DisplayName = "Gut"),
    Excellent UMETA(DisplayName = "Exzellent"),
    Rare UMETA(DisplayName = "Selten")
};

UENUM(BlueprintType)
enum class EHarvestStage : uint8
{
    Intact UMETA(DisplayName = "Intakt"),
    Damaged UMETA(DisplayName = "Beschädigt"),
    Critical UMETA(DisplayName = "Kritisch"),
    Destroyed UMETA(DisplayName = "Zerstört")
};

USTRUCT(BlueprintType)
struct FResourceDrop
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EResourceType ResourceType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinAmount = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxAmount = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DropChance = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EResourceQuality Quality = EResourceQuality::Common;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> DropActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEpoch RequiredEpoch = EEpoch::StoneAge;
};

USTRUCT(BlueprintType)
struct FToolEfficiency
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EToolType ToolType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageMultiplier = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpeedMultiplier = 1.0f;
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ItemDatabase.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
    None        UMETA(DisplayName = "None"),
    Weapon      UMETA(DisplayName = "Weapon"),
    Armor       UMETA(DisplayName = "Armor"),
    Tool        UMETA(DisplayName = "Tool"),
    Material    UMETA(DisplayName = "Material"),
    Resource    UMETA(DisplayName = "Resource"),
    Food        UMETA(DisplayName = "Food"),
    Potion      UMETA(DisplayName = "Potion"),
    Book        UMETA(DisplayName = "Book"),
    QuestItem    UMETA(DisplayName = "QuestItem"),
    Mount       UMETA(DisplayName = "Mount"),
    Pet         UMETA(DisplayName = "Pet"),
    Building   UMETA(DisplayName = "Building"),
    Seed       UMETA(DisplayName = "Seed"),
    Crop       UMETA(DisplayName = "Crop"),
    Animal     UMETA(DisplayName = "Animal")
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
    Common     UMETA(DisplayName = "Common"),
    Uncommon   UMETA(DisplayName = "Uncommon"),
    Rare       UMETA(DisplayName = "Rare"),
    Epic       UMETA(DisplayName = "Epic"),
    Legendary  UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EItemEra : uint8
{
    StoneAge   UMETA(DisplayName = "Stone Age"),
    BronzeAge  UMETA(DisplayName = "Bronze Age"),
    Medieval  UMETA(DisplayName = "Medieval")
};

UENUM(BlueprintType)
enum class EItemSlot : uint8
{
    None        UMETA(DisplayName = "None"),
    Head        UMETA(DisplayName = "Head"),
    Chest       UMETA(DisplayName = "Chest"),
    Legs        UMETA(DisplayName = "Legs"),
    Feet        UMETA(DisplayName = "Feet"),
    HandRight   UMETA(DisplayName = "Hand Right"),
    HandLeft    UMETA(DisplayName = "Hand Left"),
    Neck        UMETA(DisplayName = "Neck"),
    Back        UMETA(DisplayName = "Back"),
    Ring        UMETA(DisplayName = "Ring")
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
    None        UMETA(DisplayName = "None"),
    Physical   UMETA(DisplayName = "Physical"),
    Fire       UMETA(DisplayName = "Fire"),
    Ice        UMETA(DisplayName = "Ice"),
    Lightning  UMETA(DisplayName = "Lightning"),
    Nature     UMETA(DisplayName = "Nature"),
    Light      UMETA(DisplayName = "Light"),
    Dark       UMETA(DisplayName = "Dark")
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    None        UMETA(DisplayName = "None"),
    Sword       UMETA(DisplayName = "Sword"),
    Axe         UMETA(DisplayName = "Axe"),
    Spear       UMETA(DisplayName = "Spear"),
    Bow         UMETA(DisplayName = "Bow"),
    Mace        UMETA(DisplayName = "Mace"),
    Dagger      UMETA(DisplayName = "Dagger"),
    Staff       UMETA(DisplayName = "Staff"),
    Crossbow    UMETA(DisplayName = "Crossbow")
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
    None        UMETA(DisplayName = "None"),
    Light       UMETA(DisplayName = "Light"),
    Medium      UMETA(DisplayName = "Medium"),
    Heavy       UMETA(DisplayName = "Heavy"),
    Cloth       UMETA(DisplayName = "Cloth")
};

UENUM(BlueprintType)
enum class EToolCategory : uint8
{
    None        UMETA(DisplayName = "None"),
    Pickaxe     UMETA(DisplayName = "Pickaxe"),
    Axe         UMETA(DisplayName = "Axe"),
    Hammer      UMETA(DisplayName = "Hammer"),
    Shovel      UMETA(DisplayName = "Shovel"),
    Sickle      UMETA(DisplayName = "Sickle"),
    FishingRod  UMETA(DisplayName = "Fishing Rod"),
    Needle      UMETA(DisplayName = "Needle")
};

USTRUCT(BlueprintType)
struct FItemInfo : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemType ItemType = EItemType::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemRarity Rarity = EItemRarity::Common;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemEra Era = EItemEra::StoneAge;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemSlot InventorySlot = EItemSlot::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWeaponType WeaponType = EWeaponType::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EArmorType ArmorType = EArmorType::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EToolType ToolType = EToolType::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Weight = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStack = 99;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BuyPrice = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SellPrice = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Armor = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EDamageType DamageType = EDamageType::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CraftingSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GatheringSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MiningSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WoodcuttingSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FarmingSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CookingSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FishingSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Durability = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 HungerRestore = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ThirstRestore = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 HealthRestore = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ManaRestore = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperienceGained = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, int32> CraftingRequirements;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> CraftingProfessions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> HarvestingSources;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> DropsFrom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ResourceBiomes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnChance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MiningLevelRequired = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WoodcuttingLevelRequired = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FarmingLevelRequired = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CookingLevelRequired = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FishingLevelRequired = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LevelRequired = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCraftable = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsSellable = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsTradeable = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsDestroyable = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bQuestItem = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bSoulbound = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTexture2D> Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<USkeletalMesh> Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UStaticMesh> StaticMesh;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UItemDatabase : public UObject
{
    GENERATED_BODY()

public:
    UItemDatabase();

    UFUNCTION(BlueprintCallable, Category = "Item Database")
    static FItemData GetItemData(FName ItemID);

    UFUNCTION(BlueprintCallable, Category = "Item Database")
    static TArray<FItemData> GetItemsByType(EItemType Type);

    UFUNCTION(BlueprintCallable, Category = "Item Database")
    static TArray<FItemData> GetItemsByEra(EItemEra Era);

    UFUNCTION(BlueprintCallable, Category = "Item Database")
    static TArray<FItemData> GetItemsByRarity(EItemRarity Rarity);

    UFUNCTION(BlueprintCallable, Category = "Item Database")
    static TArray<FItemData> GetAllItems();

    UFUNCTION(BlueprintCallable, Category = "Item Database")
    static bool IsValidItem(FName ItemID);

    UFUNCTION(BlueprintCallable, Category = "Item Database")
    static int32 GetItemValue(FName ItemID);

    UFUNCTION(BlueprintCallable, Category = "Item Database")
    static float GetItemWeight(FName ItemID);

    UFUNCTION(BlueprintCallable, Category = "Item Database")
    static EItemRarity CalculateRarity(float Roll);
};
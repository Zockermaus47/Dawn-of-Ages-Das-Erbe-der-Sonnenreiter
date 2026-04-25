#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Magic.generated.h"

UENUM(BlueprintType)
enum class EMagicSchool : uint8
{
    None        UMETA(DisplayName = "None"),
    Fire        UMETA(DisplayName = "Fire"),
    Ice         UMETA(DisplayName = "Ice"),
    Nature      UMETA(DisplayName = "Nature"),
    Light       UMETA(DisplayName = "Light"),
    Dark        UMETA(DisplayName = "Dark")
};

UENUM(BlueprintType)
enum class ESpellType : uint8
{
    None        UMETA(DisplayName = "None"),
    Attack      UMETA(DisplayName = "Attack"),
    Heal        UMETA(DisplayName = "Heal"),
    Buff        UMETA(DisplayName = "Buff"),
    DeBuff      UMETA(DisplayName = "De-Buff"),
    Summon      UMETA(DisplayName = "Summon"),
    Utility     UMETA(DisplayName = "Utility")
};

USTRUCT(BlueprintType)
struct FSpellData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SpellID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMagicSchool School;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESpellType SpellType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ManaCost = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HealAmount = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Range = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Cooldown = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkillLevelRequired = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Reagents;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperienceGained = 25;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UMagicSystem : public UObject
{
    GENERATED_BODY()

public:
    UMagicSystem();

    UFUNCTION(BlueprintCallable, Category = "Magic")
    static FSpellData GetSpellData(FName SpellID);

    UFUNCTION(BlueprintCallable, Category = "Magic")
    static TArray<FSpellData> GetSpellsBySchool(EMagicSchool School);

    UFUNCTION(BlueprintCallable, Category = "Magic")
    static TArray<FSpellData> GetAllSpells();
};
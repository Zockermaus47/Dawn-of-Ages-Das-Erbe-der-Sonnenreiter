#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Poison.generated.h"

UENUM(BlueprintType)
enum class EPoisonType : uint8
{
    Antidote     UMETA(DisplayName = "Antidote"),
    Healing     UMETA(DisplayName = "Healing"),
    Paralysis   UMETA(DisplayName = "Paralysis"),
    Sleep       UMETA(DisplayName = "Sleep"),
    Slow        UMETA(DisplayName = "Slow"),
    Confusion   UMETA(DisplayName = "Confusion"),
    Strength   UMETA(DisplayName = "Strength"),
    Speed       UMETA(DisplayName = "Speed"),
    Fire        UMETA(DisplayName = "Fire"),
    Ice         UMETA(DisplayName = "Ice"),
    Lightning   UMETA(DisplayName = "Lightning"),
    Dark        UMETA(DisplayName = "Dark")
};

UENUM(BlueprintType)
enum class EHerbQuality : uint8
{
    Common      UMETA(DisplayName = "Common"),
    Uncommon    UMETA(DisplayName = "Uncommon"),
    Rare        UMETA(DisplayName = "Rare"),
    Epic        UMETA(DisplayName = "Epic"),
    Legendary   UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EEffectApplication : uint8
{
    Contact     UMETA(DisplayName = "Contact"),
    Injected    UMETA(DisplayName = "Injected"),
    Ingested    UMETA(DisplayName = "Ingested"),
    Inhaled     UMETA(DisplayName = "Inhaled")
};

USTRUCT(BlueprintType)
struct FPoisonData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName PoisonID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPoisonType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Potency = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration = 30.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredSkill = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Ingredients;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEffectApplication Application = EEffectApplication::Contact;
};

USTRUCT(BlueprintType)
struct FHerbData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName HerbID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EHerbQuality Quality = EHerbQuality::Common;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EffectID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BasePotency = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> BiomeLocations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESeason Season = ESeason::Spring;
};

USTRUCT(BlueprintType)
struct FActiveEffect
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EffectID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RemainingTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Magnitude = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsBuff = false;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UPoisonSystem : public UObject
{
    GENERATED_BODY()

public:
    UPoisonSystem();

    static FPoisonData GetPoisonData(FName PoisonID);

    static FHerbData GetHerbData(FName HerbID);

    static bool BrewPoison(FPoisonData Recipe, TArray<FName> Ingredients, int32 PlayerSkill);

    static TArray<FPoisonData> GetAllPoisonRecipes();

    static TArray<FHerbData> GetHerbsByBiome(FName BiomeID);

    static void ApplyEffect(FName EffectID, float Duration, float Magnitude, bool bIsBuff);

    static void RemoveEffect(FName EffectID);

    static void TickEffects(float DeltaTime);

    static TArray<FActiveEffect> GetActiveEffects();

    static float GetEffectMagnitude(FName EffectID);

    static bool IsEffectActive(FName EffectID);
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Music.generated.h"

UENUM(BlueprintType)
enum class EInstrumentType : uint8
{
    Flute       UMETA(DisplayName = "Flute"),
    Drum        UMETA(DisplayName = "Drum"),
    Lyre        UMETA(DisplayName = "Lyre"),
    Horn        UMETA(DisplayName = "Horn"),
    Harp        UMETA(DisplayName = "Harp"),
    Bagpipe    UMETA(DisplayName = "Bagpipe"),
    Hornpipe   UMETA(DisplayName = "Hornpipe"),
    Fiddle     UMETA(DisplayName = "Fiddle"),
    Recorder   UMETA(DisplayName = "Recorder"),
    Horn       UMETA(DisplayName = "Horn")
};

UENUM(BlueprintType)
enum class EMusicGenre : uint8
{
    Folk       UMETA(DisplayName = "Folk"),
    Celtic     UMETA(DisplayName = "Celtic"),
    Nordic     UMETA(DisplayName = "Nordic"),
    Arabian    UMETA(DisplayName = "Arabian"),
    Classical  UMETA(DisplayName = "Classical"),
    WarChant   UMETA(DisplayName = "War Chant"),
    Dance      UMETA(DisplayName = "Dance"),
    Lullaby    UMETA(DisplayName = "Lullaby"),
    Dirge      UMETA(DisplayName = "Dirge")
};

USTRUCT(BlueprintType)
struct FInstrumentData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName InstrumentID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EInstrumentType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredSkill = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Volume = 1.0f;
};

USTRUCT(BlueprintType)
struct FMusicEffect
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EffectID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMusicGenre Genre;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Range = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration = 60.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bBuffsAllies = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bDebuffsEnemies = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HealBonus = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageBonus = 0.0f;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UMusicSystem : public UObject
{
    GENERATED_BODY()

public:
    UMusicSystem();

    static FInstrumentData GetInstrument(FName InstrumentID);

    static FMusicEffect GetMusicEffect(FName EffectID);

    static bool PlayInstrument(EInstrumentType Type, FName EffectID, int32 PlayerSkill);

    static TArray<FInstrumentData> GetAllInstruments();

    static void ApplyBuff(float Duration, float HealBonus, float DamageBonus);

    static void ApplyDebuff(float Duration, float Penalty);
};
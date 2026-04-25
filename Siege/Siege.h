#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Siege.generated.h"

UENUM(BlueprintType)
enum class ESiegeWeaponType : uint8
{
    None            UMETA(DisplayName = "None"),
    Catapult       UMETA(DisplayName = "Catapult"),
    Ballista       UMETA(DisplayName = "Ballista"),
    Ram            UMETA(DisplayName = "Ram"),
    Tower          UMETA(DisplayName = "Tower"),
    Trebuchet     UMETA(DisplayName = "Trebuchet")
};

USTRUCT(BlueprintType)
struct FSiegeWeaponData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName WeaponID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESiegeWeaponType WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Range = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CrewRequired = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReloadTime = 10.0f;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API USiegeWarfareSystem : public UObject
{
    GENERATED_BODY()

public:
    USiegeWarfareSystem();

    UFUNCTION(BlueprintCallable, Category = "Siege")
    static FSiegeWeaponData GetWeaponData(FName WeaponID);

    UFUNCTION(BlueprintCallable, Category = "Siege")
    static void Fire(FSiegeWeaponData Weapon, FVector TargetLocation);

    UFUNCTION(BlueprintCallable, Category = "Siege")
    static TArray<FSiegeWeaponData> GetAllWeapons();
};
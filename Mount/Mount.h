#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Mount.generated.h"

UENUM(BlueprintType)
enum class EMountType : uint8
{
    None        UMETA(DisplayName = "None"),
    Horse       UMETA(DisplayName = "Horse"),
    Donkey      UMETA(DisplayName = "Donkey"),
    Ox          UMETA(DisplayName = "Ox"),
    Wolf        UMETA(DisplayName = "Wolf"),
    Bear        UMETA(DisplayName = "Bear"),
    Boar        UMETA(DisplayName = "Boar"),
    Camel       UMETA(DisplayName = "Camel"),
    Elephant    UMETA(DisplayName = "Elephant"),
    Griffin     UMETA(DisplayName = "Griffin"),
    Wyvern      UMETA(DisplayName = "Wyvern"),
    Dragon      UMETA(DisplayName = "Dragon")
};

USTRUCT(BlueprintType)
struct FMountData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MountID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMountType MountType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Speed = 600.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float carryingCapacity = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TamingTime = 30;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperienceGained = 50;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkillLevelRequired = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> TamingItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanFly = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanSwim = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCombatReady = false;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UMountSystem : public UObject
{
    GENERATED_BODY()

public:
    UMountSystem();

    UFUNCTION(BlueprintCallable, Category = "Mount")
    static FMountData GetMountData(FName MountID);

    UFUNCTION(BlueprintCallable, Category = "Mount")
    static bool CanTame(FMountData Mount, const TMap<FName, int32>& Inventory);

    UFUNCTION(BlueprintCallable, Category = "Mount")
    static FMountData Tame(FMountData Mount, const TMap<FName, int32>& Inventory);

    UFUNCTION(BlueprintCallable, Category = "Mount")
    static TArray<FMountData> GetMountsByType(EMountType Type);

    UFUNCTION(BlueprintCallable, Category = "Mount")
    static TArray<FMountData> GetAllMounts();
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Building.generated.h"

UENUM(BlueprintType)
enum class EBuildType : uint8
{
    None          UMETA(DisplayName = "None"),
    Cave          UMETA(DisplayName = "Cave"),
    Hut           UMETA(DisplayName = "Hut"),
    House         UMETA(DisplayName = "House"),
    Tower        UMETA(DisplayName = "Tower"),
    Castle       UMETA(DisplayName = "Castle"),
    Wall          UMETA(DisplayName = "Wall"),
    Gate          UMETA(DisplayName = "Gate"),
    Farm          UMETA(DisplayName = "Farm"),
    Stable        UMETA(DisplayName = "Stable"),
    Workshop     UMETA(DisplayName = "Workshop"),
    Warehouse    UMETA(DisplayName = "Warehouse"),
    Tavern       UMETA(DisplayName = "Tavern"),
    Temple       UMETA(DisplayName = "Temple")
};

USTRUCT(BlueprintType)
struct FBuildData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BuildingID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBuildType BuildingType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 WoodCost = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 StoneCost = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MetalCost = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxHealth = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxCapacity = 4;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UBuildingSystem : public UObject
{
    GENERATED_BODY()

public:
    UBuildingSystem();

    UFUNCTION(BlueprintCallable, Category = "Building")
    static FBuildingData GetBuildingData(FName BuildingID);

    UFUNCTION(BlueprintCallable, Category = "Building")
    static bool CanBuild(FName BuildingID, const TMap<FName, int32>& Resources);

    UFUNCTION(BlueprintCallable, Category = "Building")
    static TArray<FBuildingData> GetAllBuildings();
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FurnitureSystem.generated.h"

UENUM(BlueprintType)
enum class EFurnitureCategory : uint8
{
    Bed         UMETA(DisplayName = "Bed"),
    Chair      UMETA(DisplayName = "Chair"),
    Table      UMETA(DisplayName = "Table"),
    Storage    UMETA(DisplayName = "Storage"),
    Rug        UMETA(DisplayName = "Rug"),
    Curtain    UMETA(DisplayName = "Curtain"),
    Shelf      UMETA(DisplayName = "Shelf"),
    Lamp       UMETA(DisplayName = "Lamp"),
    Plant      UMETA(DisplayName = "Plant"),
    Decor      UMETA(DisplayName = "Decor")
};

USTRUCT(BlueprintType)
struct FHomeFurnitureItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFurnitureCategory Category;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 GridSizeX = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 GridSizeY = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Comfort = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LightOutput = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StorageSlots = 0.0f;
};

USTRUCT(BlueprintType)
struct FPlacedFurniture
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName InstanceID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FFurnitureItem Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator Rotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsActive = true;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UFurnitureSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Furniture")
    static FFurnitureItem GetFurniture(FName ItemID);

    UFUNCTION(BlueprintCallable, Category = "Furniture")
    static FPlacedFurniture PlaceFurniture(FFurnitureItem Item, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Furniture")
    static bool RemoveFurniture(FName InstanceID);

    UFUNCTION(BlueprintCallable, Category = "Furniture")
    static void RotateFurniture(FName InstanceID);

    UFUNCTION(BlueprintCallable, Category = "Furniture")
    static TArray<FPlacedFurniture> GetFurnitureInRoom(FName RoomID);

    UFUNCTION(BlueprintCallable, Category = "Furniture")
    static float GetRoomComfort(FName RoomID);

    UFUNCTION(BlueprintCallable, Category = "Furniture")
    static int32 GetStorageSlots(FName RoomID);

    UFUNCTION(BlueprintCallable, Category = "Furniture")
    static void SetHome(FName BuildingID);

    UFUNCTION(BlueprintCallable, Category = "Furniture")
    static FName GetHome();

    UFUNCTION(BlueprintCallable, Category = "Furniture")
    static bool TeleportToHome();

    UFUNCTION(BlueprintCallable, Category = "Furniture")
    static bool SetWaypoint(FVector Location, FText Name);

    UFUNCTION(BlueprintCallable, Category = "Furniture")
    static bool TeleportToWaypoint(FText Name);

    UFUNCTION(BlueprintCallable, Category = "Furniture")
    static TArray<FName> GetWaypoints();

private:
    static FName HomeBuilding;
    static TMap<FText, FVector> Waypoints;
};

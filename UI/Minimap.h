#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Minimap.generated.h"

USTRUCT(BlueprintType)
struct FMapMarker
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MarkerID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor Color = FLinearColor::White;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsVisible = true;
};

USTRUCT(BlueprintType)
struct FMinimapSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MapSize = 200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ZoomLevel = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bShowCoordinates = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bShowPlayers = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bShowMobs = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bShowPOIs = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor PlayerColor = FLinearColor::Blue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor NorthColor = FLinearColor::Red;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UMinimapSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Minimap")
    static FVector GetPlayerCoordinates();

    UFUNCTION(BlueprintCallable, Category = "Minimap")
    static FText GetCoordinatesText();

    UFUNCTION(BlueprintCallable, Category = "Minimap")
    static float GetCompassHeading();

    UFUNCTION(BlueprintCallable, Category = "Minimap")
    static FText GetCompassDirection();

    UFUNCTION(BlueprintCallable, Category = "Minimap")
    static void AddMapMarker(FMapMarker Marker);

    UFUNCTION(BlueprintCallable, Category = "Minimap")
    static void RemoveMapMarker(FName MarkerID);

    UFUNCTION(BlueprintCallable, Category = "Minimap")
    static TArray<FMapMarker> GetVisibleMarkers(FVector PlayerLoc, float Range);

    UFUNCTION(BlueprintCallable, Category = "Minimap")
    static void SetZoom(float Zoom);

    UFUNCTION(BlueprintCallable, Category = "Minimap")
    static float GetZoom();

    UFUNCTION(BlueprintCallable, Category = "Minimap")
    static void SetSettings(FMinimapSettings Settings);

    UFUNCTION(BlueprintCallable, Category = "Minimap")
    static FMinimapSettings GetSettings();

    UFUNCTION(BlueprintCallable, Category = "Minimap")
    static void CenterMap();

    UFUNCTION(BlueprintCallable, Category = "Minimap")
    static void ToggleFullMap();

private:
    static FMinimapSettings Settings;
    static TArray<FMapMarker> Markers;
};
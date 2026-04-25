#pragma once

#include "CoreMinimal.h"
#include "Harvesting/HarvestableObject.h"
#include "HarvestableRock.generated.h"

UENUM(BlueprintType)
enum class ERockState : uint8
{
    Large UMETA(DisplayName = "Großer Brocken"),
    Medium UMETA(DisplayName = "Mittelstein"),
    Small UMETA(DisplayName = "Kiesel"),
    Fragments UMETA(DisplayName = "Splitter")
};

UENUM(BlueprintType)
enum class ERockType : uint8
{
    Flint UMETA(DisplayName = "Feuerstein"),
    Granite UMETA(DisplayName = "Granit"),
    Limestone UMETA(DisplayName = "Kalkstein"),
    Sandstone UMETA(DisplayName = "Sandstein"),
    Marble UMETA(DisplayName = "Marmor"),
    Basalt UMETA(DisplayName = "Basalt"),
    Slate UMETA(DisplayName = "Schiefer"),
    OreVein UMETA(DisplayName = "Erzader"),
    CoalDeposit UMETA(DisplayName = "Kohlevorkommen")
};

UCLASS()
class STEFFIS_DAWNOFAGES_API AHarvestableRock : public AHarvestableObject
{
    GENERATED_BODY()

public:
    AHarvestableRock();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock")
    ERockState RockState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock")
    ERockType RockType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock")
    EResourceType PrimaryResource;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock")
    bool bIsOreVein = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock")
    float OreVisibility = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock|Meshes")
    UStaticMesh* LargeMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock|Meshes")
    UStaticMesh* MediumMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock|Meshes")
    UStaticMesh* SmallMesh;

    virtual void OnHit(AActor* Attacker, float Damage, FName ToolType) override;
    virtual void OnDestroyed_Implementation() override;

    UFUNCTION(BlueprintCallable, Category = "Rock")
    void BreakIntoSmaller();

    UFUNCTION(BlueprintCallable, Category = "Rock")
    void RevealOre();

    UFUNCTION(BlueprintPure, Category = "Rock")
    bool CanMineOre() const;

protected:
    virtual void BeginPlay() override;
    
    UFUNCTION()
    void UpdateMesh();

    void SetupResourceDrops();
};

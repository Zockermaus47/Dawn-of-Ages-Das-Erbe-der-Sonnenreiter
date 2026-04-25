#pragma once

#include "CoreMinimal.h"
#include "Harvesting/HarvestableObject.h"
#include "HarvestableStick.generated.h"

UENUM(BlueprintType)
enum class EStickType : uint8
{
    SmallStick UMETA(DisplayName = "Kleiner Stock"),
    MediumStick UMETA(DisplayName = "Mittlerer Stock"),
    LargeBranch UMETA(DisplayName = "Großer Ast"),
    FallenBranch UMETA(DisplayName = "Heruntergefallener Ast")
};

UCLASS()
class STEFFIS_DAWNOFAGES_API AHarvestableStick : public AHarvestableObject
{
    GENERATED_BODY()

public:
    AHarvestableStick();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stick")
    EStickType StickType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stick")
    bool bIsPickupOnly = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stick")
    float StickAmount = 1.0f;

    UFUNCTION(BlueprintCallable, Category = "Stick")
    void Pickup();

    UFUNCTION(BlueprintCallable, Category = "Stick")
    bool CanPickup() const;

protected:
    virtual void BeginPlay() override;

    void SetupResourceDrops();
};

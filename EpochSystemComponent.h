#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EpochSystemComponent.generated.h"

UENUM(BlueprintType)
enum class EEpoch : uint8
{
    StoneAge      UMETA(DisplayName = "Steinzeit"),
    BronzeAge     UMETA(DisplayName = "Bronzezeit"),
    MedievalAge   UMETA(DisplayName = "Mittelalter"),
    Any           UMETA(DisplayName = "Alle")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEpochChanged, EEpoch, NewEpoch);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEpochProgress, float, Progress);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_SPIEL_API UEpochSystemComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UEpochSystemComponent();

    UFUNCTION(BlueprintCallable)
    void AdvanceTime(float DeltaHours);

    UFUNCTION(BlueprintCallable)
    void SetEpoch(EEpoch NewEpoch);

    UFUNCTION(BlueprintCallable)
    void CheckEpochTransition();

    UFUNCTION(BlueprintPure)
    EEpoch GetCurrentEpoch() const { return CurrentEpoch; }

    UFUNCTION(BlueprintPure)
    float GetGameTimeHours() const { return GameTimeHours; }

    UFUNCTION(BlueprintPure)
    float GetEpochProgress() const;

    UFUNCTION(BlueprintPure)
    FString GetEpochDisplayName() const;

    UFUNCTION(BlueprintPure)
    bool IsItemAvailableInEpoch(FName ItemID) const;

    UFUNCTION(BlueprintPure)
    bool CanCraftRecipeInCurrentEpoch(FName RecipeID) const;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Epoch Settings")
    float HoursToBronzeAge = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Epoch Settings")
    float HoursToMedievalAge = 500.0f;

    UPROPERTY(BlueprintAssignable)
    FOnEpochChanged OnEpochChanged;

    UPROPERTY(BlueprintAssignable)
    FOnEpochProgress OnEpochProgress;

protected:
    UPROPERTY(Replicated)
    EEpoch CurrentEpoch = EEpoch::StoneAge;

    UPROPERTY(Replicated)
    float GameTimeHours = 0.0f;

private:
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
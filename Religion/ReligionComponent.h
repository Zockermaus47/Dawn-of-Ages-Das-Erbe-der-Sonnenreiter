#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ReligionComponent.generated.h"

UENUM(BlueprintType)
enum class EGod : uint8
{
    Ares UMETA(DisplayName = "Ares"),
    Gaia UMETA(DisplayName = "Gaia"),
    Athena UMETA(DisplayName = "Athena"),
    Tyche UMETA(DisplayName = "Tyche"),
    Hades UMETA(DisplayName = "Hades"),
    Hephaestus UMETA(DisplayName = "Hephaestus"),
    Poseidon UMETA(DisplayName = "Poseidon")
};

USTRUCT(BlueprintType)
struct FDivineBlessing
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religion")
    EGod God;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religion")
    FString BlessingName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religion")
    float Duration = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religion")
    float BuffStrength = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religion")
    bool bIsActive = false;
};

USTRUCT(BlueprintType)
struct FTempleData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religion")
    EGod DedicatedGod;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religion")
    FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religion")
    int32 TempleLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religion")
    float Devotion = 0.0f;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEFFIS_DAWNOFAGES_API UReligionComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UReligionComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religion")
    TMap<EGod, float> GodFavor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religion")
    TArray<FDivineBlessing> ActiveBlessings;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Religion")
    TArray<FTempleData> Temples;

    UFUNCTION(BlueprintCallable, Category = "Religion")
    void MakeOffering(EGod God, int32 OfferingValue);

    UFUNCTION(BlueprintCallable, Category = "Religion")
    bool RequestBlessing(EGod God);

    UFUNCTION(BlueprintCallable, Category = "Religion")
    void BuildTemple(EGod God, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Religion")
    void PrayAtTemple(int32 TempleIndex);

    UFUNCTION(BlueprintPure, Category = "Religion")
    float GetFavorWithGod(EGod God) const;

    UFUNCTION(BlueprintPure, Category = "Religion")
    FString GetGodName(EGod God) const;

    UFUNCTION(BlueprintPure, Category = "Religion")
    FString GetGodDomain(EGod God) const;

    UFUNCTION(BlueprintCallable, Category = "Religion")
    void UpdateBlessings(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Religion")
    FDivineBlessing CreateBlessing(EGod God);

    UFUNCTION(BlueprintPure, Category = "Religion")
    TArray<FDivineBlessing> GetActiveBlessings() const;

    UFUNCTION(BlueprintPure, Category = "Religion")
    float GetTotalBuffStrength() const;
};
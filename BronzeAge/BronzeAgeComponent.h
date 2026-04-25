#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BronzeAgeComponent.generated.h"

UENUM(BlueprintType)
enum class EBronzeAgeTech : uint8
{
    None UMETA(DisplayName = "Keine"),
    CopperMining UMETA(DisplayName = "Kupferbergbau"),
    BronzeSmelting UMETA(DisplayName = "Bronzeschmelze"),
    CopperTools UMETA(DisplayName = "Kupferwerkzeuge"),
    BronzeWeapons UMETA(DisplayName = "Bronzwaffen"),
    BronzeArmor UMETA(DisplayName = "Bronzepanzer"),
    Wheel UMETA(DisplayName = "Rad"),
    Chariot UMETA(DisplayName = "Streitwagen"),
    AdvancedPottery UMETA(DisplayName = "Töpferei"),
    Irrigation UMETA(DisplayName = "Bewässerung")
};

UENUM(BlueprintType)
enum class EMetalType : uint8
{
    None UMETA(DisplayName = "Keine"),
    Copper UMETA(DisplayName = "Kupfer"),
    Tin UMETA(DisplayName = "Zinn"),
    Bronze UMETA(DisplayName = "Bronze")
};

USTRUCT(BlueprintType)
struct FBronzeRecipe
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RecipeID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName OutputItemID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> RequiredMaterials;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> RequiredQuantities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CraftTime = 5;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBronzeAgeTech RequiredTech = EBronzeAgeTech::None;
};

USTRUCT(BlueprintType)
struct FOreDeposit
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName DepositID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMetalType MetalType = EMetalType::Copper;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Purity = 0.5f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_DAWNOFAGES_API UBronzeAgeComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UBronzeAgeComponent();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BronzeAge")
    TArray<EBronzeAgeTech> UnlockedTechs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BronzeAge")
    TArray<FBronzeRecipe> BronzeRecipes;

    UPROPERTY(BlueprintReadOnly, Category = "BronzeAge")
    int32 CopperOre = 0;

    UPROPERTY(BlueprintReadOnly, Category = "BronzeAge")
    int32 TinOre = 0;

    UPROPERTY(BlueprintReadOnly, Category = "BronzeAge")
    int32 BronzeIngots = 0;

    UFUNCTION(BlueprintCallable, Category = "BronzeAge")
    bool UnlockTech(EBronzeAgeTech Tech);

    UFUNCTION(BlueprintCallable, Category = "BronzeAge")
    bool HasTech(EBronzeAgeTech Tech) const;

    UFUNCTION(BlueprintCallable, Category = "BronzeAge")
    bool CanCraft(FBronzeRecipe Recipe) const;

    UFUNCTION(BlueprintCallable, Category = "BronzeAge")
    bool CraftBronzeItem(FBronzeRecipe Recipe);

    UFUNCTION(BlueprintCallable, Category = "BronzeAge")
    bool AddOre(EMetalType MetalType, int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "BronzeAge")
    int32 GetOre(EMetalType MetalType) const;

    UFUNCTION(BlueprintCallable, Category = "BronzeAge")
    bool SmeltBronze();

    UFUNCTION(BlueprintCallable, Category = "BronzeAge")
    TArray<EBronzeAgeTech> GetAvailableTechs() const;

    UFUNCTION(BlueprintPure, Category = "BronzeAge")
    float GetTechProgress(EBronzeAgeTech Tech) const;

private:
    int32 CalculateBronzeOutput(int32 Copper, int32 Tin, float Purity);
};
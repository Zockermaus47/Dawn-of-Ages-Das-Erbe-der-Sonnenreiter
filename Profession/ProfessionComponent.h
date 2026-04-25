#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProfessionComponent.generated.h"

UENUM(BlueprintType)
enum class EProfession : uint8
{
    None UMETA(DisplayName = "Keine"),
    
    Hunter UMETA(DisplayName = "Jäger"),
    Gatherer UMETA(DisplayName = "Sammler"),
    Woodcutter UMETA(DisplayName = "Holzfäller"),
    Miner UMETA(DisplayName = "Bergmann"),
    Farmer UMETA(DisplayName = "Bauer"),
    Blacksmith UMETA(DisplayName = "Schmied"),
    Carpenter UMETA(DisplayName = "Zimmermann"),
    Tailor UMETA(DisplayName = "Schneider"),
    Alchemist UMETA(DisplayName = "Alchemist"),
    Cook UMETA(DisplayName = "Koch"),
    Leatherworker UMETA(DisplayName = "Lederer"),
    Mason UMETA(DisplayName = "Maurer"),
    Merchant UMETA(DisplayName = "Händler"),
    Healer UMETA(DisplayName = "Heiler"),
    Scout UMETA(DisplayName = "Späher"),
    Warrior UMETA(DisplayName = "Krieger"),
    Guard UMETA(DisplayName = "Wächter"),
    BeastTamer UMETA(DisplayName = "Tierbändiger")
};

USTRUCT(BlueprintType)
struct FProfessionStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EProfession Profession = EProfession::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Level = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentXP = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredXP = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkillBonus = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalActions = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_DAWNOFAGES_API UProfessionComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UProfessionComponent();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession")
    EProfession PrimaryProfession = EProfession::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profession")
    TArray<EProfession> SecondaryProfessions;

    UPROPERTY(BlueprintReadOnly, Category = "Profession")
    FProfessionStats PrimaryStats;

    UPROPERTY(BlueprintReadOnly, Category = "Profession")
    TArray<FProfessionStats> SecondaryStats;

    UFUNCTION(BlueprintCallable, Category = "Profession")
    void SetPrimaryProfession(EProfession NewProfession);

    UFUNCTION(BlueprintCallable, Category = "Profession")
    void AddSecondaryProfession(EProfession Profession);

    UFUNCTION(BlueprintCallable, Category = "Profession")
    void RemoveProfession(EProfession Profession);

    UFUNCTION(BlueprintCallable, Category = "Profession")
    bool HasProfession(EProfession Profession) const;

    UFUNCTION(BlueprintCallable, Category = "Profession")
    int32 GetProfessionLevel(EProfession Profession) const;

    UFUNCTION(BlueprintCallable, Category = "Profession")
    void AddXP(EProfession Profession, int32 XPAmount);

    UFUNCTION(BlueprintCallable, Category = "Profession")
    bool LevelUp(EProfession Profession);

    UFUNCTION(BlueprintCallable, Category = "Profession")
    float GetSkillBonus(EProfession Profession) const;

    UFUNCTION(BlueprintPure, Category = "Profession")
    int32 GetTotalLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Profession")
    FProfessionStats GetProfessionStats(EProfession Profession) const;

    UFUNCTION(BlueprintCallable, Category = "Profession")
    TArray<EProfession> GetAllProfessions() const;

private:
    void InitializeProfession(EProfession Profession, FProfessionStats& Stats);
    int32 CalculateRequiredXP(int32 Level) const;
};

USTRUCT(BlueprintType)
struct FProfessionAction
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ActionName = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EProfession RelatedProfession = EProfession::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 XPReward = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanRepeat = true;

    UPROPERTY(BlueprintReadOnly, Category = "Profession")
    int32 TimesCompleted = 0;
};
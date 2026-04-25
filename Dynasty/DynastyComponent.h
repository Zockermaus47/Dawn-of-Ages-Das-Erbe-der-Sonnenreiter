#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DynastyComponent.generated.h"

UENUM(BlueprintType)
enum class ECharacterTrait : uint8
{
    Strong UMETA(DisplayName = "Stark"),
    Intelligent UMETA(DisplayName = "Intelligent"),
    Lucky UMETA(DisplayName = "Glücklich"),
    Healthy UMETA(DisplayName = "Gesund"),
    Fast UMETA(DisplayName = "Schnell"),
    Charismatic UMETA(DisplayName = "Charismatisch")
};

USTRUCT(BlueprintType)
struct FDynastyMember
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    FName MemberID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    int32 Generation = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    int32 Age = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    TArray<ECharacterTrait> Traits;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    FName ParentID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    bool bIsAlive = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    float Health = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    float XPBonusMultiplier = 1.0f;
};

USTRUCT(BlueprintType)
struct FLegacyBonus
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    float XPBonus = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    float GoldBonus = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    float CraftingSpeedBonus = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    float DamageBonus = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    float TradeBonus = 0.0f;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEFFIS_DAWNOFAGES_API UDynastyComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UDynastyComponent();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    TArray<FFamilyMember> FamilyTree;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    FName CurrentHeirID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    int32 CurrentGeneration = 1;

    UPROPERTY(BlueprintReadOnly, Category = "Dynasty")
    FLegacyBonus LegacyBonuses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    int32 MaxGenerations = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynasty")
    float AgeSpeed = 1.0f;

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    void CreateFounder(FName FounderName, TArray<ECharacterTrait> StartingTraits);

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    bool HaveChild(FName ChildName, FName ParentID);

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    bool PassDownGeneration(FName HeirName);

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    void CalculateLegacyBonuses();

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    void AddFamilyMember(FFamilyMember Member);

    UFUNCTION(BlueprintPure, Category = "Dynasty")
    TArray<ECharacterTrait> GetInheritedTraits(FName ParentID) const;

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    FFamilyMember FindMember(FName MemberID);

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    bool SetHeir(FName MemberID);

    UFUNCTION(BlueprintPure, Category = "Dynasty")
    float GetTraitBonus(ECharacterTrait Trait) const;

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    void AgeFamily(float DeltaTime);

    UFUNCTION(BlueprintPure, Category = "Dynasty")
    int32 GetLivingGenerations() const;

private:
    TArray<ECharacterTrait> InheritTraitsFrom(const TArray<ECharacterTrait>& ParentTraits);
    float CalculateTraitValue(ECharacterTrait Trait, int32 GenerationCount);
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Profession.generated.h"

UENUM(BlueprintType)
enum class EProfessionType : uint8
{
    None            UMETA(DisplayName = "None"),
    Hunter          UMETA(DisplayName = "Hunter"),
    Gatherer        UMETA(DisplayName = "Gatherer"),
    Miner           UMETA(DisplayName = "Miner"),
    Woodcutter      UMETA(DisplayName = "Woodcutter"),
    Farmer          UMETA(DisplayName = "Farmer"),
    Cook            UMETA(DisplayName = "Cook"),
    Brewer          UMETA(DisplayName = "Brewer"),
    Blacksmith      UMETA(DisplayName = "Blacksmith"),
    Carpenter      UMETA(DisplayName = "Carpenter"),
    Leatherworker   UMETA(DisplayName = "Leatherweaver"),
    Weaver         UMETA(DisplayName = "Weaver"),
    Jeweler        UMETA(DisplayName = "Jeweler"),
    Alchemist      UMETA(DisplayName = "Alchemist"),
    Healer         UMETA(DisplayName = "Healer"),
    Merchant       UMETA(DisplayName = "Merchant"),
    Scout          UMETA(DisplayName = "Scout"),
    Guard          UMETA(DisplayName = "Guard"),
    Bard           UMETA(DisplayName = "Bard"),
    Tamer          UMETA(DisplayName = "Tamer")
};

UENUM(BlueprintType)
enum class EProfessionTier : uint8
{
    Apprentice   UMETA(DisplayName = "Apprentice"),
    Journeyman  UMETA(DisplayName = "Journeyman"),
    Expert     UMETA(DisplayName = "Expert"),
    Master     UMETA(DisplayName = "Master"),
    GrandMaster UMETA(DisplayName = "Grand Master")
};

USTRUCT(BlueprintType)
struct FProfessionData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ProfessionID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EProfessionType ProfessionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxLevel = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperiencePerLevel = 1000;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Abilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> MasteryAbilities;
};

USTRUCT(BlueprintType)
struct FSkillTreeNode
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName NodeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Cost = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Prerequisites;
};

USTRUCT(BlueprintType)
struct FProfessionInstance
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ProfessionID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Level = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Experience = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EProfessionTier Tier = EProfessionTier::Apprentice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> UnlockedAbilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> UnlockedMasteries;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UProfessionSystem : public UObject
{
    GENERATED_BODY()

public:
    UProfessionSystem();

    UFUNCTION(BlueprintCallable, Category = "Profession")
    static FProfessionData GetProfessionData(FName ProfessionID);

    UFUNCTION(BlueprintCallable, Category = "Profession")
    static bool CanUnlockAbility(FProfessionInstance Profession, FName AbilityID);

    UFUNCTION(BlueprintCallable, Category = "Profession")
    static void UnlockAbility(FProfessionInstance& Profession, FName AbilityID);

    UFUNCTION(BlueprintCallable, Category = "Profession")
    static void AddExperience(FProfessionInstance& Profession, int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Profession")
    static bool LevelUp(FProfessionInstance& Profession);

    UFUNCTION(BlueprintCallable, Category = "Profession")
    static TArray<FSkillTreeNode> GetSkillTree(FName ProfessionID);

    UFUNCTION(BlueprintCallable, Category = "Profession")
    static TArray<FProfessionData> GetAllProfessions();
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dynasty.generated.h"

USTRUCT(BlueprintType)
struct FFamilyMember
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MemberID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Age;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SpouseID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> ChildrenIDs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsAlive = true;
};

USTRUCT(BlueprintType)
struct FDynasty
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName DynastyID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FFamilyMember> Members;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LeaderID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Generation = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Wealth = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Prestige = 0;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UDynastySystem : public UObject
{
    GENERATED_BODY()

public:
    UDynastySystem();

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    static FDynasty CreateDynasty(FText Name);

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    static void AddMember(FDynasty& Dynasty, FFamilyMember Member);

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    static void RemoveMember(FDynasty& Dynasty, FName MemberID);

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    static void Marry(FDynasty& Dynasty, FName Member1ID, FName Member2ID);

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    static FFamilyMember BirthChild(FDynasty& Dynasty, FName Parent1ID, FName Parent2ID);

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    static void PassAway(FDynasty& Dynasty, FName MemberID);

    UFUNCTION(BlueprintCallable, Category = "Dynasty")
    static void AdvanceGeneration(FDynasty& Dynasty);
};
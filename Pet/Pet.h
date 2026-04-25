#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Pet.generated.h"

UENUM(BlueprintType)
enum class EPetType : uint8
{
    None        UMETA(DisplayName = "None"),
    Dog         UMETA(DisplayName = "Dog"),
    Cat         UMETA(DisplayName = "Cat"),
    Wolf        UMETA(DisplayName = "Wolf"),
    Fox         UMETA(DisplayName = "Fox"),
    Rabbit      UMETA(DisplayName = "Rabbit"),
    Bird        UMETA(DisplayName = "Bird"),
    Monkey      UMETA(DisplayName = "Monkey")
};

USTRUCT(BlueprintType)
struct FPetData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName PetID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPetType PetType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TamingTime = 15;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> TamingItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanFight = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanGather = false;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UPetSystem : public UObject
{
    GENERATED_BODY()

public:
    UPetSystem();

    UFUNCTION(BlueprintCallable, Category = "Pet")
    static FPetData GetPetData(FName PetID);

    UFUNCTION(BlueprintCallable, Category = "Pet")
    static TArray<FPetData> GetAllPets();
};
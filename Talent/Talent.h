#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Talent.generated.h"

UENUM(BlueprintType)
enum class ETalentTree : uint8
{
    Warrior   UMETA(DisplayName = "Krieger"),
    Hunter    UMETA(DisplayName = "Jäger"),
    Mage     UMETA(DisplayName = "Magier"),
    Smith    UMETA(DisplayName = "Schmied"),
    Farmer   UMETA(DisplayName = "Bauer")
};

USTRUCT(BlueprintType)
struct FTalentNode
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FName NodeID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Cost;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FName> RequiresNodes;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bIsUnlocked;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UTalentSystem : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable) static bool UnlockTalent(FName NodeID, ETalentTree Tree);
    UFUNCTION(BlueprintCallable) static int32 GetSpentPoints(ETalentTree Tree);
    UFUNCTION(BlueprintCallable) static TArray<FTalentNode> GetUnlockedTalents(ETalentTree Tree);
};
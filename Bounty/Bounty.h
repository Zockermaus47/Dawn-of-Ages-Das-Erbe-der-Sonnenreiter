#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Bounty.generated.h"

UENUM(BlueprintType)
enum class EBountyType : uint8
{
    Capture  UMETA(DisplayName = "Capture"),
    Kill     UMETA(DisplayName = "Kill"),
    Deliver  UMETA(DisplayName = "Deliver")
};

USTRUCT(BlueprintType)
struct FBounty
{
    GENERATED_BODY()
    FName BountyID;
    FText DisplayName;
    EBountyType Type;
    FName TargetID;
    int32 Reward = 500;
    int32 Difficulty = 1;
    bool bActive = true;
    float TimeLimit = 3600.0f;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UBountySystem : public UObject
{
    GENERATED_BODY()
public:
    static FBounty CreateBounty(EBountyType Type, FName TargetID, int32 Reward);
    static TArray<FBounty> GetActiveBounties();
    static bool AcceptBounty(FName BountyID);
    static bool CompleteBounty(FName BountyID);
    static int32 GetReward();
    static FBounty GetBounty(FName BountyID);
    static TArray<FName> GetTargets();
private:
    static TArray<FBounty> ActiveBounties;
};
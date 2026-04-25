#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Slavery.generated.h"

UENUM(BlueprintType) enum class ESlaveState : uint8 { Free UMETA(DisplayName="Free"), Captive UMETA(DisplayName="Captive"), Auction UMETA(DisplayName="Auction"), Owned UMETA(DisplayName="Owned"), Escaped UMETA(DisplayName="Escaped") };

USTRUCT(BlueprintType) struct FSlaveData { GENERATED_BODY() FName SlaveID; FText Name; ESlaveState State; int32 Value = 100; int32 Loyalty = 50; FName OwnerID; bool bCanEscape = true; };

UCLASS() class STEFFIS_DAWNOFAGES_API USlaverySystem : public UObject { GENERATED_BODY() public:
    static bool Capture(FName TargetID);
    static bool Release(FName SlaveID);
    static bool Sell(FName SlaveID, int32 Price);
    static bool Buy(FName SlaveID, int32 Price);
    static bool PutOnAuction(FName SlaveID, int32 Price);
    static bool AssignTask(FName SlaveID, FName TaskID);
    static void TickSlaves(float DeltaTime);
    static TArray<FName> GetOwnedSlaves();
    static int32 GetTotalValue();
};
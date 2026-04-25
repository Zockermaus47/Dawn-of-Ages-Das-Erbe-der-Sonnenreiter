#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Multiplayer.generated.h"

UENUM(BlueprintType)
enum class EMultiplayerMode : uint8
{
    SinglePlayer  UMETA(DisplayName = "Single Player"),
    CoOp         UMETA(DisplayName = "Co-Op"),
    PvP          UMETA(DisplayName = "PvP")
};

USTRUCT(BlueprintType)
struct FPlayerSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName PlayerID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText PlayerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsReady = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Ping = 0;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UMultiplayerSystem : public UObject
{
    GENERATED_BODY()

public:
    UMultiplayerSystem();

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    static bool CreateServer(FText ServerName, int32 MaxPlayers);

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    static bool JoinServer(FName ServerID);

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    static void LeaveServer();

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    static TArray<FPlayerSettings> GetConnectedPlayers();

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    static void SetPlayerReady(bool bReady);
};
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Networking.h"
#include "MultiplayerComponent.generated.h"

UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
    None UMETA(DisplayName = "Keine"),
    Player UMETA(DisplayName = "Spieler"),
    Spectator UMETA(DisplayName = "Zuschauer"),
    Admin UMETA(DisplayName = "Admin")
};

UENUM(BlueprintType)
enum class EServerType : uint8
{
    Listen UMETA(DisplayName = "Listen Server"),
    Dedicated UMETA(DisplayName = "Dedicated Server"),
    Client UMETA(DisplayName = "Client")
};

USTRUCT(BlueprintType)
struct FPlayerInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString PlayerName = "Player";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PlayerID = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPlayerRole Role = EPlayerRole::Player;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsReady = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Ping = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_DAWNOFAGES_API UMultiplayerComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UMultiplayerComponent();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplayer")
    bool bIsHost = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplayer")
    bool bIsConnected = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplayer")
    EServerType ServerType = EServerType::Listen;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplayer")
    FString ServerName = "Dawn of Ages Server";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Multiplayer")
    int32 MaxPlayers = 32;

    UPROPERTY(BlueprintReadOnly, Category = "Multiplayer")
    TArray<FPlayerInfo> ConnectedPlayers;

    UPROPERTY(BlueprintReadOnly, Category = "Multiplayer")
    int32 LocalPlayerID = 0;

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    bool HostServer(FString InServerName, int32 InMaxPlayers);

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    bool JoinServer(FString IPAddress, int32 Port);

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    void Disconnect();

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    bool KickPlayer(int32 PlayerID);

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    bool BanPlayer(int32 PlayerID);

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    bool SendMessageToPlayer(int32 PlayerID, FString Message);

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    void SendMessageToAll(FString Message);

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    bool SaveGameState();

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    bool LoadGameState();

    UFUNCTION(BlueprintPure, Category = "Multiplayer")
    int32 GetPlayerCount() const;

    UFUNCTION(BlueprintPure, Category = "Multiplayer")
    bool IsHost() const;

    UFUNCTION(BlueprintCallable, Category = "Multiplayer")
    void SetPlayerReady(bool bReady);

private:
    void UpdatePlayerList();
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEFFIS_DAWNOFAGES_API UGuildComponent : public UActorComponent
{
    GENERATED_BODY()

public:    
    UGuildComponent();

protected:
    virtual void BeginPlay() override;

public:    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guild")
    FName GuildID = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guild")
    FString GuildName = "";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guild")
    int32 GuildLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guild")
    int32 MemberCount = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guild")
    TArray<FName> MemberIDs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guild")
    TArray<FName> AllyGuilds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guild")
    TArray<FName> EnemyGuilds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guild")
    int32 GuildBankGold = 0;

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool CreateGuild(FString InName);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool JoinGuild(FName InGuildID);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool LeaveGuild();

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool InvitePlayer(FName PlayerID);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool KickMember(FName MemberID);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool DeclareWar(FName EnemyGuildID);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool DeclarePeace(FName AllyGuildID);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool DepositGold(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool WithdrawGold(int32 Amount);

    UFUNCTION(BlueprintPure, Category = "Guild")
    bool HasPermission(FName PlayerID) const;
};
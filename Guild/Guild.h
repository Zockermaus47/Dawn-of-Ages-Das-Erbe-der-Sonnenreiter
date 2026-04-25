#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Guild.generated.h"

UENUM(BlueprintType)
enum class EGuildRank : uint8
{
    Recruit    UMETA(DisplayName = "Recruit"),
    Member    UMETA(DisplayName = "Member"),
    Officer   UMETA(DisplayName = "Officer"),
    Elder     UMETA(DisplayName = "Elder"),
    Leader    UMETA(DisplayName = "Leader"),
    Founder   UMETA(DisplayName = "Founder")
};

UENUM(BlueprintType)
enum class EGuildType : uint8
{
    Social    UMETA(DisplayName = "Social"),
    Trade     UMETA(DisplayName = "Trade"),
    Combat    UMETA(DisplayName = "Combat"),
    Thief     UMETA(DisplayName = "Thief"),
    Magic     UMETA(DisplayName = "Magic"),
    Religious UMETA(DisplayName = "Religious")
};

USTRUCT(BlueprintType)
struct FGuildData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName GuildID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGuildType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MemberCount = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxMembers = 50;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Level = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 XP = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Gold = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LeaderID;
};

USTRUCT(BlueprintType)
struct FGuildMember
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MemberID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText MemberName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGuildRank Rank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Contribution = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 LastActive = 0;
};

USTRUCT(BlueprintType)
struct FGuildPerk
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName PerkID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Cost = 100;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StatMod = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName StatType;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UGuildSystem : public UObject
{
    GENERATED_BODY()

public:
    UGuildSystem();

    static FGuildData CreateGuild(FText Name, EGuildType Type);

    static bool JoinGuild(FName GuildID);

    static void LeaveGuild();

    static FGuildData GetGuildData(FName GuildID);

    static TArray<FGuildMember> GetMembers(FName GuildID);

    static bool PromoteMember(FName MemberID, EGuildRank NewRank);

    static bool KickMember(FName MemberID);

    static void AddXP(int32 Amount);

    static void AddGold(int32 Amount);

    static bool WithdrawGold(int32 Amount);

    static TArray<FGuildPerk> GetAvailablePerks();

    static bool PurchasePerk(FName PerkID);

    static int32 GetMemberLimit();

    static float GetTaxRate();

private:
    static FName CurrentGuild;
    static int32 GuildBankGold;
};
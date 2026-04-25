#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "StoryNPCs.generated.h"

UENUM(BlueprintType)
enum class EStoryNPCType : uint8
{
    None        UMETA(DisplayName = "None"),
    Fragment   UMETA(DisplayName = "Fragment"),
    Glitch     UMETA(DisplayName = "Glitch"),
    Merchant   UMETA(DisplayName = "Merchant"),
    Smith      UMETA(DisplayName = "Schmied"),
    Healer     UMETA(DisplayName = "Heiler"),
    QuestGiver UMETA(DisplayName = "Quest-Geber"),
    Vendor     UMETA(DisplayName = "Händler")
};

USTRUCT(BlueprintType)
struct FStoryNPCData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName NPCID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EStoryNPCType NPCType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFragment AssociatedFragment;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DefaultDialog;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText QuestDialog;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> AvailableQuests;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> ShopInventory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LocationID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsHidden = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanDie = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health = 100.0f;
};

USTRUCT(BlueprintType)
struct FEchoData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EchoID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText SpawnDialog;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText GiftDialog;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText GlitchExplanation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LocationID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bGiveGift = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName GiftItemID;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UStoryNPCSystem : public UObject
{
    GENERATED_BODY()

public:
    UStoryNPCSystem();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    static FStoryNPCData GetNPCData(FName NPCID);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    static TArray<FStoryNPCData> GetNPCsByFragment(EFragment Fragment);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    static TArray<FStoryNPCData> GetAllStoryNPCs();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    static FText GetNPCDialog(FName NPCID, FName QuestID);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    static FEchoData GetEchoData();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    static bool IsEchoAvailable();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    static void UnlockEcho();
};
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct FItemInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStackSize = 99;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Weight = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsConsumable = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsEquippable = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName UseEffectID;

    FItemInfo()
    {
        ItemID = NAME_None;
        MaxStackSize = 99;
        Weight = 1.0f;
        bIsConsumable = false;
        bIsEquippable = false;
    }
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity = 0;

    FInventorySlot()
    {
        ItemID = NAME_None;
        Quantity = 0;
    }

    bool IsEmpty() const { return ItemID == NAME_None || Quantity <= 0; }
};

UCLASS(BlueprintType)
class STEFFIS_SPIEL_API UItemDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TMap<FName, FItemInfo> AllItems;

    UFUNCTION(BlueprintCallable)
    FItemInfo GetItemInfo(FName ItemID) const;

    UFUNCTION(BlueprintCallable)
    bool HasItem(FName ItemID) const;

    UFUNCTION(BlueprintCallable)
    TArray<FName> GetAllItemIDs() const;
};
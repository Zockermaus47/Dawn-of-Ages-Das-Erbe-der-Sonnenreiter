#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DawnOfAgesGameData.generated.h"

USTRUCT(BlueprintType)
struct FItemEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Weight = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStackSize = 99;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Effect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SoundFactor = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Epoch;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Icon;

    FItemEntry()
    {
        ItemID = NAME_None;
        Weight = 1.0f;
        MaxStackSize = 99;
        SoundFactor = 1.0f;
    }
};

USTRUCT(BlueprintType)
struct FCraftingRecipeEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RecipeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, int32> RequiredItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ResultItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ResultQuantity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CraftingTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Epoch;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString CraftingStation;

    FCraftingRecipeEntry()
    {
        RecipeID = NAME_None;
        ResultQuantity = 1;
        CraftingTime = 0.0f;
    }
};

UCLASS(BlueprintType)
class STEFFIS_SPIEL_API UDawnOfAgesGameData : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TMap<FName, FItemEntry> AllItems;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TMap<FName, FCraftingRecipeEntry> CraftingRecipes;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FName> StoneAgeItems;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FName> BronzeAgeItems;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FName> MedievalItems;

    UFUNCTION(BlueprintCallable)
    FItemEntry GetItem(FName ItemID) const;

    UFUNCTION(BlueprintCallable)
    FCraftingRecipeEntry GetRecipe(FName RecipeID) const;

    UFUNCTION(BlueprintCallable)
    TArray<FName> GetItemsByEpoch(FString Epoch) const;

    UFUNCTION(BlueprintCallable)
    TArray<FName> GetRecipesByEpoch(FString Epoch) const;

    UFUNCTION(BlueprintCallable)
    bool CanCraftInCurrentEpoch(FName RecipeID, FString CurrentEpoch) const;

    UFUNCTION(BlueprintCallable)
    void InitializeDefaultData();
};

UCLASS()
class STEFFIS_SPIEL_API UDawnOfAgesItemDatabase : public UDataAsset
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, CallInEditor)
    void GenerateFromCSV(const FString& CSVContent);

    UFUNCTION(BlueprintCallable)
    void SaveToDataTable();
};
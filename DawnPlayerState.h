#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ItemData.h"
#include "DawnPlayerState.generated.h"

class UInventorySystemComponent;
class UStatsComponent;
class UCraftingComponent;

UCLASS()
class STEFFIS_SPIEL_API ADawnPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    ADawnPlayerState();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    void SetPlayerName(const FString& NewName);

    UFUNCTION(BlueprintCallable)
    void SetTeamID(int32 NewTeamID);

    UFUNCTION(BlueprintPure)
    int32 GetTeamID() const { return TeamID; }

    UFUNCTION(BlueprintPure)
    int32 GetKills() const { return Kills; }

    UFUNCTION(BlueprintPure)
    int32 GetDeaths() const { return Deaths; }

    UFUNCTION(BlueprintCallable)
    void AddKill();

    UFUNCTION(BlueprintCallable)
    void AddDeath();

    UFUNCTION(BlueprintCallable)
    void AddScore(int32 ScoreToAdd);

    UFUNCTION(BlueprintPure)
    float GetKDRatio() const;

    UPROPERTY(Replicated)
    int32 TeamID = 0;

    UPROPERTY(Replicated)
    int32 Kills = 0;

    UPROPERTY(Replicated)
    int32 Deaths = 0;

    UPROPERTY(Replicated)
    int32 Score = 0;

    UPROPERTY(Replicated)
    FString PlayerNickname;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
    FLinearColor PlayerColor = FLinearColor::White;

private:
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Politics.generated.h"

UENUM(BlueprintType)
enum class EGovernment : uint8
{
    Tribal     UMETA(DisplayName = "Tribal"),
    Monarchy  UMETA(DisplayName = "Monarchy"),
    Republic  UMETA(DisplayName = "Republic"),
    Theocracy UMETA(DisplayName = "Theocracy"),
    Anarchy  UMETA(DisplayName = "Anarchy")
};

USTRUCT(BlueprintType)
struct FKingdomData
{
    GENERATED_BODY()
    FName KingdomID;
    FText Name;
    EGovernment Government;
    int32 Population = 0;
    int32 Gold = 0;
    float TaxRate = 0.1f;
    FName RulerID;
    int32 Stability = 100;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UPoliticsSystem : public UObject
{
    GENERATED_BODY()
public:
    static FKingdomData CreateKingdom(FText Name, EGovernment Gov);
    static bool Establish(FName LeaderID);
    static bool SetTaxRate(float Rate);
    static bool CollectTaxes();
    static bool EstablishLaws(FName LawID);
    static int32 GetStability();
    static void ModifyStability(int32 Amount);
    static bool DeclareWar(FName KingdomID);
    static bool SignTreaty(FName KingdomID);
    static bool ElectOfficial(FName PlayerID, FText Title);
    static FName GetRuler();
private:
    static FName CurrentKingdom;
};
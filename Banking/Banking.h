#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Banking.generated.h"

UENUM(BlueprintType)
enum class EAccountType : uint8
{
    Personal  UMETA(DisplayName = "Personal"),
    Guild     UMETA(DisplayName = "Guild"),
    Trade     UMETA(DisplayName = "Trade"),
    Loan      UMETA(DisplayName = "Loan")
};

USTRUCT(BlueprintType)
struct FBankAccount
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere) FName AccountID;
    UPROPERTY(EditAnywhere) int32 Balance = 0;
    UPROPERTY(EditAnywhere) int32 Credit = 0;
    UPROPERTY(EditAnywhere) float InterestRate = 0.02f;
    UPROPERTY(EditAnywhere) EAccountType Type;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UBankingSystem : public UObject
{
    GENERATED_BODY()
public:
    static FBankAccount CreateAccount(EAccountType Type);
    static void Deposit(int32 Amount);
    static bool Withdraw(int32 Amount);
    static int32 GetBalance();
    static void SetBalance(int32 Amount);
    static float GetInterestRate();
    static void AddInterest();
    static bool RequestLoan(int32 Amount, int32 Terms);
    static bool RepayLoan(int32 Amount);
    static int32 GetDebt();
    static void Transfer(FName ToAccount, int32 Amount);
private:
    static int32 PlayerGold;
    static int32 PlayerDebt;
};
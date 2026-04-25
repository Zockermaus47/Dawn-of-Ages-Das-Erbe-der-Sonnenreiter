#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Disease.generated.h"

UENUM(BlueprintType)
enum class EDiseaseType : uint8
{
    Infection  UMETA(DisplayName = "Infection"),
    Poison    UMETA(DisplayName = "Poison"),
    Curse     UMETA(DisplayName = "Curse"),
    Plague    UMETA(DisplayName = "Plague"),
    Madness   UMETA(DisplayName = "Madness")
};

USTRUCT(BlueprintType)
struct FDiseaseData
{
    GENERATED_BODY()
    FName DiseaseID;
    FText DisplayName;
    EDiseaseType Type;
    float DamagePerSecond = 0.0f;
    float Duration = 60.0f;
    int32 Severity = 1;
    bool bContagious = false;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UDiseaseSystem : public UObject
{
    GENERATED_BODY()
public:
    static bool Infect(FDiseaseData Disease);
    static void Cure(FName DiseaseID);
    static void TickDiseases(float DeltaTime);
    static bool IsInfected();
    static float GetDamageMultiplier();
    static bool IsContagious();
    static TArray<FDiseaseData> GetActiveDiseases();
    static void SpreadToNearby(float Radius);
    static bool CreatePlague(FName AreaID);
private:
    static TArray<FDiseaseData> ActiveDiseases;
};
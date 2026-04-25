#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Survival.generated.h"

UENUM(BlueprintType)
enum class ESurvivalState : uint8
{
    Healthy    UMETA(DisplayName = "Healthy"),
    Hungry     UMETA(DisplayName = "Hungry"),
    Starving  UMETA(DisplayName = "Starving"),
    Thirsty   UMETA(DisplayName = "Thirsty"),
    Dehydrated UMETA(DisplayName = "Dehydrated"),
    Exhausted UMETA(DisplayName = "Exhausted"),
    Dead      UMETA(DisplayName = "Dead")
};

USTRUCT(BlueprintType)
struct FSurvivalStats
{
    GENERATED_BODY()
    float Hunger = 100.0f;
    float Thirst = 100.0f;
    float Energy = 100.0f;
    float Temperature = 37.0f;
    float Weight = 0.0f;
};

UCLASS() class STEFFIS_DAWNOFAGES_API USurvivalSystem : public UObject
{
    GENERATED_BODY()
public:
    static void TickSurvival(float DeltaTime);
    static void Eat(float Amount);
    static void Drink(float Amount);
    static void Sleep(float Hours);
    static void ModifyHunger(float Delta);
    static void ModifyThirst(float Delta);
    static void ModifyEnergy(float Delta);
    static ESurvivalState GetState();
    static bool IsStarving();
    static bool IsDehydrated();
    static bool IsExhausted();
    static float GetHungerPercent();
    static float GetThirstPercent();
    static float GetEnergyPercent();
    static float GetDamageFromStarvation();
    static float GetDamageFromDehydration();
    static void AddItemWeight(float Weight);
    static void RemoveItemWeight(float Weight);
private:
    static FSurvivalStats Stats;
};
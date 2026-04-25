#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Biome.generated.h"

UENUM(BlueprintType)
enum class EBiomeType : uint8
{
    None          UMETA(DisplayName = "None"),
    Forest       UMETA(DisplayName = "Forest"),
    Tundra       UMETA(DisplayName = "Tundra"),
    Desert       UMETA(DisplayName = "Desert"),
    Swamp        UMETA(DisplayName = "Swamp"),
    Mountain     UMETA(DisplayName = "Mountain"),
    Plains       UMETA(DisplayName = "Plains"),
    Taiga       UMETA(DisplayName = "Taiga"),
    Jungle      UMETA(DisplayName = "Jungle"),
    Beach       UMETA(DisplayName = "Beach"),
    FlackeringForest  UMETA(DisplayName = "Der Flackernde Wald"),
    EndlessDesert   UMETA(DisplayName = "Die Endlose Wüste"),
    FrozenTime    UMETA(DisplayName = "Die Gefrorene Zeit"),
    MirroredLakes UMETA(DisplayName = "Die Gespiegelten Seen"),
    BrokenSky    UMETA(DisplayName = "Der Zerbrochene Himmel")
};

USTRUCT(BlueprintType)
struct FBiomeData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BiomeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBiomeType BiomeType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Resources;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Mobs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Temperature = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Rainfall = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText PhilosophicalQuestion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsStoryBiome = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsGlitchBiome = false;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UBiomeSystem : public UObject
{
    GENERATED_BODY()

public:
    UBiomeSystem();

    UFUNCTION(BlueprintCallable, Category = "Biome")
    static FBiomeData GetBiomeData(FName BiomeID);

    UFUNCTION(BlueprintCallable, Category = "Biome")
    static TArray<FBiomeData> GetAllBiomes();
};
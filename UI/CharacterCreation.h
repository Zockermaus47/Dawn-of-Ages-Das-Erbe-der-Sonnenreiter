#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterCreation.generated.h"

UENUM(BlueprintType)
enum class ECharGender : uint8
{
    Male        UMETA(DisplayName = "Mann"),
    Female      UMETA(DisplayName = "Frau"),
    NonBinary   UMETA(DisplayName = "Nicht-Binaer")
};

UENUM(BlueprintType)
enum class ESkinTone : uint8
{
    VeryLight  UMETA(DisplayName = "Sehr Hell"),
    Light      UMETA(DisplayName = "Hell"),
    Medium     UMETA(DisplayName = "Mittel"),
    Tan        UMETA(DisplayName = "Gebraeunt"),
    Dark       UMETA(DisplayName = "Dunkel"),
    VeryDark   UMETA(DisplayName = "Sehr Dunkel")
};

UENUM(BlueprintType)
enum class EHairColor : uint8
{
    Black      UMETA(DisplayName = "Schwarz"),
    Brown      UMETA(DisplayName = "Braun"),
    Blonde     UMETA(DisplayName = "Blond"),
    Red        UMETA(DisplayName = "Rot"),
    White      UMETA(DisplayName = "Weiss"),
    Gray       UMETA(DisplayName = "Grau"),
    Blue       UMETA(DisplayName = "Blau"),
    Green      UMETA(DisplayName = "Gruen"),
    Purple     UMETA(DisplayName = "Lila"),
    Pink       UMETA(DisplayName = "Rosa")
};

UENUM(BlueprintType)
enum class EHairStyle : uint8
{
    Short      UMETA(DisplayName = "Kurz"),
    Medium     UMETA(DisplayName = "Mittel"),
    Long       UMETA(DisplayName = "Lang"),
    Curly      UMETA(DisplayName = "Lockig"),
    Bald       UMETA(DisplayName = "Kahl"),
    Mohawk     UMETA(DisplayName = "Mohawk"),
    Dreadlocks UMETA(DisplayName = "Dreadlocks"),
    Ponytail   UMETA(DisplayName = "Zopf"),
    Braids     UMETA(DisplayName = "Zopfe")
};

UENUM(BlueprintType)
enum class EEyeColor : uint8
{
    Brown      UMETA(DisplayName = "Braun"),
    Blue       UMETA(DisplayName = "Blau"),
    Green      UMETA(DisplayName = "Gruen"),
    Gray       UMETA(DisplayName = "Grau"),
    Hazel      UMETA(DisplayName = "Haselnuss"),
    Black      UMETA(DisplayName = "Schwarz"),
    Purple     UMETA(DisplayName = "Lila"),
    Red        UMETA(DisplayName = "Rot")
};

UENUM(BlueprintType)
enum class EFacialHair : uint8
{
    None        UMETA(DisplayName = "Keins"),
    Beard      UMETA(DisplayName = "Bart"),
    Mustache   UMETA(DisplayName = "Schnurrbart"),
    Goatee     UMETA(DisplayName = "Spitzbart"),
    Stubble    UMETA(DisplayName = "Drei-Tage-Bart")
};

UENUM(BlueprintType)
enum class EBodyType : uint8
{
    Slim       UMETA(DisplayName = "Schlank"),
    Athletic   UMETA(DisplayName = "Athletisch"),
    Average    UMETA(DisplayName = "Durchschnittlich"),
    Heavy      UMETA(DisplayName = "Kraeftig"),
    Muscular  UMETA(DisplayName = "Muskuloes")
};

UENUM(BlueprintType)
enum class EVoiceType : uint8
{
    Deep       UMETA(DisplayName = "Tief"),
    Normal     UMETA(DisplayName = "Normal"),
    High       UMETA(DisplayName = "Hoch")
};

USTRUCT(BlueprintType)
struct FCharacterAppearance
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGender Gender = EGender::Male;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESkinTone SkinTone = ESkinTone::Medium;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EHairColor HairColor = EHairColor::Brown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EHairStyle HairStyle = EHairStyle::Short;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEyeColor EyeColor = EEyeColor::Brown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFacialHair FacialHair = EFacialHair::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBodyType BodyType = EBodyType::Average;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EVoiceType VoiceType = EVoiceType::Normal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Height = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasScars = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasTattoos = false;
};

USTRUCT(BlueprintType)
struct FCharacterName
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText FirstName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText LastName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Nickname;
};

USTRUCT(BlueprintType)
struct FCharacterBackground
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BackgroundID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, int32> StartingItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, float> StatBonuses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> StartingSkills;
};

UCLASS()
class STEFFIS_DAWNOFAGES_API UCharacterCreationSystem : public UObject
{
    GENERATED_BODY()

public:
    UCharacterCreationSystem();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void SetGender(EGender Gender);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void SetSkinTone(ESkinTone SkinTone);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void SetHairColor(EHairColor Color);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void SetHairStyle(EHairStyle Style);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void SetEyeColor(EEyeColor Color);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void SetFacialHair(EFacialHair Style);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void SetBodyType(EBodyType Type);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void SetVoiceType(EVoiceType Type);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void SetHeight(float Height);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void SetName(FText FirstName, FText LastName, FText Nickname);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void SetBackground(FName BackgroundID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static FCharacterAppearance GetCurrentAppearance();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static FCharacterName GetCurrentName();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static FCharacterBackground GetCurrentBackground();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static TArray<FCharacterBackground> GetAllBackgrounds();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static bool IsCharacterValid();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void ConfirmCharacter();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void RandomizeAppearance();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static void ResetCharacter();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static TArray<FText> GetMaleFirstNames();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static TArray<FText> GetFemaleFirstNames();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreation")
    static TArray<FText> GetLastNames();
};
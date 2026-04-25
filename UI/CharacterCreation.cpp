#include "CharacterCreation.h"

UCharacterCreationSystem::UCharacterCreationSystem()
{
}

void UCharacterCreationSystem::SetGender(ECharGender Gender)
{
}

void UCharacterCreationSystem::SetSkinTone(ESkinTone SkinTone)
{
}

void UCharacterCreationSystem::SetHairColor(EHairColor Color)
{
}

void UCharacterCreationSystem::SetHairStyle(EHairStyle Style)
{
}

void UCharacterCreationSystem::SetEyeColor(EEyeColor Color)
{
}

void UCharacterCreationSystem::SetFacialHair(EFacialHair Style)
{
}

void UCharacterCreationSystem::SetBodyType(EBodyType Type)
{
}

void UCharacterCreationSystem::SetVoiceType(EVoiceType Type)
{
}

void UCharacterCreationSystem::SetHeight(float Height)
{
}

void UCharacterCreationSystem::SetName(FText FirstName, FText LastName, FText Nickname)
{
}

void UCharacterCreationSystem::SetBackground(FName BackgroundID)
{
}

FCharacterAppearance UCharacterCreationSystem::GetCurrentAppearance()
{
    FCharacterAppearance Appearance;
    return Appearance;
}

FCharacterName UCharacterCreationSystem::GetCurrentName()
{
    FCharacterName Name;
    Name.FirstName = FText::FromString(TEXT(""));
    Name.LastName = FText::FromString(TEXT(""));
    Name.Nickname = FText::FromString(TEXT(""));
    return Name;
}

FCharacterBackground UCharacterCreationSystem::GetCurrentBackground()
{
    FCharacterBackground BG;
    BG.BackgroundID = TEXT("Wanderer");
    BG.DisplayName = FText::FromString(TEXT("Der Wanderer"));
    BG.Description = FText::FromString(TEXT("Du hast kein Zuhause. Die Welt ist dein Reich."));
    return BG;
}

TArray<FCharacterBackground> UCharacterCreationSystem::GetAllBackgrounds()
{
    TArray<FCharacterBackground> Backgrounds;

    FCharacterBackground Wanderer;
    Wanderer.BackgroundID = TEXT("Wanderer");
    Wanderer.DisplayName = FText::FromString(TEXT("Der Wanderer"));
    Wanderer.Description = FText::FromString(TEXT("Du hast kein Zuhause. Die Welt ist dein Reich. +10% Bewegungsgeschwindigkeit"));
    Wanderer.StatBonuses.Add(TEXT("Speed"), 0.1f);
    Backgrounds.Add(Wanderer);

    FCharacterBackground Krieger;
    Krieger.BackgroundID = TEXT("Krieger");
    Krieger.DisplayName = FText::FromString(TEXT("Der Krieger"));
    Krieger.Description = FText::FromString(TEXT("Du hast dein Leben dem Schwert gewidmet. +10% Schaden"));
    Krieger.StatBonuses.Add(TEXT("Damage"), 0.1f);
    Backgrounds.Add(Krieger);

    FCharacterBackground Heiler;
    Heiler.BackgroundID = TEXT("Heiler");
    Heiler.DisplayName = FText::FromString(TEXT("Der Heiler"));
    Heiler.Description = FText::FromString(TEXT("Du hast das Heilen von Kranken gelernt. +15% Heilung"));
    Heiler.StatBonuses.Add(TEXT("Healing"), 0.15f);
    Backgrounds.Add(Heiler);

    FCharacterBackground Dieb;
    Dieb.BackgroundID = TEXT("Dieb");
    Dieb.DisplayName = FText::FromString(TEXT("Der Dieb"));
    Dieb.Description = FText::FromString(TEXT("Im Schatten bist du zu Hause. +20% Kritische Treffer"));
    Dieb.StatBonuses.Add(TEXT("CritChance"), 0.2f);
    Backgrounds.Add(Dieb);

    FCharacterBackground Gelehrter;
    Gelehrter.BackgroundID = TEXT("Gelehrter");
    Gelehrter.DisplayName = FText::FromString(TEXT("Der Gelehrte"));
    Gelehrter.Description = FText::FromString(TEXT("Wissen ist Macht. +20% Erfahrung"));
    Gelehrter.StatBonuses.Add(TEXT("Experience"), 0.2f);
    Backgrounds.Add(Gelehrter);

    FCharacterBackground Jäger;
    Jäger.BackgroundID = TEXT("Jaeger");
    Jäger.DisplayName = FText::FromString(TEXT("Der Jaeger"));
    Jäger.Description = FText::FromString(TEXT("Das Wild der Waelder ist deine Beute. +15% Jagd-Ertrag"));
    Jäger.StatBonuses.Add(TEXT("Hunting"), 0.15f);
    Backgrounds.Add(Jäger);

    FCharacterBackground Bauer;
    Bauer.BackgroundID = TEXT("Bauer");
    Bauer.DisplayName = FText::FromString(TEXT("Der Bauer"));
    Bauer.Description = FText::FromString(TEXT("Die Erde ernaehrt dich. +25% Farm-Ertrag"));
    Bauer.StatBonuses.Add(TEXT("Farming"), 0.25f);
    Backgrounds.Add(Bauer);

    FCharacterBackground Handwerker;
    Handwerker.BackgroundID = TEXT("Handwerker");
    Handwerker.DisplayName = FText::FromString(TEXT("Der Handwerker"));
    Handwerker.Description = FText::FromString(TEXT("Mit deinen Haenden erschaffst du Wunder. +20% Crafting-Geschwindigkeit"));
    Handwerker.StatBonuses.Add(TEXT("Crafting"), 0.2f);
    Backgrounds.Add(Handwerker);

    return Backgrounds;
}

bool UCharacterCreationSystem::IsCharacterValid()
{
    return true;
}

void UCharacterCreationSystem::ConfirmCharacter()
{
}

void UCharacterCreationSystem::RandomizeAppearance()
{
}

void UCharacterCreationSystem::ResetCharacter()
{
}

TArray<FText> UCharacterCreationSystem::GetMaleFirstNames()
{
    TArray<FText> Names;
    Names.Add(FText::FromString(TEXT("Erik")));
    Names.Add(FText::FromString(TEXT("Bjorn")));
    Names.Add(FText::FromString(TEXT("Leif")));
    Names.Add(FText::FromString(TEXT("Ragnar")));
    Names.Add(FText::FromString(TEXT("Gunnar")));
    Names.Add(FText::FromString(TEXT("Thorin")));
    Names.Add(FText::FromString(TEXT("Kjell")));
    Names.Add(FText::FromString(TEXT("Odin")));
    Names.Add(FText::FromString(TEXT("Magnus")));
    Names.Add(FText::FromString(TEXT("Sven")));
    return Names;
}

TArray<FText> UCharacterCreationSystem::GetFemaleFirstNames()
{
    TArray<FText> Names;
    Names.Add(FText::FromString(TEXT("Freya")));
    Names.Add(FText::FromString(TEXT("Astrid")));
    Names.Add(FText::FromString(TEXT("Ingrid")));
    Names.Add(FText::FromString(TEXT("Helga")));
    Names.Add(FText::FromString(TEXT("Sigrid")));
    Names.Add(FText::FromString(TEXT("Eira")));
    Names.Add(FText::FromString(TEXT("Runa")));
    Names.Add(FText::FromString(TEXT("Thyra")));
    Names.Add(FText::FromString(TEXT("Olga")));
    Names.Add(FText::FromString(TEXT("Ida")));
    return Names;
}

TArray<FText> UCharacterCreationSystem::GetLastNames()
{
    TArray<FText> Names;
    Names.Add(FText::FromString(TEXT("Eisenfaust")));
    Names.Add(FText::FromString(TEXT("Blutberg")));
    Names.Add(FText::FromString(TEXT("Sturmklinge")));
    Names.Add(FText::FromString(TEXT("Frostherz")));
    Names.Add(FText::FromString(TEXT("Schattenlauf")));
    Names.Add(FText::FromString(TEXT("Bergmann")));
    Names.Add(FText::FromString(TEXT("Waldlaeufer")));
    Names.Add(FText::FromString(TEXT("Wellenreiter")));
    Names.Add(FText::FromString(TEXT("Feuerklinge")));
    Names.Add(FText::FromString(TEXT("Dunkelmond")));
    return Names;
}
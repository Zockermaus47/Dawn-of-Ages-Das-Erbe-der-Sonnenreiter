#include "IntroSequence.h"

UIntroSequence::UIntroSequence()
{
}

TArray<FIntroSection> UIntroSequence::GetFullIntro()
{
    TArray<FIntroSection> Intro;
    Intro.Add(GetPrologue());
    Intro.Add(GetAwakening());
    Intro.Add(GetFirstHunger());
    Intro.Add(GetFlackeringWorld());
    Intro.Add(GetHandMessage());
    return Intro;
}

FIntroSection UIntroSequence::GetPrologue()
{
    FIntroSection Section;
    Section.Phase = EIntroPhase::Prologue;
    
    FIntroScreen Screen1;
    Screen1.Title = FText::FromString(TEXT("DAWN OF AGES"));
    Screen1.Subtitle = FText::FromString(TEXT("Das Erbe der Sonnenreiter"));
    Screen1.Duration = 5.0f;
    Section.Screens.Add(Screen1);
    
    FIntroScreen Screen2;
    Screen2.Title = FText::FromString(TEXT("Eine Geschichte ueber das Unvollkommene,"));
    Screen2.Subtitle = FText::FromString(TEXT("das Lebendige und die Verzweiflung der Goetter"));
    Screen2.Duration = 5.0f;
    Section.Screens.Add(Screen2);
    
    FIntroScreen Screen3;
    Screen3.Title = FText::FromString(TEXT("Kapitel I: Die Anomalie"));
    Screen3.Subtitle = FText::FromString(TEXT(""));
    Screen3.Duration = 3.0f;
    Section.Screens.Add(Screen3);
    
    return Section;
}

FIntroSection UIntroSequence::GetAwakening()
{
    FIntroSection Section;
    Section.Phase = EIntroPhase::Awakening;
    Section.bHasWhiteFlash = true;
    Section.WhiteFlashDuration = 1.0f;
    
    FIntroLine Line1;
    Line1.Speaker = FText::FromString(TEXT(""));
    Line1.Line = FText::FromString(TEXT("... Dunkle. Es ist so dunkel."));
    Line1.Duration = 3.0f;
    Line1.bShowSpeaker = false;
    Section.Dialogs.Add(Line1);
    
    FIntroLine Line2;
    Line2.Speaker = FText::FromString(TEXT(""));
    Line2.Line = FText::FromString(TEXT("Wo... bin ich?"));
    Line2.Duration = 2.5f;
    Line2.bShowSpeaker = false;
    Section.Dialogs.Add(Line2);
    
    FIntroLine Line3;
    Line3.Speaker = FText::FromString(TEXT(""));
    Line3.Line = FText::FromString(TEXT("Es ist kalt. Und ruhig. Zu ruhig."));
    Line3.Duration = 3.0f;
    Line3.bShowSpeaker = false;
    Section.Dialogs.Add(Line3);
    
    FIntroLine Line4;
    Line4.Speaker = FText::FromString(TEXT(""));
    Line4.Line = FText::FromString(TEXT("... Licht? Da ist... Licht."));
    Line4.Duration = 2.5f;
    Line4.bShowSpeaker = false;
    Section.Dialogs.Add(Line4);
    
    return Section;
}

FIntroSection UIntroSequence::GetFirstHunger()
{
    FIntroSection Section;
    Section.Phase = EIntroPhase::FirstHunger;
    
    FIntroLine Line1;
    Line1.Speaker = FText::FromString(TEXT(""));
    Line1.Line = FText::FromString(TEXT("Du oeffnest die Augen. Ein Wald. Aber... nicht richtig."));
    Line1.Duration = 4.0f;
    Line1.bShowSpeaker = false;
    Section.Dialogs.Add(Line1);
    
    FIntroLine Line2;
    Line2.Speaker = FText::FromString(TEXT(""));
    Line2.Line = FText::FromString(TEXT("Die Baeume enden im Nichts. Der Himmel... flackert."));
    Line2.Duration = 3.5f;
    Line2.bShowSpeaker = false;
    Section.Dialogs.Add(Line2);
    
    FIntroLine Line3;
    Line3.Speaker = FText::FromString(TEXT(""));
    Line3.Line = FText::FromString(TEXT("Ein Geraeusch. Von unten. Dein Magen."));
    Line3.Duration = 3.0f;
    Line3.bShowSpeaker = false;
    Section.Dialogs.Add(Line3);
    
    FIntroLine Line4;
    Line4.Speaker = FText::FromString(TEXT(""));
    Line4.Line = FText::FromString(TEXT("Hunger. Ich... bins hungrig? Das ist neu. Das ist..."));
    Line4.Duration = 4.0f;
    Line4.bShowSpeaker = false;
    Section.Dialogs.Add(Line4);
    
    FIntroScreen Screen;
    Screen.Title = FText::FromString(TEXT("Hunger"));
    Screen.Subtitle = FText::FromString(TEXT("Das erste Gefuehl, das Aeon nie kannte."));
    Screen.Duration = 4.0f;
    Screen.TextColor = FLinearColor(1.0f, 0.5f, 0.3f, 1.0f);
    Section.Screens.Add(Screen);
    
    return Section;
}

FIntroSection UIntroSequence::GetFlackeringWorld()
{
    FIntroSection Section;
    Section.Phase = EIntroPhase::FlackeringWorld;
    
    FIntroLine Line1;
    Line1.Speaker = FText::FromString(TEXT(""));
    Line1.Line = FText::FromString(TEXT("Du stehst auf. Die Beine zittern."));
    Line1.Duration = 3.0f;
    Line1.bShowSpeaker = false;
    Section.Dialogs.Add(Line1);
    
    FIntroLine Line2;
    Line2.Speaker = FText::FromString(TEXT(""));
    Line2.Line = FText::FromString(TEXT("Die Welt um dich herum... flackert. Wie ein defekter Bildschirm."));
    Line2.Duration = 4.0f;
    Line2.bShowSpeaker = false;
    Section.Dialogs.Add(Line2);
    
    FIntroLine Line3;
    Line3.Speaker = FText::FromString(TEXT(""));
    Line3.Line = FText::FromString(TEXT("Ein Tier laeuft vorbei. Plots bleibt es stehen. Dreht sich um 180 Grad."));
    Line3.Duration = 5.0f;
    Line3.bShowSpeaker = false;
    Section.Dialogs.Add(Line3);
    
    FIntroLine Line4;
    Line4.Speaker = FText::FromString(TEXT(""));
    Line4.Line = FText::FromString(TEXT("Seine Augen sind... leer. Wie Marionetten mit gerissenen Faeden."));
    Line4.Duration = 4.5f;
    Line4.bShowSpeaker = false;
    Section.Dialogs.Add(Line4);
    
    FIntroScreen Screen;
    Screen.Title = FText::FromString(TEXT("Die Welt ist kaputt"));
    Screen.Subtitle = FText::FromString(TEXT("Und das ist keine technische Unvollkommenheit. Das ist die Wahrheit."));
    Screen.Duration = 5.0f;
    Screen.TextColor = FLinearColor(0.8f, 0.2f, 0.2f, 1.0f);
    Section.Screens.Add(Screen);
    
    return Section;
}

FIntroSection UIntroSequence::GetHandMessage()
{
    FIntroSection Section;
    Section.Phase = EIntroPhase::HandMessage;
    Section.bHasWhiteFlash = true;
    Section.WhiteFlashDuration = 0.3f;
    
    FIntroLine Line1;
    Line1.Speaker = FText::FromString(TEXT(""));
    Line1.Line = FText::FromString(TEXT("Etwas Warmes. An deiner Hand."));
    Line1.Duration = 3.0f;
    Line1.bShowSpeaker = false;
    Section.Dialogs.Add(Line1);
    
    FIntroScreen Screen1;
    Screen1.Title = FText::FromString(TEXT(""));
    Screen1.Subtitle = FText::FromString(TEXT("In leuchtenden Runen erscheint eine Nachricht:"));
    Screen1.Duration = 4.0f;
    Section.Screens.Add(Screen1);
    
    FIntroScreen Screen2;
    Screen2.Title = FText::FromString(TEXT(""));
    Screen2.Subtitle = FText::FromString(TEXT("\"Verzeihe mir.\nIch weiss nicht mehr, wie man lebt.\nKannst du es mir zeigen?\""));
    Screen2.Duration = 6.0f;
    Screen2.TextColor = FLinearColor(0.3f, 0.8f, 1.0f, 1.0f);
    Section.Screens.Add(Screen2);
    
    FIntroLine Line2;
    Line2.Speaker = FText::FromString(TEXT(""));
    Line2.Line = FText::FromString(TEXT("Wer... spricht zu mir?"));
    Line2.Duration = 2.5f;
    Line2.bShowSpeaker = false;
    Section.Dialogs.Add(Line2);
    
    FIntroLine Line3;
    Line3.Speaker = FText::FromString(TEXT(""));
    Line3.Line = FText::FromString(TEXT("Und warum... glaube ich daran?"));
    Line3.Duration = 2.5f;
    Line3.bShowSpeaker = false;
    Section.Dialogs.Add(Line3);
    
    FIntroScreen EndScreen;
    EndScreen.Title = FText::FromString(TEXT("Akt I: Die Anomalie"));
    EndScreen.Subtitle = FText::FromString(TEXT("Finde heraus, was diese Welt ist... und wer du bist."));
    EndScreen.Duration = 4.0f;
    EndScreen.TextColor = FLinearColor(1.0f, 0.9f, 0.7f, 1.0f);
    Section.Screens.Add(EndScreen);
    
    return Section;
}

void UIntroSequence::StartIntro()
{
}

void UIntroSequence::SkipIntro()
{
}

bool UIntroSequence::IsIntroComplete()
{
    return false;
}

void UIntroSequence::SetIntroComplete(bool bComplete)
{
}
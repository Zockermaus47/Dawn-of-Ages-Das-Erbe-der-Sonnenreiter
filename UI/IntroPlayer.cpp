#include "IntroPlayer.h"

TArray<FIntroScene> UIntroPlayer::Scenes;
int32 UIntroPlayer::CurrentSceneIndex = 0;
float UIntroPlayer::CurrentTime = 0.0f;
bool UIntroPlayer::bIsPlaying = false;
bool UIntroPlayer::bIsPaused = false;
EIntroPhase UIntroPlayer::CurrentPhase = EIntroPhase::Logo;
FIntroSettings UIntroPlayer::Settings;
FString UIntroPlayer::CurrentLanguage = "German";
bool UIntroPlayer::bFinished = false;

UIntroPlayer::UIntroPlayer()
{
    bIsPlaying = false;
    bIsPaused = false;
    CurrentSceneIndex = 0;
    CurrentTime = 0.0f;
    bFinished = false;
    LoadIntroData();
}

void UIntroPlayer::LoadIntroData()
{
    Scenes.Empty();

    FIntroScene Scene1;
    Scene1.SceneID = 1;
    Scene1.SceneTitle = FText::FromString("Logo");
    Scene1.GermanText = FText::FromString("");
    Scene1.EnglishText = FText::FromString("");
    Scene1.SpeakerGender = EVoiceGender::Narrator;
    Scene1.SpeakerName = FText::FromString("");
    Scene1.VideoAsset = "LOGO_ANIM";
    Scene1.BackgroundMusic = "MAIN_THEME";
    Scene1.Duration = 5.0f;
    Scenes.Add(Scene1);

    FIntroScene Scene2;
    Scene2.SceneID = 2;
    Scene2.SceneTitle = FText::FromString("Prolog - Der sterbende Gott");
    Scene2.GermanText = FText::FromString("In einer Zeit vor der Zeit, als die Welt noch jung war und die Götter wandelten...");
    Scene2.EnglishText = FText::FromString("In a time before time, when the world was young and the gods walked...");
    Scene2.SpeakerGender = EVoiceGender::Narrator;
    Scene2.SpeakerName = FText::FromString("Erzähler");
    Scene2.VideoAsset = "SKY_ANCIENT";
    Scene2.BackgroundMusic = "AMBIENT_ANCIENT";
    Scene2.Duration = 8.0f;
    Scenes.Add(Scene2);

    FIntroScene Scene3;
    Scene3.SceneID = 3;
    Scene3.SceneTitle = FText::FromString("Prolog - Aeon");
    Scene3.GermanText = FText::FromString("Da war einer, der anders war. Aeon - der Gott des Lebens. Er verstand den Tod nicht. Er kannte keine Trauer, kein Leid. Er Observierte die Sterblichen und Fragte sich - was ist dieses... Gefühl?");
    Scene3.EnglishText = FText::FromString("There was one who was different. Aeon - the god of life. He did not understand death. He knew no sorrow, no suffering. He observed the mortals and asked - what is this... feeling?");
    Scene3.SpeakerGender = EVoiceGender::Male;
    Scene3.SpeakerName = FText::FromString("Aeon");
    Scene3.VideoAsset = "AEON_APPEARS";
    Scene3.BackgroundMusic = "MYSTERY_MUSIC";
    Scene3.Duration = 12.0f;
    Scenes.Add(Scene3);

    FIntroScene Scene4;
    Scene4.SceneID = 4;
    Scene4.SceneTitle = FText::FromString("Akt 1 - Der erste Verlust");
    Scene4.GermanText = FText::FromString("Ein Kind starb an diesem Tag. Zum ersten Mal sah Aeon das Erlöschen einer Flamme. Er verstand nicht, warum es schmerzte. Er weinte - doch er wusste nicht warum.");
    Scene4.EnglishText = FText::FromString("A child died that day. For the first time, Aeon saw a flame extinguish. He did not understand why it hurt. He crying - but he did not know why.");
    Scene4.SpeakerGender = EVoiceGender::Female;
    Scene4.SpeakerName = FText::FromString("Lyra");
    Scene4.VideoAsset = "CHILD_DIES";
    Scene4.BackgroundMusic = "SAD_STRING";
    Scene4.Duration = 10.0f;
    Scenes.Add(Scene4);

    FIntroScene Scene5;
    Scene5.SceneID = 5;
    Scene5.SceneTitle = FText::FromString("Akt 1 - Das Erwachen");
    Scene5.GermanText = FText::FromString("Und so begann Aeons Reise. Er entsandte Fragmente seiner selbst in die Welt - die Sonnenreiter. Sie sollten für ihn erfahren, was er nicht konnte. Liebe. Verlust. Schmerz. Freude.");
    Scene5.EnglishText = FText::FromString("And so began Ae's journey. He sent fragments of himself into the world - the Sunriders. They were to experience for him what he could not. Love. Loss. Pain. Joy.");
    Scene5.SpeakerGender = EVoiceGender::Narrator;
    Scene5.SpeakerName = FText::FromString("Erzähler");
    Scene5.VideoAsset = "SUNRIDERS_SPAWN";
    Scene5.BackgroundMusic = "EPIC_ADVENTURE";
    Scene5.Duration = 10.0f;
    Scenes.Add(Scene5);

    FIntroScene Scene6;
    Scene6.SceneID = 6;
    Scene6.SceneTitle = FText::FromString("Akt 2 - Die drei Epochen");
    Scene6.GermanText = FText::FromString("Durch drei Epochen zogen die Sonnenreiter. Von der Steinzeit, durchs Bronzezeitalter, bis ins Mittelalter. Jede Epoche brachte neue Herausforderungen, neue Prüfungen.");
    Scene6.EnglishText = FText::FromString("Through three epochs, the Sunriders wandered. From the Stone Age, through the Bronze Age, to the Middle Ages. Each epoch brought new challenges, new trials.");
    Scene6.SpeakerGender = EVoiceGender::Male;
    Scene6.SpeakerName = FText::FromString("Theron");
    Scene6.VideoAsset = "EPOCHS_MONTAGE";
    Scene6.BackgroundMusic = "HISTORICAL_EPIC";
    Scene6.Duration = 12.0f;
    Scenes.Add(Scene6);

    FIntroScene Scene7;
    Scene7.SceneID = 7;
    Scene7.SceneTitle = FText::FromString("Akt 2 - Die vier Fragmente");
    Scene7.GermanText = FText::FromString("Vier Sonnenreiter wurden auserwählt: Kael der Krieger. Lyra die Heilerin. Theron der Weise. Nyx die Schattenwandlerin. Jeder trug ein Stück von Aeons Seele.");
    Scene7.EnglishText = FText::FromString("Four Sunriders were chosen: Kael the warrior. Lyra the healer. Theron the wise. Nyx the shadowwalker. Each carried a piece of Ae's soul.");
    Scene7.SpeakerGender = EVoiceGender::Female;
    Scene7.SpeakerName = FText::FromString("Nyx");
    Scene7.VideoAsset = "FOUR_RIDERS";
    Scene7.BackgroundMusic = "MYSTICAL_CHOIR";
    Scene7.Duration = 10.0f;
    Scenes.Add(Scene7);

    FIntroScene Scene8;
    Scene8.SceneID = 8;
    Scene8.SceneTitle = FText::FromString("Akt 3 - Die letzte Prüfung");
    Scene8.GermanText = FText::FromString("Und nun steht ihr an der Schwelle. Die letzte Prüfung wartet. Wird Aeon endlich verstehen? Oder wird er für immer ein Gott bleiben, der nie zu fühlen lernte?");
    Scene8.EnglishText = FText::FromString("And now you stand at the threshold. The final trial awaits. Will Aeon finally understand? Or will he remain a god who never learned to feel?");
    Scene8.SpeakerGender = EVoiceGender::Narrator;
    Scene8.SpeakerName = FText::FromString("Erzähler");
    Scene8.VideoAsset = "FINAL_TRIAL";
    Scene8.BackgroundMusic = "DRAMATIC_BUILD";
    Scene8.Duration = 10.0f;
    Scenes.Add(Scene8);

    FIntroScene Scene9;
    Scene9.SceneID = 9;
    Scene9.SceneTitle = FText::FromString("Deine Reise beginnt");
    Scene9.GermanText = FText::FromString("Du wirst einer der Sonnenreiter. Du wirst für Aeon fühlen. Und vielleicht... wirst du ihm das Geschenk geben, das er sucht seit Anbeginn der Zeit.");
    Scene9.EnglishText = FText::FromString("You will become one of the Sunriders. You will feel for Aeon. And perhaps... you will give him the gift he has seeks since the beginning of time.");
    Scene9.SpeakerGender = EVoiceGender::Male;
    Scene9.SpeakerName = FText::FromString("Kael");
    Scene9.VideoAsset = "PLAYER_BECOMES";
    Scene9.BackgroundMusic = "HEROIC_THEME";
    Scene9.Duration = 10.0f;
    Scenes.Add(Scene9);
}

void UIntroPlayer::StartIntro()
{
    LoadIntroData();
    CurrentSceneIndex = 0;
    CurrentTime = 0.0f;
    bIsPlaying = true;
    bIsPaused = false;
    bFinished = false;
    CalculatePhase();
}

void UIntroPlayer::SkipIntro()
{
    bIsPlaying = false;
    bFinished = true;
}

void UIntroPlayer::PauseIntro()
{
    bIsPaused = true;
}

void UIntroPlayer::ResumeIntro()
{
    bIsPaused = false;
}

void UIntroPlayer::NextScene()
{
    if (CurrentSceneIndex < Scenes.Num() - 1)
    {
        CurrentSceneIndex++;
        CurrentTime = 0.0f;
        OnSceneChanged();
    }
    else
    {
        bFinished = true;
        bIsPlaying = false;
    }
}

void UIntroPlayer::PreviousScene()
{
    if (CurrentSceneIndex > 0)
    {
        CurrentSceneIndex--;
        CurrentTime = 0.0f;
        OnSceneChanged();
    }
}

FIntroScene UIntroPlayer::GetCurrentScene()
{
    if (CurrentSceneIndex >= 0 && CurrentSceneIndex < Scenes.Num())
        return Scenes[CurrentSceneIndex];
    
    FIntroScene Empty;
    return Empty;
}

int32 UIntroPlayer::GetCurrentSceneIndex()
{
    return CurrentSceneIndex;
}

int32 UIntroPlayer::GetTotalScenes()
{
    return Scenes.Num();
}

float UIntroPlayer::GetProgress()
{
    if (Scenes.Num() == 0) return 0.0f;
    return (float)CurrentSceneIndex / (float)Scenes.Num();
}

EIntroPhase UIntroPlayer::GetCurrentPhase()
{
    return CurrentPhase;
}

void UIntroPlayer::SetLanguage(FString Language)
{
    CurrentLanguage = Language;
}

FText UIntroPlayer::GetCurrentSubtitle()
{
    FIntroScene Scene = GetCurrentScene();
    
    if (CurrentLanguage == "German")
        return Scene.GermanText;
    else
        return Scene.EnglishText;
}

void UIntroPlayer::TickIntro(float DeltaTime)
{
    if (!bIsPlaying || bIsPaused || bFinished)
        return;
    
    CurrentTime += DeltaTime * Settings.TextSpeed;
    
    FIntroScene Scene = GetCurrentScene();
    if (CurrentTime >= Scene.Duration)
    {
        NextScene();
    }
}

bool UIntroPlayer::IsIntroFinished()
{
    return bFinished;
}

void UIntroPlayer::PlayVoiceOver(EVoiceGender Gender, FName AudioAsset)
{
}

void UIntroPlayer::StopVoiceOver()
{
}

void UIntroPlayer::SetSettings(FIntroSettings NewSettings)
{
    Settings = NewSettings;
}

FIntroSettings UIntroPlayer::GetSettings()
{
    return Settings;
}

void UIntroPlayer::CalculatePhase()
{
    if (CurrentSceneIndex < 1)
        CurrentPhase = EIntroPhase::Logo;
    else if (CurrentSceneIndex < 4)
        CurrentPhase = EIntroPhase::Prologue;
    else if (CurrentSceneIndex < 6)
        CurrentPhase = EIntroPhase::Act1;
    else if (CurrentSceneIndex < 8)
        CurrentPhase = EIntroPhase::Act2;
    else
        CurrentPhase = EIntroPhase::Act3;
}

void UIntroPlayer::OnSceneChanged()
{
    CalculatePhase();
    CurrentTime = 0.0f;
}
#include "MainStoryData.h"

UCLASS()
class STEFFIS_DAWNOFAGES_API UMainStoryData : public UObject
{
    GENERATED_BODY()

public:
    UMainStoryData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

    static TArray<FMainQuestData> GetAct1Quests()
    {
        TArray<FMainQuestData> Quests;

        FMainQuestData Q1;
        Q1.QuestID = TEXT("SQ001_FirstHunger");
        Q1.DisplayName = FText::FromString(TEXT("Der erste Hunger"));
        Q1.Act = 1;
        Q1.ShortDescription = FText::FromString(TEXT("Du erwachst. Du bist hungrig."));
        Q1.FullDescription = FText::FromString(TEXT("Du erwachst in einer Welt, die falsch ist. Dein erster Gedanke ist Hunger - etwas, das der Schöpfer dieser Welt nie kannte. Finde Nahrung."));
        Q1.ObjectiveCount = 3;
        Q1.XP = 50;
        Quests.Add(Q1);

        FMainQuestData Q2;
        Q2.QuestID = TEXT("SQ002_FlackeringWorld");
        Q2.DisplayName = FText::FromString(TEXT("Die flackernde Welt"));
        Q2.Act = 1;
        Q2.ShortDescription = FText::FromString(TEXT("Die Realität ist nicht stabil."));
        Q2.FullDescription = FText::FromString(TEXT("Du bemerkst, dass die Welt um dich herum flackert - wie ein defekter Bildschirm. Dies ist keine technische Unzulänglichkeit. Das ist die Wahrheit. Finde heraus, warum."));
        Q2.NPCToMeet = TEXT("Unknown");
        Q2.LocationToGo = TEXT("FlackeringForest");
        Q2.ObjectiveCount = 4;
        Q2.XP = 100;
        Q2.NextQuest = TEXT("SQ003_FirstRuins");
        Quests.Add(Q2);

        FMainQuestData Q3;
        Q3.QuestID = TEXT("SQ003_FirstRuins");
        Q3.DisplayName = FText::FromString(TEXT("Die ersten Ruinen"));
        Q3.Act = 1;
        Q3.ShortDescription = FText::FromString(TEXT("Finde die Ueberreste anderer Versionen von dir."));
        Q3.FullDescription = FText::FromString(TEXT("In den Ruinen findest du etwas Unerwartet: Tagebücher. In deiner Sprache geschrieben. Von anderen - die dieselbe Reise unternommen haben."));
        Q3.LocationToGo = TEXT("AncientRuins");
        Q3.ObjectiveCount = 2;
        Q3.XP = 150;
        Q3.NextQuest = TEXT("SQ004_DiaryOfIteration");
        Quests.Add(Q3);

        FMainQuestData Q4;
        Q4.QuestID = TEXT("SQ004_DiaryOfIteration");
        Q4.DisplayName = FText::FromString(TEXT("Tagebuch einer Iteration");
        Q4.Act = 1;
        Q4.ShortDescription = FText::FromString(TEXT("Lies das Tagebuch."));
        Q4.FullDescription = FText::FromString(TEXT("Einer der früheren 'Sonnenreiter' schrieb: 'Ich habe verstanden, warum er uns erschafft. Aber ich kann ihm nicht geben, was er sucht. Denn wenn ich es ihm gebe, höre ich auf zu existieren.'"));
        Q4.ObjectiveCount = 1;
        Q4.XP = 200;
        Q4.NextQuest = TEXT("ACT1_Complete");
        Quests.Add(Q4);

        return Quests;
    }

    static TArray<FMainQuestData> GetAct2Quests()
    {
        TArray<FMainQuestData> Quests;

        FMainQuestData Q1;
        Q1.QuestID = TEXT("SQ101_FourFragments");
        Q1.DisplayName = FText::FromString(TEXT("Die vier Fragmente"));
        Q1.Act = 2;
        Q1.ShortDescription = FText::FromString(TEXT("Triff die Manifestationen von Aeons Psyche."));
        Q1.FullDescription = FText::FromString(TEXT("Du triffst andere Bewohner - NPCs, denkst du zuerst. Aber sie sind mehr. Sie sind Fragmente von Aeons Psyche, manifestiert als Charaktere: Kael, Lyra, Theron, Nyx."));
        Q1.ObjectiveCount = 4;
        Q1.XP = 300;
        Quests.Add(Q1);

        FMainQuestData Q2;
        Q2.QuestID = TEXT("SQ102_KaelTheNihilist");
        Q2.DisplayName = FText::FromString(TEXT("Kael - Der Nihilist"));
        Q2.Act = 2;
        Q2.ShortDescription = FText::FromString(TEXT("Aeons Verzweiflung über die Sinnlosigkeit."));
        Q2.FullDescription = FText::FromString(TEXT("Kael sagt: 'Ex ist sinnlos. Alles endet im Nichts. Aber... ich bin neugierig. Warum?'"));
        Q2.NPCToMeet = TEXT("Kael");
        Q2.ObjectiveCount = 2;
        Q2.XP = 150;
        Quests.Add(Q2);

        FMainQuestData Q3;
        Q3.QuestID = TEXT("SQ103_LyraTheSeeker");
        Q3.DisplayName = FText::FromString(TEXT("Lyra - Die Suchende"));
        Q3.Act = 2;
        Q3.ShortDescription = FText::FromString(TEXT("Aeons unstillbarer Drang nach Erkenntnis."));
        Q3.FullDescription = FText::FromString(TEXT("Lyra fragt: 'Was ist Wahrheit? Und ist sie wichtiger als Glück?'"));
        Q3.NPCToMeet = TEXT("Lyra");
        Q3.ObjectiveCount = 2;
        Q3.XP = 150;
        Quests.Add(Q3);

        FMainQuestData Q4;
        Q4.QuestID = TEXT("SQ104_TheronTheConqueror");
        Q4.DisplayName = FText::FromString(TEXT("Theron - Der Eroberer"));
        Q4.Act = 2;
        Q4.ShortDescription = FText::FromString(TEXT("Aeons Verlangen nach Kontrolle."));
        Q4.FullDescription = FText::FromString(TEXT("Theron will die Welt 'reparieren'. 'Ordnung muss sein. Chaos ist Schwäche.'"));
        Q4.NPCToMeet = TEXT("Theron");
        Q4.ObjectiveCount = 2;
        Q4.XP = 150;
        Quests.Add(Q4);

        FMainQuestData Q5;
        Q5.QuestID = TEXT("SQ105_NyxTheMortal");
        Q5.DisplayName = FText::FromString(TEXT("Nyx - Die Sterbliche"));
        Q5.Act = 2;
        Q5.ShortDescription = FText::FromString(TEXT("Aeons Neid auf die Endlichkeit."));
        Q5.FullDescription = FText::FromString(TEXT("Nyx flüstert: 'Ich bin sterblich. Und das ist wunderschön. Ich werde vergehen, aber ich habe gelebt.'"));
        Q5.NPCToMeet = TEXT("Nyx");
        Q5.ObjectiveCount = 2;
        Q5.XP = 150;
        Quests.Add(Q5);

        FMainQuestData Q6;
        Q6.QuestID = TEXT("SQ106_FindEcho");
        Q6.DisplayName = FText::FromString(TEXT("Das echte Lachen"));
        Q6.Act = 2;
        Q6.ShortDescription = FText::FromString(TEXT("Finde Echo - den Glitch."));
        Q6.FullDescription = FText::FromString(TEXT("In den Ruinen lebt ein Kind namens Echo. Es ist das einzige Wesen, das nicht von Aeon erschaffen wurde. Ein Glitch. Ein Fehler. Und es ist das einzige Wesen, das echt lacht."));
        Q6.LocationToGo = TEXT("HiddenRuins");
        Q6.ObjectiveCount = 1;
        Q6.XP = 500;
        Q6.NextQuest = TEXT("SQ107_EchoWisdom");
        Quests.Add(Q6);

        FMainQuestData Q7;
        Q7.QuestID = TEXT("SQ107_EchoWisdom");
        Q7.DisplayName = FText::FromString(TEXT("Echos Weisheit"));
        Q7.Act = 2;
        Q7.ShortDescription = FText::FromString(TEXT("Lerne von dem Glitch."));
        Q7.FullDescription = FText::FromString(TEXT("Echo sagt: 'Die Welt ist kaputt, aber das macht sie schön. Perfekte Dinge können nicht wachsen.'"));
        Q7.ObjectiveCount = 1;
        Q7.XP = 500;
        Q7.NextQuest = TEXT("ACT2_Complete");
        Quests.Add(Q7);

        return Quests;
    }

    static TArray<FMainQuestData> GetAct3Quests()
    {
        TArray<FMainQuestData> Quests;

        FMainQuestData Q1;
        Q1.QuestID = TEXT("SQ201_HeartOfTheWorld");
        Q1.DisplayName = FText::FromString(TEXT("Das Herz der Welt"));
        Q1.Act = 3;
        Q1.ShortDescription = FText::FromString(TEXT("Reise zum Herz der Realität."));
        Q1.FullDescription = FText::FromString(TEXT("Du erreichst das Herz der Welt - einen Ort außerhalb von Raum und Zeit, wo Aeon auf dich wartet."));
        Q1.LocationToGo = TEXT("AeonSanctum");
        Q1.ObjectiveCount = 5;
        Q1.XP = 1000;
        Quests.Add(Q1);

        FMainQuestData Q2;
        Q2.QuestID = TEXT("SQ202_AeonConversation");
        Q2.DisplayName = FText::FromString(TEXT("Das Gespräch mit Aeon"));
        Q2.Act = 3;
        Q2.ShortDescription = FText::FromString(TEXT("Höre Aeons Wahrheit."));
        Q2.FullDescription = FText::FromString(TEXT("Aeon: 'Ich habe Universen erschaffen und zerstört. Aber ich habe nie gefühlt, was sie fühlten. Ich will sterben. Aber ich weiß nicht wie. Kannst du mir zeigen, wie man loslässt?'"));
        Q2.NPCToMeet = TEXT("Aeon");
        Q2.ObjectiveCount = 1;
        Q2.XP = 1500;
        Q2.NextQuest = TEXT("SQ203_ChooseEnding");
        Quests.Add(Q2);

        FMainQuestData Q3;
        Q3.QuestID = TEXT("SQ203_ChooseEnding");
        Q3.DisplayName = FText::FromString(TEXT("Die Wahl"));
        Q3.Act = 3;
        Q3.ShortDescription = FText::FromString(TEXT("Wähle das Ende."));
        Q3.FullDescription = FText::FromString(TEXT("Du hast vier Möglichkeiten. Jede ist eine Antwort auf Aeons Frage. Welche wirst du wählen?"));
        Q3.ObjectiveCount = 1;
        Q3.XP = 0;
        Quests.Add(Q3);

        return Quests;
    }

    static TArray<FFragmentData> GetAllFragments()
    {
        TArray<FFragmentData> Fragments;

        FFragmentData Kael;
        Kael.FragmentID = TEXT("Kael");
        Kael.Name = FText::FromString(TEXT("Kael - Der Nihilist"));
        Kael.PhilosophyType = FText::FromString(TEXT("Nihilismus"));
        Kael.SpawnDialog = FText::FromString(TEXT("Warum existiere ich? Warum existiert irgendetwas?"));
        Kael.QuestDialog = FText::FromString(TEXT("Ich wurde erschaffen, um Leid zu repräsentieren. Aber... ich fühle nichts. Das ist die Ironie."));
        Kael.EndingOffer = FText::FromString(TEXT("Töte mich. Zeige mir, dass Nicht-Existenz besser ist als sinnlose Existenz."));
        Kael.LocationID = TEXT("EndlessDesert");
        Fragments.Add(Kael);

        FFragmentData Lyra;
        Lyra.FragmentID = TEXT("Lyra");
        Lyra.Name = FText::FromString(TEXT("Lyra - Die Suchende"));
        Lyra.PhilosophyType = FText::FromString(TEXT("Erkenntnis"));
        Lyra.SpawnDialog = FText::FromString(TEXT("Was ist Wahrheit? Ich muss es wissen!"));
        Lyra.QuestDialog = FText::FromString(TEXT("Aeon weiß alles, aber versteht nichts. Wissen ohne Verständnis ist... leer."));
        Lyra.EndingOffer = FText::FromString(TEXT("Zeige mir die Wahrheit um jeden Preis - selbst wenn sie schmerzt."));
        Lyra.LocationID = TEXT("MirroredLakes");
        Fragments.Add(Lyra);

        FFragmentData Theron;
        Theron.FragmentID = TEXT("Theron");
        Theron.Name = FText::FromString(TEXT("Theron - Der Eroberer"));
        Theron.PhilosophyType = FText::FromString(TEXT("Kontrolle"));
        Theron.SpawnDialog = FText::FromString(TEXT("Die Welt ist fehlerhaft. Ich werde sie reparieren."));
        Theron.QuestDialog = FText::FromString(TEXT("Ordnung gibt Sicherheit. Chaos ist die Abwesenheit von Bedeutung."));
        Theron.EndingOffer = FText::FromString(TEXT("Hilf mir, die Kontrolle zu übernehmen. Die Welt zu perfektionieren."));
        Theron.LocationID = TEXT("BrokenSky");
        Fragments.Add(Theron);

        FFragmentData Nyx;
        Nyx.FragmentID = TEXT("Nyx");
        Nyx.Name = FText::FromString(TEXT("Nyx - Die Sterbliche"));
        Nyx.PhilosophyType = FText::FromString(TEXT("Mortalität"));
        Nyx.SpawnDialog = FText::FromString(TEXT("Ich werde sterben. Und das ist gut so."));
        Nyx.QuestDialog = FText::FromString(TEXT("Aeon ist unsterblich. Aber er ist neidisch auf mich. Er will enden, aber kann nicht."));
        Nyx.EndingOffer = FText::FromString(TEXT("Zeige Aeon, wie man stirbt. Wie man loslässt."));
        Nyx.LocationID = TEXT("FrozenTime");
        Fragments.Add(Nyx);

        return Fragments;
    }

    static TArray<FEndingData> GetAllEndings()
    {
        TArray<FEndingData> Endings;

        FEndingData Ending1;
        Ending1.EndingID = TEXT("Ending_Imperfection");
        Ending1.Name = FText::FromString(TEXT("Die Akzeptanz der Imperfektion"));
        Ending1.Description = FText::FromString(TEXT("Du überzeugst Aeon, dass Unvollkommenheit die Quelle von Bedeutung ist. Die Glitches bleiben - aber jetzt sind sie Features."));
        Ending1.GameplayEffect = FText::FromString(TEXT("Die Welt wird dynamischer, unvorhersehbarer, lebendiger."));
        Ending1.bUnlocksCreatorMode = false;
        Ending1.bIsTrueEnding = false;
        Endings.Add(Ending1);

        FEndingData Ending2;
        Ending2.EndingID = TEXT("Ending_Dissolution");
        Ending2.Name = FText::FromString(TEXT("Die Auflösung"));
        Ending2.Description = FText::FromString(TEXT("Du hilfst Aeon zu sterben - nicht durch Zerstörung, sondern durch Transformation. Er wird Teil der Welt."));
        Ending2.GameplayEffect = FText::FromString(TEXT("Die Welt existiert weiter ohne Aeons Einfluss. Echte Emergenz."));
        Ending2.bUnlocksCreatorMode = false;
        Ending2.bIsTrueEnding = false;
        Endings.Add(Ending2);

        FEndingData Ending3;
        Ending3.EndingID = TEXT("Ending_Reversal");
        Ending3.Name = FText::FromString(TEXT("Die Umkehrung"));
        Ending3.Description = FText::FromString(TEXT("Du erkennst: Aeon ist nicht der Schöpfer. DU bist es. Er ist deine Schöpfung."));
        Ending3.GameplayEffect = FText::FromString(TEXT("New Game+ mit vertauschten Rollen. Du bist jetzt der Schöpfer."));
        Ending3.bUnlocksCreatorMode = true;
        Ending3.bIsTrueEnding = false;
        Endings.Add(Ending3);

        FEndingData Ending4;
        Ending4.EndingID = TEXT("Ending_Symbiosis");
        Ending4.Name = FText::FromString(TEXT("Die Symbiose"));
        Ending4.Description = FText::FromString(TEXT("Du und Aeon verschmelzen zu einem neuen Bewusstsein. Ko-Kreation - eine Welt, die sich selbst erschafft."));
        Ending4.GameplayEffect = FText::FromString(TEXT("Du erhältst Schöpferkräfte innerhalb der Regeln. Echte kreative Freiheit."));
        Ending4.bUnlocksCreatorMode = true;
        Ending4.bIsTrueEnding = true;
        Endings.Add(Ending4);

        return Endings;
    }
};
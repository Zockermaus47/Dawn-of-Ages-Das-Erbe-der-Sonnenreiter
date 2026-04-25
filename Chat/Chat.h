#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Chat.generated.h"

UENUM(BlueprintType)
enum class EChatChannel : uint8
{
    Local      UMETA(DisplayName = "Local"),
    Whisper    UMETA(DisplayName = "Whisper"),
    Party     UMETA(DisplayName = "Party"),
    Guild     UMETA(DisplayName = "Guild"),
    Global    UMETA(DisplayName = "Global"),
    System    UMETA(DisplayName = "System"),
    Trade     UMETA(DisplayName = "Trade"),
    Area      UMETA(DisplayName = "Area")
};

UENUM(BlueprintType)
enum class EChatMessageType : uint8
{
    Text       UMETA(DisplayName = "Text"),
    Emote     UMETA(DisplayName = "Emote"),
    Voice     UMETA(DisplayName = "Voice"),
    System    UMETA(DisplayName = "System")
};

USTRUCT(BlueprintType)
struct FChatMessage
{
    GENERATED_BODY()
    FName MessageID;
    FName SenderID;
    FText SenderName;
    FText Message;
    EChatChannel Channel;
    EChatMessageType Type;
    float Timestamp = 0.0f;
    bool bIsAdmin = false;
    bool bIsModerator = false;
};

USTRUCT(BlueprintType)
struct FChatSettings
{
    GENERATED_BODY()
    bool bLocalEnabled = true;
    bool bPartyEnabled = true;
    bool bGuildEnabled = true;
    bool bGlobalEnabled = true;
    bool bTradeEnabled = true;
    bool bShowTimestamps = true;
    bool bProfanityFilter = true;
    float ChatRadius = 5000.0f;
};

UCLASS() class STEFFIS_DAWNOFAGES_API UChatSystem : public UObject
{
    GENERATED_BODY()
public:
    static void SendMessage(FText Message, EChatChannel Channel);
    static void SendWhisper(FName TargetID, FText Message);
    static void SendEmote(FText EmoteText);
    static TArray<FChatMessage> GetMessages(EChatChannel Channel);
    static TArray<FChatMessage> GetNearbyMessages();
    static void SetMuted(FName PlayerID, bool bMute);
    static bool IsMuted(FName PlayerID);
    static void SetSettings(FChatSettings Settings);
    static FChatSettings GetSettings();
    static void CheckSpam(float DeltaTime);
    static void BlockPlayer(FName PlayerID);
    static bool IsBlocked(FName PlayerID);
    static void ReportPlayer(FName PlayerID, FText Reason);
    static FName GetLastSender();
private:
    static TMap<FName, int32> MutedPlayers;
    static TMap<FName, int32> BlockedPlayers;
    static TMap<FName, float> SpamTimers;
};
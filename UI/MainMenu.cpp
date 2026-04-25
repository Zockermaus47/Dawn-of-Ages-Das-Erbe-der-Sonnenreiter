#include "MainMenu.h"

UMainMenuSystem::UMainMenuSystem()
{
}

void UMainMenuSystem::OpenMainMenu()
{
}

void UMainMenuSystem::StartNewGame(EGameDifficulty Difficulty)
{
}

void UMainMenuSystem::ContinueGame(FName SaveID)
{
}

void UMainMenuSystem::SaveGame(FName SaveName)
{
}

void UMainMenuSystem::LoadGame(FName SaveID)
{
}

TArray<FSaveGameData> UMainMenuSystem::GetSaveGames()
{
    return TArray<FSaveGameData>();
}

void UMainMenuSystem::DeleteSave(FName SaveID)
{
}

void UMainMenuSystem::QuitGame()
{
}

FSoundSettings UMainMenuSystem::GetAudioSettings()
{
    FSoundSettings Settings;
    Settings.MasterVolume = 1.0f;
    Settings.MusicVolume = 0.8f;
    Settings.SFXVolume = 1.0f;
    Settings.VoiceVolume = 1.0f;
    Settings.AmbientVolume = 0.7f;
    Settings.bMuteAudio = false;
    Settings.bSubtitlesEnabled = true;
    return Settings;
}

void UMainMenuSystem::SetAudioSettings(FSoundSettings Settings)
{
}

void UMainMenuSystem::SetMasterVolume(float Volume)
{
}

void UMainMenuSystem::SetMusicVolume(float Volume)
{
}

void UMainMenuSystem::SetSFXVolume(float Volume)
{
}

FVideoSettings UMainMenuSystem::GetVideoSettings()
{
    FVideoSettings Settings;
    Settings.ResolutionX = 1920;
    Settings.ResolutionY = 1080;
    Settings.bFullscreen = true;
    Settings.QualityPreset = 2;
    Settings.bVSync = true;
    Settings.FieldOfView = 90.0f;
    Settings.bMotionBlur = true;
    Settings.bBloom = true;
    Settings.bAmbientOcclusion = true;
    Settings.AntiAliasing = 2;
    return Settings;
}

void UMainMenuSystem::SetVideoSettings(FVideoSettings Settings)
{
}

void UMainMenuSystem::SetFullscreen(bool bFullscreen)
{
}

void UMainMenuSystem::SetResolution(int32 X, int32 Y)
{
}

FGameSettings UMainMenuSystem::GetGameSettings()
{
    FGameSettings Settings;
    Settings.Difficulty = EGameDifficulty::Normal;
    Settings.bShowDamageNumbers = true;
    Settings.bShowTutorials = true;
    Settings.bAutoLoot = false;
    Settings.bCameraShake = true;
    Settings.bVibration = true;
    Settings.MouseSensitivity = 1.0f;
    Settings.bInvertMouse = false;
    Settings.bToggleSprint = false;
    return Settings;
}

void UMainMenuSystem::SetGameSettings(FGameSettings Settings)
{
}

void UMainMenuSystem::SetDifficulty(EGameDifficulty Difficulty)
{
}

void UMainMenuSystem::SaveSettings()
{
}

void UMainMenuSystem::LoadSettings()
{
}

void UMainMenuSystem::ShowCredits()
{
}

bool UMainMenuSystem::HasExistingSave()
{
    return false;
}
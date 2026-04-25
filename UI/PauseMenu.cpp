#include "PauseMenu.h"

UPauseMenuSystem::UPauseMenuSystem()
{
}

void UPauseMenuSystem::OpenPauseMenu()
{
}

void UPauseMenuSystem::ClosePauseMenu()
{
}

void UPauseMenuSystem::TogglePauseMenu()
{
}

bool UPauseMenuSystem::IsPauseMenuOpen()
{
    return false;
}

void UPauseMenuSystem::SetPauseMenuState(EPauseMenuState State)
{
}

EPauseMenuState UPauseMenuSystem::GetPauseMenuState()
{
    return EPauseMenuState::None;
}

void UPauseMenuSystem::QuickSave()
{
}

void UPauseMenuSystem::SaveToSlot(ESaveSlot Slot, FText SaveName)
{
}

bool UPauseMenuSystem::CanSaveGame()
{
    return true;
}

FQuickSaveData UPauseMenuSystem::GetSaveData(ESaveSlot Slot)
{
    FQuickSaveData Data;
    Data.PlayerName = FText::FromString(TEXT("Spieler"));
    Data.PlayerLevel = 1;
    Data.CurrentBiome = FText::FromString(TEXT("Wald"));
    Data.CurrentQuest = FText::FromString(TEXT("Der erste Hunger"));
    Data.PlayTimeSeconds = 0;
    Data.Gold = 0;
    Data.HealthPercent = 1.0f;
    Data.ManaPercent = 1.0f;
    Data.Act = 1;
    Data.SavedAt = FDateTime::Now();
    return Data;
}

TArray<FQuickSaveData> UPauseMenuSystem::GetAllSaveData()
{
    return TArray<FQuickSaveData>();
}

bool UPauseMenuSystem::DeleteSave(ESaveSlot Slot)
{
    return false;
}

void UPauseMenuSystem::LoadFromSlot(ESaveSlot Slot)
{
}

bool UPauseMenuSystem::HasSaveData(ESaveSlot Slot)
{
    return false;
}

void UPauseMenuSystem::ReturnToMainMenu()
{
}

void UPauseMenuSystem::RestartFromCheckpoint()
{
}

float UPauseMenuSystem::GetGameTime()
{
    return 0.0f;
}

void UPauseMenuSystem::SetGameTime(float Time)
{
}

FText UPauseMenuSystem::GetFormattedPlayTime()
{
    return FText::FromString(TEXT("00:00:00"));
}

void UPauseMenuSystem::ExitToDesktop()
{
}

bool UPauseMenuSystem::IsGameInProgress()
{
    return false;
}
#include "dawnOfAges.h"

void FDawnOfAgesModule::StartupModule()
{
    UE_LOG(LogInit, Log, TEXT("DawnOfAges: Das Erbe der Sonnenreiter - Starting up"));
}

void FDawnOfAgesModule::ShutdownModule()
{
    UE_LOG(LogInit, Log, TEXT("DawnOfAges: Das Erbe der Sonnenreiter - Shutting down"));
}

IMPLEMENT_MODULE(FDawnOfAgesModule, dawnOfAges)
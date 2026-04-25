#pragma once

#include "CoreMinimal.h"

/**
 * Dawn of Ages: Das Erbe der Sonnenreiter
 * Survival Multiplayer Game Module
 */

class FDawnOfAgesModule : public IModuleInterface
{
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
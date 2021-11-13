/// \file Levels.h
/// \author Paolo Mazzon
/// \brief Forward declares all level functions
#pragma once
#include "Nym/Structs.h"

// Splash screen
void nymLevelSplashScreenStart(NymGame game);
NymLevel nymLevelSplashScreenUpdate(NymGame game);
void nymLevelSplashScreenDraw(NymGame game);
void nymLevelSplashScreenEnd(NymGame game);

// Menu
void nymLevelMenuStart(NymGame game);
NymLevel nymLevelMenuUpdate(NymGame game);
void nymLevelMenuDraw(NymGame game);
void nymLevelMenuEnd(NymGame game);

// Testing arena
void nymLevelTestingArenaStart(NymGame game);
NymLevel nymLevelTestingArenaUpdate(NymGame game);
void nymLevelTestingArenaDraw(NymGame game);
void nymLevelTestingArenaEnd(NymGame game);
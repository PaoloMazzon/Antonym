/// \file Constants.c
/// \author Paolo Mazzon

// This file contains no actual code so we'll put the implementation here
#define NYMASSETS_IMPLEMENTATION
#include "Nym/Assets.h"
#include "Nym/Levels.h"

// Actual constants
const char *NYM_LOG_FILE = "antonym.log";

const char *NYM_WINDOW_NAME = "Antonym";

int NYM_WINDOW_WIDTH = 400;

int NYM_WINDOW_HEIGHT = 225;

float NYM_GAME_WIDTH = 400;

float NYM_GAME_HEIGHT = 225;

const char *NYM_SAVE_FILE = "save.bin";

uint32_t NYM_SAVE_VERSION = 1;

void(*NYM_LEVEL_START_FUNCTIONS[NYM_LEVEL_MAX])(NymGame) = {
		&nymLevelSplashScreenStart,
		&nymLevelMenuStart,
		&nymLevelTestingArenaStart,
};

NymLevel(*NYM_LEVEL_UPDATE_FUNCTIONS[NYM_LEVEL_MAX])(NymGame) = {
		&nymLevelSplashScreenUpdate,
		&nymLevelMenuUpdate,
		&nymLevelTestingArenaUpdate,
};

void(*NYM_LEVEL_DRAW_FUNCTIONS[NYM_LEVEL_MAX])(NymGame) = {
		&nymLevelSplashScreenDraw,
		&nymLevelMenuDraw,
		&nymLevelTestingArenaDraw,
};

void(*NYM_LEVEL_END_FUNCTIONS[NYM_LEVEL_MAX])(NymGame) = {
		&nymLevelSplashScreenEnd,
		&nymLevelMenuEnd,
		&nymLevelTestingArenaEnd,
};
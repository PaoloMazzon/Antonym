/// \file Constants.c
/// \author Paolo Mazzon

// This file contains no actual code so we'll put the implementation here
#define NYMASSETS_IMPLEMENTATION
#include "Nym/Assets.h"
#include "Nym/Levels.h"

// Function pointers for levels
void(*NYM_LEVEL_START_FUNCTIONS[NYM_LEVEL_MAX])(const NymGame) = {
		&nymLevelSplashScreenStart,
		&nymLevelMenuStart,
		&nymLevelTestingArenaStart,
		&nymLevelConnectionScreenStart,
		&nymLevelLobbyStart,
		&nymLevelGameWorldStart,
};

NymLevel(*NYM_LEVEL_UPDATE_FUNCTIONS[NYM_LEVEL_MAX])(const NymGame) = {
		&nymLevelSplashScreenUpdate,
		&nymLevelMenuUpdate,
		&nymLevelTestingArenaUpdate,
		&nymLevelConnectionScreenUpdate,
		&nymLevelLobbyUpdate,
		&nymLevelGameWorldUpdate,
};

void(*NYM_LEVEL_DRAW_FUNCTIONS[NYM_LEVEL_MAX])(const NymGame) = {
		&nymLevelSplashScreenDraw,
		&nymLevelMenuDraw,
		&nymLevelTestingArenaDraw,
		&nymLevelConnectionScreenDraw,
		&nymLevelLobbyDraw,
		&nymLevelGameWorldDraw,
};

void(*NYM_LEVEL_END_FUNCTIONS[NYM_LEVEL_MAX])(const NymGame) = {
		&nymLevelSplashScreenEnd,
		&nymLevelMenuEnd,
		&nymLevelTestingArenaEnd,
		&nymLevelConnectionScreenEnd,
		&nymLevelLobbyEnd,
		&nymLevelGameWorldEnd,
};

// Actual constants
const char *NYM_LOG_FILE = "antonym.log";

const char *NYM_WINDOW_NAME = "Antonym";

int NYM_WINDOW_WIDTH = 400;

int NYM_WINDOW_HEIGHT = 225;

float NYM_GAME_WIDTH = 400;

float NYM_GAME_HEIGHT = 225;

const char *NYM_SAVE_FILE = "save.bin";

uint32_t NYM_SAVE_VERSION = 1;

const char *NYM_DEFAULT_PORT = "7000";

int NYM_CONNECTION_TIMEOUT = 5000;

int NYM_PLAYER_INDEX = 0;

double NYM_SPLASH_SCREEN_DURATION = 5;

const char *NYM_SPLASH_SCREEN_TEXT = "Paolo Mazzon (c) 2021";
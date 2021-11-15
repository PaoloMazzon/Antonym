/// \file Structs.h
/// \author Paolo Mazzon
/// \brief Forward declares all structs and important types
#pragma once
#include <stdint.h>
#include "JamUtil.h"

/********************** Forward-Declare Structs **********************/

typedef struct NymGame *NymGame;
typedef struct NymSave *NymSave;
typedef struct NymUIButton NymUIButton;
typedef struct NymClient *NymClient;
typedef struct NymUIMessage NymUIMessage;
typedef struct NymPacketClient NymPacketClient;
typedef struct NymPacketServer NymPacketServer;
typedef struct NymPlayer *NymPlayer;
typedef struct NymPlayerControls NymPlayerControls;
typedef struct NymPlayerState NymPlayerState;
typedef struct NymUITextbox NymUITextbox;

/********************** Enums **********************/

/// \brief Log levels for the logging function
typedef enum {
	NYM_LOG_LEVEL_MESSAGE = 0,  ///< Just a message
	NYM_LOG_LEVEL_WARNING = 1,  ///< Warning something has gone wrong
	NYM_LOG_LEVEL_ERROR = 2,    ///< Recoverable error
	NYM_LOG_LEVEL_CRITICAL = 3, ///< Fatal error that will crash now the game
} NymLogLevel;

/// \brief All the levels in the game -- must be sequential
typedef enum {
	NYM_LEVEL_SPLASH_SCREEN = 0,    ///< Opening splash screen
	NYM_LEVEL_MENU = 1,             ///< Menu
	NYM_LEVEL_TESTINGARENA = 2,     ///< Testing arena
	NYM_LEVEL_CONNECTIONSCREEN = 3, ///< Connect to server screen
	NYM_LEVEL_LOBBY = 4,            ///< Lobby screen before games
	NYM_LEVEL_GAMEWORLD = 5,        ///< Actual game world where game takes place
	NYM_LEVEL_MAX = 6,              ///< Total number of levels
	NYM_LEVEL_QUIT = 500,           ///< Quit the game
} NymLevel;
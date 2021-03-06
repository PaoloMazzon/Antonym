/// \file Constants.h
/// \author Paolo Mazzon
/// \brief Declares externs to constants
#pragma once

///< Start of level functions
extern void(*NYM_LEVEL_START_FUNCTIONS[NYM_LEVEL_MAX])(const NymGame);

///< Update level functions
extern NymLevel(*NYM_LEVEL_UPDATE_FUNCTIONS[NYM_LEVEL_MAX])(const NymGame);

///< Draw level functions
extern void(*NYM_LEVEL_DRAW_FUNCTIONS[NYM_LEVEL_MAX])(const NymGame);

///< End of level functions
extern void(*NYM_LEVEL_END_FUNCTIONS[NYM_LEVEL_MAX])(const NymGame);

///< File where logs from nymLog are stored
extern const char *NYM_LOG_FILE;

///< Name of the window
extern const char *NYM_WINDOW_NAME;

///< Width of the window on startup
extern int NYM_WINDOW_WIDTH;

///< Height of the window on startup
extern int NYM_WINDOW_HEIGHT;

///< Width of the game on startup
extern float NYM_GAME_WIDTH;

///< Height of the game on startup
extern float NYM_GAME_HEIGHT;

///< Save file location
extern const char *NYM_SAVE_FILE;

///< Save file version
extern uint32_t NYM_SAVE_VERSION;

///< Default port for connecting to hosts
extern const char *NYM_DEFAULT_PORT;

///< Amount of time in milliseconds to wait before failing to connect to a host
extern int NYM_CONNECTION_TIMEOUT;

///< Size in bytes of the overlay message buffer
#define NYM_MESSAGE_BUFFER_SIZE 1024

///< Size in bytes of the title of the overlay message
#define NYM_MESSAGE_TITLE_BUFFER_SIZE 100

///< Max number of players in a game
#define NYM_MAX_PLAYERS 10

///< Index of the player character in the player array (character this game is controlling)
extern int NYM_PLAYER_INDEX;

///< Duration in seconds of the splash screen
extern double NYM_SPLASH_SCREEN_DURATION;

///< Text displayed on the splash screen
extern const char *NYM_SPLASH_SCREEN_TEXT;

///< Maximum number of characters in a textbox
#define NYM_MAX_TEXTBOX_CHARACTERS 100

///< Max number of characters in a player's name
#define NYM_NAME_MAX_CHARACTERS 15

///< Max number of characters in a chat message
#define NYM_MAX_CHAT_CHARACTERS 45

///< Max number of chat messages on screen at once
#define NYM_MAX_CHAT_MESSAGES 5

///< How long between sending packets to the server
extern double NYM_PACKET_DELAY;

///< Index of the local player in the player array
extern int NYM_PLAYER_CHARACTER;

///< ID of a player that does not exist
extern int NYM_PLAYER_INVALID;

///< Max health of a player
extern double NYM_PLAYER_MAX_HP;

///< How many elements to add to an array when extending it
extern int NYM_ARRAY_EXTENSION;
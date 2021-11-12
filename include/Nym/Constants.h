/// \file Constants.h
/// \author Paolo Mazzon
/// \brief Declares externs to constants
#pragma once

///< Start of level functions
extern void(*NYM_LEVEL_START_FUNCTIONS[NYM_LEVEL_MAX])(NymGame);

///< Update level functions
extern NymLevel(*NYM_LEVEL_UPDATE_FUNCTIONS[NYM_LEVEL_MAX])(NymGame);

///< Draw level functions
extern void(*NYM_LEVEL_DRAW_FUNCTIONS[NYM_LEVEL_MAX])(NymGame);

///< End of level functions
extern void(*NYM_LEVEL_END_FUNCTIONS[NYM_LEVEL_MAX])(NymGame);

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
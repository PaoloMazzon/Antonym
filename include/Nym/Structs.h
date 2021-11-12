/// \file Structs.h
/// \author Paolo Mazzon
/// \brief Forward declares all structs and important types
#pragma once
#include <stdint.h>
#include "JamUtil.h"

/********************** Forward-Declare Structs **********************/

typedef struct NymGame *NymGame;
typedef struct NymSave *NymSave;

/********************** Enums **********************/

/// \brief Log levels for the logging function
typedef enum {
	NYM_LOG_LEVEL_MESSAGE = 0,  ///< Just a message
	NYM_LOG_LEVEL_WARNING = 1,  ///< Warning something has gone wrong
	NYM_LOG_LEVEL_ERROR = 2,    ///< Recoverable error
	NYM_LOG_LEVEL_CRITICAL = 3, ///< Fatal error that will crash now the game
} NymLogLevel;

/// \file Util.h
/// \author Paolo Mazzon
/// \brief Defines some utility features like memory and logging
#pragma once
#include "Nym/Structs.h"

/// \brief Same as malloc but crashes on failure
void *nymMalloc(uint32_t size);

/// \brief Same as malloc but crashes on failure and zeroes the data
void *nymCalloc(uint32_t size);

/// \brief Logs a message to the debug console and to a file
void nymLog(NymLogLevel level, const char *fmt, ...);

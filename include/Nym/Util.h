/// \file Util.h
/// \author Paolo Mazzon
/// \brief Defines some utility features like memory and logging
#pragma once
#include "Nym/Structs.h"

/// \brief Same as malloc but crashes on failure (only use nymFree for this data)
void *nymMalloc(uint32_t size);

/// \brief Same as malloc but crashes on failure and zeroes the data (only use nymFree for this data)
void *nymCalloc(uint32_t size);

/// \brief Same as realloc but crashes on failure (only use nymFree for this data)
void *nymRealloc(void *ptr, uint32_t size);

/// \brief Same as free but in the Nym engine (NULL is safe to pass)
void nymFree(void *ptr);

/// \brief Logs a message to the debug console and to a file
void nymLog(NymLogLevel level, const char *fmt, ...);

/// \brief Makes sure a string is safe by putting a \0 at the end of a string
/// \param string String to sanitize
/// \param size Max size in bytes the string is supposed to be
void nymSanitizeString(char *string, int size);
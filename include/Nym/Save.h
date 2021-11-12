/// \file Save.h
/// \author Paolo Mazzon
/// \brief Handles saving and loading data for the game
#pragma once
#include "Nym/Structs.h"

/// \brief All save data stored for Antonym
///
/// The save is stored in a file as its raw binary data. The first 4 bytes of the struct
/// will always be the save version number, so when loaded we can just check the first 4
/// bytes and load the save depending on what version of save it is.
struct NymSave {
	uint32_t saveVersion; ///< For compatibility across different versions of the save file
	VK2DRendererConfig rendererConfig; ///< Render config
};

/// \brief Loads a save from a file, creating a new one with default values if not
NymSave nymSaveLoad(const char *file);

/// \brief Flushes a save to file
void nymSaveFlush(NymSave save, const char *file);

/// \brief Destroys a save -- does not flush
void nymSaveDestroy(NymSave save);
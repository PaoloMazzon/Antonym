/// \file Game.h
/// \author Paolo Mazzon
/// \brief Declares the main game data struct and top level game functions
#pragma once
#include "Nym/Assets.h"
#include "Nym/Save.h"

struct NymGame {
	NymAssets *assets; ///< Game assets
	NymSave save; ///< Game save file

	///< Core stuff like window
	struct {
		SDL_Window *window; ///< Window the game is in
	} Core;
};

/// \brief Starts the game
void nymStart();
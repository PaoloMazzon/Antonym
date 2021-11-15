/// \file Game.h
/// \author Paolo Mazzon
/// \brief Declares the main game data struct and top level game functions
#pragma once
#include "Nym/Assets.h"
#include "Nym/Save.h"
#include "Nym/Client.h"
#include "Nym/Constants.h"

struct NymGame {
	NymAssets *assets;                  ///< Game assets
	NymSave save;                       ///< Game save file
	NymLevel level;                     ///< Current level - do not modify this variable outside of `Game.c`
	NymClient client;                   ///< Client for online multiplayer
	NymPlayer players[NYM_MAX_PLAYERS]; ///< All possible players in the game (player character is always 0)

	///< Core stuff like window
	struct {
		SDL_Window *window;     ///< Window the game is in
		VK2DTexture backbuffer; ///< Where the game is drawn
		bool debug;             ///< Run the game in debug mode
	} Core;

	///< Input things
	struct {
		float mx;   ///< Mouse x
		float my;   ///< Mouse y
		bool ml[2]; ///< Mouse button left (current frame and last frame)
		bool mm[2]; ///< Mouse button middle (current frame and last frame)
		bool mr[2]; ///< Mouse button right (current frame and last frame)
	} Input;
};

/// \brief Starts the game
void nymStart(bool debug);
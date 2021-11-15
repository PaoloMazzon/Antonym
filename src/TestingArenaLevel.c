/// \file TestingArenaLevel.c
/// \author Paolo Mazzon
#include "Nym/Levels.h"
#include "Nym/Game.h"
#include "Nym/UI.h"
#include "Nym/Player.h"

void nymLevelTestingArenaStart(NymGame game) {
	// Start online client
	game->client = nymClientCreate("localhost");
	if (game->client == NULL) {
		nymUICreateMessage("Connection failed", "Failed to connect to host");
	}

	// TODO: Get a player id from the server

	// Create player character
	game->players[NYM_PLAYER_INDEX] = nymPlayerCreate(0, game->assets->sprPlayer1Idle, 100, 100);
}

NymLevel nymLevelTestingArenaUpdate(NymGame game) {
	// Update player character
	NymPlayerControls controls = {};
	nymPlayerUpdateFromControls(game, game->players[NYM_PLAYER_INDEX], &controls);

	// Meta
	if (juKeyboardGetKey(SDL_SCANCODE_ESCAPE) || game->client == NULL)
		return NYM_LEVEL_MENU;
	return NYM_LEVEL_TESTINGARENA;
}

void nymLevelTestingArenaDraw(NymGame game) {
	// Draw all the players
	for (int i = 0; i < NYM_MAX_PLAYERS; i++)
		nymPlayerDraw(game, game->players[i]);
}

void nymLevelTestingArenaEnd(NymGame game) {
	// Destroy the players
	for (int i = 0; i < NYM_MAX_PLAYERS; i++)
		nymPlayerDestroy(game->players[i]);
	memset(game->players, 0, sizeof(NymPlayer) * NYM_MAX_PLAYERS);

	nymClientDestroy(game->client);
	game->client = NULL;
}

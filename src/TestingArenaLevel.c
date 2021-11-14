/// \file TestingArenaLevel.c
/// \author Paolo Mazzon
#include "Nym/Levels.h"
#include "Nym/Game.h"
#include "Nym/UI.h"

void nymLevelTestingArenaStart(NymGame game) {
	game->client = nymClientCreate("localhost");
	if (game->client == NULL) {
		nymUICreateMessage("Connection failed", "Failed to connect to host");
	}
}

NymLevel nymLevelTestingArenaUpdate(NymGame game) {
	if (juKeyboardGetKey(SDL_SCANCODE_ESCAPE) || game->client == NULL)
		return NYM_LEVEL_MENU;
	return NYM_LEVEL_TESTINGARENA;
}

void nymLevelTestingArenaDraw(NymGame game) {

}

void nymLevelTestingArenaEnd(NymGame game) {
	nymClientDestroy(game->client);
	game->client = NULL;
}

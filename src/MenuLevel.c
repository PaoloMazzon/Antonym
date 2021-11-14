/// \file MenuLevel.c
/// \author Paolo Mazzon
#include "Nym/Levels.h"
#include "Nym/Game.h"
#include "Nym/UI.h"

static NymUIButton PLAY_BUTTON = {32, 32};
static NymUIButton OPTIONS_BUTTON = {40, 32 + 64};
static NymUIButton QUIT_BUTTON = {48, 32 + 64 + 64};

void nymLevelMenuStart(NymGame game) {
	// Setup the buttons
	PLAY_BUTTON.spr = game->assets->sprMenuPlayButton;
	OPTIONS_BUTTON.spr = game->assets->sprMenuOptionsButton;
	QUIT_BUTTON.spr = game->assets->sprMenuQuitButton;
}

NymLevel nymLevelMenuUpdate(NymGame game) {
	if (nymUICheckButton(game, &PLAY_BUTTON))
		return NYM_LEVEL_TESTINGARENA;
	if (nymUICheckButton(game, &OPTIONS_BUTTON))
		nymUICreateMessage("Unimplemented", "Under construction.");
	if (nymUICheckButton(game, &QUIT_BUTTON))
		return NYM_LEVEL_QUIT;
	return NYM_LEVEL_MENU;
}

void nymLevelMenuDraw(NymGame game) {
	// Background
	vk2dDrawTexture(game->assets->texMenuBackground, 0, 0);

	// Draw the buttons
	nymUIDrawButton(game, &PLAY_BUTTON);
	nymUIDrawButton(game, &OPTIONS_BUTTON);
	nymUIDrawButton(game, &QUIT_BUTTON);
}

void nymLevelMenuEnd(NymGame game) {

}
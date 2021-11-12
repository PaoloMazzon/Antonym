/// \file MenuLevel.c
/// \author Paolo Mazzon
#include "Nym/Levels.h"
#include "Nym/Game.h"

void nymLevelMenuStart(NymGame game) {

}

NymLevel nymLevelMenuUpdate(NymGame game) {
	return NYM_LEVEL_MENU;
}

void nymLevelMenuDraw(NymGame game) {
	vk2dRendererSetColourMod((void*)VK2D_BLACK);
	juFontDraw(game->assets->fntTNR16, 0, 0, "Menu");
	vk2dRendererSetColourMod((void*)VK2D_DEFAULT_COLOUR_MOD);
}

void nymLevelMenuEnd(NymGame game) {

}
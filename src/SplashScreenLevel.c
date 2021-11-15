/// \file SplashScreenLevel.c
/// \author Paolo Mazzon
#include "Nym/Levels.h"
#include "Nym/Game.h"

void nymLevelSplashScreenStart(NymGame game) {

}

NymLevel nymLevelSplashScreenUpdate(NymGame game) {
	if (game->Core.debug || juTime() > NYM_SPLASH_SCREEN_DURATION || juKeyboardGetKey(SDL_SCANCODE_SPACE) || game->Input.ml[0])
		return NYM_LEVEL_MENU;
	else
		return NYM_LEVEL_SPLASH_SCREEN;
}

void nymLevelSplashScreenDraw(NymGame game) {
	vk2dRendererSetColourMod(VK2D_BLACK);
	juFontDraw(game->assets->fntTNR16, 0, 0, NYM_SPLASH_SCREEN_TEXT);
	vk2dRendererSetColourMod(VK2D_DEFAULT_COLOUR_MOD);
}

void nymLevelSplashScreenEnd(NymGame game) {

}

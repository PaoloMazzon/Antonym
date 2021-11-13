/// \file UI.c
/// \author Paolo Mazzon
#include "Nym/UI.h"
#include "Nym/Game.h"

void nymUIDrawButton(NymGame game, NymUIButton *button) {
	// TODO: Lock to the UI camera
	JURectangle r = {button->x, button->y, button->spr->Internal.w, button->spr->Internal.h};
	int frame = juPointInRectangle(&r, game->Input.mx, game->Input.my) ? (game->Input.ml[0] ? 2 : 1) : 0;
	juSpriteDrawFrame(button->spr, frame, button->x, button->y);
}

bool nymUICheckButton(NymGame game, NymUIButton *button) {
	JURectangle r = {button->x, button->y, button->spr->Internal.w, button->spr->Internal.h};
	return juPointInRectangle(&r, game->Input.mx, game->Input.my) && !game->Input.ml[0] && game->Input.ml[1];
}
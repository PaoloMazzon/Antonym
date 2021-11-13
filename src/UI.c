/// \file UI.c
/// \author Paolo Mazzon
#include "Nym/UI.h"
#include "Nym/Game.h"

static NymUIMessage gMessageBox;

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

void nymUISetMessageSprite(JUSprite sprite) {
	gMessageBox.confirmButton.spr = sprite;
	// TODO: Button placement
}

void nymUICreateMessage(const char *title, const char *message) {
	gMessageBox.active = true;
	strncpy(gMessageBox.message, title, NYM_MESSAGE_BUFFER_SIZE - 1);
	strncpy(gMessageBox.message, title, NYM_MESSAGE_TITLE_BUFFER_SIZE - 1);
}

bool nymUIMessageActive() {
	return gMessageBox.active;
}

void nymUIDrawOverly() {
	// TODO: This
}

void nymUIDrawMessage() {
	// TODO: This
}
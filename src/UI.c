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
	gMessageBox.confirmButton.x = 184;
	gMessageBox.confirmButton.y = 152;
}

void nymUICreateMessage(const char *title, const char *message) {
	gMessageBox.active = true;
	strncpy(gMessageBox.message, message, NYM_MESSAGE_BUFFER_SIZE - 1);
	strncpy(gMessageBox.title, title, NYM_MESSAGE_TITLE_BUFFER_SIZE - 1);
}

bool nymUIMessageActive() {
	return gMessageBox.active;
}

void nymUIDrawOverly() {
	// TODO: Debug overlay
}

void nymUIDrawMessage(NymGame game) {
	if (gMessageBox.active) {
		// Background
		vk2dDrawTexture(game->assets->texMessageBoxBackground, 64, 48);

		// Title
		vk2dRendererSetColourMod(VK2D_BLACK);
		juFontDraw(game->assets->fntTNR16, 80, 54, "%s", gMessageBox.title);

		// Message
		juFontDrawWrapped(game->assets->fntTNR16, 80, 80, 16 * 15, "%s", gMessageBox.message);

		// Button
		vk2dRendererSetColourMod(VK2D_DEFAULT_COLOUR_MOD);
		nymUIDrawButton(game, &gMessageBox.confirmButton);
		if (nymUICheckButton(game, &gMessageBox.confirmButton))
			gMessageBox.active = false;
	}
}
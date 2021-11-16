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

void _nymUIAddTextboxCharacter(NymUITextbox *textbox, char c) {
	if (strlen(textbox->text) < textbox->maxCharacters) {
		textbox->text[strlen(textbox->text) + 1] = 0;
		textbox->text[strlen(textbox->text)] = c;
	}
}

void nymUIUpdateTextbox(NymGame game, NymUITextbox *textbox) {
	const int w = game->assets->fntUbuntuMono16->characters->w;
	JURectangle r = {textbox->x, textbox->y, w * textbox->maxCharacters, game->assets->fntUbuntuMono16->newLineHeight};

	// Select the textbox
	if (juPointInRectangle(&r, game->Input.mx, game->Input.my) && game->Input.ml[0] && textbox->selectable)
		textbox->active = true;
	else if (!juPointInRectangle(&r, game->Input.mx, game->Input.my) && game->Input.ml[0])
		textbox->active = false;

	// Enter text
	if (textbox->active) {
		// Numbers
		for (int i = SDL_SCANCODE_1; i <= SDL_SCANCODE_0; i++)
			if (juKeyboardGetKeyPressed(i))
				_nymUIAddTextboxCharacter(textbox, SDL_GetScancodeName(i)[0]);

		if (!textbox->numbersOnly) {
			// Characters
			for (int i = SDL_SCANCODE_A; i <= SDL_SCANCODE_Z; i++)
				if (juKeyboardGetKeyPressed(i))
					_nymUIAddTextboxCharacter(textbox, SDL_GetScancodeName(i)[0]);

			// Symbols
			for (int i = SDL_SCANCODE_MINUS; i <= SDL_SCANCODE_SLASH; i++)
				if (juKeyboardGetKeyPressed(i))
					_nymUIAddTextboxCharacter(textbox, SDL_GetScancodeName(i)[0]);

			// Space bar
			if (juKeyboardGetKeyPressed(SDL_SCANCODE_SPACE))
				_nymUIAddTextboxCharacter(textbox, ' ');
		}

		// Backspace
		if (juKeyboardGetKeyPressed(SDL_SCANCODE_BACKSPACE) && strlen(textbox->text) > 0) {
			textbox->text[strlen(textbox->text) - 1] = 0;
		}
	}
}

void nymUIDrawTextbox(NymGame game, NymUITextbox *textbox) {
	vec4 gray = {0.5, 0.5, 0.5, 1};
	vec4 textGray = {0.1, 0.1, 0.1, 1};
	vec4 darkGray = {0.3, 0.3, 0.3, 1};
	const int w = game->assets->fntUbuntuMono16->characters->w;

	// Set background colour and draw background
	if (textbox->active)
		vk2dRendererSetColourMod(gray);
	else
		vk2dRendererSetColourMod(darkGray);
	vk2dDrawRectangle(textbox->x, textbox->y, w * (textbox->maxCharacters + 1), game->assets->fntUbuntuMono16->newLineHeight);

	// Set text colour
	if (textbox->active)
		vk2dRendererSetColourMod(VK2D_BLACK);
	else
		vk2dRendererSetColourMod(textGray);

	// Draw text input/hint
	if (textbox->active || strlen(textbox->text) > 0) {
		if ((int) juTime() % 2 && textbox->active)
			juFontDraw(game->assets->fntUbuntuMono16, textbox->x, textbox->y, "%s|", textbox->text);
		else
			juFontDraw(game->assets->fntUbuntuMono16, textbox->x, textbox->y, "%s", textbox->text);
	} else {
		juFontDraw(game->assets->fntUbuntuMono16, textbox->x, textbox->y, "%s", textbox->hint);
	}

	vk2dRendererSetColourMod(VK2D_DEFAULT_COLOUR_MOD);
}
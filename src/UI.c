/// \file UI.c
/// \author Paolo Mazzon
#include "Nym/UI.h"
#include "Nym/Game.h"

static NymUIMessage gMessageBox;

static NymUIChatbox gChatbox = {
		{
			"",
			"",
			0,
			0,
			NYM_MAX_CHAT_CHARACTERS,
			false,
			false,
			false,
		}
};

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

		if (!textbox->numbersOnly) { // TODO: The shift key for lowercase and symbols
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

float nymUIGetChatWidth(NymGame game) {
	return (NYM_MAX_CHAT_CHARACTERS + 1) * game->assets->fntUbuntuMono16->characters[0].w;
}

float nymUIGetChatHeight(NymGame game) {
	return (NYM_MAX_CHAT_MESSAGES + 1) * game->assets->fntUbuntuMono16->newLineHeight;
}

void nymUISelectChat(NymGame game, bool select) {
	gChatbox.chat.active = select;
}

bool nymUIChatSelected(NymGame game) {
	return gChatbox.chat.active;
}

void nymUIAddChatMessage(NymGame game, const char *message) {
	// 0 is the newest message displayed closest to the text input, like monster hunter world for example
	for (int i = NYM_MAX_CHAT_MESSAGES - 1; i > 0; i--)
		strncpy(gChatbox.messages[i], gChatbox.messages[i - 1], NYM_MAX_CHAT_CHARACTERS);
	strncpy(gChatbox.messages[0], message, NYM_MAX_CHAT_CHARACTERS);
}

void nymUIGetChatInput(NymGame game, char *out) {
	strcpy(out, gChatbox.chat.text);
	gChatbox.chat.text[0] = 0;
}

void nymUIUpdateChat(NymGame game, float x, float y) {
	gChatbox.chat.x = x;
	gChatbox.chat.y = nymUIGetChatHeight(game) - game->assets->fntUbuntuMono16->newLineHeight;
	nymUIUpdateTextbox(game, &gChatbox.chat);
}

void nymUIDrawChat(NymGame game, float x, float y, bool drawInput, float alpha) {
	float w = nymUIGetChatWidth(game);
	float h = nymUIGetChatHeight(game);
	vec4 background = {0.35, 0.35, 0.35, alpha};
	vec4 text = {0.8, 0.8, 0.8, alpha};

	// Update coords and draw text input
	gChatbox.chat.x = x;
	gChatbox.chat.y = y + (h - game->assets->fntUbuntuMono16->newLineHeight);
	if (drawInput)
		nymUIDrawTextbox(game, &gChatbox.chat);

	// Draw background
	vk2dRendererSetColourMod(background);
	vk2dDrawRectangle(x, y, w, h - game->assets->fntUbuntuMono16->newLineHeight);

	// Draw messages
	int j = 0;
	vk2dRendererSetColourMod(text);
	for (int i = NYM_MAX_CHAT_MESSAGES - 1; i >= 0; i--) {
		juFontDraw(game->assets->fntUbuntuMono16, x, y + (game->assets->fntUbuntuMono16->newLineHeight * j), "%s", gChatbox.messages[i]);
		j++;
	}
	vk2dRendererSetColourMod(VK2D_DEFAULT_COLOUR_MOD);
}

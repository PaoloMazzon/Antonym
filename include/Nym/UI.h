/// \file UI.h
/// \author Paolo Mazzon
/// \brief Tools for the UI
#pragma once
#include "JamUtil.h"
#include "Nym/Structs.h"
#include "Nym/Constants.h"

/// \brief Information needed for buttons
struct NymUIButton {
	float x;      ///< X position on screen
	float y;      ///< Y position on screen
	JUSprite spr; ///< 3 frame sprite of the button
};

/// \brief Data for an overlay message
struct NymUIMessage {
	char title[NYM_MESSAGE_TITLE_BUFFER_SIZE]; ///< Title of the message
	char message[NYM_MESSAGE_BUFFER_SIZE];     ///< Contents of the message
	bool active;                               ///< Whether or not the message is currently being displayed
	NymUIButton confirmButton;                 ///< The ok button
};

/// \brief Textbox for text entry
struct NymUITextbox {
	char text[NYM_MAX_TEXTBOX_CHARACTERS]; ///< Text input
	char hint[NYM_MAX_TEXTBOX_CHARACTERS]; ///< Hint text
	float x;                               ///< X position of the textbox
	float y;                               ///< Y position of the textbox
	float maxCharacters;                   ///< Maximum characters in this textbox
	bool active;                           ///< Whether or not this textbox is currently accepting input
	bool selectable;                       ///< Can this textbox be selected
	bool numbersOnly;                      ///< Only accept numbers as input
};

/// \brief Chatbox for online comms
struct NymUIChatbox {
	NymUITextbox chat; ///< Text input for chat
	char messages[NYM_MAX_CHAT_CHARACTERS][NYM_MAX_CHAT_MESSAGES]; ///< Previous chat messages
};

/// \brief Draws a button to the screen using a sprite with 3 images
void nymUIDrawButton(NymGame game, NymUIButton *button);

/// \brief Returns true if a given button is pressed
bool nymUICheckButton(NymGame game, NymUIButton *button);

/// \brief Call at startup to set the message box's button's sprite
void nymUISetMessageSprite(JUSprite sprite);

/// \brief Sets a message to be displayed on top of the screen
void nymUICreateMessage(const char *title, const char *message);

/// \brief Returns true if there is currently a message on screen
bool nymUIMessageActive();

/// \brief Draws the overlay (whatever that means)
void nymUIDrawOverly();

/// \brief Draws the message if its active
void nymUIDrawMessage(NymGame game);

/// \brief Updates a textbox
void nymUIUpdateTextbox(NymGame game, NymUITextbox *textbox);

/// \brief Draws a textbox
void nymUIDrawTextbox(NymGame game, NymUITextbox *textbox);

/// \brief Gets chat windows width
float nymUIGetChatWidth(NymGame game);

/// \brief Gets chat windows height
float nymUIGetChatHeight(NymGame game);

/// \brief Forces text input into chat
void nymUISelectChat(NymGame game);

/// \brief Returns whether or not chat is currently selected
bool nymUIChatSelected(NymGame game);

/// \brief Adds a new message to the chat box, pushing back the old ones
void nymUIAddChatMessage(NymGame game, const char *message);

/// \brief Copies the chat text into a string and clears the chat message
void nymUIGetChatInput(NymGame game, char *out);

/// \brief Updates chat
void nymUIUpdateChat(NymGame game, float x, float y);

/// \brief Draws chat
void nymUIDrawChat(NymGame game, float x, float y, bool drawInput, float alpha);
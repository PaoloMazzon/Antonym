/// \file UI.h
/// \author Paolo Mazzon
/// \brief Tools for the UI
#pragma once
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

struct NymUITextbox {
	char text[NYM_MAX_TEXTBOX_CHARACTERS]; ///< Text input
	char hint[NYM_MAX_TEXTBOX_CHARACTERS]; ///< Hint text
	float x;                               ///< X position of the textbox
	float y;                               ///< Y position of the textbox
	float maxCharacters;                   ///< Maximum characters in this textbox
	bool active;                           ///< Whether or not this textbox is currently accepting input
	bool selectable;                       ///< Can this textbox be selected
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
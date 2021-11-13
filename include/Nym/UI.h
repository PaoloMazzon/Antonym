/// \file UI.h
/// \author Paolo Mazzon
/// \brief Tools for the UI
#pragma once
#include "Nym/Structs.h"

/// \brief Information needed for buttons
struct NymUIButton {
	float x;      ///< X position on screen
	float y;      ///< Y position on screen
	JUSprite spr; ///< 3 frame sprite of the button
};

/// \brief Draws a button to the screen using a sprite with 3 images
void nymUIDrawButton(NymGame game, NymUIButton *button);

/// \brief Returns true if a given button is pressed
bool nymUICheckButton(NymGame game, NymUIButton *button);
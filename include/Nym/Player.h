/// \file Player.h
/// \author Paolo Mazzon
/// \brief
#pragma once
#include "Nym/Structs.h"

/// \brief All possible controls the player may use
struct NymPlayerControls {
	float moveX;     ///< Movement of the player in the x direction from -1 to 1
	float moveY;     ///< Movement of the player in the y direction from -1 to 1
	float direction; ///< Direction the player is
	bool fire;       ///< Whether or not fire was pressed
};

/// \brief Mandatory data needed to update the player from raw data
struct NymPlayerState {
	double x;         ///< X coordinate of this player
	double y;         ///< Y coordinate of this player
	double hsp;       ///< Horizontal speed of this player
	double vsp;       ///< Vertical speed of this player
	double health;    ///< Current health
	double maxHealth; ///< New health
};

/// \brief A player in the game, AI, human online, or this computer's player
struct NymPlayer {
	uint32_t id;          ///< ID of this player so we know what the server is talking about
	JUSprite sprite;      ///< Sprite for this player
	NymPlayerState state; ///< State of this player
};

/// \brief Creates a player
NymPlayer nymPlayerCreate(uint32_t id, JUSprite sprite, float x, float y);

/// \brief Updates a player based on provided input
void nymPlayerUpdateFromControls(NymGame game, NymPlayer player, NymPlayerControls *controls);

/// \brief Updates a player to a given state
void nymPlayerUpdateFromState(NymGame game, NymPlayer player, NymPlayerState *state);

/// \brief Creates a packet from a players data (provide a packet yourself)
void nymPlayerCreatePacket(NymPlayer player, NymPacketClient *packet);

/// \brief Destroys a player from memory
void nymPlayerDestroy(NymPlayer player);
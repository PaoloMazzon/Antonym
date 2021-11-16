/// \file Packet.h
/// \author Paolo Mazzon
/// \brief Just declares the contents of an Antonym packet
#pragma once
#include "Nym/Structs.h"
#include "Nym/Constants.h"

///< All packet structs must start with this
#define NYM_PACKET_HEADER NymPacketType type;

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

/// \brief Player information
struct NymPacketClientPlayerUpdate {
	NYM_PACKET_HEADER
	NymPlayerState state; ///< State of this player
};

/// \brief Client side chat message
struct NymPacketClientMessage {
	NYM_PACKET_HEADER
	char message[NYM_MAX_CHAT_CHARACTERS]; ///< Contents of the message
	int len;                               ///< Length of the chat message
};

/// \brief Client side information on the user's lobby choices
struct NymPacketClientLobby {
	NYM_PACKET_HEADER
};

/// \brief Server sending information on all player's whereabouts
struct NymPacketServerPlayerUpdates {
	NYM_PACKET_HEADER
};

/// \brief When a new message is recieved from the server
struct NymPacketServerMessage {
	NYM_PACKET_HEADER
};

/// \brief Server sending information on the lobby
struct NymPacketServerLobby {
	NYM_PACKET_HEADER
};

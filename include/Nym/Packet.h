/// \file Packet.h
/// \author Paolo Mazzon
/// \brief Just declares the contents of an Antonym packet
#pragma once
#include <stdbool.h>
#include "Nym/Structs.h"
#include "Nym/Constants.h"

///< All packet structs must start with this
#define NYM_PACKET_HEADER NymPacketType type;

///< Amount of bytes the above header is
#define NYM_PACKET_HEADER_OFFSET sizeof(NymPacketType)

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
	int spriteIndex;  ///< Index of the sprite to use for this player
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
	char playerName[NYM_NAME_MAX_CHARACTERS]; ///< Player's name
};

/// \brief What the client will return to the game loop
struct NymPacketClientMaster {
	NYM_PACKET_HEADER
	union {
		NymPacketClientLobby lobby;
		NymPacketClientMessage message;
		NymPacketClientPlayerUpdate playerUpdate;
	};
};

/// \brief Server sending information on all player's whereabouts
struct NymPacketServerPlayerUpdates {
	NYM_PACKET_HEADER
};

/// \brief When a new message is recieved from the server
struct NymPacketServerMessage {
	NYM_PACKET_HEADER
	char message[NYM_MAX_CHAT_CHARACTERS]; ///< Contents of the message
	int len;                               ///< Length of the chat message
};

/// \brief Server sending information on the lobby
struct NymPacketServerLobby {
	NYM_PACKET_HEADER
};

/// \brief Server sends this to each new client when they connect
struct NymPacketServerInitial {
	NYM_PACKET_HEADER
	NymPlayerID id; ///< ID assigned to whoever recieves this packet
};

/// \brief Server sending info on someone connecting or disconnecting
struct NymPacketServerConnection {
	NYM_PACKET_HEADER
	NymConnectType connection;           ///< Type of connection event this is
	NymPlayerID id;                      ///< ID of the player who just disconnected or ID of the new player
	NymPlayerState initialState;         ///< Initial state of the new player if its a new connection
	char *name[NYM_NAME_MAX_CHARACTERS]; ///< Name of the new player if its a new connection
};

/// \brief What the server will send to the client
struct NymPacketServerMaster {
	NYM_PACKET_HEADER
	union {
		NymPacketServerLobby lobby;
		NymPacketServerMessage message;
		NymPacketServerPlayerUpdates playerUpdates;
		NymPacketServerConnection serverConnection;
		NymPacketServerInitial initial;
	};
};
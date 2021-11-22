/// \file Player.h
/// \author Paolo Mazzon
/// \brief
#pragma once
#include "JamUtil.h"
#include "Nym/Structs.h"
#include "Nym/Packet.h"

/// \brief A player in the game, AI, human online, or this computer's player
struct NymPlayer {
	NymPlayerID id;       ///< ID of this player so we know what the server is talking about
	NymPlayerState state; ///< State of this player
};

/// \brief Creates a player
NymPlayer nymPlayerCreate(uint32_t id, JUSprite sprite, float x, float y);

/// \brief Updates a player based on provided input
void nymPlayerUpdateFromControls(NymGame game, NymPlayer player, NymPlayerControls *controls);

/// \brief Updates a player to a given state
void nymPlayerUpdateFromState(NymGame game, NymPlayer player, NymPlayerState *state);

/// \brief Draws a player
void nymPlayerDraw(NymGame game, NymPlayer player);

/// \brief Creates a packet from a players data (provide a packet yourself)
void nymPlayerCreatePacket(NymPlayer player, NymPacketClient *packet);

/// \brief Destroys a player from memory
void nymPlayerDestroy(NymPlayer player);
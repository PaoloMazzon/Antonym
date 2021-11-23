/// \file Player.h
/// \author Paolo Mazzon
/// \brief
#pragma once
#include <pthread.h>
#include "JamUtil.h"
#include "Nym/Structs.h"
#include "Nym/Packet.h"

/// \brief A player in the game, AI, human online, or this computer's player
///
/// Do not access the members of this struct directly
struct NymPlayer {
	_Atomic NymPlayerID id;    ///< ID of this player so we know what the server is talking about
	NymPlayerState state;      ///< State of this player
	pthread_mutex_t stateLock; ///< Lock for accessing this player's state
};

/// \brief Creates a player
NymPlayer nymPlayerCreate(NymPlayerID id, int sprite, float x, float y);

/// \brief Updates a player based on provided input (thread-safe)
void nymPlayerUpdateFromControls(NymGame game, NymPlayer player, NymPlayerControls *controls);

/// \brief Updates a player to a given state (thread-safe)
void nymPlayerUpdateFromState(NymGame game, NymPlayer player, NymPlayerState *state);

/// \brief Draws a player
void nymPlayerDraw(NymGame game, NymPlayer player);

/// \brief Gets and locks the state of the player (thread-safe)
void nymPlayerLockState(NymPlayer player, NymPlayerState *state);

/// \brief Sets a new player state and unlocks the player (thread-safe)
void nymPlayerUnlockState(NymPlayer player, NymPlayerState *state);

/// \brief Gets a player's state (thread-safe)
NymPlayerState nymPlayerGetState(NymPlayer player);

/// \brief Creates a packet from a players data (provide a packet yourself)
void nymPlayerCreatePacket(NymPlayer player, NymPacketClientPlayerUpdate *packet);

/// \brief Destroys a player from memory
void nymPlayerDestroy(NymPlayer player);
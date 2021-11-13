/// \file Client.h
/// \author Paolo Mazzon
/// \brief Manages the client-side networking
#pragma once
#include "enet.h"
#include "Nym/Structs.h"

/// \brief Data for managing the client
struct NymClient {
	ENetPeer *client; ///< Actual client
};

/// \brief Creates a client
NymClient nymClientCreate(uint32_t ip, int port);

/// \brief Destroys a client
void nymClientDestroy(NymClient client);
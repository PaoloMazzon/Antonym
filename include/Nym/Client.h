/// \file Client.h
/// \author Paolo Mazzon
/// \brief Manages the client-side networking
#pragma once
#include "enet.h"
#include "Nym/Structs.h"

/// \brief Data for managing the client
struct NymClient {
	ENetHost *client;    ///< Client
	ENetPeer *peer;      ///< Connection to the remote host
	ENetAddress address; ///< Address of the host
};

/// \brief Creates a client -- blocking and will return NULL if it fails to connect
NymClient nymClientCreate(const char *ip);

/// \brief Destroys a client
void nymClientDestroy(NymClient client);
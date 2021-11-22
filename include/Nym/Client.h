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
	double lastTime;     ///< Time since the last general packet was sent
};

/// \brief Creates a client -- blocking and will return NULL if it fails to connect
NymClient nymClientCreate(const char *ip, const char *port);

/// \brief Prepares a packet (if this returns something other than NYM_CLIENT_STATUS_OK you gotta free the client)
/// \param client Client to send through
/// \param data Data to send
/// \param size Size of the data in bytes
/// \param reliable If true, the packet is guaranteed to be delivered
/// \return
NymClientStatus nymClientSendPacket(NymClient client, void *data, uint32_t size, bool reliable);

/// \brief Should be called every frame (if this returns something other than NYM_CLIENT_STATUS_OK you gotta free the client)
NymClientStatus nymClientUpdate(NymGame game, NymClient client, NymPacketServerMaster *packet);

/// \brief Destroys a client
void nymClientDestroy(NymClient client);
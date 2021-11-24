/// \file Client.h
/// \author Paolo Mazzon
/// \brief Manages the client-side networking
#pragma once
#include <pthread.h>
#include "enet.h"
#include "Nym/Structs.h"

/// \brief Data for managing the client
struct NymClient {
	// Net code
	ENetHost *client;    ///< Client
	ENetPeer *peer;      ///< Connection to the remote host
	ENetAddress address; ///< Address of the host
	double lastTime;     ///< Time since the last general packet was sent

	// Packet management
	NymPacketServerMaster *packetQueue; ///< All packets waiting to be grabbed by the game
	int packetCount;                    ///< How many packets in the queue
	int packetQueueSize;                ///< Size of the queue array in elements

	// Synchronization
	_Atomic NymClientStatus status; ///< If true the client has stopped and needs to be destroyed
	pthread_t thread;               ///< Thread the client is happening in
	pthread_mutex_t clientLock;     ///< Lock for stopping both threads from accessing the client at the same time
	pthread_mutex_t packetLock;     ///< Lock for stopping both threads from accessing packets at the same time
};

/// \brief Creates a client -- blocking and will return NULL if it fails to connect
NymClient nymClientCreate(const char *ip, const char *port);

/// \brief Prepares a packet (thread-safe)
/// \param client Client to send through
/// \param data Data to send
/// \param size Size of the data in bytes
/// \param reliable If true, the packet is guaranteed to be delivered
void nymClientSendPacket(NymClient client, void *data, uint32_t size, bool reliable);

/// \brief Should be called every frame (if this returns something other than NYM_CLIENT_STATUS_OK you gotta free the client)
void nymClientStart(NymGame game, NymClient client, NymPacketServerMaster *packet);

/// \brief If this returns anything other that NYM_CLIENT_STATUS_OK you have to free the client (thread-safe)
NymClientStatus nymClientGetStatus(NymClient client);

/// \brief Destroys a client
void nymClientDestroy(NymClient client);
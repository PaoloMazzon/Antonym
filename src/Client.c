/// \file Client.c
/// \author Paolo Mazzon
#include "JamUtil.h"
#include "Nym/Client.h"
#include "Nym/Util.h"
#include "Nym/Constants.h"
#include "Nym/Packet.h"
#include "Nym/Game.h"
#include "Nym/Player.h"

/// \brief Passes data to the client thread
typedef struct _NymClientArgs {
	NymGame game;
	NymClient client;
} _NymClientArgs;

void _nymClientAddPacketToQueue(NymClient client, NymPacketServerMaster *packet) {
	pthread_mutex_lock(&client->packetLock);

	NymPacketServerMaster *ptr = nymMalloc(sizeof(struct NymPacketServerMaster));
	*ptr = *packet;

	// Check if there is space in the packet queue
	if (client->packetQueueSize <= client->packetCount) {
		client->packetQueueSize += NYM_ARRAY_EXTENSION;
		client->packetQueue = nymRealloc(client->packetQueue, client->packetQueueSize * sizeof(NymPacketServerMaster*));
	}

	// Put the packet at the back of the queue
	client->packetQueue[client->packetCount] = ptr;
	client->packetCount++;

	pthread_mutex_unlock(&client->packetLock);
}

// Non-thread safe version of send packet
void _nymClientSendPacket(NymClient client, void *data, uint32_t size, bool reliable) {
	ENetPacket *packet = enet_packet_create(data, size, reliable ? ENET_PACKET_FLAG_RELIABLE : 0);
	if (enet_peer_send(client->peer, 0, packet) < 0) {
		nymLog(NYM_LOG_LEVEL_ERROR, "Failed to send packet.");
		client->status = NYM_CLIENT_STATUS_ERROR;
	}
}

void *_nymClientUpdate(void *data) {
	NymGame game = ((_NymClientArgs*)data)->game;
	NymClient client = ((_NymClientArgs*)data)->client;

	// Run the client as long as the status is good
	while (client->status == NYM_CLIENT_STATUS_OK) {
		pthread_mutex_lock(&client->clientLock);
		NymPacketServerMaster packet = {};

		// Check if we're still connected and all that
		ENetPeerState peerStatus = enet_peer_get_state(client->peer);
		if (peerStatus == ENET_PEER_STATE_DISCONNECTED) {
			nymLog(NYM_LOG_LEVEL_WARNING, "Disconnected from host.");
			client->status = NYM_CLIENT_STATUS_DISCONNECTED;
		}

		// Process whatever event might be waiting
		ENetEvent event;
		if (enet_host_service(client->client, &event, 0) >= 0) {
			// We received a packet, ship it off
			if (event.type == ENET_EVENT_TYPE_RECEIVE) {
				if (sizeof(struct NymPacketClientMaster) - NYM_PACKET_HEADER_OFFSET < event.packet->dataLength) {
					nymLog(NYM_LOG_LEVEL_WARNING, "Bad packet of size %i received.", event.packet->dataLength);
				} else {
					memcpy(&packet.message, event.packet->data, event.packet->dataLength);
					packet.type = packet.lobby.type;
					_nymClientAddPacketToQueue(client, &packet);
				}
				enet_packet_destroy(event.packet);
			}
			if (event.peer != NULL)
				event.peer->data = NULL;
		} else {
			nymLog(NYM_LOG_LEVEL_ERROR, "Failed to update enet.");
			client->status = NYM_CLIENT_STATUS_ERROR;
		}

		// Check if we need to send a new general packet (for game state)
		if (juTime() - client->lastTime >= NYM_PACKET_DELAY / 1000) {
			// Create packet for player state and send it
			NymPacketClientPlayerUpdate playerPacket;
			nymPlayerCreatePacket(game->players[NYM_PLAYER_INDEX], &playerPacket);
			nymClientSendPacket(client, &playerPacket, sizeof(struct NymPacketClientPlayerUpdate), false);

			client->lastTime = juTime();
		}
		pthread_mutex_unlock(&client->clientLock);
	}

	return NULL;
}

NymClient nymClientCreate(const char *ip, const char *port) {
	NymClient client = nymCalloc(sizeof(struct NymClient)); // TODO: Parse port

	// Create host client
	client->client = enet_host_create(NULL, 1, 2, 0, 0);
	client->status = NYM_CLIENT_STATUS_OK;
	if (client->client != NULL) {
		// Setup enet
		int portint;
		sscanf(port, "%i", &portint);
		client->address.port = (uint16_t)portint;
		enet_address_set_host(&client->address, ip);
		client->peer = enet_host_connect(client->client, &client->address, 2, 0);

		// Create the mutexes
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_setprotocol(&attr, PTHREAD_MUTEX_DEFAULT);
		pthread_mutex_init(&client->clientLock, &attr);
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_setprotocol(&attr, PTHREAD_MUTEX_DEFAULT);
		pthread_mutex_init(&client->packetLock, &attr);

		// Make sure we get connected
		ENetEvent event;
		if (enet_host_service(client->client, &event, NYM_CONNECTION_TIMEOUT) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
			enet_host_flush(client->client);
			client->lastTime = juTime();
			nymLog(NYM_LOG_LEVEL_MESSAGE, "Connected to host \"%s\" on port [%s].", ip, port);
		} else {
			nymLog(NYM_LOG_LEVEL_ERROR, "Failed to connect to host \"%s\" on port [%s].", ip, port);
			enet_host_destroy(client->client);
			nymFree(client);
			client = NULL;
		}
	} else {
		nymFree(client);
		client = NULL;
		nymLog(NYM_LOG_LEVEL_ERROR, "Failed to create ENet host.");
	}

	return client;
}

void nymClientSendPacket(NymClient client, void *data, uint32_t size, bool reliable) {
	if (client->status == NYM_CLIENT_STATUS_OK) {
		pthread_mutex_lock(&client->clientLock);
		_nymClientSendPacket(client, data, size, reliable);
		pthread_mutex_unlock(&client->clientLock);
	}
}

NymPacketServerMaster *nymClientGetPacket(NymClient client) {
	NymPacketServerMaster *out = NULL;
	if (client->packetCount > 0) {
		pthread_mutex_lock(&client->packetLock);

		// Get the packet
		out = client->packetQueue[0];

		// Shift the queue down
		for (int i = 0; i < client->packetCount - 1; i++)
			client->packetQueue[i] = client->packetQueue[i + 1];
		client->packetCount--;

		pthread_mutex_unlock(&client->packetLock);
	}
	return out;
}

void nymClientStart(NymGame game, NymClient client) {
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	_NymClientArgs arg = {game, client};
	if (pthread_create(&client->thread, &attr, _nymClientUpdate, &arg) != 0) {
		nymLog(NYM_LOG_LEVEL_ERROR, "Failed to create client thread.");
		client->status = NYM_CLIENT_STATUS_ERROR;
	}
}

NymClientStatus nymClientGetStatus(NymClient client) {
	return client->status;
}

void nymClientDestroy(NymClient client) {
	if (client != NULL) {
		client->status = NYM_CLIENT_STATUS_KILL;
		pthread_join(client->thread, NULL);
		pthread_mutex_destroy(&client->clientLock);
		enet_peer_disconnect(client->peer, 0);
		enet_host_destroy(client->client);
		nymFree(client->packetQueue);
		nymFree(client);
	}
}
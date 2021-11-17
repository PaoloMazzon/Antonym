/// \file Client.c
/// \author Paolo Mazzon
#include "Nym/Client.h"
#include "Nym/Util.h"
#include "Nym/Constants.h"
#include "Nym/Packet.h"

NymClient nymClientCreate(const char *ip, const char *port) {
	NymClient client = nymCalloc(sizeof(struct NymClient)); // TODO: Parse port

	// Create host client
	client->client = enet_host_create(NULL, 1, 2, 0, 0);
	if (client->client != NULL) {
		// Create peer
		client->address.port = 7000; // TODO: Use the port
		enet_address_set_host(&client->address, ip);
		client->peer = enet_host_connect(client->client, &client->address, 2, 0);

		// Make sure we get connected
		ENetEvent event;
		if (enet_host_service(client->client, &event, NYM_CONNECTION_TIMEOUT) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
			enet_host_flush(client->client);
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

NymClientStatus nymClientSendPacket(NymClient client, void *data, uint32_t size, bool reliable) {
	ENetPacket *packet = enet_packet_create(data, size, reliable ? ENET_PACKET_FLAG_RELIABLE : 0);
	if (enet_peer_send(client->peer, 0, packet) < 0) {
		nymLog(NYM_LOG_LEVEL_ERROR, "Failed to send packet.");
		return NYM_CLIENT_STATUS_ERROR;
	}
	return NYM_CLIENT_STATUS_OK;
}

NymClientStatus nymClientUpdate(NymClient client, NymPacketServerMaster *packet) {
	// Just in case, we set the packet type to none
	packet->type = NYM_PACKET_TYPE_NONE;

	// Check if we're still connected and all that
	ENetPeerState peerStatus = enet_peer_get_state(client->peer);
	if (peerStatus == ENET_PEER_STATE_DISCONNECTED) {
		nymLog(NYM_LOG_LEVEL_WARNING, "Disconnected from host.");
		return NYM_CLIENT_STATUS_DISCONNECTED;
	}

	// Process whatever event might be waiting
	ENetEvent event;
	if (enet_host_service(client->client, &event, 0) >= 0) {
		// We recieved a packet, ship it off
		if (event.type == ENET_EVENT_TYPE_RECEIVE) {
			if (sizeof(struct NymPacketClientMaster) - NYM_PACKET_HEADER_OFFSET < event.packet->dataLength) {
				nymLog(NYM_LOG_LEVEL_WARNING, "Bad packet of size %i received.", event.packet->dataLength);
			} else {
				memcpy(&packet->message, event.packet->data, event.packet->dataLength);
				packet->type = packet->lobby.type;
			}
			enet_packet_destroy(event.packet);
		}
		if (event.peer != NULL)
			event.peer->data = NULL;
	} else {
		nymLog(NYM_LOG_LEVEL_ERROR, "Failed to update enet.");
		return NYM_CLIENT_STATUS_ERROR;
	}

	return NYM_CLIENT_STATUS_OK;
}

void nymClientDestroy(NymClient client) {
	if (client != NULL) {
		enet_peer_disconnect(client->peer, 0);
		enet_host_destroy(client->client);
		nymFree(client);
	}
}
/// \file Client.c
/// \author Paolo Mazzon
#include "Nym/Client.h"
#include "Nym/Util.h"
#include "Nym/Constants.h"

NymClient nymClientCreate(const char *ip, const char *port) {
	NymClient client = nymCalloc(sizeof(struct NymClient)); // TODO: Parse port

	// Create host client
	client->client = enet_host_create(NULL, 1, 2, 0, 0);
	if (client->client != NULL) {
		// Create peer
		client->address.port = NYM_DEFAULT_PORT;
		enet_address_set_host(&client->address, ip);
		client->peer = enet_host_connect(client->client, &client->address, 2, 0);

		// Make sure we get connected
		ENetEvent event;
		if (enet_host_service(client->client, &event, NYM_CONNECTION_TIMEOUT) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
			enet_host_flush(client->client);
			nymLog(NYM_LOG_LEVEL_MESSAGE, "Connected to host \"%s\".", ip);
		} else {
			nymLog(NYM_LOG_LEVEL_ERROR, "Failed to connect to host \"%s\".", ip);
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

void nymClientDestroy(NymClient client) {
	if (client != NULL) {
		enet_peer_disconnect(client->peer, 0);
		enet_host_destroy(client->client);
		nymFree(client);
	}
}
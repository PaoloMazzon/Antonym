/// \file LobbyLevel.c
/// \author Paolo Mazzon
#include "Nym/Levels.h"
#include "Nym/Game.h"
#include "Nym/Client.h"
#include "Nym/Packet.h"
#include "Nym/UI.h"

NymUITextbox gChatTextbox = {
		"",
		"Chat",
		32,
		225-48,
		30,
		true,
		true,
		false,
};

void nymLevelLobbyStart(NymGame game) {

}

NymLevel nymLevelLobbyUpdate(NymGame game) {
	if (game->client != NULL) {
		// Update online stuff
		NymPacketClientMaster packet;
		if (nymClientUpdate(game->client, &packet) != NYM_CLIENT_STATUS_OK) {
			nymUICreateMessage("Error", "Disconnected from host");
			nymClientDestroy(game->client);
			game->client = NULL;
		}

		// Handle the new packet
		if (packet.type != NYM_PACKET_TYPE_NONE) {
			// TODO: This
		}

		// Chat
		nymUIUpdateTextbox(game, &gChatTextbox);
		if (juKeyboardGetKeyPressed(SDL_SCANCODE_RETURN) && gChatTextbox.active) {
			NymPacketClientMessage message = {NYM_PACKET_TYPE_CLIENT_MESSAGE, "", strlen(gChatTextbox.text)};
			strcpy(message.message, gChatTextbox.text);
			nymClientSendPacket(game->client, &message, sizeof(struct NymPacketClientMessage), true);
			gChatTextbox.text[0] = 0;
		}

		return NYM_LEVEL_LOBBY;
	} else {
		return NYM_LEVEL_CONNECTIONSCREEN;
	}
}

void nymLevelLobbyDraw(NymGame game) {
	nymUIDrawTextbox(game, &gChatTextbox);
}

void nymLevelLobbyEnd(NymGame game) {

}

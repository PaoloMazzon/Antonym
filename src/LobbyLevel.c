/// \file LobbyLevel.c
/// \author Paolo Mazzon
#include "Nym/Util.h"
#include "Nym/Levels.h"
#include "Nym/Game.h"
#include "Nym/Client.h"
#include "Nym/Packet.h"
#include "Nym/UI.h"

const float CHAT_X = 16;
const float CHAT_Y = 16;

void nymLevelLobbyStart(NymGame game) {

}

NymLevel nymLevelLobbyUpdate(NymGame game) {
	if (game->client != NULL) {
		// Update online stuff
		NymPacketServerMaster packet;
		if (nymClientUpdate(game->client, &packet) != NYM_CLIENT_STATUS_OK) {
			nymUICreateMessage("Error", "Disconnected from host");
			nymClientDestroy(game->client);
			game->client = NULL;
		}

		// Handle the new packet
		if (packet.type != NYM_PACKET_TYPE_NONE) {
			if (packet.type == NYM_PACKET_TYPE_SERVER_MESSAGE) {
				nymUIAddChatMessage(game, packet.message.message);
			}

			// TODO: Handle other packet types
		}

		// Chat
		nymUIUpdateChat(game, CHAT_X, CHAT_Y);
		if (juKeyboardGetKeyPressed(SDL_SCANCODE_RETURN) && nymUIChatSelected(game)) {
			NymPacketClientMessage message = {NYM_PACKET_TYPE_CLIENT_MESSAGE, "", 0};
			nymUIGetChatInput(game, message.message);
			message.len = strlen(message.message);
			nymClientSendPacket(game->client, &message, sizeof(struct NymPacketClientMessage), true);
		} else if (juKeyboardGetKeyPressed(SDL_SCANCODE_RETURN) && !nymUIChatSelected(game)) {
			nymUISelectChat(game);
		}

		return NYM_LEVEL_LOBBY;
	} else {
		return NYM_LEVEL_CONNECTIONSCREEN;
	}
}

void nymLevelLobbyDraw(NymGame game) {
	nymUIDrawChat(game, CHAT_X, CHAT_Y, true, 1);
}

void nymLevelLobbyEnd(NymGame game) {

}

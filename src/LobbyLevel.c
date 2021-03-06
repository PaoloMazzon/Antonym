/// \file LobbyLevel.c
/// \author Paolo Mazzon
#include "Nym/Util.h"
#include "Nym/Levels.h"
#include "Nym/Game.h"
#include "Nym/Client.h"
#include "Nym/Packet.h"
#include "Nym/UI.h"
#include "Nym/Player.h"
#include "Nym/Net.h"

const float CHAT_X = 16;
const float CHAT_Y = 16;

void nymLevelLobbyStart(NymGame game) {

}

NymLevel nymLevelLobbyUpdate(NymGame game) {
	if (game->client != NULL) {
		// Get new packets
		NymPacketServerMaster *packet = nymClientGetPacket(game->client);
		while (packet != NULL) {
			if (packet->type != NYM_PACKET_TYPE_NONE)
				nymNetHandlePacket(game, packet);
			nymFree(packet);
			packet = nymClientGetPacket(game->client);
		}

		// Chat
		nymUIUpdateChat(game, CHAT_X, CHAT_Y);
		if (juKeyboardGetKeyPressed(SDL_SCANCODE_RETURN) && nymUIChatSelected(game)) {
			NymPacketClientMessage message = {NYM_PACKET_TYPE_CLIENT_MESSAGE, "", 0};
			nymUIGetChatInput(game, message.message);
			message.len = strlen(message.message);
			nymClientSendPacket(game->client, &message, sizeof(struct NymPacketClientMessage), true);
			nymUISelectChat(game, false);
		} else if (juKeyboardGetKeyPressed(SDL_SCANCODE_RETURN) && !nymUIChatSelected(game)) {
			nymUISelectChat(game, true);
		}

		// Check client status
		NymClientStatus status = nymClientGetStatus(game->client);
		if (status != NYM_CLIENT_STATUS_OK) {
			if (game->Flags.versionMismatch) {
				game->Flags.versionMismatch = false;
				nymUICreateMessage("Version error", "Version mismatch between host and client.");
			} else {
				if (status == NYM_CLIENT_STATUS_TIMEOUT)
					nymUICreateMessage("Timeout", "Disconnected due to timeout");
				else if (status == NYM_CLIENT_STATUS_KICKED)
					nymUICreateMessage("Kicked", "Kicked from the game");
				else
					nymUICreateMessage("Error", "Disconnected from host");
			}
			nymClientDestroy(game->client);
			game->client = NULL;
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

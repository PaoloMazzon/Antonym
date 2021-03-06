/// \file ConnectionScreenLevel.h.c
/// \author Paolo Mazzon
#include "Nym/Levels.h"
#include "Nym/Packet.h"
#include "Nym/Game.h"
#include "Nym/UI.h"
#include "Nym/Client.h"

static NymUITextbox gIPTextbox = {
		"127.0.0.1",
		"IP address",
		70,
		48+16,
		15,
		false,
		true,
		false
};

static NymUITextbox gPortTextbox = {
		"7000",
		"Port",
		70,
		80+16,
		15,
		false,
		true,
		true
};

static NymUITextbox gNameTextbox = {
		"JOE MAMA",
		"Player Name",
		70,
		112+16,
		NYM_NAME_MAX_CHARACTERS,
		false,
		true,
		false
};

static NymUIButton gBackButton = {
	200 - 32 - 75,
	176,
};

static NymUIButton gPlayButton = {
		200 - 32 + 75,
		176,
};

void nymLevelConnectionScreenStart(NymGame game) {
	gBackButton.spr = game->assets->sprBackButton;
	gPlayButton.spr = game->assets->sprPlayButton;
	strcpy(gIPTextbox.text, game->save->lastIP);
	strcpy(gPortTextbox.text, game->save->lastPort);
	strcpy(gNameTextbox.text, game->save->lastName);
}

NymLevel nymLevelConnectionScreenUpdate(NymGame game) {
	nymUIUpdateTextbox(game, &gIPTextbox);
	nymUIUpdateTextbox(game, &gPortTextbox);
	nymUIUpdateTextbox(game, &gNameTextbox);

	if (nymUICheckButton(game, &gBackButton)) {
		return NYM_LEVEL_MENU;
	} else if (nymUICheckButton(game, &gPlayButton)) {
		game->client = nymClientCreate(gIPTextbox.text, gPortTextbox.text);
		if (game->client != NULL) {
			// Save new connection presets then go to the lobby
			strcpy(game->save->lastIP, gIPTextbox.text);
			strcpy(game->save->lastPort, gPortTextbox.text);
			strcpy(game->save->lastName, gNameTextbox.text);
			nymSaveFlush(game->save, NYM_SAVE_FILE);

			// Send the lobby pakcet
			NymPacketClientLobby lobby = {NYM_PACKET_TYPE_CLIENT_LOBBY};
			strncpy(lobby.playerName, gNameTextbox.text, gNameTextbox.maxCharacters);
			lobby.version = NYM_NET_VERSION;
			nymClientStart(game, game->client);
			nymClientSendPacket(game->client, &lobby, sizeof(struct NymPacketClientLobby), true);

			return NYM_LEVEL_LOBBY;
		} else {
			nymUICreateMessage("Connection failed", "Failed to connect to host");
		}
	}
	return NYM_LEVEL_CONNECTIONSCREEN;
}

void nymLevelConnectionScreenDraw(NymGame game) {
	vk2dDrawTexture(game->assets->texConnectionScreenBackground, 0, 0);
	nymUIDrawTextbox(game, &gIPTextbox);
	nymUIDrawTextbox(game, &gPortTextbox);
	nymUIDrawTextbox(game, &gNameTextbox);
	nymUIDrawButton(game, &gBackButton);
	nymUIDrawButton(game, &gPlayButton);
}

void nymLevelConnectionScreenEnd(NymGame game) {

}

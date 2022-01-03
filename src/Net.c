/// \file Net.c
/// \author Paolo Mazzon
#include "Nym/Net.h"
#include "Nym/Util.h"
#include "Nym/UI.h"
#include "Nym/Game.h"
#include "Nym/Player.h"

void nymNetHandlePacket(NymGame game, NymPacketServerMaster *packet) {
	if (packet->type == NYM_PACKET_TYPE_SERVER_MESSAGE) {
		nymSanitizeString(packet->message.message, NYM_MAX_CHAT_CHARACTERS);
		nymUIAddChatMessage(game, packet->message.message);
	} else if (packet->type == NYM_PACKET_TYPE_SERVER_INITIAL) {
		if (packet->initial.version != NYM_NET_VERSION) {
			// Wrong version
			game->Flags.versionMismatch = true;
		} else {
			game->players[NYM_PLAYER_INDEX] = nymPlayerCreate(packet->initial.id, game->save->playerSprite, packet->initial.x, packet->initial.y);
		}
	} else if (packet->type == NYM_PACKET_TYPE_SERVER_CONNECTION) {
		// TODO: This
	}
}
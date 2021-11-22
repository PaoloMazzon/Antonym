/// \file Player.c
/// \author Paolo Mazzon
#include "Nym/Player.h"
#include "Nym/Util.h"

NymPlayer nymPlayerCreate(NymPlayerID id, int sprite, float x, float y) {
	NymPlayer player = nymCalloc(sizeof(struct NymPlayer));
	player->state.spriteIndex = sprite;
	player->state.x = x;
	player->state.y = y;
	player->id = id;
	player->state.health = NYM_PLAYER_MAX_HP;
	player->state.maxHealth = NYM_PLAYER_MAX_HP;

	return player;
}

void nymPlayerUpdateFromControls(NymGame game, NymPlayer player, NymPlayerControls *controls) {
	if (player != NULL) {
		// TODO: This
	}
}

void nymPlayerUpdateFromState(NymGame game, NymPlayer player, NymPlayerState *state) {
	if (player != NULL) {
		player->state = *state;
	}
}

void nymPlayerDraw(NymGame game, NymPlayer player) {
	if (player != NULL) {
		// TODO: This
	}
}

void nymPlayerCreatePacket(NymPlayer player, NymPacketClient *packet) {
	if (player != NULL) {
		// TODO: This
	}
}

void nymPlayerDestroy(NymPlayer player) {
	if (player != NULL) {
		nymFree(player);
	}
}

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
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutex_init(&player->stateLock, &attr);

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

void nymPlayerLockState(NymPlayer player, NymPlayerState *state) {
	pthread_mutex_lock(&player->stateLock);
	*state = player->state;
}

void nymPlayerUnlockState(NymPlayer player, NymPlayerState *state) {
	player->state = *state;
	pthread_mutex_lock(&player->stateLock);
}

NymPlayerState nymPlayerGetState(NymPlayer player) {
	NymPlayerState out;
	pthread_mutex_lock(&player->stateLock);
	out = player->state;
	pthread_mutex_unlock(&player->stateLock);
	return out;
}

void nymPlayerCreatePacket(NymPlayer player, NymPacketClientPlayerUpdate *packet) {
	if (player != NULL) {
		packet->type = NYM_PACKET_TYPE_CLIENT_PLAYERUPDATE;
		packet->state = nymPlayerGetState(player);
	}
}

void nymPlayerDestroy(NymPlayer player) {
	if (player != NULL) {
		pthread_mutex_destroy(&player->stateLock);
		nymFree(player);
	}
}

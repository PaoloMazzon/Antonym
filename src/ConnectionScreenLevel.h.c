/// \file ConnectionScreenLevel.h.c
/// \author Paolo Mazzon
#include "Nym/Levels.h"
#include "Nym/Game.h"
#include "Nym/UI.h"

static NymUITextbox gIPTextbox = {
		"127.0.0.1",
		"IP address",
		16,
		16,
		15,
		false,
		true
};

static NymUITextbox gPortTextbox = {
		"7000",
		"Port",
		16,
		48,
		15,
		false,
		true
};

static NymUITextbox gNameTextbox = {
		"Joe",
		"Player Name",
		16,
		80,
		NYM_NAME_MAX_CHARACTERS,
		false,
		true
};

void nymLevelConnectionScreenStart(NymGame game) {

}

NymLevel nymLevelConnectionScreenUpdate(NymGame game) {
	nymUIUpdateTextbox(game, &gIPTextbox);
	nymUIUpdateTextbox(game, &gPortTextbox);
	nymUIUpdateTextbox(game, &gNameTextbox);
	return NYM_LEVEL_CONNECTIONSCREEN;
}

void nymLevelConnectionScreenDraw(NymGame game) {
	nymUIDrawTextbox(game, &gIPTextbox);
	nymUIDrawTextbox(game, &gPortTextbox);
	nymUIDrawTextbox(game, &gNameTextbox);
}

void nymLevelConnectionScreenEnd(NymGame game) {

}

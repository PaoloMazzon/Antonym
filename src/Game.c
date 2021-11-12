/// \file Game.c
/// \author Paolo Mazzon
#include "Nym/Game.h"
#include "Nym/Util.h"
#include "Nym/Constants.h"

static NymGame _nymInitializeGame() {
	NymGame game = nymCalloc(sizeof(struct NymGame));

	// Start SDL, VK2D, and JamUtil
	VK2DRendererConfig config = {
			msaa_32x,
			sm_TripleBuffer,
			ft_Nearest
	};
	game->Core.window = SDL_CreateWindow(NYM_WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, NYM_WINDOW_WIDTH, NYM_WINDOW_HEIGHT, SDL_WINDOW_VULKAN);
	vk2dRendererInit(game->Core.window, config);
	juInit(game->Core.window);

	// Load assets
	game->assets = buildNymAssets();
	return game;
}

static void _nymDeinitializeGame(NymGame game) {
	// Destroy all contexts in order
	juQuit();
	vk2dRendererQuit();
	SDL_DestroyWindow(game->Core.window);
	destroyNymAssets(game->assets);
	nymFree(game);
}

void nymStart() {
	nymLog(NYM_LOG_LEVEL_MESSAGE, "Antonym started...");

	// Initialize game struct
	NymGame game = _nymInitializeGame();

	// Run game
	// TODO: This


	// Cleanup
	_nymDeinitializeGame(game);

	nymLog(NYM_LOG_LEVEL_MESSAGE, "Antonym closing...");
}
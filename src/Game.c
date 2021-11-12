/// \file Game.c
/// \author Paolo Mazzon
#include "Nym/Game.h"
#include "Nym/Util.h"
#include "Nym/Constants.h"

static NymGame _nymInitializeGame() {
	NymGame game = nymCalloc(sizeof(struct NymGame));

	// Load save file first
	game->save = nymSaveLoad(NYM_SAVE_FILE);

	// Start SDL, VK2D, and JamUtil
	game->Core.window = SDL_CreateWindow(NYM_WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, NYM_WINDOW_WIDTH, NYM_WINDOW_HEIGHT, SDL_WINDOW_VULKAN);
	vk2dRendererInit(game->Core.window, game->save->rendererConfig);
	juInit(game->Core.window);

	// Load assets
	game->assets = buildNymAssets();

	// Begin the first level
	game->level = NYM_LEVEL_MENU;
	NYM_LEVEL_START_FUNCTIONS[game->level](game);

	return game;
}

static void _nymDeinitializeGame(NymGame game) {
	// Destroy all contexts in order
	destroyNymAssets(game->assets);
	juQuit();
	vk2dRendererQuit();
	SDL_DestroyWindow(game->Core.window);
	nymSaveDestroy(game->save);
	nymFree(game);
}

void nymStart() {
	nymLog(NYM_LOG_LEVEL_MESSAGE, "Antonym started...");

	// Initialize game struct
	NymGame game = _nymInitializeGame();

	// Run game
	bool run = true;
	bool kill = false;
	SDL_Event event;
	while (run) {
		juUpdate();
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				kill = true;

		NymLevel newLevel = NYM_LEVEL_UPDATE_FUNCTIONS[game->level](game);
		NYM_LEVEL_DRAW_FUNCTIONS[game->level](game);

		if (newLevel == NYM_LEVEL_QUIT || kill) {
			NYM_LEVEL_END_FUNCTIONS[game->level](game);
			run = false;
		} else if (newLevel != game->level) {
			// Unload current level, load new one
			nymLog(NYM_LOG_LEVEL_MESSAGE, "Unloading level %i and loading level %i.", game->level, newLevel);
			NYM_LEVEL_END_FUNCTIONS[game->level](game);
			game->level = newLevel;
			NYM_LEVEL_START_FUNCTIONS[game->level](game);
		}
	}

	// Cleanup
	_nymDeinitializeGame(game);

	nymLog(NYM_LOG_LEVEL_MESSAGE, "Antonym closing...");
}
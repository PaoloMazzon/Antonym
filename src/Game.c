/// \file Game.c
/// \author Paolo Mazzon
#include "VK2D/VK2D.h"
#include "Nym/Game.h"
#include "Nym/Util.h"
#include "Nym/Constants.h"

static NymGame _nymInitializeGame() {
	NymGame game = nymCalloc(sizeof(struct NymGame));

	// Load save file first
	game->save = nymSaveLoad(NYM_SAVE_FILE);

	// Start SDL, VK2D, and JamUtil
	game->Core.window = SDL_CreateWindow(NYM_WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, NYM_WINDOW_WIDTH, NYM_WINDOW_HEIGHT, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
	vk2dRendererInit(game->Core.window, game->save->rendererConfig);
	juInit(game->Core.window);
	game->Core.backbuffer = vk2dTextureCreate(vk2dRendererGetDevice(), NYM_GAME_WIDTH, NYM_GAME_HEIGHT);
	vk2dRendererSetTextureCamera(true);

	// Load assets
	game->assets = buildNymAssets();

	// Begin the first level
	game->level = NYM_LEVEL_SPLASH_SCREEN;
	NYM_LEVEL_START_FUNCTIONS[game->level](game);

	return game;
}

static void _nymDeinitializeGame(NymGame game) {
	// Destroy all contexts in order
	vk2dRendererWait();
	vk2dTextureFree(game->Core.backbuffer);
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
		// Window update
		juUpdate();
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				kill = true;

		// Get mouse input
		int w, h, mx, my;
		uint32_t mouseState;
		float minScale = (float)w / NYM_GAME_WIDTH > (float)h / NYM_GAME_HEIGHT ? h / NYM_GAME_HEIGHT : w / NYM_GAME_WIDTH;
		SDL_GetWindowSize(game->Core.window, &w, &h);
		mouseState = SDL_GetMouseState(&mx, &my);
		float frameXDisplacement = (w - (minScale * NYM_GAME_WIDTH)) / 2;
		float frameYDisplacement = (h - (minScale * NYM_GAME_HEIGHT)) / 2;
		game->Input.mx = (mx - frameXDisplacement) / minScale;
		game->Input.my = (my - frameYDisplacement) / minScale;
		game->Input.ml[1] = game->Input.ml[0];
		game->Input.mm[1] = game->Input.mm[0];
		game->Input.mr[1] = game->Input.mr[0];
		game->Input.ml[0] = mouseState & SDL_BUTTON_LEFT;
		game->Input.mm[0] = mouseState & SDL_BUTTON_MIDDLE;
		game->Input.mr[0] = mouseState & SDL_BUTTON_RIGHT;

		// Run the current level
		NymLevel newLevel = NYM_LEVEL_UPDATE_FUNCTIONS[game->level](game);

		// Draw the current level, setting up the backbuffer before hand
		vk2dRendererStartFrame((void*)VK2D_BLACK);
		vk2dRendererSetTarget(game->Core.backbuffer);
		vk2dRendererClear();
		NYM_LEVEL_DRAW_FUNCTIONS[game->level](game);

		// Draw the backbuffer to the screen
		vk2dRendererLockCameras(VK2D_DEFAULT_CAMERA);
		vk2dRendererSetTarget(VK2D_TARGET_SCREEN);
		vk2dDrawTextureExt(game->Core.backbuffer, frameXDisplacement, frameYDisplacement, minScale, minScale, 0, 0, 0);
		vk2dRendererUnlockCameras();
		vk2dRendererEndFrame();

		// Handle switching levels/quitting
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
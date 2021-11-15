#define SDL_MAIN_HANDLED
#include "Nym/Game.h"

int main(int argc, const char *argv[]) {
	bool debug = false;
	for (int i = 1; i < argc; i++)
		if (strcmp(argv[i], "--debug"))
			debug = true;
	nymStart(debug);
	return 0;
}

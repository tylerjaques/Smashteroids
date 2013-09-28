#include "Game.h"

//Reminder - we made a 'windows application' not a console app.
//because of this we get no console, but instead the app expectes 'winmain' & signature
//instead of main.  Using sfml-main.lib we can get around this to have a standard main.
//there is no static or dynamic versions of sfml-main, just one for debug and release.
int main() {
	Game game;

	game.Run();

    return 0;
}
#include "Game.h"
#include <crtdbg.h>
//Reminder - we made a 'windows application' not a console app.
//because of this we get no console, but instead the app expectes 'winmain' & signature
//instead of main.  Using sfml-main.lib we can get around this to have a standard main.
//there is no static or dynamic versions of sfml-main, just one for debug and release.

int main() {

	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
    _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
    _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );

	Game game;

	game.Run();

	return 0;
}
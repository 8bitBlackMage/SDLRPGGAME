#include "Display.h"
#include "Globals.h"
//#include "Tilemaps.h"
#include "Events.h"
#include "Map.h"
#include "Sprite.h"
#include "Gamehandler.h"
#include "Player.h"
int Scale;
Display Graphics(Globals::Width,Globals::Height,&Scale);

EventHandler Loop;

int main(int argc, char* args[]) {
	//test objects (will be removed as game is finished) 


	Player mPlayer;
	mPlayer.ImgPath = "Player.png";
	mPlayer.init(&Graphics);
	GameEvents Game(&mPlayer,&Graphics);
	Game.loadNewMap("Test");
	while (Loop.isRunning()) {
		uint32_t startTicks = SDL_GetTicks();
		Graphics.clear();
		Game.GameLoop(&Loop.G_keycodes);
		Graphics.flip();
		Loop.Loop(&Graphics);
		uint32_t endTicks = SDL_GetTicks();
		uint32_t frametime = endTicks - startTicks;

		if (frametime < 1000 / 60) {

			SDL_Delay((1000 / 60) - (frametime));
		}
	}

	

	return 0;
}
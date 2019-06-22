#include "Display.h"
#include "Globals.h"
#include "Tilemaps.h"
#include "Events.h"
#include "Map.h"
#include "Sprite.h"
#include "Gamehandler.h"
int Scale;
Display Graphics(Globals::Width,Globals::Height,&Scale);
TileMap Tile;

EventHandler Loop;

int main(int argc, char* args[]) {
	//test objects (will be removed as game is finished) 
	//SDL_Texture * IMG = Graphics.LoadMedia("TileSet.png");
	//Tile.load("tiles.xml");
	Player mPlayer;
	mPlayer.ImgPath = "Player.png";
	mPlayer.init(&Graphics);
	GameEvents Game(&mPlayer,&Graphics);
	TileLayer Background(1920,1080);
//	Map test("maps/Test.tmx",&Graphics);
	Game.loadNewMap("Test");
	while (Loop.isRunning()) {
		//runs the game loop
		uint32_t startTicks = SDL_GetTicks();
		Graphics.clear();
//		test.Draw();
		Game.GameLoop(&Loop.keycodes);
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
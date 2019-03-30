#include "Display.h"
#include "Tilemaps.h"
#include "Events.h"
#include "Map.h"
#include "Sprite.h"
Display Graphics(1024, 768);
TileMap Tile;

EventHandler Loop;

int main(int argc, char* args[]) {
	
	//SDL_Texture * IMG = Graphics.LoadMedia("TileSet.png");
	//Tile.load("tiles.xml");
	Player Player("Player.png",Graphics);	
	SpriteSheets overworld("TileSet.PNG",Graphics.getRender());
	TileLayer Background(1920,1080);
	Map test("maps/test.tmx","TileSet.png");
	while (true) {
		Graphics.clear();
		test.Draw(&Graphics, overworld);
		Player.draw();
		Player.update();

		Graphics.flip();
		Loop.Loop(&Graphics);
	}

	

	return 0;
}
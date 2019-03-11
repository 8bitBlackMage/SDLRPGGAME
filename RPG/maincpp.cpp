#include "Display.h"
#include "Tilemaps.h"
#include "Events.h"
#include "Map.h"
Display Graphics(1024, 768);
TileMap Tile;
EventHandler Loop;
int main(int argc, char* args[]) {
	
	//SDL_Texture * IMG = Graphics.LoadMedia("TileSet.png");
	//Tile.load("tiles.xml");
	
	SpriteSheets overworld("TileSet.PNG",Graphics.getRender());
	TileLayer Background(1920,1080);
	Map test("maps/test.tmx","TileSet.png");
	int i = 0;
	while (true) {
		Graphics.clear();
	//	for (int x = 0; x < 32; x++) {
	//		for (int y = 0; y < 24; y++) {
					//Graphics.drawTextures(10, overworld, &Background, x, y);
				test.Draw(&Graphics, overworld);
	//		}
	//	}
		Graphics.flip();
		Loop.Loop(&Graphics);
		i++;
	}

	

	return 0;
}
#pragma once
//defines consts for game 

namespace Globals {
	const int Width = 1024;
	const int Height = 768;
	const int TScale = 64;
	const int FPS = 60;
	const int tilesX = 10;
	const int tilesY = 8;



}

struct CollisionBool {
	bool top = false;
	bool bottom = false;
	bool left = false ;
	bool right = false;
	void reset() {
		top = false;
		bottom = false;
		left = false;
		right = false;
	}
};





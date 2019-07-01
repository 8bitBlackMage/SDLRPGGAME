#pragma once
#include "SDL.h"
#include "Globals.h"
#include <vector>
//this file holds all the classes for the various layer types 


//master layer object exists only for iheretence use, do not call, has no storage
class layer {
public:
	layer() {}

	virtual void draw() = 0;
	virtual void update() = 0;
	int M_layer;
};

class TileLayer
{
	TileLayer() {}
	TileLayer(int w, int h) {
		Tiles.resize(h);
		GIDs.resize(h);
		for (int i = 0; i < h; i++) {
			Tiles[i].resize(w);
			GIDs[i].resize(w);

		}
		for (int mh = 0; mh < h; mh++) {
			for (int mw = 0; mw < w; mw++) {
				Tiles.at(mh).at(mw).w = Globals::TScale;
				Tiles.at(mh).at(mw).h = Globals::TScale;
				Tiles.at(mh).at(mw).x = (mw * Globals::TScale);
				Tiles.at(mh).at(mw).y = (mh * Globals::TScale);

			}

		}
	}
	int layer;
	std::vector<std::vector<SDL_Rect>>Tiles;
	std::vector<std::vector<__int8>>GIDs;
	std::vector<std::vector<bool>>passable;
};

class SpriteLayer {
	int layer;
	std::vector<SDL_Rect>Sprites;

};
#pragma once
#include "SDL.h"
#include "DIsplay.h"
#include "Tilemaps.h"




struct SpriteSheets
{
	SpriteSheets(std::string imgPath, SDL_Renderer*Ren)
	{
		SDL_Surface * tmp;

		//loads bitmap file from 
		tmp = IMG_Load(imgPath.c_str());
		Map.AutoLoad(tmp);
		Texture = SDL_CreateTextureFromSurface(Ren, tmp);
		SDL_FreeSurface(tmp);

	}
	SDL_Texture* Texture;
	TileMap Map;

};

struct TileLayer
{
	TileLayer(int w, int h) {
		Tiles.resize(h);
		GIDs.resize(h);
		for (int i = 0; i < h; i++) {
			Tiles[i].resize(w);
			GIDs[i].resize(w);

		}
		for (int mh = 0; mh < h; mh++) {
			for (int mw = 0; mw < w; mw++) {
				Tiles.at(mh).at(mw).w = 32;
				Tiles.at(mh).at(mw).h = 32;
				Tiles.at(mh).at(mw).x = (mh * 32);
				Tiles.at(mh).at(mw).y = (mw * 32);

			}

		}
	}
	int layer;
	std::vector<std::vector<SDL_Rect>>Tiles;
	std::vector<std::vector<int>>GIDs;
};
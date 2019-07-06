#pragma once
#include "SDL.h"
#include "Globals.h"
#include "Tileset.h"
#include <vector>
//this file holds all the classes for the various layer types 


//master layer object exists only for iheretence use, do not call, has no storage
class layer {
public:
	layer() {}

	virtual void draw() = 0;
	virtual void update() = 0;
	Display * M_graphics;
	__int8 M_layertype;
	int M_layer;
};

class TileLayer : public layer
{
public:
	TileLayer() {}
	TileLayer(int w, int h, Display * graphics) {
		M_layertype = 1;
		M_graphics = (graphics);
		M_Tiles.resize(h);
		M_GIDs.resize(h);
		for (int i = 0; i < h; i++) {
			M_Tiles[i].resize(w);
			M_GIDs[i].resize(w);

		}
		for (int mh = 0; mh < h; mh++) {
			for (int mw = 0; mw < w; mw++) {
				M_Tiles.at(mh).at(mw).w = Globals::TScale;
				M_Tiles.at(mh).at(mw).h = Globals::TScale;
				M_Tiles.at(mh).at(mw).x = (mw * Globals::TScale);
				M_Tiles.at(mh).at(mw).y = (mh * Globals::TScale);

			}

		}
	}
	
	void draw() override
	{
		for (int y = 0; y < (M_graphics->M_ScreenHeight / Globals::TScale); y++) {

			for (int x = 0; x < (M_graphics->M_ScreenWidth / Globals::TScale); x++) {

				SDL_RenderCopy(M_graphics->getRender(), M_Tilesets[0]->getImage(), &M_Tilesets[0]->getSrcRect(M_GIDs[y + M_graphics->G_ScrollY][x + M_graphics->G_ScrollX]), &M_Tiles.at(y).at(x));
				
			}
		}
	}
	void update() override {

	}
	
	void getTilesets(std::vector<Tileset*> inputTileset) {
		M_Tilesets = inputTileset;
	}

	std::vector<std::vector<SDL_Rect>>M_Tiles;
	std::vector<std::vector<__int8>>M_GIDs;
	std::vector<Tileset*>M_Tilesets;
};

class SpriteLayer : public layer {
public:
	SpriteLayer(){}

	SpriteLayer(Display * graphcs) {
		M_graphics = graphcs;
		M_layertype = 2;
	}
	void draw() override {
		for (int i = 0; i < spritecount; i++) {
			SDL_RenderCopy(M_graphics->getRender(),Spriteimages[i]->M_Texture, &Spriteimages[i]->M_sheetparts[Spriteimages[i]->M_currentSheetPart] ,&Sprites[i]);
		}
	}
	void update() override {

	}

	
	std::vector<SDL_Rect>Sprites;
	std::vector<image*>Spriteimages;
	int spritecount;
};


class collisionLayer: public  layer{
public:
	collisionLayer() {
		M_layertype = 3;
	}

	void draw() override {

	}

	void generateTileCollisionMap(TileLayer * Layer)
	{
		for (int x = 0; x < Layer->M_GIDs.size(); x++) {
			for (int y = 0; y < Layer->M_GIDs[x].size(); y++) {
				if (Layer->M_Tilesets[0]->getPassible(Layer->M_GIDs[x][y]) == true) {
					M_CollisionTiles.push_back(Layer->M_Tiles[x][y]);
				}

			}
		}
	}

	void generateSpriteCollisionMap(SpriteLayer * Layer)
	{
		M_CollisionSprites = Layer->Sprites;
	}

	void update() override {

	}
	std::vector<SDL_Rect>M_CollisionTiles;
	std::vector<SDL_Rect>M_CollisionSprites;
};
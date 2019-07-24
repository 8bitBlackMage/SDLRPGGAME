#pragma once

#ifdef _WIN32

#include "SDL.h"
#endif //_Win32
#ifdef __linux__
#include <SDL2/SDL.h>
#endif // 



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
	int8_t M_layertype;
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
		if(M_GIDs.size() > 0){
		for (int y = 0; y < (M_graphics->M_ScreenHeight / Globals::TScale); y++) {

			for (int x = 0; x < (M_graphics->M_ScreenWidth / Globals::TScale); x++) {
				SDL_Rect srcRect = M_Tilesets[0]->getSrcRect(M_GIDs[y + M_graphics->G_ScrollY][x + M_graphics->G_ScrollX]);
				SDL_RenderCopy(M_graphics->getRender(), M_Tilesets[0]->getImage(), &srcRect, &M_Tiles.at(y).at(x));
				
			}
		}
		}
	}
	void update() override {

	}
	
	void getTilesets(std::vector<Tileset*> inputTileset) {
		M_Tilesets = inputTileset;
	}

	std::vector<std::vector<SDL_Rect>>M_Tiles;
	std::vector<std::vector<int8_t>>M_GIDs;
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
			SDL_Rect DEST = Sprites[i];
			if (i == 0) {
			
					DEST.x -= M_graphics->G_ScrollX * Globals::TScale;
					DEST.y -= M_graphics->G_ScrollY* Globals::TScale;
				
			}

			if (Spriteimages[i] != nullptr) {
				SDL_RenderCopy(M_graphics->getRender(), Spriteimages[i]->M_Texture, &Spriteimages[i]->M_sheetparts[Spriteimages[i]->M_currentSheetPart], &DEST);
			}
		}
	}
	void update() override {
		return;
	}

	
	std::vector<SDL_Rect>Sprites;
	std::vector<SDL_Rect>ActualLocations;
	std::vector<image*>Spriteimages;
	int spritecount;
};

class collisionLayer: public  layer{
public:
	collisionLayer(Display * Graphics) {
		M_graphics = Graphics;
		M_layertype = 3;
	}

	void draw() override {
		if (Globals::testMode == true) {
			for (int i = 0; i < M_CollisionTiles.size(); i++)
			{
				SDL_Rect TMPRECT = M_CollisionTiles.at(i);
				TMPRECT.x -= M_graphics->G_ScrollX * Globals::TScale;
				TMPRECT.y -= M_graphics->G_ScrollY * Globals::TScale;
				SDL_SetRenderDrawColor(M_graphics->getRender(), 255, 255, 255, 25);
				SDL_RenderFillRect(M_graphics->getRender(), &TMPRECT);
				SDL_RenderDrawRect(M_graphics->getRender(), &TMPRECT);
			}
		}
	}
	void generateTileCollisionMap(TileLayer * Layer)
	{
		for (int x = 0; x < Layer->M_GIDs.size(); x++) {
			for (int y = 0; y < Layer->M_GIDs[x].size(); y++) {
				if (Layer->M_Tilesets[0]->getPassible(Layer->M_GIDs[x][y]) == false) {
					M_CollisionTiles.push_back(Layer->M_Tiles[x][y]);
				}

			}
		}
	}

	void generateSpriteCollisionMap(SpriteLayer * Layer)
	{
		M_CollisionSprites = Layer->ActualLocations;
		M_CollisionData.resize(M_CollisionSprites.size());
	}

	void update() override 
	{


		for (int i = 0; i < M_CollisionSprites.size(); i++) {
			M_CollisionData.at(i).reset();


			int leftA = M_CollisionSprites.at(i).x;
			int rightA = M_CollisionSprites.at(i).x + M_CollisionSprites.at(i).w ;
			int topA = M_CollisionSprites.at(i).y;
			int bottomA = M_CollisionSprites.at(i).y + M_CollisionSprites.at(i).h;

			for (int n = 0; n < M_CollisionTiles.size(); n++)
			{
			//	std::cout << n << std::endl;
				int leftB = M_CollisionTiles.at(n).x;
				int rightB = M_CollisionTiles.at(n).x + M_CollisionTiles.at(n).w;
				int topB = M_CollisionTiles.at(n).y;
				int bottomB = M_CollisionTiles.at(n).y + M_CollisionTiles.at(n).h;
			
				if (M_CollisionTiles.at(n).x == M_CollisionSprites.at(i).x) {
					if (topA == bottomB) {
						M_CollisionData.at(i).top = true;
					}
					if (bottomA == topB) {
						M_CollisionData.at(i).bottom = true;
					}
				}
				if (M_CollisionTiles.at(n).y == M_CollisionSprites.at(i).y) {
				
					if (leftA == rightB) {
						M_CollisionData.at(i).left = true;
					}
					if (rightA == leftB) {
						M_CollisionData.at(i).right = true;
					}
				}
				if (M_CollisionTiles.at(n).x == M_CollisionSprites.at(i).x) {

					if (leftA == rightB) {
						M_CollisionData.at(i).left = true;
					}
					if (rightA == leftB) {
						M_CollisionData.at(i).right = true;
					}
				}
				if (M_CollisionTiles.at(n).y == M_CollisionSprites.at(i).y) {
					if (topA == bottomB) {
						M_CollisionData.at(i).top = true;
					}
					if (bottomA == topB) {
						M_CollisionData.at(i).bottom = true;
					}
				}



			}	

		}
	}

	std::vector<CollisionBool> pushCollisionData() {
		return M_CollisionData;
	}
	std::vector<CollisionBool> M_CollisionData;
	std::vector<SDL_Rect>M_CollisionTiles;
	std::vector<SDL_Rect>M_CollisionSprites;
};


class UiLayer : public layer {
//layer that draws UI elements, such as pause menus, text boxes, and battle infomation
	void draw() override{}
	void update() override{}




};
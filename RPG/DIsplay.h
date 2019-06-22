#pragma once
#include "Globals.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
#include "Tilemaps.h"

struct TileLayer
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
	std::vector<std::vector<int>>GIDs;
};

struct SpriteSheets
{
	SpriteSheets(std::string imgPath, SDL_Renderer*Ren)
	{
		load(imgPath, Ren);
	}
	void load(std::string imgPath, SDL_Renderer*Ren) {
		SDL_Surface * tmp;

		//loads bitmap file from 
		tmp = IMG_Load(imgPath.c_str());
		Map.AutoLoad(tmp);
		Texture = SDL_CreateTextureFromSurface(Ren, tmp);
		SDL_FreeSurface(tmp);

	}
	SpriteSheets() {}
	SDL_Texture* Texture;
	TileMap Map;

};



class Display
{
public:
	Display(int ScreenWidth, int ScreenHeight, int* scale) : mScreenWidth(ScreenWidth), mScreenHeight(ScreenHeight)
	{
		DisplayScale(mScreenWidth,mScreenHeight);
		//standard constructor, initialises display, offscreen rendering
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cout << "error" << std::endl;
		}
		else {
			mWin = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mScreenWidth, mScreenHeight, SDL_WINDOW_SHOWN);
			ScrollboxW = mScreenWidth / 2;
			ScrollBoxH = mScreenHeight / 2;
			ScrollboxX = mScreenWidth - ScrollboxW;
			ScrollboxY = mScreenHeight - ScrollboxY;
			if (mWin == NULL) {

				std::cout << "error" << std::endl;

			}

			mRen = SDL_CreateRenderer(mWin, -1, SDL_RENDERER_ACCELERATED);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				std::cout << "error" << std::endl;
			}

		}
	}
	~Display() {
		//deconstructor to free memory
		SDL_DestroyWindow(mWin);
		SDL_DestroyRenderer(mRen);
		mWin = NULL;
		mRen = NULL;
		IMG_Quit();
		SDL_Quit();
	}
	SDL_Texture * LoadMedia(std::string path)
	{
		SDL_Surface * tmp;
		SDL_Texture * ret;
		//loads bitmap file from 
		tmp = IMG_Load(path.c_str());
		ret = SDL_CreateTextureFromSurface(mRen, tmp);
		SDL_FreeSurface(tmp);
		return ret;
	}

	void clear() {
		SDL_RenderClear(mRen);

	}
	void flip() {
		SDL_RenderPresent(mRen);
	}
	void drawTextures(int GID, SpriteSheets *sheet, TileLayer * Layer, int x, int y)
	{
		SDL_RenderCopy(mRen, sheet->Texture, &sheet->Map.getTile(GID), &Layer->Tiles.at(y).at(x));
	}
	void drawMobTexture(int GID, SpriteSheets sheet, int x, int y)
	{
		SDL_Rect DestRect = {x,y,Globals::TScale,Globals::TScale };

		SDL_RenderCopy(mRen, sheet.Texture, &sheet.Map.getTile(GID),&DestRect);
	}
	SDL_Renderer* getRender() {
		return mRen;
	}
	int mScreenScale, mWideoffset;
	int TileScale;
	int ScrollboxX, ScrollboxY, ScrollBoxH,ScrollboxW;
	int ScrollX;
	int ScrollY;
	int mScreenHeight, mScreenWidth;
private:
	void DisplayScale(int w, int h)
	{
		TileScale = h / 10;
	}

	

	SDL_Window * mWin;
	SDL_Renderer * mRen;
	

	bool mIsWidescreen;
	
};



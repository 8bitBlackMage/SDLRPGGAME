#pragma once
#include "Gobals.h"
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

struct Tile
{
	SDL_Rect IMGSRC;
	int GID;
	std::string name;

};

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
	SpriteSheets() {}
	SDL_Texture* Texture;
	TileMap Map;

};



class Display
{
public:
	Display(int ScreenWidth, int ScreenHeight) : mScreenWidth(ScreenWidth), mScreenHeight(ScreenHeight)
	{
		DisplayScale();
		//standard constructor, initialises display, offscreen rendering
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cout << "error" << std::endl;
		}
		else {
			mWin = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mScreenWidth, mScreenHeight, SDL_WINDOW_SHOWN);

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
	void drawTextures(int GID, SpriteSheets sheet, TileLayer * Layer, int x, int y)
	{
		SDL_RenderCopy(mRen, sheet.Texture, &sheet.Map.getTile(GID), &Layer->Tiles.at(x).at(y));
	}
	void drawMobTexture(int GID, SpriteSheets sheet, int x, int y)
	{
		SDL_Rect DestRect = {x,y,64,64};

		SDL_RenderCopy(mRen, sheet.Texture, &sheet.Map.getTile(GID),&DestRect);
	}
	SDL_Renderer* getRender() {
		return mRen;
	}
	int mScreenScale, mWideoffset;
private:
	void DisplayScale()
	{
		if (mIsWidescreen= true)
		{
			int adjustedw = mScreenWidth / 1.333333333333333333333;
			int TW = adjustedw /16;

			mWideoffset = (mScreenWidth - adjustedw) / 2;
			mScreenScale = TW;
		}
		else
		{
			int TW = mScreenWidth / 16;
			mScreenScale = TW;
		}





	}

	SDL_Window * mWin;
	SDL_Renderer * mRen;
	int mScreenHeight, mScreenWidth;
	bool mIsWidescreen;
	
};



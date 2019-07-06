#pragma once 
#include "DIsplay.h"
#include "Globals.h"
#include "Layers.h"
#include <array>
#include <string>

class Sprite {
public:

	Sprite(std::string imgPath, Display &Graphics):mGraphics(&Graphics)
	{
		Spriteimage.load(imgPath, mGraphics);
		Spriteimage.HandleImageset();
		x = 0;
		y = 0;
		location = new SDL_Rect{ x,y ,Globals::TScale,Globals::TScale };
		mGid = 1;
	}
	~Sprite(){}

	void addtolayer(SpriteLayer * layer)
	{
		location->x = x;
		location->y = y;
		std::cout << x << " " << y << std::endl;
		switch (facing) {

		case(left): {mGid = 4;
			break; }
		case(right): {mGid = 7;
			break; }
		case(up): {mGid = 10;
			break; }
		case(down): {
			mGid = 1;
			break;
		}
		}
		Spriteimage.M_currentSheetPart = mGid;
		layer->Spriteimages.push_back(&Spriteimage);
		layer->Sprites.push_back(*location);
		layer->spritecount++;
	}

	enum SpriteDirection {
		left, right, up, down, idle

	};
	SpriteDirection facing;
	int x, y;
protected:
	int  mGid;
	
private:
	
	image Spriteimage;
	SDL_Rect * location;
	Display * mGraphics;
};

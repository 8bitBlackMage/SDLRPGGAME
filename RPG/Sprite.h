#pragma once 
#include "Display.h"
#include "Globals.h"
#include "Layers.h"
#include <array>
#include <string>

class Sprite {
public:

	Sprite(std::string imgPath, Display &Graphics) :mGraphics(&Graphics)
	{
		Spriteimage = new image();
		Spriteimage->load(imgPath, mGraphics);
		Spriteimage->HandleImageset();
		x = 0;
		y = 0;
		AnimationLoc = new SDL_Rect{ x,y ,Globals::TScale,Globals::TScale };
		location = new SDL_Rect{ x,y ,Globals::TScale,Globals::TScale };
		mGid = 1;
	}
	Sprite(Display &Graphics) :mGraphics(&Graphics) {
		x = 0;
		y = 0;
		
		location = new SDL_Rect{ x,y ,Globals::TScale,Globals::TScale };
		
		mGid = 1;
	}
	~Sprite()
	{
		
		delete location;
		delete Spriteimage;
	
	}

	void setSpriteID(int ID) {
		SpriteID = ID;
	}
	void addtolayer(SpriteLayer * layer)
	{
		Moving = false;
		location->y = y;
		location->x = x;

		while (AnimationLoc->x != location->x) {
			Moving = true;

			if (mGraphics->M_scroll == true) {
				AnimationLoc->x = location->x;
			}
			if (mGraphics->M_scroll == false) {
				if (location->x < AnimationLoc->x) {
					AnimationLoc->x -= 8;
					break;
				}
				if (location->x > AnimationLoc->x) {
					AnimationLoc->x += 8;
					break;
				}
			}
		}
	while (AnimationLoc->y != location->y) {
		Moving = true;

		if (mGraphics->M_scroll == true) {
			AnimationLoc->y = location->y;
		}
		if (mGraphics->M_scroll == false) {
			if (location->y < AnimationLoc->y) {
				AnimationLoc->y -= 8;
				break;
			}
			if (location->y > AnimationLoc->y) {
				AnimationLoc->y += 8;
				break;
			}
		}
	}



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

		if (Spriteimage != nullptr) {
			Spriteimage->M_currentSheetPart = mGid;
			layer->Spriteimages.at(SpriteID) = Spriteimage;
			layer->Sprites.at(SpriteID) = *AnimationLoc;
			layer->ActualLocations.at(SpriteID) = *location;

		}





	}

	enum SpriteDirection {
		left, right, up, down, idle

	};
	SpriteDirection facing;
	int x, y;

	int SpriteID;
	bool Moving;
	SDL_Rect  * AnimationLoc;
	SDL_Rect * location;
protected:
	int  mGid;
	
private:
	
	image * Spriteimage;
	

	Display * mGraphics;
};

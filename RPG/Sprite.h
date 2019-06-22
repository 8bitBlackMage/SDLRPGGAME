#pragma once 
#include "DIsplay.h"
#include "Globals.h"
#include <array>
#include <string>

class Sprite {
public:

	Sprite(std::string imgPath, Display &Graphics):Sheet(imgPath,Graphics.getRender()),mGraphics(&Graphics)
	{
		x = 0;
		y = 0;
		mGid = 1;
	}
	~Sprite(){}
	virtual void update()
	{

	}
	void draw()
	{
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
		mGraphics->drawMobTexture(mGid, Sheet, x, y);
	}
	enum SpriteDirection {
		left, right, up, down, idle

	};
	SpriteDirection facing;
	int x, y;
protected:
	int  mGid;
	
private:
	
	SpriteSheets Sheet;
	
	Display * mGraphics;
};


//class Player : public Sprite {
//public:
//	Player(std::string imgPath, Display &Graphics):Sprite(imgPath, Graphics){
//	}
//	void update(std::array<bool, SDL_NUM_SCANCODES> * keycodes)
//	{
//
//	move(keycodes);
//	
//
//	}
//	void move( std::array<bool, SDL_NUM_SCANCODES>  *keycodes)
//	{
//	if (keycodes->at(SDL_SCANCODE_LEFT) == true) {
//		x -= Globals::TScale;
//		facing = Sprite::left;
//	}
//	if (keycodes->at(SDL_SCANCODE_RIGHT) == true) {
//		x += Globals::TScale;
//		facing = Sprite::right;
//	}
//	if (keycodes->at(SDL_SCANCODE_UP) == true) {
//		y -= Globals::TScale;
//		facing = Sprite::up;
//	}
//	if (keycodes->at(SDL_SCANCODE_DOWN) == true) {
//		y += Globals::TScale;
//		facing = Sprite::down;
//	}
//	}
//	void boundChecker() {
//		if (x > Globals::Width) {
//			std::cout << "LINE" << std::endl;
//		}
//	}
//
//
//
//private:
//
//};
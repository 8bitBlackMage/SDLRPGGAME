#pragma once 
#include "DIsplay.h"
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
		mGraphics->drawMobTexture(mGid, Sheet, x, y);
	}

protected:
	int x, y, mGid;
private:
	enum Spritesheet {

	};
	SpriteSheets Sheet;
	
	Display * mGraphics;
};


class Player : public Sprite {
public:
	Player(std::string imgPath, Display &Graphics):Sprite(imgPath, Graphics){
	}
	void update(std::map<SDL_Scancode, bool> * keycodes)
	{
	move(keycodes);
	}
	void move(std::map<SDL_Scancode, bool> * keycodes)
	{
	if (keycodes->at(SDL_SCANCODE_LEFT) == true) {
		x--;
	}
	if (keycodes->at(SDL_SCANCODE_RIGHT) == true) {
		x++;
	}
	if (keycodes->at(SDL_SCANCODE_UP) == true) {
		y++;
	}
	if (keycodes->at(SDL_SCANCODE_DOWN) == true) {
		y--;
	}
	}

};
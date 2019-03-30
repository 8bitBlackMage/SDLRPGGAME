#pragma once 
#include "DIsplay.h"
#include <string>

class Sprite {
public:
	Sprite(std::string imgPath, Display &Graphics):Sheet(imgPath,Graphics.getRender()),mGraphics(&Graphics)
	{
		x = 0;
		y = 0;
	}
	~Sprite(){}
	virtual void update()
	{

	}
	void draw()
	{
		mGraphics->drawMobTexture(1, Sheet, x, y);
	}

protected:
	int x, y;
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
	void update() {
		x++;
	}



};
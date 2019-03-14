#pragma once 
#include "DIsplay.h"


class Sprite {
public:
	Sprite(std::string imgPath, Display Graphics):Sheet(imgPath,Graphics.getRender()),mGraphics(&Graphics)
	{
	}
	~Sprite(){}
	virtual void update()
	{

	}
	void draw()
	{
		mGraphics->drawMobTexture(0, Sheet, x, y);
	}

private:
	enum Spritesheet {

	};
	SpriteSheets Sheet;
	int x, y;
	Display * mGraphics;
};


class Player : public Sprite {

};
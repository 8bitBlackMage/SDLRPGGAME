#pragma once 
#include "DIsplay.h"


class Sprite {
public:
	Sprite(std::string imgPath, Display Graphics):Sheet(imgPath,Graphics.getRender()),mGraphics(&Graphics)
	{
	}
	Sprite(bool test, Display Graphics):mGraphics(&Graphics)
	{
	


	}
	~Sprite(){}
	virtual void update()
	{

	}
	void draw(Display *Graphics)
	{
		
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
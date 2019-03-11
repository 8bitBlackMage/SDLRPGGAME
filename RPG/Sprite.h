#pragma once 
#include "DIsplay.h"


class Sprite {
public:
	Sprite(std::string imgPath, Display Graphics):Sheet(imgPath,Graphics.getRender())
	{
	}

	~Sprite(){}
	virtual void update()
	{

	}
	void draw(Display *Graphics)
	{
//		Graphics->drawTextures();
	}

private:
	enum Spritesheet {

	};
	SpriteSheets Sheet;
	int x, y;
};


class Player : public Sprite {

};
#pragma once
#include "Sprite.h"

class GameObject {
	// master gameobject, all others inheret from this 
public:
	GameObject(){}
	virtual void init(Display* graph) = 0;
	virtual void update() = 0;
	virtual void onCollide() = 0;
	virtual void draw(Display * Graphics) = 0;
	void imageload() {
		OverWorldImage = new Sprite(ImgPath ,*graphics);
	}
	int x; 
	int y;
	int w;
	int h;
	Display * graphics;
	Sprite * OverWorldImage;
	std::string ImgPath;
};

class MoveableGameObject : public GameObject {
	//base class for any moveable objects, all NPCs inherit from this
public:
	virtual void move() = 0;
	 


};

class NPCObject: public MoveableGameObject
{
public:
	NPCObject() {}
	//all NPC characters are built from this object, contains all interaction text and other code for interaction

	void init(Display* graph) override
	{

	}

	void update() override
	{
	}
	void move() override
	{

	}
	void draw(Display * Graphics) override
	{

	}

	void onCollide() override
	{

	}

	bool hasItem;
	
};

class Player : public MoveableGameObject {
	//the player class is created once and contains all the code for the player, controls stats, intventory etc
public:
	Player() {

	}
	void init(Display* graph) override {
		graphics = graph;
		imageload();
	}
	void onCollide() override {

	}
	void update() override
	{
		if (OverWorldImage->x == x && OverWorldImage->y == y) {
			move();
		}

	}
	void move() override
	{
		if (m_keycodes->at(SDL_SCANCODE_LEFT) == true)
		{
				x -= Globals::TScale;
				OverWorldImage->facing = Sprite::left;
		}
		if (m_keycodes->at(SDL_SCANCODE_RIGHT) == true) {
					x += Globals::TScale;
					OverWorldImage->facing = Sprite::right;
		}
		if (m_keycodes->at(SDL_SCANCODE_UP) == true)
		{
					y -= Globals::TScale;
					OverWorldImage->facing = Sprite::up;
		}
		if (m_keycodes->at(SDL_SCANCODE_DOWN) == true)
		{
					y += Globals::TScale;
					OverWorldImage->facing = Sprite::down;
		}

	}
	void draw(Display * Graphics) override
	{
		//OverWorldImage->x = x;
		//OverWorldImage->y = y;
		while (OverWorldImage->x != x) {
			if (OverWorldImage->x < x) {
				OverWorldImage->x += 8;
				break;
			}
			if (OverWorldImage->x > x) {
				OverWorldImage->x -= 8;
				break;
			}
		}
		while (OverWorldImage->y != y) {
			if (OverWorldImage->y < y) {
				OverWorldImage->y += 8;
				break;
			}
			if (OverWorldImage->y > y) {
				OverWorldImage->y -= 8 ;
				break;
			}
		}


		OverWorldImage->draw();
	}


	void passScanCodes(std::array<bool, SDL_NUM_SCANCODES>  *keycodes) {
		m_keycodes = keycodes;
	}

private: 
	std::array<bool, SDL_NUM_SCANCODES>  *m_keycodes;
	int mGid;
};

class Door : public GameObject {
public:
	Door() 
	{

	}
	void init(Display* graph) override 	{

	}
	//handles all enterences and exits, transistions between maps 
	void update() override {

	}

	void onCollide()override {

	}

	void draw(Display * Graphics) override {
	
	}
	int destX;
	int destY;
	std::string mapname;

};
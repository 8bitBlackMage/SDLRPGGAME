#pragma once
#include "GameObject.h"
#include  "Map.h"

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
		if (OverWorldImage->x == RelativeX && OverWorldImage->y == RelativeY) {
			move();
		//	Collisions = mMap->getcollision(x,y);
			std::cout << x << " " << y << std::endl;
		}
		Scrolling();  
	
	}
	void move() override
	{
		if (m_keycodes->at(SDL_SCANCODE_LEFT) == true)
		{
			if(Collisions[0] == false)
				x -= Globals::TScale;
				OverWorldImage->facing = Sprite::left;
			

		}
		if (m_keycodes->at(SDL_SCANCODE_RIGHT) == true) {
			if(Collisions[1] == false)
				x += Globals::TScale;
				OverWorldImage->facing = Sprite::right;
			
		}
		if (m_keycodes->at(SDL_SCANCODE_UP) == true)
		{
			if(Collisions[2] == false)
				y -= Globals::TScale;
				OverWorldImage->facing = Sprite::up;
			
		}
		if (m_keycodes->at(SDL_SCANCODE_DOWN) == true)
		{
			if(Collisions[3] == false)
				y += Globals::TScale;
				OverWorldImage->facing = Sprite::down;
			
		}
		
	}
	void AddToLayer(SpriteLayer * layer) override
	{

			//smooth moving
			while (OverWorldImage->x != RelativeX) {
				if (OverWorldImage->x < RelativeX) {
					OverWorldImage->x += 8;
					break;
				}
				if (OverWorldImage->x > RelativeX) {
					OverWorldImage->x -= 8;
					break;
				}
			}
			while (OverWorldImage->y != RelativeY) {
				if (OverWorldImage->y < RelativeY) {
					OverWorldImage->y += 8;
					break;
				}
				if (OverWorldImage->y > RelativeY) {
					OverWorldImage->y -= 8;
					break;
				}
			}

		
			OverWorldImage->addtolayer(layer);
	}
	void Scrolling() {
		if (x == graphics->G_FScrollX && (graphics->G_FScrollX / Globals::TScale) < (graphics->mapSizeX - graphics->G_ScrollXoffset)) {
			graphics->G_ScrollX++;
			graphics->G_FScrollX += Globals::TScale;
			graphics->G_BScrollX += Globals::TScale;
			std::cout << (graphics->G_FScrollX / 64 )<< std::endl << graphics->G_BScrollX / 64 << std::endl;
			
		}
		if (x == (graphics->G_BScrollX ) && graphics->G_ScrollX != 0) {
			graphics->G_FScrollX -= Globals::TScale;
			graphics->G_BScrollX -= Globals::TScale;
			graphics->G_ScrollX--;
		}
		if (y == graphics->G_FScrollY && (graphics->G_FScrollY / Globals::TScale) < (graphics->mapSizeY - graphics->G_ScrollYoffset))  {

			
			graphics->G_FScrollY += Globals::TScale;
			graphics->G_BScrollY += Globals::TScale;
			graphics->G_ScrollY++;
		}
		if (y == (graphics->G_BScrollY ) && graphics->G_ScrollY != 0) {
			graphics->G_FScrollY -= Globals::TScale;
			graphics->G_BScrollY -= Globals::TScale;
			graphics->G_ScrollY--;
		}
		getRelative();
	}
	void getRelative() {
		RelativeX = x - graphics->G_ScrollX * Globals::TScale;
		RelativeY = y - graphics->G_ScrollY * Globals::TScale;
	}

	void passScanCodes(std::array<bool, SDL_NUM_SCANCODES>  *G_keycodes) {
		m_keycodes = G_keycodes;
	}
	void getMap(Map * data) {
		mMap = data;
	}





private:
	Map * mMap;
	std::array<bool, 4>Collisions;
	std::array<bool, SDL_NUM_SCANCODES>  *m_keycodes;
	int mGid;
	int RelativeX, RelativeY;
	
};
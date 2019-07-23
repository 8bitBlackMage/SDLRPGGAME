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
		std::cout << OverWorldImage->Moving << std::endl;
		if (OverWorldImage->Moving == false) {
			move();
		
		}
		Scrolling();  
	
	}
	void move() override
	{
		std::cout << CollsionData.left << " " << CollsionData.right << " " << CollsionData.top << " " << CollsionData.bottom << std::endl;
 		if (m_keycodes->at(SDL_SCANCODE_LEFT) == true)
		{
			if(CollsionData.left == false)
				x -= Globals::TScale;
				OverWorldImage->facing = Sprite::left;
			

		}
		if (m_keycodes->at(SDL_SCANCODE_RIGHT) == true) {
			if(CollsionData.right == false)
				x += Globals::TScale;
				OverWorldImage->facing = Sprite::right;
			
		}
		if (m_keycodes->at(SDL_SCANCODE_UP) == true)
		{
			if(CollsionData.top == false)
				y -= Globals::TScale;
				OverWorldImage->facing = Sprite::up;
			
		}
		if (m_keycodes->at(SDL_SCANCODE_DOWN) == true)
		{
			if(CollsionData.bottom == false)
				y += Globals::TScale;
				OverWorldImage->facing = Sprite::down;
			
		}
		
	}
	void AddToLayer(SpriteLayer * layer) override
	{
		OverWorldImage->x = x;
		OverWorldImage->y = y;
		OverWorldImage->addtolayer(layer);
	}
	void Scrolling() {
		graphics->M_scroll = false;
		if (x == graphics->G_FScrollX && (graphics->G_FScrollX / Globals::TScale) < (graphics->mapSizeX - graphics->G_ScrollXoffset)) {
			graphics->G_ScrollX++;
			graphics->G_FScrollX += Globals::TScale;
			graphics->G_BScrollX += Globals::TScale;
			graphics->M_scroll = true;
		}
		if (x == (graphics->G_BScrollX ) && graphics->G_ScrollX != 0) {
			graphics->G_FScrollX -= Globals::TScale;
			graphics->G_BScrollX -= Globals::TScale;
			graphics->G_ScrollX--;
			graphics->M_scroll = true;
		}
		if (y == graphics->G_FScrollY && (graphics->G_FScrollY / Globals::TScale) < (graphics->mapSizeY - graphics->G_ScrollYoffset))  {

			
			graphics->G_FScrollY += Globals::TScale;
			graphics->G_BScrollY += Globals::TScale;
			graphics->G_ScrollY++;
			graphics->M_scroll = true;
		}
		if (y == (graphics->G_BScrollY ) && graphics->G_ScrollY != 0) {
			graphics->G_FScrollY -= Globals::TScale;
			graphics->G_BScrollY -= Globals::TScale;
			graphics->G_ScrollY--;
			graphics->M_scroll = true;
		}
		
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

	
};
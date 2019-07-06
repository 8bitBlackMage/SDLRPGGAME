#pragma once
#include <vector>
#include "Sprite.h"
#include "GameObject.h"
#include "Map.h"
#include "Player.h"
#include "Layers.h"
#include "Tileset.h"


//master game object, holds the global Loop and draw functions along with lists of maps, objects and layers
class GameEvents
{
	//game events are not processed every frame, they are processed every 6 frames,
	//to reduce impact on the CPU and to keep gameplay at a reasonable speed 
public:
	//constructor filled with test code atm
	GameEvents(Player * mainPlayer, Display *Graphics)
	{
		M_MainPlayer = mainPlayer;
		M_MainPlayer->x = 256;
		M_MainPlayer->y = 256;
		M_graphics = Graphics;
		M_Vbuffer.push_back(new TileLayer());
		M_Vbuffer.push_back(new TileLayer());
		M_Vbuffer.push_back(new SpriteLayer());
		M_Vbuffer.push_back(new collisionLayer());
	}


	//loads new map into the vector of maps, handles the path generation and object processing 
	void loadNewMap(std::string MapName)
	{
	std::string path = "maps/" + MapName + ".tmx";
	
	M_maps.push_back(new Map(path,M_graphics));
	M_maps[0]->handleObjects(G_MapObjects);
	M_maps[0]->AddToLayer(&M_Vbuffer);

	M_MainPlayer->getMap(M_maps[0]);
	}

	//master Draw function will hold layer drawing code in future versions 
	void LoopDraw()
	{
		SpriteLayer  tmp = {M_graphics};
		
		M_MainPlayer->AddToLayer(&tmp);
		M_Vbuffer.at(2) = &tmp;
		for (int i = 0; i < M_Objects; i++)
		{
		//	MapObjects[i]->AddToLayer(m_graphics);

		}
		for (int i = 0; i < M_Vbuffer.size(); i++) {
			M_Vbuffer[i]->draw();
		}
	}
	void GameLoop(std::array<bool, SDL_NUM_SCANCODES>*Input)
	{
		LoopDraw();
		if (M_counter == 6) {
			M_MainPlayer->passScanCodes(Input);
			M_MainPlayer->update();
			for (int i = 0; i < M_Objects; i++)
			{
				G_MapObjects[i]->update();
			}
			M_counter = 0;
		}
		M_counter++;
	}





	std::vector<GameObject*>G_MapObjects;

private:
	std::vector<layer*>M_Vbuffer;

	Display * M_graphics;
	std::vector<Map*>M_maps;
	
	Player* M_MainPlayer;
	int M_Objects;
	__int8 M_counter = 0; 
};
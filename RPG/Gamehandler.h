#pragma once
#include <vector>
#include "Sprite.h"
#include "GameObject.h"
#include "Map.h"
class GameEvents
{
	//game events are not processed every frame, they are processed every 6 frames,
	//to reduce impact on the CPU and to keep gameplay at a reasonable speed 
public:
	GameEvents(Player * mainPlayer, Display *Graphics)
	{
		m_MainPlayer = mainPlayer;
		m_graphics = Graphics;
	}

	void loadNewMap(std::string MapName)
	{
	std::string path = "maps/" + MapName + ".tmx";
	
	maps.push_back(new Map(path,m_graphics));
	maps[0]->handleObjects(MapObjects);
	}

	void LoopDraw()
	{
		maps[0]->Draw();
		m_MainPlayer->draw(m_graphics);
		for (int i = 0; i < Objects; i++)
		{
			MapObjects[i]->draw(m_graphics);

		}
	}
	void GameLoop(std::array<bool, SDL_NUM_SCANCODES>*Input)
	{
		LoopDraw();
		if (counter == 6) {
			m_MainPlayer->passScanCodes(Input);
			m_MainPlayer->update();
			for (int i = 0; i < Objects; i++)
			{
				MapObjects[i]->update();
			}
			counter = 0;
		}
		counter++;
	}





	std::vector<GameObject*>MapObjects;

private:
	Display * m_graphics;
	std::vector<Map*>maps;
	Player* m_MainPlayer;
	int Objects;
	__int8 counter = 0; 
};
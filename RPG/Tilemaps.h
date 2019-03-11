#pragma once
#include "SDL.h"
#include "TinyXML/tinyxml2.h"
#include "Gobals.h"
#include <map>
using namespace tinyxml2;
class TileMap {
public:
	TileMap() {}
	~TileMap() {}
	void load(std::string path) {
		int GID = 1;
		XMLDocument Doc;
		Doc.LoadFile(path.c_str());
		int tmpGID;
		SDL_Rect tmpRect;
		//creates empty XML doc var 

		//loads data structure of the file into the doc
		XMLElement *Root = Doc.FirstChildElement("Document");
		if (Root != NULL) {
			//loads the <Document> element to load the rest of the information 
			XMLElement *Tile = Root->FirstChildElement();
			if (Tile != NULL)
			{
				while (Tile)
				{
					Tile->QueryIntAttribute("GID", &tmpGID);
					Tile->QueryIntAttribute("x",&tmpRect.x);
					Tile->QueryIntAttribute("y",&tmpRect.y);
					tmpRect.w = Globals::TScale;
					tmpRect.h = Globals::TScale;
					tmpRect.x = tmpRect.x * Globals::TScale;
					tmpRect.y = tmpRect.y * Globals::TScale;
					m_Tiles.insert(std::pair<int, SDL_Rect>(GID, tmpRect));
					GID++;
					Tile = Tile->NextSiblingElement();
				}
			}




		}
		
	}
	void AutoLoad(SDL_Surface *spritesheet)
	{
		int sizeW = spritesheet->w / 32;
		int sizeH = spritesheet->h / 32;
		int GID = 1;
		for (int y = 0; y < sizeH; y++) {
			for (int x = 0; x < sizeW; x++) {
				SDL_Rect tmpRect{x*32,y*32,32,32};
				m_Tiles.emplace(std::pair<int, SDL_Rect>(GID, tmpRect));
				GID++;
			}
	}
		m_numtiles = GID ;
	}
	SDL_Rect getTile(int GID)
	{
		if (GID > 0) {

			if (GID < m_numtiles) {
				return m_Tiles.at(GID);
			}
		}
	}
private:
	std::map< int, SDL_Rect> m_Tiles;
	int m_numtiles;
};


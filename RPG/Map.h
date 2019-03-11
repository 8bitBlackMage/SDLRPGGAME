#pragma once

#include "Tilemaps.h"
#include "DIsplay.h"
#include "SDL.h"
#include <sstream>
using namespace tinyxml2;
class Map {

public:
	Map(std::string Mappath, std::string IMG) {
		Load(Mappath);
	}

	void Load(std::string Mappath) {
		int i = 0;
		XMLDocument Doc;
		Doc.LoadFile(Mappath.c_str());
		XMLElement* MapNode = Doc.FirstChildElement();
		MapNode->QueryIntAttribute("width", &mWidth);
		MapNode->QueryIntAttribute("height", &mHeight);
		XMLElement* LayerNode = MapNode->FirstChildElement("layer");
		if (LayerNode != NULL) {
			while (LayerNode) {

				Layers.resize(i);
				XMLElement* Data = LayerNode->FirstChildElement();
				const char * tmpstring = Data->GetText();
			//	printf("%i\n", i);
			//	printf(tmpstring);
				TileLayer tmp{ mWidth,mHeight, };
				tmp.GIDs = CSV(tmpstring, mWidth,mHeight);
				Layers.push_back(tmp);
				LayerNode = LayerNode->NextSiblingElement();
				i++;
			}
		}
	}

	void Draw(Display * Graphics,SpriteSheets sheet) {
		
		
		for (int i = 0; i < Layers.size(); i++) {
			
			
			for (int y = 0; y < Layers[i].GIDs.size(); y++) {
				
				for (int x = 0; x < Layers[i].GIDs[y].size(); x++) {
				//	SDL_RenderCopy(Graphics->getRender(), sheet.Texture, &tileAtlas.getTile(Layers[i].GIDs[x][y]), &Layers[i].Tiles[x][y]);
					Graphics->drawTextures(Layers[i].GIDs[x][y], sheet, &Layers[i], x, y);
				//	printf("draw");
				}
			}
	}
	}

private:
	TileMap tileAtlas;
	std::vector<TileLayer>Layers;
	int mWidth, mHeight;
	std::vector<std::vector<int>> CSV(const char * CSVData, int w, int h) {
		std::vector<std::vector<int>> ret;
		std::istringstream tmp(CSVData);
		std::string line;
		int i;
		int x(0);
		int y(0);
		std::vector<int> vec;		
		while (!tmp.eof()){
			
			while (getline(tmp, line)) {

				std::stringstream tmpstring(line);
				if (!line.empty()) {
					for (x = 0; x < w; x++) {

						if (tmpstring.peek() == ',') {
							tmpstring.ignore();
						}
						tmpstring >> i;
						vec.push_back(i);

					}

					ret.push_back(vec);
					vec.clear();
					y++;
				}
			}
		}
		return ret;
	}



};
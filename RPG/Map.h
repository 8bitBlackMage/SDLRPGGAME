#pragma once

#include "Tilemaps.h"
#include "GameObject.h"
#include "DIsplay.h"
#include "SDL.h"
#include <sstream>
using namespace tinyxml2;
class Map {

public:
	Map(std::string Mappath, Display * Graphics) {
		graphics = Graphics;
		Load(Mappath);
	}

	void Load(std::string Mappath) {
		int i = 0;
		XMLDocument Doc;


		//handles all the map tile data 
		Doc.LoadFile(Mappath.c_str());
		XMLElement* MapNode = Doc.FirstChildElement();
		MapNode->QueryIntAttribute("width", &mWidth);
		MapNode->QueryIntAttribute("height", &mHeight);


		XMLElement * TilesetNode = MapNode->FirstChildElement("tileset");
		const char * tilepath;
		TilesetNode->QueryStringAttribute("source", &tilepath);
		loadTileset(tilepath);
		XMLElement* LayerNode = MapNode->FirstChildElement("layer");
		if (LayerNode != NULL) {
			while (LayerNode) {

				Layers.resize(i);
				TileLayer tmp{ mWidth,mHeight, };
				tmp.layer = LayerNode->IntAttribute("id");
				XMLElement* Data = LayerNode->FirstChildElement();
				const char * tmpstring = Data->GetText();

				
				tmp.GIDs = CSV(tmpstring, mWidth,mHeight);
				Layers.push_back(tmp);
				LayerNode = LayerNode->NextSiblingElement("layer");
				i++;
			}
		}
		XMLElement* ObjectGroupNode = MapNode->FirstChildElement("objectgroup");
		if (ObjectGroupNode != NULL) {
			printf("objects present \n");
			//generates a list of objects for each map
			XMLElement* Object = ObjectGroupNode->FirstChildElement("object");
			const char * ObjectType;
			Object->QueryStringAttribute("template",&ObjectType);
			std::string workableObjectType = ObjectType;
			if (workableObjectType == "MapTemplates/Door.tx") 
			{
				
				prepareDoorObject(Object);
				printf("door\n");
			}
			if (workableObjectType == "MapTemplates/NPC.tx")
			{
				prepareNPCObject(Object);
			}
			}
		printf("done");
	}

	void Draw() {
		
		
		for (int i = 0; i < Layers.size(); i++) {
			
			
			for (int y = 0; y < (graphics->mScreenHeight / Globals::TScale); y++) {
				
				for (int x = 0; x < (graphics->mScreenWidth / Globals::TScale); x++) {
				//	SDL_RenderCopy(Graphics->getRender(), sheet->Texture, &tileAtlas.getTile(Layers[i].GIDs[x][y]), &Layers[i].Tiles[x][y]);
				//	Graphics->drawTextures(Layers[i].GIDs[x][y], sheet, &Layers[i], x, y);
					graphics->drawTextures(Layers[i].GIDs[y + graphics->ScrollY][x + graphics->ScrollX], &Tileset, &Layers[i], x, y);
				//	printf("draw");
				}
			}
	}
	}
	void MoveCamera() {

	}
	void handleObjects(std::vector<GameObject*> container) {
		container = MapObjects;
	}
private:
	TileMap tileAtlas;  
	SpriteSheets  Tileset;
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
	std::vector<GameObject*>MapObjects;
	Display * graphics;

	void loadTileset(std::string TSXFILEPATH) {
		//automatically loads the  image from the tileset file of the map file

		std::string fullpath = "maps/" + TSXFILEPATH;
		XMLDocument tileDoc;
		
		tileDoc.LoadFile(fullpath.c_str());
		XMLElement * TilesetElement = tileDoc.FirstChildElement("tileset");
		XMLElement * SourceElement = TilesetElement->FirstChildElement("image");
		const char * CimgPath;
		SourceElement->QueryStringAttribute("source", &CimgPath);

		std::string imgPath = CimgPath;
		imgPath.erase(0, 3);
		Tileset.load(imgPath, graphics->getRender());
	}

	void prepareDoorObject(XMLElement * ObjectData) {
		Door enterance;
		ObjectData->QueryIntAttribute("x", &enterance.x);
		ObjectData->QueryIntAttribute("y", &enterance.y);
		XMLElement* ObjectProperties = ObjectData->FirstChildElement("properties")->FirstChildElement("property");
		while (ObjectProperties)
		{
			const char * name;
			ObjectProperties->QueryStringAttribute("name", &name);
			std::string workName = name;
			if (name == "DestY") {
				ObjectProperties->QueryIntAttribute("value", &enterance.destY);
			}
			if (name == "DestX") {
				ObjectProperties->QueryIntAttribute("value", &enterance.destX);
			}
			if (name == "mapName") {
				const char * mapName;
				ObjectProperties->QueryStringAttribute("value", &mapName);
				enterance.mapname = mapName;
			}

			ObjectProperties = ObjectProperties->NextSiblingElement("property");

		}
		MapObjects.push_back(new Door(enterance));

	}
	void prepareNPCObject(XMLElement * ObjectData)
	{
		NPCObject Character;
		ObjectData->QueryIntAttribute("x", &Character.x);
		ObjectData->QueryIntAttribute("y", &Character.y);
		XMLElement* ObjectProperties = ObjectData->FirstChildElement("properties")->FirstChildElement("property");
		while (ObjectProperties)
		{
			const char * name;
			ObjectProperties->QueryStringAttribute("name", &name);
			std::string workName = name;
			if (name == "Name") {
				const char * Name;
				ObjectProperties->QueryStringAttribute("value", &Name);
			}
			if (name == "hasItem") {
				ObjectProperties->QueryBoolAttribute("value", &Character.hasItem);
			}
			if (name == "spriteName") {
				const char * mapName;
				ObjectProperties->QueryStringAttribute("value", &mapName);
				Character.ImgPath = mapName;
			}

			ObjectProperties = ObjectProperties->NextSiblingElement("property");

		}
		MapObjects.push_back(new NPCObject(Character));
	}
	
};
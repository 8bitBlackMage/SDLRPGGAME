#pragma once

#include "Tileset.h"
#include "Layers.h"
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

	//std::array<bool,4> getcollision(int x, int y)
	//{
	//	int tileX = x / Globals::TScale;
	//	int tileY = y/  Globals::TScale;
	//	bool Left = false;
	//	bool Right = false;
	//	bool Up = false;
	//	bool Down = false;
	//	std::array<bool,4>Collision;
	//		//left 
	//	if (x <= 0) {
	//		Left = true;
	//	}
	//	if (Left == false) {
	//		Left = Layers[0].passable[tileX -1][tileY];
	//	}
	//	if (Left == false) {
	//		Left = Layers[1].passable[tileX - 1][tileY];
	//		}
	//	Collision[0] = Left;
	//		//right
	//	if (Right == false) {
	//		Right = Layers[0].passable[tileX + 1][tileY];
	//	}
	//	if (Right == false) {
	//		Right = Layers[1].passable[tileX + 1][tileY];
	//	}
	//	Collision[1] = Right;
	//		//up
	//	if (y <= 0) {
	//		Up = true;
	//	}
	//	if (Up == false) {
	//		Up = Layers[0].passable[tileX][tileY - 1];
	//	}
	//	if (Up == false) {
	//		Up = Layers[1].passable[tileX][tileY - 1];
	//	}
	//	Collision[2] = Up;
	//		//down
	//	if (Down == false) {
	//		Down = Layers[0].passable[tileX][tileY +1];
	//	}
	//	if (Down == false) {
	//		Down = Layers[1].passable[tileX][tileY + 1];
	//	}
	//	Collision[3] = Down;

	//		return Collision;
	//}




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
		int offset;
		TilesetNode->QueryStringAttribute("source", &tilepath);
		TilesetNode->QueryIntAttribute("firstgid", &offset);
		std::string Stilepath = tilepath;
		Tileset* FirstTileSet = new Tileset(Stilepath , offset, graphics);
		Tilesets.push_back(FirstTileSet);
		XMLElement* LayerNode = MapNode->FirstChildElement("layer");
		if (LayerNode != NULL) {
			while (LayerNode) {

				Layers.resize(i);
				TileLayer tmp{ mWidth,mHeight,graphics};
				tmp.M_layer = LayerNode->IntAttribute("id");
				XMLElement* Data = LayerNode->FirstChildElement();
				const char * tmpstring = Data->GetText();

				
				tmp.M_GIDs = CSV(tmpstring, mWidth,mHeight);
				
				Layers.push_back(tmp);
				LayerNode = LayerNode->NextSiblingElement("layer");
				i++;
			}
		}
		for (int i = 0; i < Layers.size(); i++) {
			Layers.at(i).getTilesets(Tilesets);
		}


		//generateCollisionmap();
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
	}

	void AddToLayer(std::vector<layer*>*Buffer) {
		for (int i = 0; i < Layers.size(); i++) {
			Buffer->at(i) = (&Layers.at(i));
			
		}
		

	}

	void handleObjects(std::vector<GameObject*>* container) {
		for (int i = 0; i < G_MapObjects.size(); i++) {
			container->push_back(G_MapObjects.at(i));
		}
	}
	int mWidth, mHeight;
	std::vector<TileLayer>Layers;
private:
	
	
	std::vector<bool>tileCollision;
	
	std::vector<std::vector<__int8>> CSV(const char * CSVData, int w, int h) {
		std::vector<std::vector<__int8>> ret;
		std::istringstream tmp(CSVData);
		std::string line;
		int i;
		int x(0);
		int y(0);
		std::vector<__int8> vec;		
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
	std::vector<Tileset*>Tilesets;
	std::vector<GameObject*>G_MapObjects;
	Display * graphics;
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
		G_MapObjects.push_back(new Door(enterance));

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
		G_MapObjects.push_back(new NPCObject(Character));
	}
	
};
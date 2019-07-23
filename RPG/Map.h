#pragma once

#include "Tileset.h"
#include "Layers.h"
#include "GameObject.h"
#include "Display.h"
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

		int ret = Doc.LoadFile(Mappath.c_str());
		if(ret != 0){
			
			std::cout << "error " << Doc.ErrorStr() <<std::endl;
			abort();
		}
		if(ret == 0 ){
		std::cout << ret << std::endl;
		XMLElement* MapNode = Doc.FirstChildElement();
		if(MapNode != NULL){
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
		Doc.Clear();
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
	
	std::vector<std::vector<int8_t>> CSV(const char * CSVData, int w, int h) {
		std::vector<std::vector<int8_t>> ret;
		std::istringstream tmp(CSVData);
		std::string line;
		int i;
		int x(0);
		int y(0);
		std::vector<int8_t> vec;		
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
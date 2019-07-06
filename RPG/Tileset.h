#pragma once
#include "Display.h"

#include <vector>
#include "TinyXML/tinyxml2.h"

using namespace tinyxml2;
class Tileset {
public:
// default constructor DO NOT USE  
Tileset(Display * graphics):mgraphics(graphics)
{

}

//standard constructor for tileset, use this one 
Tileset(std::string PathToTMXFile, int offset, Display * graphics):mgraphics(graphics),mGlobalOffset(offset) {
	loadTileset(PathToTMXFile);
}
//passes the path of the PNG file and hands it to the Img struct to be loaded into VRAM 
void Imgload(std::string imgpath) {
	mTilesetImage.load(imgpath, mgraphics);
	handleImgFile(mTilesetImage.M_Texture);
}
//master function called from Map file, handles the TMX files's XML headers and extracts the relevant infomation, to pass on to the rest of the functions
void loadTileset(std::string TSXFILEPATH) {
	
	std::string fullpath = "maps/" + TSXFILEPATH;
	XMLDocument tileDoc;

	tileDoc.LoadFile(fullpath.c_str());
	XMLElement * TilesetElement = tileDoc.FirstChildElement("tileset");
	XMLElement * SourceElement = TilesetElement->FirstChildElement("image");
	const char * CimgPath;
	SourceElement->QueryStringAttribute("source", &CimgPath);

	std::string imgPath = CimgPath;
	imgPath.erase(0, 3);
	Imgload(imgPath);
	XMLElement * TileElement = TilesetElement->FirstChildElement("tile");
	int i = 0;
	if (TileElement != NULL) {
		while (TileElement) {
			XMLElement *propertyElement = TileElement->FirstChildElement("properties")->FirstChildElement("property");;


			const char * name;
			propertyElement->QueryStringAttribute("name", &name);
			std::string workName = name;

			if (workName == "passable") {
				
				bool passable;
				propertyElement->QueryBoolAttribute("value", &passable);
				M_Passabe.push_back(passable);
				std::cout << i << std::endl;
				i++;
			}

			TileElement = TileElement->NextSiblingElement();

		}
	}
	tileDoc.Clear();
}


//handles the SDL_Rect genertaiton from the SDL_texture 
void handleImgFile(SDL_Texture *spritesheet)
{
	if (spritesheet != nullptr) {
		int sizeW;
		int sizeH;
		SDL_QueryTexture(mTilesetImage.M_Texture, NULL, 0, &sizeW, &sizeH);
		sizeW /= 32;
		sizeH /= 32;
		for (int y = 0; y < sizeH; y++) {
			for (int x = 0; x < sizeW; x++) {
				SDL_Rect tmpRect{ x * 32,y * 32,32,32 };
				mTiles.push_back(tmpRect);

			}
		}
	}
}

//sets the internal offset value to convert between GID format and internal tileID's 
void setLocalOffset(int FirstTileoffset) {

}


bool getPassible(int GlobalID) {
	if (GlobalID == 0) {
		return true;
	}
	return M_Passabe.at(GlobalID - mGlobalOffset);
}


SDL_Texture * getImage() {
	return mTilesetImage.M_Texture;
}
SDL_Rect getSrcRect(int GlobalID) {
	if (GlobalID == 0) {
		SDL_Rect tile{};
		return tile;
	}
	return mTiles.at(GlobalID - mGlobalOffset);
}





private:
	//this holds the map offset for converting between GID format and local format
	int mGlobalOffset;
	//stores the actual optimised image 
	image mTilesetImage;
	//holds the info of each tile
	std::vector<SDL_Rect>mTiles;
	//holds data to see if sprites can pass through it
	std::vector<bool>M_Passabe;
	//pointer to graphics stack to handle rendering and optimisations 
	Display * mgraphics;
};
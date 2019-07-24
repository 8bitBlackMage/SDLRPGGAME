#pragma once 
#include "Display.h"
#include "SDL_ttf.h"
#include <string>
class TextHandler {

	TextHandler() {
		if (TTF_Init() < 0) {
			abort();
		}
	}
	TextHandler(std::string pathtoFont): FontPath(pathtoFont){
		if (TTF_Init() < 0) {
			abort();
		}
	}
	void loadFont(std::string pathtoFont) {
		GameFont = TTF_OpenFont(pathtoFont.c_str(), 20);
	}
	



	TTF_Font * GameFont;
	std::string FontPath;
//this class handles all the text drawing and 
};
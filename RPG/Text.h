#pragma once 
#include "Display.h"
#ifdef __WIN32
#include "SDL_ttf.h"
#endif
#ifdef __linux__
#include <SDL2/SDL_ttf.h>
#endif
#include <string>
class TextHandler {
//this class handles all the text drawing and font management
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
	
	SDL_Texture * drawText(std::string TexttoDraw){
		SDL_Surface * TextSurface = TTF_RenderText_Solid(GameFont,TexttoDraw.c_str(), MainTextColour);
		if(TextSurface != NULL){
			SDL_Texture * TextTexture = SDL_CreateTextureFromSurface(M_Graphics->getRender(),TextSurface);

			SDL_FreeSurface(TextSurface);
			return TextTexture;
		}
		return NULL;
	}


	Display * M_Graphics;
	TTF_Font * GameFont;
	std::string FontPath;
	SDL_Color MainTextColour;
	SDL_Color ErrorTextColour;
};
#pragma once 
#include "Display.h"
#ifdef _WIN32
#include "SDL_ttf.h"
#endif
#ifdef __linux__
#include <SDL2/SDL_ttf.h>
#endif
#include <string>







class TextHandler {
//this class handles all the text drawing and font management
public:
	TextHandler(Display * Graphics): M_Graphics(Graphics) {
		if (TTF_Init() < 0) {
			abort();
		}
		MainTextColour = {255,255,255};
		ErrorTextColour = { 255,0,0 };
	}
	TextHandler(std::string pathtoFont, Display * Graphics): FontPath(pathtoFont), M_Graphics(Graphics) 
	{
		if (TTF_Init() < 0) {
			abort();
		
		}
		loadFont(FontPath);
	}
	void loadFont(std::string pathtoFont) {
		GameFont = TTF_OpenFont(pathtoFont.c_str(), 20);
	}
	
	OnscreenTextObject  GenerateText(std::string TexttoDraw, int x, int y){
		SDL_Surface * TextSurface = TTF_RenderText_Solid(GameFont,TexttoDraw.c_str(), MainTextColour);
		if(TextSurface != NULL){
			OnscreenTextObject TMPTEXT;
			TMPTEXT.TextToRender = SDL_CreateTextureFromSurface(M_Graphics->getRender(),TextSurface);
			TMPTEXT.RenderLocation.x = x;
			TMPTEXT.RenderLocation.y = y;
			TMPTEXT.RenderLocation.h = TextSurface->h;
			TMPTEXT.RenderLocation.w = TextSurface->w;
			SDL_FreeSurface(TextSurface);
		 	return TMPTEXT;
		}
		
	}
	void RenderText(OnscreenTextObject ObjectToRender) {
		SDL_RenderCopy(M_Graphics->getRender(), ObjectToRender.TextToRender, NULL, &ObjectToRender.RenderLocation);
	}

	Display * M_Graphics;
	TTF_Font * GameFont;
	std::string FontPath;
	SDL_Color MainTextColour;
	SDL_Color ErrorTextColour;
};
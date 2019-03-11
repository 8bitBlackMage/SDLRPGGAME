#pragma once
#include "SDL.h"
#include "Display.h"
#include "Map.h"
#include "Tilemaps.h"
class EventHandler {
public:
	EventHandler()/*:Graphics(1024,768)*/{};
	void Loop(Display * Graphics) {
		SDL_PollEvent(&Event);
		switch (Event.type) {
		case(SDL_QUIT): {
			Graphics->~Display();
			return;
			break;
			}
		default:
			break;



		}
	}

private:
	SDL_Event Event;
	//Display Graphics;

};
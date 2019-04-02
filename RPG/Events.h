#pragma once
#include "SDL.h"
#include "Display.h"
#include "Map.h"
#include "Tilemaps.h"
class EventHandler {
public:
	EventHandler()/*:Graphics(1024,768)*/{
		//keycodes.resize(SDL_scan);
	}

	void Loop(Display * Graphics) {
		SDL_PollEvent(&Event);
		switch (Event.type) {
		case(SDL_QUIT): {
			Graphics->~Display();
			return;
			break;
			}
		case(SDL_KEYDOWN): {
			keycodes[Event.key.keysym.scancode] = true;
		
		}
		case(SDL_KEYUP): {
			keycodes[Event.key.keysym.scancode] = false;
		}
		
		default:
			break;



		}
	}

	std::map<SDL_Scancode,bool>keycodes;


private:
	SDL_Event Event;
	//Display Graphics;

};
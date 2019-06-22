#pragma once
#include "SDL.h"
#include "Display.h"
#include <array>
#include "Tilemaps.h"
class EventHandler {
public:
	EventHandler()/*:Graphics(1024,768)*/{
		for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
			
	}
	}

	void Loop(Display * Graphics) {
		SDL_PollEvent(&Event);
		switch (Event.type) {
		case(SDL_QUIT): {
			running = false;
			break;
			}
		case(SDL_KEYDOWN): {
			keycodes[Event.key.keysym.scancode] = true;
			break;
		}
		case(SDL_KEYUP): {
			keycodes[Event.key.keysym.scancode] = false;
			break;
		}
		
		default:
			break;



		}
	}
	bool isRunning() {
		return running;
	}
	std::array<bool, SDL_NUM_SCANCODES>keycodes;


private:
	SDL_Event Event;
	//Display Graphics;
	bool running = true;
};
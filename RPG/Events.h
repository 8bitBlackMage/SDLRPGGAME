#pragma once
#include "Display.h"
#include <array>



//overall SDL event handling, differs from game loop in so far as its called multiple times per frame, and handles OS functions such as keyboard reading 
class EventHandler {
public:

	//default constructor, unused
	EventHandler(){

	}
	//handles all SDL event functions
	void Loop(Display * Graphics) {
		SDL_PollEvent(&M_Event);
		switch (M_Event.type) {
		case(SDL_QUIT): {
			M_running = false;
			break;
			}
		case(SDL_KEYDOWN): {
			G_keycodes[M_Event.key.keysym.scancode] = true;
			break;
		}
		case(SDL_KEYUP): {
			G_keycodes[M_Event.key.keysym.scancode] = false;
			break;
		}
		
		default:
			break;



		}
	}

	//returns check to keep the main loop running (hopefully will be depreicated soon), 
	bool isRunning() {
		return M_running;
	}
	//array of per loop keypresses, read by other functions / objects needing to read the keyboard
	std::array<bool, SDL_NUM_SCANCODES>G_keycodes;


private:
	//standard event type, will change per loop depending on whats hit 
	SDL_Event M_Event;

	//flag to keep execution continual, killing the SDL window thread triggers this to be false thus ending excecution
	bool M_running = true;
};
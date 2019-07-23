#pragma once



#ifdef _WIN32
#include "SDL.h"
#include "SDL_mixer.h"
#endif

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif
#include <vector>



class SoundManager{
//overall class to store SFX and BGM code
public:
	SoundManager() {
		//default constructor, opens the SDL mixer to default stereo audio formats
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {

			abort();
		}
	}



	void loadMusic(std::string pathToFile) {
		//loads wav file music into memory for playback
		M_BGM = Mix_LoadMUS(pathToFile.c_str());
	}
	void loadSFX(std::string pathToFile) {
		//adds sound effect into SFX vector (future option of not keeping these in memory?)
		Mix_Chunk * tmp = new Mix_Chunk;

		tmp = Mix_LoadWAV(pathToFile.c_str());
		M_SFX.push_back(tmp);
	}
	void playSFX(int SFXID,int loops)
	{
		Mix_PlayChannel(-1, M_SFX.at(SFXID), loops);
	}
private:
	
	Mix_Music  * M_BGM;
	// container for background music for current area 
	std::vector<Mix_Chunk*>M_SFX;
	//vector of sound effect wav data 
	int M_MusicVol;
	//global var for music volume
	int M_SFXVol;
	//global var for sound effects volume
};
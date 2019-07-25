#pragma once
#include "Globals.h"
#ifdef _WIN32
#include "SDL.h"
#include "SDL_image.h"
#endif
#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif // __linux__

#include <iostream>
#include <vector>




struct SpriteSheets
{
	SpriteSheets(std::string imgPath, SDL_Renderer*Ren)
	{
		load(imgPath, Ren);
	}
	void load(std::string imgPath, SDL_Renderer*Ren) {
		SDL_Surface * tmp;

		//loads bitmap file from 
		tmp = IMG_Load(imgPath.c_str());

		M_Texture = SDL_CreateTextureFromSurface(Ren, tmp);
		SDL_FreeSurface(tmp);

	}
	SpriteSheets() {}
	SDL_Texture* M_Texture;
};

//overall class to store  display code, holds all base code to rendering to the screen 
class Display
{
public:
	//standard constructor, initialises display, offscreen rendering
	Display(int ScreenWidth, int ScreenHeight, int* scale) : M_ScreenWidth(ScreenWidth), M_ScreenHeight(ScreenHeight)
	{
		
		
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::cout << "error" << std::endl;
			abort();
		}
		else {
			M_Win = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, M_ScreenWidth, M_ScreenHeight, SDL_WINDOW_SHOWN);
 
			if (M_Win == NULL) {

				std::cout << "error" << std::endl;
				abort();
			}
			G_BScrollX = M_ScreenWidth * 0.25;
			G_BScrollY = M_ScreenHeight * 0.25;
			G_ScrollXoffset = G_BScrollX / Globals::TScale;
			G_ScrollYoffset = G_BScrollY / Globals::TScale;
			G_FScrollX = M_ScreenWidth - G_BScrollX;
			G_FScrollY = M_ScreenHeight - G_BScrollY;
 			M_Ren = SDL_CreateRenderer(M_Win, -1, SDL_RENDERER_ACCELERATED);
			if (SDL_SetRenderDrawBlendMode(M_Ren, SDL_BLENDMODE_BLEND) < 0) {
				abort();
			}
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				std::cout << "error" << std::endl;
			}

		}
	}
	//deconstructor to free memory
	~Display() {
		
		SDL_DestroyWindow(M_Win);
		SDL_DestroyRenderer(M_Ren);
		M_Win = NULL;
		M_Ren = NULL;
		IMG_Quit();
		SDL_Quit();
	}
	//standard optimised image loader routine, use this for all media loading 
	SDL_Texture * LoadMedia(std::string path)
	{
		SDL_Surface * tmp;
		SDL_Texture * ret;
		//loads bitmap file from 
		tmp = IMG_Load(path.c_str());
		ret = SDL_CreateTextureFromSurface(M_Ren, tmp);
		SDL_FreeSurface(tmp);
		return ret;
	}
	
	//empties the render surface for drawing over 
	void clear() {
		SDL_RenderClear(M_Ren);

	}

	//pushes the offscreen render texture to the display buffer 
	void flip() {
		SDL_RenderPresent(M_Ren);
	}
	




	//returns the renderer for use in other drawing functions
	SDL_Renderer* getRender() {
		return M_Ren;
	}
	
	//scrolling boundry coodernates, initialised to onscreen pixels 
	int G_FScrollX, G_FScrollY, G_BScrollX, G_BScrollY;

	//amount of tiles scrolled from zero in the X axis 
	int G_ScrollX;
	//amount of tiles scrolled from zero in the y axis 
	int G_ScrollY;
	//used to calcuate offsets on scroll boundries 
	int G_ScrollXoffset;
	//used to calcuate offsets on scroll boundries 
	int G_ScrollYoffset;
	// locally stored screen sizes, in pixels
	int M_ScreenHeight, M_ScreenWidth;
	// locally stored map size in pixels 
	int mapSizeX, mapSizeY;
	//bools if map scrolled at all



	bool M_scroll;
private:
	//window for rendering 
	SDL_Window * M_Win;
	//renderer for drawing to 
	SDL_Renderer * M_Ren;

	
};

//coverall class for image files and data for said images 
typedef struct  {

	
	//pointer to VRAM holding image data 
	SDL_Texture* M_Texture;


	//vector to hold info for different frames of image, for tilesets / animated sprites 
	std::vector<SDL_Rect>M_sheetparts;


	//small int to store current rect being used for rendering 
	int8_t M_currentSheetPart;


	//function to load png file into VRAM 
	void load(std::string imgPath, Display * graphics) 
	{
		M_Texture = graphics->LoadMedia(imgPath);
	}


	//generates individual frames from sprite sheet for animation / multi tiles etc 
	void HandleImageset()
	{
		int sizeW;
		int sizeH;
		SDL_QueryTexture(M_Texture, NULL, 0, &sizeW, &sizeH);
		sizeW /= 32;
		sizeH /= 32;
		for (int y = 0; y < sizeH; y++) {
			for (int x = 0; x < sizeW; x++) {
				SDL_Rect tmpRect{ x * 32,y * 32,32,32 };
				M_sheetparts.push_back(tmpRect);

			}

		}

	}
}image;
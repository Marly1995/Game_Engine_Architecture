#include <iostream>
#include "SDL.h"

int main(int argc, char* argv[])
{
	//send HelloWorld! to console output_iteratorstd::cout << "HelloWorld!\n";
	
	if (SDL_Init(SDL_INIT_EVERYTHING) !=0) {
		SDL_logCritical(SDL_LOG_CATEGORY_APPLICATION,
		"SDL_Init Error: %s\n", SDL_GetError());
		return1;
	}
	SDL_Log("SDL initialised OK!\n");
	
	return 0;
}
#include <iostream>

#include "SDL.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

int main(int argc, char* argv[])
{
	// send HelloWorld! to console output
	std::cout << "HelloWorld!\n";

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Log("SDL initialized OK!\n");
	
	char* data;
	SDL_RWops *file = SDL_RWFromFile("C:/Users/Computing/Documents/LogFile.txt", "rb");

	if (file != nullptr)
	{
		SDL_Log("Should have finished writing!\n");
		
		if (SDL_RWread(file, &data, sizeof(data), 1)) {
			printf("i tried %c \n", data);
		}
		SDL_Log("Should have finished writing!\n");
		SDL_RWclose(file);
	}
	else
	{

		SDL_Log("File not loaded correclty!!!\n");
		file = SDL_RWFromFile("C:/Users/Computing/Documents/LogFile.txt", "w");
	}
	return 0;
}
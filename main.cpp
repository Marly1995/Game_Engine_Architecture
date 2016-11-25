#include <iostream>
#include <fstream>
#include <string>

#include "SDL.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace std;

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

	string line;
	ifstream file("C:/Users/Computing/Documents/LogFile.txt");

	if (file.is_open())
	{
		SDL_Log("File opened!\n");
		
		while (getline(file, line))
		{
			cout << line << "\n";
		}
		SDL_Log("Should have finished writing!\n");
		file.close();
	}
	else
	{
		SDL_Log("File not opened correclty!!!\n");
	}
	return 0;
}
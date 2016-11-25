#include <iostream>
#include <fstream>
#include <string>
#include <list>

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

	list<glm::vec3> positionData;
	string line;
	ifstream file("C:/Users/Computing/Documents/LogFile.txt");
	string number;
	if (file.is_open())
	{
		SDL_Log("File opened!\n");
		int dataPosition = 0;
		while (getline(file, line))
		{			
			int i;
			int k = 0;
			float x, y, z;
			for (i = 4; i < line.size(); i++)
			{
				if (line[i] != ',')
				{
					number += line[i];
				}
				else if (line[i] == ',' && k == 0)
				{
					x = stof(number);
					k++;
					i += 3;
				}
				else if (line[i] == ',' && k == 1)
				{
					y = stof(number);
					k++;
					i += 3;
				}
				else if (line[i] == ',' && k == 2)
				{
					z = stof(number);
				}
			}
			positionData.assign(1, glm::vec3(x, y, z));
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
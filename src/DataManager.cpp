#include "Datamanager.h"

DataManager::DataManager()
{
}

int DataManager::loadFile(char* fileDirectory)
{
	ifstream file;
	string line;
	if (fileDirectory != nullptr)
	{
		file.open(fileDirectory);
	}
	if (file.is_open())
	{
		SDL_Log("File opened!\n");
		getline(file, line);
		if (line == "position ")
		{
			loadPositionFile(fileDirectory);
			file.close();
			return 1;
		}
		else if (line == "power ")
		{
			loadPowerFile(fileDirectory);
			file.close();
			return 2;
		}
		else if (line == "batteries ")
		{
			loadBatteryFile(fileDirectory);
			file.close();
			return 1;
		}
		else
		{
			loadStateFile(fileDirectory);
			file.close();
			return 1 ;
		}
	}
	else
	{
		SDL_Log("File not opened correclty!!!\n");
		return 0;
	}
}

void DataManager::loadPowerFile(char* fileDirectory)
{
	Histogram tempHistogram = Histogram();
	ifstream file;
	string line;
	string number;
	float x;
	if (fileDirectory != nullptr)
	{
		file.open(fileDirectory);
	}
	if (file.is_open())
	{
		SDL_Log("File opened!\n");
		int dataPosition = 0;
		while (getline(file, line))
		{
			if (line == "power ")
			{
			}
			else
			{
				number = line;
				x = stof(number);
				tempHistogram.vertexData.push_back(x);
			}
		}
		SDL_Log("Should have finished writing!\n");
		file.close();
	}
	else
	{
		SDL_Log("File not opened correclty!!!\n");
	}
	tempHistogram.BuildHistogram(histograms.size());
	histograms.clear();
	histograms.push_back(tempHistogram);
}

void DataManager::loadPositionFile(char* fileDirectory)
{
	Heatmap tempHeatmap = Heatmap();
	Trajectory tempTrajectory = Trajectory();
	tempTrajectory.BuildTrajectory(trajectories.size());
	tempHeatmap.PickColor(0);
	ifstream file;
	string line;
	string number;
	if (fileDirectory != nullptr)
	{
		file.open(fileDirectory);
	}
	if (file.is_open())
	{
		SDL_Log("File opened!\n");
		int dataPosition = 0;
		while (getline(file, line))
		{
			int i;
			int k = 0;
			float x, y, z;
			x = 0;
			y = 0;
			z = 0;
			if (line == "position ")
			{
			}
			else
			{
				for (i = 4; i < line.size(); i++)
				{
					if (line[i] != ',' && line[i] != ')')
					{
						number += line[i];
					}
					else if (line[i] == ',' && k == 0)
					{
						x = stof(number);
						k++;
						i += 3;
						number = "";
					}
					else if ((line[i] == ',' && k == 1) || (line[i] == ')' && k == 1))
					{
						y = stof(number);
						k++;
						i += 3;
						number = "";
					}
					else if (line[i] == ')' && k == 2)
					{
						z = stof(number);
						number = "";
					}
				}
				tempHeatmap.vectorData.push_back(glm::vec3(x, y, z));

				tempHeatmap.vertexData.push_back(x);
				tempHeatmap.vertexData.push_back(y);
				tempHeatmap.vertexData.push_back(z);
				tempHeatmap.vertexData.push_back(tempHeatmap.color.x);
				tempHeatmap.vertexData.push_back(tempHeatmap.color.y);
				tempHeatmap.vertexData.push_back(tempHeatmap.color.z);
				tempHeatmap.vertexData.push_back(1.0f);

				tempTrajectory.vertexData.push_back(x / 3000.0f);
				tempTrajectory.vertexData.push_back(y / 3000.0f);
				tempTrajectory.vertexData.push_back(z / 3000.0f);
				tempTrajectory.vertexData.push_back(tempTrajectory.color.x);
				tempTrajectory.vertexData.push_back(tempTrajectory.color.y);
				tempTrajectory.vertexData.push_back(tempTrajectory.color.z);
				tempTrajectory.vertexData.push_back(1.0f);
			}
		}
		SDL_Log("Should have finished writing!\n");
		file.close();
	}
	else
	{
		SDL_Log("File not opened correclty!!!\n");
	}
	trajectories.push_back(tempTrajectory);
	if (heatmaps.size() < 1)
	{
		Heatmap heat = Heatmap();
		Heatmap heat1 = Heatmap();
		Heatmap heat2 = Heatmap();
		tempHeatmap.BuildHeatmap(1.0f);
		heatmaps.push_back(tempHeatmap);
		heatmaps.push_back(heat);
		heatmaps.push_back(heat1);
		heatmaps.push_back(heat2);
	}
	else
	{
		heatmaps[0].PickColor(0);
		heatmaps[0].RebuildHeatmap(tempHeatmap, 1.0f);
	}
	/*int newheat = 0;
	cout << "Do you wish to create a new heatmap?" << endl;
	cout << "Enter 1 for YES and 2 for NO" << endl;
	cin >> newheat;
	if (newheat == 1)
	{
		tempHeatmap.BuildHeatmap(0.05f);
		heatmaps.push_back(tempHeatmap);
	}
	if (newheat == 2)
	{
		int numheat = 0;
		cout << "What number heatmap do you wish to add it to?" << endl;
		cin >> numheat;
		heatmaps[numheat].RebuildHeatmap(tempHeatmap, 0.05f);
	}*/
}

void DataManager::loadBatteryFile(char* fileDirectory)
{
	Heatmap tempHeatmap = Heatmap();
	tempHeatmap.PickColor(-1);
	ifstream file;
	string line;
	string number;
	if (fileDirectory != nullptr)
	{
		file.open(fileDirectory);
	}
	if (file.is_open())
	{
		SDL_Log("File opened!\n");
		int dataPosition = 0;
		while (getline(file, line))
		{
			int i;
			int k = 0;
			float x, y, z;
			x = 0;
			y = 0;
			z = 0;
			if (line == "batteries ")
			{
			}
			else
			{
				for (i = 4; i < line.size(); i++)
				{
					if (line[i] != ',' && line[i] != ')')
					{
						number += line[i];
					}
					else if (line[i] == ',' && k == 0)
					{
						x = stof(number);
						k++;
						i += 3;
						number = "";
					}
					else if ((line[i] == ',' && k == 1) || (line[i] == ')' && k == 1))
					{
						y = stof(number);
						k++;
						i += 3;
						number = "";
					}
					else if (line[i] == ')' && k == 2)
					{
						z = stof(number);
						number = "";
					}
				}
				tempHeatmap.vectorData.push_back(glm::vec3(x, y, z));

				tempHeatmap.vertexData.push_back(x);
				tempHeatmap.vertexData.push_back(y);
				tempHeatmap.vertexData.push_back(z);
				tempHeatmap.vertexData.push_back(tempHeatmap.color.x);
				tempHeatmap.vertexData.push_back(tempHeatmap.color.y);
				tempHeatmap.vertexData.push_back(tempHeatmap.color.z);
				tempHeatmap.vertexData.push_back(1.0f);

			}
		}
		SDL_Log("Should have finished writing!\n");
		file.close();
	}
	else
	{
		SDL_Log("File not opened correclty!!!\n");
	}
	if (heatmaps.size() < 1)
	{
		Heatmap heat = Heatmap();
		Heatmap heat1 = Heatmap();
		Heatmap heat2 = Heatmap();
		tempHeatmap.BuildHeatmap(0.5f);
		heatmaps.push_back(heat);
		heatmaps.push_back(tempHeatmap);
		heatmaps.push_back(heat1);
		heatmaps.push_back(heat2);
	}
	else
	{
		heatmaps[1].PickColor(-1);
		heatmaps[1].RebuildHeatmap(tempHeatmap, 0.5f);
	}
}

void DataManager::loadStateFile(char* fileDirectory)
{
	Heatmap tempHeatmap = Heatmap();
	ifstream file;
	string line;
	string number;
	int winloss = 0;
	if (fileDirectory != nullptr)
	{
		file.open(fileDirectory);
	}
	if (file.is_open())
	{
		SDL_Log("File opened!\n");
		int dataPosition = 0;
		while (getline(file, line))
		{
			int i;
			int k = 0;
			float x, y, z;
			x = 0;
			y = 0;
			z = 0;
			if (line[0] == 'W')
			{
				winloss = 1;
			}
			else if (line[0] == 'L')
			{
				winloss = 2;
			}
			for (i = 5; i < line.size(); i++)
			{
				if (line[i] != ',' && line[i] != ')')
				{
					number += line[i];
				}
				else if (line[i] == ',' && k == 0)
				{
					x = stof(number);
					k++;
					i += 3;
					number = "";
				}
				else if ((line[i] == ',' && k == 1) || (line[i] == ')' && k == 1))
				{
					y = stof(number);
					k++;
					i += 3;
					number = "";
				}
				else if (line[i] == ')' && k == 2)
				{
					z = stof(number);
					number = "";
				}
			}
			tempHeatmap.vectorData.push_back(glm::vec3(x, y, z));

			tempHeatmap.vertexData.push_back(x);
			tempHeatmap.vertexData.push_back(y);
			tempHeatmap.vertexData.push_back(z);
			tempHeatmap.vertexData.push_back(tempHeatmap.color.x);
			tempHeatmap.vertexData.push_back(tempHeatmap.color.y);
			tempHeatmap.vertexData.push_back(tempHeatmap.color.z);
			tempHeatmap.vertexData.push_back(1.0f);

			}
		SDL_Log("Should have finished writing!\n");
		file.close();
	}
	else
	{
		SDL_Log("File not opened correclty!!!\n");
	}
	if (winloss == 1) 
	{
		if (heatmaps.size() < 1)
		{
			tempHeatmap.PickColor(-2);
			Heatmap heat = Heatmap();
			Heatmap heat1 = Heatmap();
			Heatmap heat2 = Heatmap();
			tempHeatmap.BuildHeatmap(0.5f);
			heatmaps.push_back(heat);
			heatmaps.push_back(heat1);
			heatmaps.push_back(tempHeatmap);
			heatmaps.push_back(heat2);
		}
		else
		{
			heatmaps[2].PickColor(-2);
			heatmaps[2].RebuildHeatmap(tempHeatmap, 0.5f);
		}
	}
	if (winloss == 2) 
	{
		if (heatmaps.size() < 1)
		{
			tempHeatmap.PickColor(-3);
			Heatmap heat = Heatmap();
			Heatmap heat1 = Heatmap();
			Heatmap heat2 = Heatmap();
			tempHeatmap.BuildHeatmap(0.5f);
			heatmaps.push_back(heat);
			heatmaps.push_back(heat1);
			heatmaps.push_back(heat2);
			heatmaps.push_back(tempHeatmap);
		}
		else
		{
			heatmaps[3].PickColor(-3);
			heatmaps[3].RebuildHeatmap(tempHeatmap, 0.5f);
		}
	}
}
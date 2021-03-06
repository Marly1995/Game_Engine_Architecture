#include "Heatmap.h"

Heatmap::Heatmap()
{
	for (int i = 0; i < 10; i++)
	{
		vertexBuffer.push_back(i);
		vertexObject.push_back(i);
	}
}

void Heatmap::PickColor(int index)
{
	switch (index)
	{
	case -3:
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		break;
	case -2:
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	case -1:
		color = glm::vec3(0.8f, 0.6f, 0.2f);
		break;
	case 0:
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case 1:
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		break;
	case 2:
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		break;
	case 3:
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		break;
	}
}


void Heatmap::BuildHeatmap(float heat)
{
	ready = true;
	int range = vertexData.size() / 7;

	float xRange = 4000.0f;
	float yRange = 3400.0f;

	float xIncrement = xRange / 100;
	float yIncrement = yRange / 100;

	for (int i = 0; i < range; i++)
	{
		float xTemp = vectorData[i].x + 2000.0f;
		float yTemp = vectorData[i].y + 1700.0f;

		for (int z = 0; z < 100; z++)
		{
			if (xTemp >= xIncrement * z && xTemp < xIncrement * (z + 1))
			{
				for (int p = 0; p < 100; p++)
				{
					if (yTemp >= yIncrement * p && yTemp < yIncrement * (p + 1))
					{		
						if (spread[z][p] <= 0.25)
						{
							spread[z][p] += heat;
						}

						if (spread[z][p] >= 0.5f)
						{
							spread[z][p] += heat / 2;

							spread[z - 1][p] += heat / 2;
							spread[z + 1][p] += heat / 2;
							spread[z][p - 1] += heat / 2;
							spread[z][p + 1] += heat / 2;
							
							//
							spread[z - 2][p] += heat / 6;
							spread[z + 2][p] += heat / 6;
							spread[z][p - 2] += heat / 6;
							spread[z][p + 2] += heat / 6;

							spread[z - 1][p + 1] += heat / 6;
							spread[z + 1][p - 1] += heat / 6;
							spread[z - 1][p - 1] += heat / 6;
							spread[z + 1][p + 1] += heat / 6;

							//
							spread[z - 3][p] += heat / 10;
							spread[z + 3][p] += heat / 10;
							spread[z][p - 3] += heat / 10;
							spread[z][p + 3] += heat / 10;

							spread[z - 2][p + 1] += heat / 10;
							spread[z - 1][p + 2] += heat / 10;
							spread[z + 2][p + 1] += heat / 10;
							spread[z + 1][p + 2] += heat / 10;
							spread[z - 2][p - 1] += heat / 10;
							spread[z - 1][p - 2] += heat / 10;
							spread[z + 2][p - 1] += heat / 10;
							spread[z + 1][p - 2] += heat / 10;
						}
						else if (spread[z][p] >= 0.25f)
						{
							spread[z][p] += heat;

							spread[z - 1][p] += heat/2;
							spread[z + 1][p] += heat/2;
							spread[z][p - 1] += heat/2;
							spread[z][p + 1] += heat/2;

							spread[z - 2][p] += heat / 4;
							spread[z + 2][p] += heat / 4;
							spread[z][p - 2] += heat / 4;
							spread[z][p + 2] += heat / 4;

							spread[z - 1][p + 1] += heat / 4;
							spread[z + 1][p - 1] += heat / 4;
							spread[z - 1][p - 1] += heat / 4;
							spread[z + 1][p + 1] += heat / 4;
						}
					}
				}
			}

		}
	}

	vertexData.clear();
	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			vertexData.push_back(-1.0f + (x*0.02f));
			vertexData.push_back(-1.0f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(color.x);
			vertexData.push_back(color.y);
			vertexData.push_back(color.z);
			vertexData.push_back(spread[x][y]);
			// point 2
			vertexData.push_back(-1.0f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(color.x);
			vertexData.push_back(color.y);
			vertexData.push_back(color.z);
			vertexData.push_back(spread[x][y]);
			//point 3
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-1.0f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(color.x);
			vertexData.push_back(color.y);
			vertexData.push_back(color.z);
			vertexData.push_back(spread[x][y]);

			//point 1
			vertexData.push_back(-1.0f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(color.x);
			vertexData.push_back(color.y);
			vertexData.push_back(color.z);
			vertexData.push_back(spread[x][y]);
			//point 2
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(color.x);
			vertexData.push_back(color.y);
			vertexData.push_back(color.z);
			vertexData.push_back(spread[x][y]);
			//point 3
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-1.0f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(color.x);
			vertexData.push_back(color.y);
			vertexData.push_back(color.z);
			vertexData.push_back(spread[x][y]);
		}
	}
}

void Heatmap::RebuildHeatmap(Heatmap heatmap, float heat)
{
	ready = true;
	int range = heatmap.vertexData.size() / 7;

	float xRange = 4000.0f;
	float yRange = 3400.0f;

	float xIncrement = xRange / 100;
	float yIncrement = yRange / 100;

	for (int i = 0; i < range; i++)
	{
		float xTemp = heatmap.vectorData[i].x + 2000.0f;
		float yTemp = heatmap.vectorData[i].y + 1700.0f;

		for (int z = 0; z < 100; z++)
		{
			if (xTemp >= xIncrement * z && xTemp < xIncrement * (z + 1))
			{
				for (int p = 0; p < 100; p++)
				{
					if (yTemp >= yIncrement * p && yTemp < yIncrement * (p + 1))
					{
						if (spread[z][p] <= 0.25)
						{ 
							spread[z][p] += heat;
						}

						if (spread[z][p] >= 0.5f)
						{
							spread[z][p] += heat / 4;

							spread[z - 1][p] += heat / 6;
							spread[z + 1][p] += heat / 6;
							spread[z][p - 1] += heat / 6;
							spread[z][p + 1] += heat / 6;

							//
							spread[z - 2][p] += heat / 8;
							spread[z + 2][p] += heat / 8;
							spread[z][p - 2] += heat / 8;
							spread[z][p + 2] += heat / 8;

							spread[z - 1][p + 1] += heat / 8;
							spread[z + 1][p - 1] += heat / 8;
							spread[z - 1][p - 1] += heat / 8;
							spread[z + 1][p + 1] += heat / 8;

							//
							spread[z - 3][p] += heat / 10;
							spread[z + 3][p] += heat / 10;
							spread[z][p - 3] += heat / 10;
							spread[z][p + 3] += heat / 10;

							spread[z - 2][p + 1] += heat / 10;
							spread[z - 1][p + 2] += heat / 10;
							spread[z + 2][p + 1] += heat / 10;
							spread[z + 1][p + 2] += heat / 10;
							spread[z - 2][p - 1] += heat / 10;
							spread[z - 1][p - 2] += heat / 10;
							spread[z + 2][p - 1] += heat / 10;
							spread[z + 1][p - 2] += heat / 10;
						}
						else if (spread[z][p] >= 0.25f)
						{
							spread[z][p] += heat;

							spread[z - 1][p] += heat / 2;
							spread[z + 1][p] += heat / 2;
							spread[z][p - 1] += heat / 2;
							spread[z][p + 1] += heat / 2;

							spread[z - 2][p] += heat / 4;
							spread[z + 2][p] += heat / 4;
							spread[z][p - 2] += heat / 4;
							spread[z][p + 2] += heat / 4;

							spread[z - 1][p + 1] += heat / 4;
							spread[z + 1][p - 1] += heat / 4;
							spread[z - 1][p - 1] += heat / 4;
							spread[z + 1][p + 1] += heat / 4;
						}
					}
				}
			}

		}
	}

	vertexData.clear();
	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{
			vertexData.push_back(-1.0f + (x*0.02f));
			vertexData.push_back(-1.0f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(color.x);
			vertexData.push_back(color.y);
			vertexData.push_back(color.z);
			vertexData.push_back(spread[x][y]);
			// point 2
			vertexData.push_back(-1.0f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(color.x);
			vertexData.push_back(color.y);
			vertexData.push_back(color.z);
			vertexData.push_back(spread[x][y]);
			//point 3
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-1.0f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(color.x);
			vertexData.push_back(color.y);
			vertexData.push_back(color.z);
			vertexData.push_back(spread[x][y]);

			//point 1
			vertexData.push_back(-1.0f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(color.x);
			vertexData.push_back(color.y);
			vertexData.push_back(color.z);
			vertexData.push_back(spread[x][y]);
			//point 2
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(color.x);
			vertexData.push_back(color.y);
			vertexData.push_back(color.z);
			vertexData.push_back(spread[x][y]);
			//point 3
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-1.0f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(color.x);
			vertexData.push_back(color.y);
			vertexData.push_back(color.z);
			vertexData.push_back(spread[x][y]);
		}
	}
}

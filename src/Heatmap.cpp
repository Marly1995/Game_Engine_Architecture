#include "Heatmap.h"

Heatmap::Heatmap()
{

}

void Heatmap::PickColor(int index)
{
	switch (index)
	{
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

float Heatmap::colPick(float index, int col)
{
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
	if (index >= 0.05f && index <= 1.0f){ color = glm::vec3(0.0f, 1.0f * index, 1.0f); }
	else if (index > 1.0f && index <= 2.0f){ color = glm::vec3(0.0f, 1.0f, 1.0f * (2-index)); }
	else if (index > 2.0f && index <= 3.0f){ color = glm::vec3(1.0f, 1.0f * (3 - index), 0.0f); }
	else if (index > 3.0f) { color = glm::vec3(1.0f * (0.5f * (index - 3.0f)), 0.0f, 0.0f); }

	if (col == 1){ return color.x; }	
	if (col == 2) { return color.y; }
	if (col == 3) { return color.z; }
}

void Heatmap::BuildHeatmap()
{

	int range = vertexData.size() / 7;

	float xMin = 0, yMin = 0, xMax = 0, yMax = 0;

	for (int i = 0; i < range; i++)
	{
		float xTemp = vectorData[i].x;
		float yTemp = vectorData[i].y;

		if (xTemp > xMax) { xMax = xTemp; }
		if (xTemp < xMin) { xMin = xTemp; }
		if (yTemp > yMax) { yMax = yTemp; }
		if (yTemp < yMin) { yMin = yTemp; }
	}

	float xRange = xMax - xMin;
	float yRange = yMax - yMin;

	float xIncrement = xRange / 100;
	float yIncrement = yRange / 100;

	for (int i = 0; i < range; i++)
	{
		float xTemp = vectorData[i].x;
		float yTemp = vectorData[i].y;

		for (int z = 0; z < 100; z++)
		{
			if (xTemp >= xIncrement * z && xTemp < xIncrement * (z + 1))
			{
				for (int p = 0; p < 100; p++)
				{
					if (yTemp >= yIncrement * p && yTemp < yIncrement * (p + 1))
					{		
						spread[z][p] += 0.1f;
						if (spread[z][p] > 4.0f) { spread[z][p] = 4.0f; }
						if (spread[z][p] >= 0.5f)
						{
							spread[z - 1][p] += 0.05f;
							spread[z + 1][p] += 0.05f;
							spread[z][p - 1] += 0.05f;
							spread[z][p + 1] += 0.05f;
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
			vertexData.push_back(colPick(spread[x][y], 1));
			vertexData.push_back(colPick(spread[x][y], 2));
			vertexData.push_back(colPick(spread[x][y], 3));
			vertexData.push_back(1.0f);
			// point 2
			vertexData.push_back(-1.0f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(colPick(spread[x][y], 1));
			vertexData.push_back(colPick(spread[x][y], 2));
			vertexData.push_back(colPick(spread[x][y], 3));
			vertexData.push_back(1.0f);
			//point 3
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-1.0f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(colPick(spread[x][y], 1));
			vertexData.push_back(colPick(spread[x][y], 2));
			vertexData.push_back(colPick(spread[x][y], 3));
			vertexData.push_back(1.0f);

			//point 1
			vertexData.push_back(-1.0f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(colPick(spread[x][y], 1));
			vertexData.push_back(colPick(spread[x][y], 2));
			vertexData.push_back(colPick(spread[x][y], 3));
			vertexData.push_back(1.0f);
			//point 2
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(colPick(spread[x][y], 1));
			vertexData.push_back(colPick(spread[x][y], 2));
			vertexData.push_back(colPick(spread[x][y], 3));
			vertexData.push_back(1.0f);
			//point 3
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-1.0f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(colPick(spread[x][y], 1));
			vertexData.push_back(colPick(spread[x][y], 2));
			vertexData.push_back(colPick(spread[x][y], 3));
			vertexData.push_back(1.0f);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		vertexBuffer.push_back(i);
		vertexObject.push_back(i);
	}
}

void Heatmap::RebuildHeatmap(Heatmap heatmap)
{
	int range = heatmap.vertexData.size() / 7;

	float xMin = 0, yMin = 0, xMax = 0, yMax = 0;

	for (int i = 0; i < range; i++)
	{
		float xTemp = heatmap.vectorData[i].x;
		float yTemp = heatmap.vectorData[i].y;

		if (xTemp > xMax) { xMax = xTemp; }
		if (xTemp < xMin) { xMin = xTemp; }
		if (yTemp > yMax) { yMax = yTemp; }
		if (yTemp < yMin) { yMin = yTemp; }
	}

	float xRange = xMax - xMin;
	float yRange = yMax - yMin;

	float xIncrement = xRange / 100;
	float yIncrement = yRange / 100;

	for (int i = 0; i < range; i++)
	{
		float xTemp = heatmap.vectorData[i].x;
		float yTemp = heatmap.vectorData[i].y;

		for (int z = 0; z < 100; z++)
		{
			if (xTemp >= xIncrement * z && xTemp < xIncrement * (z + 1))
			{
				for (int p = 0; p < 100; p++)
				{
					if (yTemp >= yIncrement * p && yTemp < yIncrement * (p + 1))
					{
						spread[z][p] += 0.1f;
						if (spread[z][p] >= 0.5f)
						{
							spread[z - 1][p] += 0.05f;
							spread[z + 1][p] += 0.05f;
							spread[z][p - 1] += 0.05f;
							spread[z][p + 1] += 0.05f;
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
			vertexData.push_back(colPick(spread[x][y], 1));
			vertexData.push_back(colPick(spread[x][y], 2));
			vertexData.push_back(colPick(spread[x][y], 3));
			vertexData.push_back(1.0f);
			// point 2
			vertexData.push_back(-1.0f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(colPick(spread[x][y], 1));
			vertexData.push_back(colPick(spread[x][y], 2));
			vertexData.push_back(colPick(spread[x][y], 3));
			vertexData.push_back(1.0f);
			//point 3
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-1.0f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(colPick(spread[x][y], 1));
			vertexData.push_back(colPick(spread[x][y], 2));
			vertexData.push_back(colPick(spread[x][y], 3));
			vertexData.push_back(1.0f);

			//point 1
			vertexData.push_back(-1.0f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(colPick(spread[x][y], 1));
			vertexData.push_back(colPick(spread[x][y], 2));
			vertexData.push_back(colPick(spread[x][y], 3));
			vertexData.push_back(1.0f);
			//point 2
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(colPick(spread[x][y], 1));
			vertexData.push_back(colPick(spread[x][y], 2));
			vertexData.push_back(colPick(spread[x][y], 3));
			vertexData.push_back(1.0f);
			//point 3
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-1.0f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(colPick(spread[x][y], 1));
			vertexData.push_back(colPick(spread[x][y], 2));
			vertexData.push_back(colPick(spread[x][y], 3));
			vertexData.push_back(1.0f);
		}
	}
}

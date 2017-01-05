#include "Heatmap.h"

Heatmap::Heatmap()
{

}

void Heatmap::BuildHeatmap()
{
	float spread[100][100] = { 0 };

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

	int spreadMax = 0;

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
						spread[z][p]++;
						if (spread[z][p] > spreadMax) { spreadMax = spread[z][p]; }
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
			vertexData.push_back(1.0f);
			vertexData.push_back(0.0f);
			vertexData.push_back(0.0f);
			vertexData.push_back(spread[x][y] / 4);
			// point 2
			vertexData.push_back(-1.0f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(1.0f);
			vertexData.push_back(0.0f);
			vertexData.push_back(0.0f);
			vertexData.push_back(spread[x][y] / 4);
			//point 3
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-1.0f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(1.0f);
			vertexData.push_back(0.0f);
			vertexData.push_back(0.0f);
			vertexData.push_back(spread[x][y] / 4);

			//point 1
			vertexData.push_back(-1.0f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(1.0f);
			vertexData.push_back(0.0f);
			vertexData.push_back(0.0f);
			vertexData.push_back(spread[x][y] / 4);
			//point 2
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-0.98f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(1.0f);
			vertexData.push_back(0.0f);
			vertexData.push_back(0.0f);
			vertexData.push_back(spread[x][y] / 4);
			//point 3
			vertexData.push_back(-0.98f + (x*0.02f));
			vertexData.push_back(-1.0f + (y*0.02f));
			vertexData.push_back(0.0f);
			vertexData.push_back(1.0f);
			vertexData.push_back(0.0f);
			vertexData.push_back(0.0f);
			vertexData.push_back(spread[x][y] / 4);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		vertexBuffer.push_back(i);
		vertexObject.push_back(i);
	}
}
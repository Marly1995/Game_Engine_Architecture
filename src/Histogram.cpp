#include "Histogram.h"

Histogram::Histogram()
{
}

void Histogram::BuildHistogram(int index)
{
	int spread[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	float temp;
	int range = vertexData.size();
	float increment = 2.0f / range;
	for (int i = 0; i < range; i++)
	{
		temp = vertexData[i];

		if (temp <= 300) { spread[0]++; }
		else if (temp > 300 && temp <= 600) { spread[1]++; }
		else if (temp > 600 && temp <= 900) { spread[2]++; }
		else if (temp > 900 && temp <= 1200) { spread[3]++; }
		else if (temp > 1200 && temp <= 1500) { spread[4]++; }
		else if (temp > 1500 && temp <= 1800) { spread[5]++; }
		else if (temp > 1800 && temp <= 2100) { spread[6]++; }
		else if (temp > 2100 && temp <= 2400) { spread[7]++; }
		else if (temp > 2400 && temp <= 2700) { spread[8]++; }
		else if (temp > 2700 && temp <= 3000) { spread[9]++; }
	}

	float xpos = -1.0f;
	vertexData.clear();
	for (int i = 0; i < 10; i++)
	{
		// point 1
		vertexData.push_back(xpos);
		vertexData.push_back(0.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(1.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(1.0f);
		// point 2
		vertexData.push_back(xpos);
		vertexData.push_back(spread[i] * increment);
		vertexData.push_back(0.0f);
		vertexData.push_back(1.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(1.0f);
		//point 3
		vertexData.push_back(xpos + 0.05f);
		vertexData.push_back(0.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(1.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(1.0f);

		//point 1
		vertexData.push_back(xpos);
		vertexData.push_back(spread[i] * increment);
		vertexData.push_back(0.0f);
		vertexData.push_back(1.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(1.0f);
		//point 2
		vertexData.push_back(xpos + 0.05f);
		vertexData.push_back(spread[i] * increment);
		vertexData.push_back(0.0f);
		vertexData.push_back(1.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(1.0f);
		//point 3
		vertexData.push_back(xpos + 0.05f);
		vertexData.push_back(0.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(1.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(0.0f);
		vertexData.push_back(1.0f);

		xpos += 0.1f;

		vertexBuffer = index;
		vertexObject = index;
	}
}
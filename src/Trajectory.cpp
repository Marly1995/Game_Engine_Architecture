#include "Trajectory.h"

Trajectory::Trajectory()
{
}

void Trajectory::BuildTrajectory(int index)
{
	int bufferCount = (vertexData.size() / 50000) + 1;

	for (int i = 0; i < bufferCount; i++)
	{
		vertexBuffer.push_back(i);
		vertexObject.push_back(i);
	}

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

void Trajectory::AddPower()
{
	int x = 0;
	for (int i = 6; i < vertexData.size(); i+=7)
	{
			float temp = powerData[x];

			if (temp <= 300) { vertexData[i]=0.1f; }
			else if (temp > 300 && temp <= 600) { vertexData[i]=0.2f; }
			else if (temp > 600 && temp <= 900) { vertexData[i]=0.3f; }
			else if (temp > 900 && temp <= 1200) { vertexData[i]=0.4f; }
			else if (temp > 1200 && temp <= 1500) { vertexData[i]=0.5f; }
			else if (temp > 1500 && temp <= 1800) { vertexData[i]=0.6f; }
			else if (temp > 1800 && temp <= 2100) { vertexData[i]=0.7f; }
			else if (temp > 2100 && temp <= 2400) { vertexData[i]=0.8f; }
			else if (temp > 2400 && temp <= 2700) { vertexData[i]=0.9f; }
			else if (temp > 2700) { vertexData[i]=1.0f;}
			x++;
	}
}
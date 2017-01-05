#include "Trajectory.h"

Trajectory::Trajectory()
{
}

void Trajectory::BuildTrajectory(int index)
{
	vertexBuffer = index;
	vertexObject = index;
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
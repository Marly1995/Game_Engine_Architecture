#include "Trajectory.h"

Trajectory::Trajectory()
{
}

void Trajectory::BuildTrajectory(int index)
{
	vertexBuffer = index;
	vertexObject = index;
}
#pragma once
#include "c:\Users\Computing\Documents\GitHub\Game_Engine_Architecture\includes.h"


using namespace std;

class Trajectory
{
public:

	vector<GLfloat> vertexData;
	GLuint vertexBuffer;
	GLuint vertexObject;
	glm::vec3 color;

	Trajectory();

	void BuildTrajectory(int index);

};
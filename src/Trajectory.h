#pragma once
#include "c:\Users\Marlon\Documents\GitHub\Game_Engine_Architecture\includes.h"


using namespace std;

class Trajectory
{
public:

	vector<GLfloat> vertexData;
	GLuint vertexBuffer;
	GLuint vertexObject;

	Trajectory();

	void BuildTrajectory(int index);

};
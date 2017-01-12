#pragma once
#include "c:\Users\Computing\Documents\GitHub\Game_Engine_Architecture\includes.h"


using namespace std;

class Trajectory
{
public:

	vector<GLfloat> vertexData;
	vector<GLfloat> powerData;
	vector<GLuint> vertexBuffer;
	vector<GLuint> vertexObject;
	glm::vec3 color;

	Trajectory();

	void BuildTrajectory(int index);
	void AddPower();

};
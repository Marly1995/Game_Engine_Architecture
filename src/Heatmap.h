#pragma once
#include "c:\Users\Marlon\Documents\GitHub\Game_Engine_Architecture\includes.h"

using namespace std;

class Heatmap
{
public:

	vector<GLfloat> vertexData;
	vector<glm::vec3> vectorData;
	vector<GLuint> vertexBuffer;
	vector<GLuint> vertexObject;

	Heatmap();

	void BuildHeatmap();
	
};
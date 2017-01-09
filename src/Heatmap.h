#pragma once
#include "c:\Users\Computing\Documents\GitHub\Game_Engine_Architecture\includes.h"

using namespace std;

class Heatmap
{
public:

	vector<GLfloat> vertexData;
	vector<glm::vec3> vectorData;
	vector<GLuint> vertexBuffer;
	vector<GLuint> vertexObject;
	glm::vec3 color;
	float spread[100][100] = { 0 };

	Heatmap();

	void BuildHeatmap();
	void RebuildHeatmap(Heatmap heatmap);
	void PickColor(int index);
	float colPick(float index, int col);
};
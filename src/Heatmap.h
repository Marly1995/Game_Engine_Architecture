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
	bool ready = false;

	Heatmap();

	void BuildHeatmap(float heat);
	void RebuildHeatmap(Heatmap heatmap, float heat);
	void PickColor(int index);
	
};
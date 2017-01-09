#pragma once
#include "c:\Users\Computing\Documents\GitHub\Game_Engine_Architecture\includes.h"

using namespace std;

class Histogram
{
public:
	vector<GLfloat> vertexData;
	GLuint vertexBuffer;
	GLuint vertexObject;

	Histogram();

	void BuildHistogram(int index);

};
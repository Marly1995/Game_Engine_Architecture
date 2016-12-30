#pragma once
class histogram
{

public:

	float range[];
	vector<GLfloat> dataSet;

	histogram(float min, float max);

	~histogram();
};


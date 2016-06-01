#pragma once

#include <list>

class MyBox
{
public:
	MyBox(float posX, float posY, int size, float r, float g, float b, float xStep, float yStep);
	~MyBox();
	void checkBoundary();
	void draw();
	void advance();
	static std::list<MyBox*> _boxes;

	float _top;
	float _bottom;
	float _left;
	float _right;

	float _r;
	float _g;
	float _b;

	float _xStep;
	float _yStep;
};
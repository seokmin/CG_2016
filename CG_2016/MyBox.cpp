#include "MyBox.h"
#include <gl/glut.h>

std::list<MyBox*> MyBox::_boxes;

MyBox::MyBox(float posX, float posY, int size, float r, float g, float b, float xStep, float yStep)
{
	_r = r;
	_g = g;
	_b = b;
	_xStep = xStep;
	_yStep = yStep;

	_left = posX;
	_right = _left + size;
	_bottom = posY;
	_top = _bottom + size;

	_boxes.push_back(this);
}

MyBox::~MyBox()
{
	_boxes.remove(this);
}

void MyBox::checkBoundary()
{
	if (this->_xStep == 0.f && this->_yStep == 0.f)
		return;

	auto xFlip = false;
	auto yFlip = false;
	for (auto i : _boxes)
	{
		// 자기자신 잘라냄
		if (i == this)
			continue;

		// 벗어난 애들 잘라냄
		if (i->_top < this->_bottom ||
			i->_bottom > this->_top ||
			i->_left > this->_right ||
			i->_right < this->_left)
			continue;
		// 여기까지 왔으면 겹친 애들
		// 왼쪽에서 온놈이면
		if (i->_right < this->_right)
			xFlip = true;
		if (i->_left > this->_left)//오른쪽에서온놈
			xFlip = true;
		if (i->_bottom > this->_bottom)
			yFlip = true;
		if (i->_top < this->_top)
			yFlip = true;
	}
	if (xFlip)
		_xStep = -_xStep;
	if (yFlip)
		_yStep = -_yStep;
}

void MyBox::draw()
{
	glColor3f(_r, _g, _b);
	glRectf(_left, _bottom, _right, _top);
}

void MyBox::advance()
{
	_left += _xStep;
	_right += _xStep;
	_top += _yStep;
	_bottom += _yStep;
}

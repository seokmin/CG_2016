
#include <gl/glut.h>
#include <windows.h>
#include <array>
#include "MyBox.h"


float window_width = 100 * 800 / 600;
float window_height = 100;

std::list<MyBox*> &boxes = MyBox::_boxes;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	{	//render codes here
		for (auto i : boxes)
			i->draw();
	}

	glutSwapBuffers();
}

void SetupRC(void)

{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	new MyBox(-50, -50, 20, 1, 0, 0, 1.5f, 1.f);
	new MyBox(-50, +50, 30, 0, 1, 0, 1.f, -1.5f);
	new MyBox(+50, +50, 40, 0, 0, 1, -1.5f, -1.f);
	new MyBox(+50, -50, 50, 1, 1, 1, -1.f, 1.5f);
	new MyBox(-window_width - window_height * 2, -window_height, 2 * window_height, 1, 1, 1, 0.f, 0.f);//��
	new MyBox(window_width, -window_height, window_height * 2, 1, 1, 1, 0.f, 0.f);//��
	new MyBox(-window_width, window_height, 2 * window_width, 1, 1, 1, 0.f, 0.f);//��
	new MyBox(-window_width, -window_height - 2*window_width, 2 * window_width, 1, 1, 1, 0.f, 0.f);//��
}

void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	if (w <= h)
	{
		window_width = 100.f;
		window_height = 100.f * h / w;
	}
	else
	{
		window_width = 100.f * w / h;
		window_height = 100.f;
	}
	glOrtho(-window_width, window_width, -window_height, window_height, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TimerFunc(int value)
{

	for (auto i : boxes)
	{
		i->advance();
	}
	for (auto i : boxes)
	{
		i->checkBoundary();
	}
	glutPostRedisplay();
	glutTimerFunc(17, TimerFunc, 1);
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow("CG_2016");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(500, TimerFunc, 1);
	SetupRC();
	glutMainLoop();
}
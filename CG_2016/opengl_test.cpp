#include <windows.h>
#include <gl/glut.h>

struct Box
{
	GLfloat posX;
	GLfloat posY;
	GLsizei rectSize;

	GLfloat r;
	GLfloat g;
	GLfloat b;

	GLfloat xstep;
	GLfloat ystep;
};


GLfloat window_width;
GLfloat window_height;

#define NUM_OF_BOXES 4
Box boxes[NUM_OF_BOXES];

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	{	//render codes here

		for (auto& i : boxes)
		{
			glColor3f(i.r,i.g,i.b);
			glRectf(i.posX, i.posY, i.posX + i.rectSize, i.posY + i.rectSize);
		}
			// 		for (auto i = 0; i < NUM_OF_BOXES; ++i)
		// 			glRectf(boxes[i].posX, boxes[i].posY, boxes[i].posX + boxes[i].rectSize, boxes[i].posY + boxes[i].rectSize);
	}

	glutSwapBuffers();
}

void SetupRC(void)

{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	window_width = 100.f;
	window_height = 100.f;
	GLsizei rectSize = 50.f;
	ZeroMemory(boxes, NUM_OF_BOXES);
	boxes[0] = { -window_width,window_height - rectSize,rectSize, 1.f,0.f,0.f,2.f,2.f };
	boxes[1] = { window_width - rectSize,window_height - rectSize,rectSize,0.f,1.f,0.f,2.f,2.f };
	boxes[2] = { -window_width,-window_height,rectSize,0.f,0.f,1.f,2.f,2.f };
	boxes[3] = { window_width - rectSize,-window_height,rectSize,1.f,1.f,1.f,2.f,2.f };

}

void ChangeSize(GLsizei w, GLsizei h)
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
	for (auto& i : boxes)
	{
		if (i.posX >= window_width - i.rectSize || i.posX <= -window_width)
			i.xstep = -i.xstep;
		if (i.posY >= window_height - i.rectSize || i.posY <= -window_height)
			i.ystep = -i.ystep;

		if (i.posX >= window_width - i.rectSize)
			i.posX = window_width - i.rectSize - 1;
		if (i.posY >= window_height - i.rectSize)
			i.posY = window_height - i.rectSize - 1;		if (i.posX <= -window_width)
			i.posX = -window_width+1;
		if (i.posY <= -window_height)
			i.posY = -window_height+ 1;
		i.posX += i.xstep;
		i.posY += i.ystep;

	}

	glutPostRedisplay();
	glutTimerFunc(33, TimerFunc, 1);
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow("CG_2016");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(2000, TimerFunc, 1);
	SetupRC();
	glutMainLoop();
}
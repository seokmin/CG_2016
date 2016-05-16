#include <windows.h>
#include <gl\glut.h>
#include <math.h>

GLfloat xRot = 0.f;
GLfloat yRot = 0.f;
const GLfloat GL_PI = 3.1415;

bool iCull = FALSE;
bool iOutline = FALSE;
bool iDepth = FALSE;

void ProcessMenu(int value) //add
{
	switch (value)
	{
	case 1:
		iDepth = !iDepth;
		break;
	case 2:
		iCull = !iCull;
		break;
	case 3:
		iOutline = !iOutline;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void RenderScene(void)
{
	GLfloat x, y, z, angle;
	int iPivot = 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xRot, 1.f, 0.f, 0.f);
	glRotatef(yRot, 0.f, 1.f, 0.f);

	if (iCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
	if (iDepth)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	if (iOutline)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex3f(0.f, 0.f, 75.f);//기준점
		for (angle = 0.f; angle < (2.f * GL_PI); angle += (GL_PI / 8.f))
		{
			x = 50.f*sin(angle);
			y = 50.f*cos(angle);

			if (iPivot % 2 == 0)
				glColor3f(0.f, 1.f, 0.f);
			else
				glColor3f(1.f, 0.f, 0.f);
			iPivot++;
			glVertex2f(x, y);

		}
	}glEnd();
	glBegin(GL_TRIANGLE_FAN);
	{
		glVertex2d(0.f, 0.f);
		for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
		{
			x = 50.0f*sin(angle);
			y = 50.0f*cos(angle);
			if ((iPivot % 2) == 0) // add
				glColor3f(0.0f, 1.0f, 0.0f);
			else
				glColor3f(1.0f, 0.0f, 0.0f);
			iPivot++;
			glVertex2f(x, y);
		}
	}glEnd();
	
	glPopMatrix();
	glutSwapBuffers();
}
void KeyControl(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
	glutPostRedisplay();
}

void SetupRC(void)
{
	glClearColor(0.f,0.f, 0.f, 1.0f);
	glColor3f(0.f, 1.f, 0.f);
	glShadeModel(GL_FLAT);
	glFrontFace(GL_CW);
}
void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(512,512);
	glutCreateWindow("Springs!");
	
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("깊이 테스트", 1);
	glutAddMenuEntry("은면 제거", 2);
	glutAddMenuEntry("뒷면 라인 그리기", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();
}
#include <windows.h>
#include <gl\glut.h>
#include <math.h>

const GLfloat GL_PI = 3.1415;

void SetupRC(void)
{
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glColor3f(0.f, 1.f, 0.f);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000/60, TimerFunc, 1);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;

	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange*2.f, nRange*2.f);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange*2.f, nRange*2.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void RenderScene(void)
{
	static GLfloat fElect1 = 0.f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.f, 0.f, -100.f);
	glColor3ub(255, 0, 0);
	glutSolidSphere(10.f, 15, 15);

	glPushMatrix();
	glRotatef(fElect1, 0.f, 1.f, 0.f);
	glTranslatef(90.f, 0.f, 0.f);
	glColor3ub(255, 255, 0);
	glutSolidSphere(6.f, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45.f, 0.f, 1.f, 1.f);
	glRotatef(fElect1, 0.f, 1.f, 0.f);
	glTranslatef(-70.f, 0.f, 0.f);
	glutSolidSphere(6.f, 15, 15);
	glPopMatrix();


	glPushMatrix();
	glRotatef(90.f, 0.f, 0.f, 1.f);
	glRotatef(fElect1, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, 60.f);
	glutSolidSphere(6.f, 15, 15);
	glPopMatrix();

	fElect1 += 2.f;
	if (fElect1 > 360.f)
		fElect1 = 0.f;

	glutSwapBuffers();
}


void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(512,512);
	glutCreateWindow("Atom!");
	glutTimerFunc(1000/60, TimerFunc, 1);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();
}
/*
#include <windows.h>
#include <gl\glut.h>
#include <math.h>

const GLfloat GL_PI = 3.1415;

void SetupRC(void)
{
	// Light Values
	GLfloat ambientLight[] = { 0.5f,0.5f,0.5f,0.5f };

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	// Áß¿ä
	glEnable(GL_LIGHTING);

	

}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000/60, TimerFunc, 1);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat fAspect;

	glViewport(0, 0, w, h);
	
	fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	
	gluPerspective(60.f, fAspect, 1.f, 500.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.f, 0.f, -200.f);

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
}*/
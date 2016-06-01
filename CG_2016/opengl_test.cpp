#include <windows.h>
#include <gl\glut.h>
#include <math.h>

const GLfloat GL_PI = 3.1415;

void SetupRC(void)
{
	// ºû
	GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat lightPos[] = { 0, 0, -100, 1.0f };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

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
	static GLfloat fElect2 = 0.f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//ÅÂ¾ç
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.f, 0.f, -100.f);
	glColor3ub(255, 0, 0);
	glutSolidSphere(10.f, 15, 15);
	
	//Áö±¸
	glPushMatrix();
	glRotatef(fElect1, 0.f, 1.f, 0.f);
	glTranslatef(50.f, 0.f, 0.f);
	glColor3ub(255, 255, 0);
	glutSolidSphere(6.f, 15, 15);

	glPushMatrix();
	glRotatef(fElect2, 0.f, 1.f, 0.f);
	glTranslatef(-20.f, 0.f, 0.f);
	glColor3ub(0, 255, 0);
	glutSolidSphere(3.f, 15, 15);
	glPopMatrix();

	fElect1 += 0.5f;
	fElect2 += 2.f;
	if (fElect1 > 360.f)
		fElect1 = 0.f;
	if (fElect2 > 360.f)
		fElect2 = 0.f;

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
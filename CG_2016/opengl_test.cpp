#include <windows.h>
#include <gl\glut.h>
#include <math.h>
#include "lodepng.h"


const GLfloat GL_PI = 3.1415;
static GLfloat xRot = 0.f;
static GLfloat yRot = 0.f;
static GLfloat zDistance = 0.f;

GLfloat amb[] = {0.3f, 0.3f, 0.3f, 1.f};
GLfloat dif[] = {0.8f, 0.8f, 0.8f, 1.f};
GLfloat lightPos[] = { -50.f, 50.f, 100.f, 1.f };

GLuint texID;

void SetupRC(void)
{
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
}

void LoadTexture()
{
	std::vector<unsigned char> image;
	unsigned width, height, error;

	error = lodepng::decode(image, width, height, "texture.png");

	if (error)
		printf("error %u: %s\n", error, lodepng_error_text(error));
	printf("\nimage size is %i", image.size());

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,image.data());


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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	{
		glRotatef(xRot, 1.f, 0.f, 0.f);
		glRotatef(yRot, 1.f, 0.f, 0.f);
		glTranslatef(0.f, 0.f, zDistance);

		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_AMBIENT,amb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE,dif);
		glLightfv(GL_LIGHT0, GL_POSITION,lightPos);
		glEnable(GL_LIGHT0);

		glColor3f(1.f,1.f,1.f);
		glutSolidTeapot(10.f);
	}
	glPopMatrix();

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
	LoadTexture()

	glutMainLoop();
}
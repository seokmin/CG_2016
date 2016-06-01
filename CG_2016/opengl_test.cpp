#include <windows.h>
#include <gl\glut.h>
#include <math.h>
#include "lodepng.h"

int window_width;
int window_height;
int width_devide;
int height_devide;
void Mouse(int iButton, int iState, int x, int y);
struct MyCircle
{
	GLfloat x;
	GLfloat y;
	GLfloat r;
};

std::vector<MyCircle> g_circles;

const GLfloat GL_PI = 3.1415;
GLuint texIDs[3];

// ºû
GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
GLfloat lightPos[] = { 0, 0, -100, 1.0f };

GLUquadricObj *sphere = nullptr;

void LoadTexture(std::string filename)
{
	std::vector<unsigned char> image;
	unsigned width, height, error;

	error = lodepng::decode(image, width, height, filename);

	if (error)
		printf("error %u: %s\n", error, lodepng_error_text(error));
	printf("\nimage size is %i", image.size());


	static auto index = 0;
	glBindTexture(GL_TEXTURE_2D, texIDs[index++]);

	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

}

void SetupRC(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	glGenTextures(3, texIDs);

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
	window_width = w;
	window_height = h;

	if (w <= h)
	{
		width_devide = 100.f;
		height_devide = 100.f * h / w;
	}
	else
	{
		width_devide = 100.f * w / h;
		height_devide = 100.f;
	}
}

void RenderScene(void)

{
	static GLfloat fElect1 = 0.f;
	static GLfloat fElect2 = 0.f;
	static GLfloat earthPingPing = 0.f;
	static GLfloat moonPingPing = 0.f;


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto i : g_circles)
	{
		glLoadIdentity();
		glPushMatrix();
		glTranslatef(i.x*2, i.y*2, -300.f);
		glBindTexture(GL_TEXTURE_2D, texIDs[0]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		gluSphere(sphere, i.r, i.r*3, i.r*3);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glPopMatrix();
	}
	//ÅÂ¾ç
	glLoadIdentity();
	glTranslatef(0.f, 0.f, -100.f);
	glBindTexture(GL_TEXTURE_2D, texIDs[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glPushMatrix();
	glRotatef(fElect1, 0.f, 1.f, 0.f);
	gluSphere(sphere, 15.f, 50, 50);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPopMatrix();
	//Áö±¸
	glPushMatrix();
	glRotatef(fElect1, 0.f, 1.f, 0.f);

	glTranslatef(50.f, 0.f, 0.f);
	glBindTexture(GL_TEXTURE_2D, texIDs[1]);
	glPushMatrix();
	glRotatef(-earthPingPing, 0.f, 1.f, 0.f);
	gluSphere(sphere, 6.f, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(fElect2, 0.f, 1.f, 0.f);
	glTranslatef(-20.f, 0.f, 0.f);
	glBindTexture(GL_TEXTURE_2D, texIDs[2]);
	glPushMatrix();
	glRotatef(moonPingPing, 0.f, 1.f, 0.f);
	gluSphere(sphere, 3.f, 15, 15);
	glPopMatrix();
	glPopMatrix(); glPopMatrix();

	fElect1 += 0.5f;
	if (fElect1 > 360.f)
		fElect1 = 0.f;
	fElect2 += 2.f;
	if (fElect2 > 360.f)
		fElect2 = 0.f;
	earthPingPing += 6.f;
	if (earthPingPing > 360.f)
		earthPingPing = 0.f;
	moonPingPing += 10.f;
	if (moonPingPing > 360.f)
		moonPingPing = 0.f;

	glutSwapBuffers();
}


void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(512,512);
	glutCreateWindow("Solar System!");
	glutTimerFunc(1000/60, TimerFunc, 1);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(Mouse);
	SetupRC();

	LoadTexture("sun.png");
	LoadTexture("earth.png");
	LoadTexture("moon.png");
	
	glutMainLoop();
}

void Mouse(int iButton, int iState, int x, int y)
{
	if (iState == GLUT_DOWN)
	{
		switch (iButton)
		{
		case GLUT_LEFT_BUTTON:
			static auto size = 5.f;
			x -= window_width/2;
			y -= window_height/2;
			y *= -1;

			x *= (float)width_devide / ((float)window_width / 2.f);
			y *= (float)height_devide / ((float)window_height / 2.f);

			g_circles.emplace_back(MyCircle{(float)x,(float)y,size});
			size += 1.f;
			break;
		}
	}
}
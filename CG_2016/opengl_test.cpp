#include <windows.h>
#include <gl\glut.h>
#include <math.h>

GLfloat xRot = 0.f;
GLfloat yRot = 0.f;

struct MyColor
{
	float r;
	float g;
	float b;
};

struct MyPoint
{
	float x;
	float y;
	float z;
	MyColor rgb;
};

void drawVertex(MyPoint point)
{
	glColor3f(point.rgb.r, point.rgb.g, point.rgb.b);
	glVertex3f(point.x, point.y, point.z);
}

//½Ã°è¹æÇâÀ¸·Î ³Ö¾îÁà¾ßÇÔ
void drawRect(MyPoint p1, MyPoint p2, MyPoint p3, MyPoint p4)
{
	drawVertex(p1);
	drawVertex(p2);
	drawVertex(p4);
	drawVertex(p3);
}

void RenderScene(void)
{
	GLfloat x, y, z, angle;
	int iPivot = 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xRot, 1.f, 0.f, 0.f);
	glRotatef(yRot, 0.f, 1.f, 0.f);
	glBegin(GL_QUAD_STRIP);
	{
		const MyColor red = { 1.f,0.f,0.f };
		const MyColor green = { 0.f,1.f,0.f };
		const MyColor blue = { 0.f,0.f,1.f };
		const MyColor white = { 1.f,1.f,1.f };
		const MyColor cheongRok = { 0.f,1.f,1.f };
		const MyColor jahong = { 1.f,0.f,1.f };
		const MyColor yellow = { 1.f,1.f,0.f };
		const MyColor black = { 0.f,0.f,0.f };

		float size = 40.f;
		float centerZ = 0.f;
		MyPoint vertices[8] = {
			{ -size,-size,+size,blue },// ¾Õ¸é
			{ -size,+size,+size,cheongRok },// ¾Õ¸é
			{ +size,+size,+size,white },// ¾Õ¸é
			{ +size,-size,+size,jahong },// ¾Õ¸é
			{ +size,-size,-size,red },// µÞ¸é
			{ +size,+size,-size,yellow },// µÞ¸é
			{ -size,+size,-size,green },// µÞ¸é
			{ -size,-size,-size,black },// µÞ¸é
		};
		drawRect(vertices[0], vertices[1], vertices[2], vertices[3]);//¾Õ
		drawRect(vertices[7], vertices[6], vertices[1], vertices[0]);//¿Þ
		drawRect(vertices[2], vertices[5], vertices[4], vertices[3]);//¿À
		drawRect(vertices[1], vertices[6], vertices[5], vertices[2]);//»ó
		drawRect(vertices[7], vertices[0], vertices[3], vertices[4]);//ÇÏ
		drawRect(vertices[4], vertices[5], vertices[6], vertices[7]);//ÈÄ
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
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
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
	glutCreateWindow("Cube!");

	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();
}
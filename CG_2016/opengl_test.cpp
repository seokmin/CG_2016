#include <windows.h>
#include <gl\glut.h>
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(0.0f, 0.0f, 50.0f, 30.0f);
	glFlush();
}
void SetupRC(void)
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}
void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-100.0f, 100.0f, -
			100.0f*h / w, 100.0f*h / w, 1.0f, -1.0f);
	else
		glOrtho(-100.0f*w / h, 100.0f*w / h, -
			100.0f, 100.0f, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void main(void)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Rectangle");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();
}
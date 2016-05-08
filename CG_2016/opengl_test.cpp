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

struct CollisionBox
{
	GLfloat centerX;
	GLfloat centerY;
	GLfloat width;
	GLfloat height;
};

GLfloat window_width = 100 * 800 / 600;
GLfloat window_height = 100;



#define NUM_OF_BOXES 8
Box boxes[NUM_OF_BOXES];
Box yebiBoxes[NUM_OF_BOXES];
CollisionBox collisionBoxes[NUM_OF_BOXES];
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
	GLsizei rectSize = 40;
	ZeroMemory(boxes, NUM_OF_BOXES);
	boxes[0] = { -window_width,window_height - rectSize,rectSize, 1.f,0.f,0.f,3.f,3.f};
	boxes[1] = { window_width - rectSize,window_height - rectSize,rectSize,0.f,1.f,0.f,3.f,3.f };
	boxes[2] = { -window_width,-window_height,rectSize,0.f,0.f,1.f,3.f,3.f };
	boxes[3] = { window_width - rectSize,-window_height,rectSize,1.f,1.f,1.f,3.f,3.f };

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

	boxes[4] = { window_width,-window_height,2 * (int)window_height,1.f,1.f,1.f,0.f,0.f };
	boxes[5] = { -window_width - 2.f*window_height,-window_height,2 * (int)window_height,1.f,1.f,1.f,0.f,0.f };
	boxes[6] = { -window_width,window_height,2 * (int)window_width,1.f,1.f,1.f,0.f,0.f };
	boxes[7] = { -window_width,-window_height - 2.f*window_width,2 * (int)window_width,1.f,1.f,1.f,0.f,0.f };
}

void TimerFunc(int value)
{
	for (auto i = 0; i < NUM_OF_BOXES; ++i)
	{
		yebiBoxes[i] = boxes[i];
		auto half = boxes[i].rectSize / 2.f;
		auto& currentCb = collisionBoxes[i];
		currentCb.centerX = boxes[i].posX + half;
		currentCb.centerY = boxes[i].posY + half;
		currentCb.width = half;
		currentCb.height = half;
	}
	for (auto i = 0; i<NUM_OF_BOXES; ++i)
	{
		auto& currentBox = boxes[i];
		if(currentBox.xstep == 0 || currentBox.ystep == 0)
			continue;
		auto& yebiBox = yebiBoxes[i];
		auto w_h = window_height;
		for (auto j = 0; j<NUM_OF_BOXES; ++j)
		{
			if(i==j)
				continue;
			auto& collisionBox = collisionBoxes[j];

			auto currentRB = currentBox.posX + currentBox.rectSize;
			auto currentLB = currentBox.posX;
			auto currentTB = currentBox.posY + currentBox.rectSize;
			auto currentBB = currentBox.posY;
			auto targetRB = collisionBox.centerX + collisionBox.width;
			auto targetLB = collisionBox.centerX - collisionBox.width;
			auto targetTB = collisionBox.centerY + collisionBox.height;
			auto targetBB = collisionBox.centerY - collisionBox.height;

			//겹치는 사각형
			auto fightingW = 0;
			auto fightingH = 0;

			//충돌 아닐시 continue
			if (currentLB > targetRB || currentRB < targetLB || currentTB < targetBB || currentBB > targetTB)
				continue;
			fightingW = min(currentRB, targetRB) - max(currentLB, targetLB);
			fightingH = min(currentTB, targetTB) - max(currentBB, targetBB);
			if (fightingH > fightingW)
			{
				yebiBox.xstep *= -1;
				//튕기기
				if (currentRB < targetRB)//왼쪽에서 들어왔으면
					yebiBox.posX = targetLB - currentBox.rectSize;
				else
					yebiBox.posX = targetRB;
			}
			else if (fightingW > fightingH)
			{
				if (currentTB < targetTB)
					yebiBox.posY = targetBB - currentBox.rectSize;
				else
					yebiBox.posY = targetTB;
				yebiBox.ystep *= -1;
			}
			else
			{
				yebiBox.xstep *= -1;
				yebiBox.ystep *= -1;
				if (currentRB < targetRB)//왼쪽에서 들어왔으면
					yebiBox.posX = targetRB - currentBox.rectSize;
				else
					yebiBox.posX = targetRB;
				if (currentTB < targetTB)
					yebiBox.posY = targetTB - currentBox.rectSize;
				else
					yebiBox.posY = targetTB;
			}


			break;
		}
		yebiBox.posX += yebiBox.xstep;
		yebiBox.posY += yebiBox.ystep;
	}
	for (auto i = 0; i < NUM_OF_BOXES; ++i)
		boxes[i] = yebiBoxes[i];
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
	glutTimerFunc(500, TimerFunc, 1);
	SetupRC();
	glutMainLoop();
}
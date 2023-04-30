#include <GL/glut.h>
#include <stdlib.h>

static void myInit(void);
static void display(void);

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);

	glutCreateWindow("Sierpinski Gasket");
	glutDisplayFunc(display);

	myInit();

	glutMainLoop();

	return 0;
}

static void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 500.0, 0.0, 500.0, 500.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
}

static void display(void)
{
	typedef GLfloat point2[2];

	int i, k;
	point2 p = {75.0, 50.0};
	point2 vertices[3] = {
		{0.0, 0.0},
		{250.0, 500.0},
		{500.0, 0.0}
	};

	glClear(GL_COLOR_BUFFER_BIT);

	for (k = 0; k < 500000; ++k)
	{
		i = rand() % 3;
		p[0] = (p[0] + vertices[i][0]) / 2.0;
		p[1] = (p[1] + vertices[i][1]) / 2.0;

		glBegin(GL_POINTS);
			glVertex2fv(p);
		glEnd();
	}

	glFlush();
}

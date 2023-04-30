#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

typedef GLfloat point2[2];

static void myInit(void);
static void display(void);
static void divide_triangle(point2 a, point2 b, point2 c, int m);
static void triangle(point2 a, point2 b, point2 c);

static point2 v[3] = {
	//{-1.0, -0.58}, {1.0, -0.58}, {0.0, 1.15}
	{-1.8, -1.8}, {1.8, -1.8}, {0.0, 1.8}
};

static int n;

int main(int argc, char **argv)
{
	if (argc == 1) {
		printf("An integer argument of recursion depth is expected.\n");
		return (0);
	}
	
	n = atoi(argv[1]);

	if (n <= 0) {
		printf("Error. A positive integer argument is expected.\n");
		return (1);
	}

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
	glColor3f(0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, -2.0);
	glMatrixMode(GL_MODELVIEW);
}

static void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	divide_triangle(v[0], v[1], v[2], n);
	glFlush();
}

static void divide_triangle(point2 a, point2 b, point2 c, int m)
{
	point2 v0, v1, v2;
	int i;

	if (m > 0)
	{
		for (i = 0; i < 2;  i++)
			v0[i] = (a[i] + b[i]) / 2.0;
		for (i = 0; i < 2;  i++)
			v1[i] = (a[i] + c[i]) / 2.0;
		for (i = 0; i < 2;  i++)
			v2[i] = (b[i] + c[i]) / 2.0;

		divide_triangle(a, v0, v1, m - 1);
		divide_triangle(b, v2, v0, m - 1);
		divide_triangle(c, v1, v2, m - 1);
	}
	else 
	{
		triangle(a, b, c);
	}
}

static void triangle(point2 a, point2 b, point2 c)
{
	glBegin(GL_TRIANGLES);
		glVertex2fv(a);
		glVertex2fv(b);
		glVertex2fv(c);
	glEnd();
}

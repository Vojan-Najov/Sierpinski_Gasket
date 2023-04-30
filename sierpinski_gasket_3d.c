#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

typedef float point3[3];

static void myReshape(int w, int h);
static void display(void);
static void tetrahedron(int m);
void divide_triangle(point3 a, point3 b, point3 c, int m);
void triangle(point3 a, point3 b, point3 c);

static int n;

point3 v[] = {
	{0.0, 0.0, 1.0},
	{0.0, 0.942809, -0.33333},
	{-0.816497, -0.471405, -0.333333},
	{0.816597, -0.471405, -0.333333}
};

point3 vertices[4] = {
	{-250.0, -100.0, 0.0},
	{0.0, 200.0, 0.0},
	{250.0, -100.0, 0.0},
	{0.0, 0.0, 500.0}
};

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

	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);

	glutCreateWindow("Sierpinski Gasket");

	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutMainLoop();

	return 0;
}

static void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(-2.0, 2.0,
				-2.0 * (GLfloat)h / (GLfloat)w, 
				2.0 * (GLfloat)h / (GLfloat)w,
				-2.0, 2.0);
	} else {
		glOrtho(-2.0 * (GLfloat)h / (GLfloat)w, 
				2.0 * (GLfloat)h / (GLfloat)w,
				-2.0, 2.0, -2.0, 2.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

static void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	tetrahedron(n);
	glFlush();
}

static void tetrahedron(int m)
{
	glColor3f(1.0, 0.0, 0.0);
	divide_triangle(v[0], v[1], v[2], m);
	glColor3f(0.0, 1.0, 0.0);
	divide_triangle(v[3], v[2], v[1], m);
	glColor3f(0.0, 0.0, 1.0);
	divide_triangle(v[0], v[3], v[1], m);
	glColor3f(0.0, 0.0, 0.0);
	divide_triangle(v[0], v[2], v[3], m);
}

void divide_triangle(point3 a, point3 b, point3 c, int m)
{
	point3 v1, v2, v3;
	int j;

	if (m > 0) {
		for (j = 0; j < 3; ++j) {
			v1[j] = (a[j] + b[j]) / 2.0;
		}
		for (j = 0; j < 3; ++j) {
			v2[j] = (a[j] + c[j]) / 2.0;
		}
		for (j = 0; j < 3; ++j) {
			v3[j] = (b[j] + c[j]) / 2.0;
		}
		divide_triangle(a, v1, v2, m - 1);
		divide_triangle(c, v2, v3, m - 1);
		divide_triangle(b, v3, v1, m - 1);
	} else {
		triangle(a, b, c);
	}


}

void triangle(point3 a, point3 b, point3 c)
{
	glBegin(GL_POLYGON);
		glNormal3fv(a);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
	glEnd();
}


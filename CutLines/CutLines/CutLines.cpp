#include<GL/freeglut.h>
#include<iostream>
#include<stdlib.h>
#include <algorithm>
using namespace std;
#define xl 100
#define xr 300
#define yb 100
#define yt 300
void drawLine(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex2i(x1, y1);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex2i(x2, y2);
	glEnd();
}
void drawborder()
{
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(xl, yb);
	glVertex2f(xl, yt);
	glVertex2f(xr, yt);
	glVertex2f(xr, yb);
	glEnd();
}
int xs , ys, xe , ye ;
int getcode(int x, int y)
{
	int code = 0;
	if (x < xl) code += 1;
	if (x > xr) code += 2;
	if (y < yb) code += 4;
	if (y > yt) code += 8;
	return code;
}
void cut(int *x, int *y, int border, int m, float k)
{
	float x0, y0;
	switch (m)
	{
	case 1: {
		y0 = *y + k * (border - *x);
		x0 = border;
		*x = x0;
		*y = y0;
		break;
	}
	case 2: {
		y0 = *y + k * (border - *x);
		x0 = border;
		*x = x0;
		*y = y0;
		break;
	}
	case 3: {
		x0 = *x + (border - *y) / k;
		y0 = border;
		*x = x0;
		*y = y0;
		break;
	}
	case 4: {
		x0 = *x + (border - *y) / k;
		y0 = border;
		*x = x0;
		*y = y0;
		break;
	}
	}
}
void Cohen_Sutherland(int &xs, int &ys, int &xe, int &ye)
{
	int code1, code2, code, m = 1, x0, y0;
	float k;
	k = (float)(ye - ys) / (xe - xs);
	code1 = getcode(xs, ys);
	code2 = getcode(xe, ye);
	if (code1&code2) return;
	while (code1 | code2)
	{
		m = 1;
		if (code1 == 0) {
			swap(xs, xe);
			swap(ys, ye);
			swap(code1, code2);
		}
		code = code1;
		for(;code%2!=1;)
		{
			code /= 2;
			m++;
		}
		x0 = xs; y0 = ys;
		switch (m)
		{
		case 1: {
			cut(&x0, &y0, xl, m, k);
			break;
		}
		case 2: {
			cut(&x0, &y0, xr, m, k);
			break;
		}
		case 3: {
			cut(&x0, &y0, yb, m, k);
			break;
		}
		case 4: {
			cut(&x0, &y0, yt, m, k);
			break;
		}
		}
		code1 = getcode(x0, y0);
		xs = x0; ys = y0;
		swap(xs, xe);
		swap(ys, ye);
		swap(code1, code2);
	}
}
void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawborder();
	drawLine(xs, ys, xe, ye);
	glFlush();
}
void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	cout << "输入起始点和终止点\n";
	cin >> xs >> ys >> xe >> ye;
	cout << "按c裁剪,x退出" << endl;
}
void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c':
		Cohen_Sutherland(xs, ys, xe, ye);
		glutPostRedisplay();
		break;
	case 'x':
		exit(0);
		break;
	default:
		break;
	}
}
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("CUT");

	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
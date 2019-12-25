#include<Windows.h>
#include<gl/freeglut.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
static  int i = 1;

void Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);      
	glMatrixMode(GL_PROJECTION);    
	gluOrtho2D(-200.0, 200.0, -200.0, 200.0);   
}

void CirclePoint(float x, float y)
{
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(x, y);
	glVertex2f(y, x);
	glVertex2f(-y, x);
	glVertex2f(-x, y);
	glVertex2f(-x, -y);
	glVertex2f(-y, -x);
	glVertex2f(y, -x);
	glVertex2f(x, -y);
	glEnd();
}
void BresenhamCircle_Mid(float r)
{
	float d, x0, y0;
	d = 1 - r;
	x0 = 0;
	y0 = r;
	while (x0 <= y0)
	{
		CirclePoint(x0, y0);
		if (d < 0) {
			d = d + 2 * x0 + 3;
			x0++;
		}
		else {
			d = d + 2 * (x0 - y0) + 5;
			y0--; x0++;
		}
	}
	glFlush();
}
void Display(void)
{
	float r;
	cout << "Please enter the radius of the circle:" << endl;
	cin >> r;
	BresenhamCircle_Mid(r);
	system("pause");
	exit(0);
}
int main(int argc, char* argv[])

{
	glutInit(&argc, argv);				 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(400, 400);             
	glutInitWindowPosition(100, 100);       
	glutCreateWindow("Բ");                 

	glutDisplayFunc(Display);     
	Initial();                              
	glutMainLoop();                   
	return 0;
}
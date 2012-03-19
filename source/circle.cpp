#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <cmath>

using namespace std;

float cx,cy,r,num_segments;
void draw_Circle() 
{ 
	float theta = 2 * 3.1415926 / float(num_segments); 
	float tangetial_factor = tanf(theta);//calculate the tangential factor 

	float radial_factor = cosf(theta);//calculate the radial factor 

	float x = r;//we start at angle = 0 

	float y = 0; 

	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		glVertex2f(x + cx, y + cy);
		float tx = -y; 
		float ty = x; 
		x += tx * tangetial_factor; 
		y += ty * tangetial_factor;
		x *= radial_factor; 
		y *= radial_factor; 
	} 
	glEnd(); 
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	glutCreateWindow("Circle");
	glutInitWindowSize(600,600);
	glutInitWindowPosition(0,0);
	cin >> cx >> cy >> r >> num_segments;
	glutDisplayFunc(draw_Circle);
	glutMainLoop();
}

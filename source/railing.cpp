
//
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>       // Header file for trigonometric functions.


void railing (float x1,float y1,float z1,float x2, float y2, float z2) {
	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
		glVertex3f(x2+0.4,y2,z2);
		glVertex3f(x1+0.4,y1,z1);	
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x1+0.4,y1,z1);
		glVertex3f(x1+0.4,y1-0.1,z1);
		glVertex3f(x1+1.0,y1-0.1,z1);
		glVertex3f(x1+1.0,y1,z1);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x2+0.4,y2,z2);
		glVertex3f(x2+0.4,y2+0.1,z2);
		glVertex3f(x2+1.0,y2+0.1,z2);
		glVertex3f(x2+1.0,y2,z2);
	glEnd();
}


void railing_three(float x1,float y1,float z1,float x2, float y2, float z2) {
	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
		glVertex3f(x2+0.4,y2,z2+0.4);
		glVertex3f(x1+0.4,y1,z1+0.4);	
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x1+0.4,y1,z1+0.4);
		glVertex3f(x1+0.4,y1-0.1,z1+0.4);
		glVertex3f(x1+1.0,y1-0.1,z1+1.0);
		glVertex3f(x1+1.0,y1,z1+1.0);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x2+0.4,y2,z2+0.4);
		glVertex3f(x2+0.4,y2+0.1,z2+0.4);
		glVertex3f(x2+1.0,y2+0.1,z2+1.0);
		glVertex3f(x2+1.0,y2,z2+1.0);
	glEnd();
}


void railing_four(float x1,float y1,float z1,float x2, float y2, float z2) {
	z1++;
	z2++;
	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
		glVertex3f(x2+0.4,y2,z2+0.2);
		glVertex3f(x1+0.4,y1,z1+0.2);	
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x1+0.4,y1,z1+0.2);
		glVertex3f(x1+0.4,y1-0.1,z1+0.2);
		glVertex3f(x1+1.0,y1-0.1,z1+0.3);
		glVertex3f(x1+1.0,y1,z1+0.3);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x2+0.4,y2,z2+0.2);
		glVertex3f(x2+0.4,y2+0.1,z2+0.2);
		glVertex3f(x2+1.0,y2+0.1,z2+0.3);
		glVertex3f(x2+1.0,y2,z2+0.3);
	glEnd();
}



void railing_five(float x1,float y1,float z1,float x2, float y2, float z2) {

	z1+=1.3;
	z2+=1.3;
	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
		glVertex3f(x2+0.4,y2,z2-0.15);
		glVertex3f(x1+0.4,y1,z1-0.15);	
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x1+0.4,y1,z1-0.15);
		glVertex3f(x1+0.4,y1-0.1,z1-0.15);
		glVertex3f(x1+1.0,y1-0.1,z1-0.3);
		glVertex3f(x1+1.0,y1,z1-0.3);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x2+0.4,y2,z2-0.15);
		glVertex3f(x2+0.4,y2+0.1,z2-0.15);
		glVertex3f(x2+1.0,y2+0.1,z2-0.3);
		glVertex3f(x2+1.0,y2,z2-0.3);
	glEnd();
}


void railing_six(float x1,float y1,float z1,float x2, float y2, float z2) {

	z1+=1.3;
	z2+=1.3;

	z1-=0.3;
	z2-=0.3;

	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
		glVertex3f(x2+0.4,y2,z2-0.4);
		glVertex3f(x1+0.4,y1,z1-0.4);	
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x1+0.4,y1,z1-0.4);
		glVertex3f(x1+0.4,y1-0.1,z1-0.4);
		glVertex3f(x1+1.0,y1-0.1,z1-1.0);
		glVertex3f(x1+1.0,y1,z1-1.0);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x2+0.4,y2,z2-0.4);
		glVertex3f(x2+0.4,y2+0.1,z2-0.4);
		glVertex3f(x2+1.0,y2+0.1,z2-1.0);
		glVertex3f(x2+1.0,y2,z2-1.0);
	glEnd();
}

void railing_side(float x1,float y1,float z1,float x2, float y2, float z2) {

	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
		glVertex3f(x2+0.2,y2,z2);
		glVertex3f(x1+0.2,y1,z1);	
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x1+0.2,y1,z1);
		glVertex3f(x1+0.2,y1-0.1,z1);
		glVertex3f(x1+1.3,y1-0.1,z1);
		glVertex3f(x1+1.3,y1,z1);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x2+0.2,y2,z2);
		glVertex3f(x2+0.2,y2+0.1,z2);
		glVertex3f(x2+1.3,y2+0.1,z2);
		glVertex3f(x2+1.3,y2,z2);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x1+1.3,y1,z1);
		glVertex3f(x2+1.3,y2,z2);
		glVertex3f(x2+1.5,y2,z2);
		glVertex3f(x1+1.5,y1,z1);	
	glEnd();

}



void make_Railing()
{
	float x1 = -7.0f,y1 = 1.5f,z1 = 3.0f;
	float x2 = -7.0f,y2 = 1.0f,z2 = 3.0f;

	int i;
	glColor3f(0.8,0.8,0.8);
	for( i = 1; i <= 2; i++ ) {
		railing(x1,y1,z1,x2,y2,z2);
		x1+=1.0;
		x2+=1.0;
	}
//	x1++;
//	x2++;
	
	railing_three(x1,y1,z1,x2,y2,z2);
	x1++;
	x2++;

	railing_four(x1,y1,z1,x2,y2,z2);
	x1++;
	x2++;

	railing_five(x1,y1,z1,x2,y2,z2);
	x1++;
	x2++;

	railing_six(x1,y1,z1,x2,y2,z2);
	x1++;
	x2++;

	/*for( i = 6; i <= 6; i++ ) {
	//	railing(x1,y1,z1,x2,y2,z2);
		x1+=1.0;
		x2+=1.0;
	}*/

	for( i = 7; i <= 10; i++ ) {
		railing(x1,y1,z1,x2,y2,z2);
		x1+=1.0;
		x2+=1.0;
	}
	railing_side(3.0,1.5,3.0,3.0,1.0,3.0);

	x1 = -7.0f; y1 = 2.5f; z1 = 1.5f;
	x2 = -7.0f; y2 = 2.0f; z2 = 1.5f;

	for( i = 1; i <= 10; i++ ) {
		railing(x1,y1,z1,x2,y2,z2);
		x1+=1.0;
		x2+=1.0;
	}

	railing_side(3.0,2.5,3.0,3.0,2.0,3.0);
}

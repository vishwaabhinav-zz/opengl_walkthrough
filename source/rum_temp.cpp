
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>       // Header file for trigonometric functions.

//#include "bed.cpp"

void render_Walls_Upper( float x1, float y1, float z1,float z2 ) {
///////////external wall
	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1);
		glVertex3f(x1+1.0,y1,z1);
		glVertex3f(x1+1.0,y1+1.0,z1);
		glVertex3f(x1,y1+1.0,z1);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x1+1.4,y1,z1);
		glVertex3f(x1+2.0,y1,z1);
		glVertex3f(x1+2.0,y1+1.0,z1);
		glVertex3f(x1+1.4,y1+1.0,z1);
	glEnd();
/////////////back partition
	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z2+1.0f);
		glVertex3f(x1+1.6,y1,z2+1.0f);
		glVertex3f(x1+1.6,y1+1.0,z2+1.0f);
		glVertex3f(x1,y1+1.0,z2+1.0f);
	glEnd();


/*	glBegin(GL_QUADS);
		glVertex3f(x1+1.4,y1,z2+1.0f);
		glVertex3f(x1+2.0,y1,z2+1.0f);
		glVertex3f(x1+2.0,y1+1.0,z2+1.0f);
		glVertex3f(x1+1.4,y1+1.0,z2+1.0f);
	glEnd();*/
//////////////////////////////////////
	glBegin(GL_QUADS);
		glVertex3f(x1+1.0,y1+0.8,z1);
		glVertex3f(x1+1.4,y1+0.8,z1);
		glVertex3f(x1+1.4,y1+1.0,z1);
		glVertex3f(x1+1.0,y1+1.0,z1);
	glEnd();


	glBegin(GL_QUADS);
		glVertex3f(x1+2.0,y1,z1);
		glVertex3f(x1+2.0,y1,z2);
		glVertex3f(x1+2.0,y1+1.0,z2);
		glVertex3f(x1+2.0,y1+1.0,z1);
	glEnd();
}


void render_Walls_Lower( float x1, float y1, float z1,float z2 ) {
///external partition
	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z1);
		glVertex3f(x1+1.0,y1,z1);
		glVertex3f(x1+1.0,y1+1.0,z1);
		glVertex3f(x1,y1+1.0,z1);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x1,y1,z2+1.0f);
		glVertex3f(x1+1.6,y1,z2+1.0f);
		glVertex3f(x1+1.6,y1+1.0,z2+1.0f);
		glVertex3f(x1,y1+1.0,z2+1.0f);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x1+1.4,y1,z1);
		glVertex3f(x1+2.0,y1,z1);
		glVertex3f(x1+2.0,y1+1.0,z1);
		glVertex3f(x1+1.4,y1+1.0,z1);
	glEnd();

////////////front partition
	glBegin(GL_QUADS);
		glVertex3f(x1+0.4,y1,z1-1.0f);
		glVertex3f(x1+2.0,y1,z1-1.0f);
		glVertex3f(x1+2.0,y1+1.0,z1-1.0f);
		glVertex3f(x1+0.4,y1+1.0,z1-1.0f);
	glEnd();
/////////////////////////////////////////////////////////////////////////////////
	glBegin(GL_QUADS);
		glVertex3f(x1+1.0,y1+0.8,z1);
		glVertex3f(x1+1.4,y1+0.8,z1);
		glVertex3f(x1+1.4,y1+1.0,z1);
		glVertex3f(x1+1.0,y1+1.0,z1);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(x1+2.0,y1,z1);
		glVertex3f(x1+2.0,y1,z2);
		glVertex3f(x1+2.0,y1+1.0,z2);
		glVertex3f(x1+2.0,y1+1.0,z1);
	glEnd();
}


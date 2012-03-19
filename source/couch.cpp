
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>       // Header file for trigonometric functions.

#define MATTRESS 0.2, 0.2, 0.2, 0.0
#define BACK_MATTRESS 0.3, 0.3, 0.3, 0.0
#define SIDE_MATTRESS 0.4, 0.4, 0.4, 0.0

void renderCouch(void) {
	//BAse
	glColor4d(MATTRESS);
	glPushMatrix();
	glTranslated(0.0125, 0.0, -0.10);
	glScaled(0.4, 0.1, 0.8);
	glTranslated(0.5, 0.45, -0.3);
	glutSolidCube(0.85);
	glPopMatrix();

	//back
	glColor4d(BACK_MATTRESS);
	glPushMatrix();
	glRotated(90,0.0,0.0,1.0);
	glTranslated(0.0,-0.4,0.0);
	glTranslated(0.0125, 0.0, -0.10);
	glScaled(0.3, 0.08, 0.8);
	glTranslated(0.5, 0.45, -0.3);
	glutSolidCube(0.85);
	glPopMatrix();

	//sides
	glColor4d(SIDE_MATTRESS);
	glPushMatrix();
	glRotated(90,1.0,0.0,0.0);
	glScaled(0.4, 0.08, 0.2);
	glTranslated(0.5, 0.15, -0.3);
	glutSolidCube(0.85);
	glPopMatrix();

	glColor4d(SIDE_MATTRESS);
	glPushMatrix();
	glRotated(90,1.0,0.0,0.0);
	glScaled(0.4, 0.08, 0.2);
	glTranslated(0.5, -8.5, -0.3);
	glutSolidCube(0.85);
	glPopMatrix();
}


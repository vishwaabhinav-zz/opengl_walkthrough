
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>       // Header file for trigonometric functions.

#define COLOR_WOOD 0.8, 0.6, 0.4, 1.0
//#define COLOR_BED_FRAME 0.2, 0.15, 0.1, 1.0
//#define COLOR_MATTRESS 0.0, 0.15, 0.25, 1.0

void renderFrame(double width, double height, double depth) {
	glPushMatrix();
	glScaled(depth, height - depth, depth);
	glTranslated(0.5, 0.5, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(depth, 0.0, 0.0);
	glScaled(width - depth, depth, depth);
	glTranslated(0.5, 0.5, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();


	glPushMatrix();
	glTranslated(width - depth, depth, 0.0);
	glScaled(depth, height - depth, depth);
	glTranslated(0.5, 0.5, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, height - depth, 0.0);
	glScaled(width - depth, depth, depth);
	glTranslated(0.5, 0.5, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();
}


void renderTablePost(void);

void renderTable(void) {
	//Create the foot of the table
	glPushMatrix();
	glTranslated(0.0, 0.0, -0.18);
	renderTablePost();
	glPopMatrix();

	//Create the head of the table
	glPushMatrix();
	glTranslated(0.0, 0.0, -0.65);
	renderTablePost();
	glPopMatrix();

	glColor4d(COLOR_WOOD);
	glPushMatrix();
	//  glTranslated(0.0125, 0.4625, -0.1);
	glScaled(0.4, 0.1, 0.8);
	glTranslated(0.5, 2.0, -0.5);
	glutSolidCube(0.75);
	glPopMatrix();
}

/**
 * Renders a single bed endpiece, consisting of two posts with three horizontal
 * members connecting them, and all made out of wood.
 *
 * @author Nicolas Ward '05
 **/
void renderTablePost(void) {
	//Use wood
	glColor4d(COLOR_WOOD);

	//Create the left post
	glPushMatrix();
	glTranslated(0.08, 0.0, 0.0);
	glScaled(0.03, 0.2, 0.03);
	glTranslated(0.0, 0.45, 0.8);
	glutSolidCube(1.0);
	glPopMatrix();

	//Create the right post
	glPushMatrix();
	glTranslated(0.33, 0.0, 0.0);
	glScaled(0.03, 0.2, 0.03);
	glTranslated(0.05, 0.5, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();
}


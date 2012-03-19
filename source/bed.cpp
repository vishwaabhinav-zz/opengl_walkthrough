
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>       // Header file for trigonometric functions.

#define COLOR_WOOD 0.8, 0.6, 0.4, 1.0
#define COLOR_BED_FRAME 0.2, 0.15, 0.1, 1.0
#define COLOR_MATTRESS 0.0, 0.15, 0.25, 1.0

void renderBedPost(void);

void renderSolidFrame(double width, double height, double depth) {
	//Create the left frame member
	glPushMatrix();
	glScaled(depth, height - depth, depth);
	glTranslated(0.5, 0.5, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	//Create the bottom frame member
	glPushMatrix();
	glTranslated(depth, 0.0, 0.0);
	glScaled(width - depth, depth, depth);
	glTranslated(0.5, 0.5, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	//Create the right frame member
	glPushMatrix();
	glTranslated(width - depth, depth, 0.0);
	glScaled(depth, height - depth, depth);
	glTranslated(0.5, 0.5, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	//Create the top frame member
	glPushMatrix();
	glTranslated(0.0, height - depth, 0.0);
	glScaled(width - depth, depth, depth);
	glTranslated(0.5, 0.5, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();  
}

void renderBed(void) {
	//Create the foot of the bed
	glPushMatrix();
	glTranslated(0.05, 0.0, -0.56);
//	renderBedPost();
	glPopMatrix();

	//Create the head of the bed
	glPushMatrix();
	glTranslated(0.05, 0.0, -0.13);
//	renderBedPost();
	glPopMatrix();

	//Create the frame of the bed
	glColor4d(COLOR_BED_FRAME);
	glPushMatrix();
	glTranslated(0.030, 0.0255, 0.04);
	glRotated(-90, 1.0, 0.0, 0.0);
	renderSolidFrame(0.84,0.84, 0.05);
	glPopMatrix();

	//Create the mattress
	glColor4d(COLOR_MATTRESS);
	glPushMatrix();
	glTranslated(0.0125, 0.02, -0.10);
	glScaled(0.9, 0.2, 0.9);
	glTranslated(0.5, 0.45, -0.3);
	glutSolidCube(0.85);
	glPopMatrix();
}

/**
 * Renders a single bed endpiece, consisting of two posts with three horizontal
 * members connecting them, and all made out of wood.
 *
 * @author Nicolas Ward '05
 **/
void renderBedPost(void) {
	//Use wood
	glColor4d(COLOR_WOOD);

	//Create the left post
	glPushMatrix();
	glScaled(0.02, 0.15, 0.01);
	glTranslated(0.0, 0.45, -0.13);
	glutSolidCube(1.0);
	glPopMatrix();

	//Create the right post
	glPushMatrix();
	glTranslated(0.23, 0.0, 0.0);
	glScaled(0.02, 0.15, 0.01);
	glTranslated(0.5, 0.47, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();

	//Create the top crossbar
	glPushMatrix();
	glTranslated(0.047, 0.1, 0.0);
	glScaled(0.26, 0.01, 0.01);
	glTranslated(0.28, 0.0, 0.0);  
	glutSolidCube(1.0);
	glPopMatrix();

	//Create the bottom crossbar
	glPushMatrix();
	glTranslated(0.047, 0.14, 0.0);
	glScaled(0.26, 0.01, 0.01);
	glTranslated(0.28, 0.0, 0.0);  
	glutSolidCube(1.0);
	glPopMatrix();  
}


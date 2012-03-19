
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>       // Header file for trigonometric functions.

#define COLOR_STAIRWELL 0.70, 0.70, 0.70, 1.0

void renderRectangle(double x1, double y1, double x2, double y2) {
	//Create the rectangle as a very thin cube centered in the XY plane
	glPushMatrix();
	glTranslated(x1, y1, 0.0);
	glScaled(x2 - x1, y2 - y1, 0.005);
	glTranslated(0.5, 0.5, 0.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void renderStairwell(double rise, double run, double width, int steps) {
	int i;
	double riseDist, runDist;
	GLfloat specular[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat noSpecular[] = {0.0, 0.0, 0.0, 1.0};

	//Set the stair material
	glColor4d(COLOR_STAIRWELL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.25);

	//Loop over the stairwell, generating the riser and runner of each step
	for (i = 0, riseDist = 0.0, runDist = 0.0; i < steps;
			i++, riseDist += rise, runDist += run) {
		//Start the transformation for this step
		glPushMatrix();

		//Translate to the current step
		glTranslated(0.0, riseDist, runDist);
		//Draw the current step's riser
		glColor3f(0.95,0.95,0.95);
		renderRectangle(0.0, 0.0, width, rise);

		//Translate the runner up
		glTranslated(0.0, rise, 0.0);

		//Rotate to the runner
		glRotated(90, 1.0, 0.0, 0.0);
		glColor3f(0.70,0.70,0.70);
		//Draw the current step's runner
		renderRectangle(0.0, 0.0, width, run);

		//End the transformation for this step 
		glPopMatrix();
	}

	//Draw the stairwell's final riser
	glPushMatrix();
	glTranslated(0.0, riseDist, runDist);
	renderRectangle(0.0, 0.0, width, rise);
	glPopMatrix();

	//Unset the railing material
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, noSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0);
}


void makeStairs()
{
	//	glTranslatef(3.6,0.0,2.5);
	//	renderStairwell(0.1,0.1,0.8,9);
	glPushMatrix();
	glTranslated(3.6,0.0,1.0);
	glScaled(1.0, 1.0, -1.0);
	renderStairwell(0.1,0.1, 0.9, 9);
	glPopMatrix();


	glPushMatrix();
	glTranslated(3.6,1.0,1.0);
	glScaled(1.0, 1.0, -1.0);
	renderStairwell(0.1,0.1, 0.9, 9);
	glPopMatrix();
}

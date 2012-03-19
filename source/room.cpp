
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>       // Header file for trigonometric functions.

//#include "bed.cpp"

GLuint text_wall[3];

// Load Bitmaps And Convert To Textures
GLvoid LoadTexture_Wall(GLvoid) 
{	
	// Load Texture
	Image *image5;
	Image *image6;
	//	Image *image2;

	// allocate space for texture
	image5 = (Image *) malloc(sizeof(Image));
	image6 = (Image *) malloc(sizeof(Image));
	//	image2 = (Image *) malloc(sizeof(Image));
	if (image5 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("Data/lesson10/wall_strip.bmp", image5)) {
		printf("Image Not Loaded");
		exit(1);
	}        


	if (image6 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("Data/lesson10/wall_strip.bmp", image6)) {
		printf("Image Not Loaded");
		exit(1);
	}        

	// Create Textures	
	glGenTextures(3, text_wall);

	// nearest filtered texture
	//	glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)
	//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // scale cheaply when image bigger than texture
	//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // scale cheaply when image smalled than texture
	//	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);

	// linear filtered texture
	glBindTexture(GL_TEXTURE_2D, text_wall[0]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image5->sizeX, image5->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image5->data);


	glBindTexture(GL_TEXTURE_2D, text_wall[1]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image6->sizeX, image6->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image6->data);
};

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

	glBindTexture(GL_TEXTURE_2D, text_wall[0]);   // 2d texture (x and y size)
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

		glTexCoord2f(0,0);
		glVertex3f(x1,y1,z2+1.0f);

		glTexCoord2f(8,0);
		glVertex3f(x1+1.6,y1,z2+1.0f);

		glTexCoord2f(8,1);
		glVertex3f(x1+1.6,y1+1.0,z2+1.0f);

		glTexCoord2f(0,1);
		glVertex3f(x1,y1+1.0,z2+1.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);


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



	glBindTexture(GL_TEXTURE_2D, text_wall[0]);   // 2d texture (x and y size)
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);

		glTexCoord2f(0,0);
		glVertex3f(x1+2.0,y1,z1);

		glTexCoord2f(8,0);
		glVertex3f(x1+2.0,y1,z2);

		glTexCoord2f(8,1);
		glVertex3f(x1+2.0,y1+1.0,z2);

		glTexCoord2f(0,1);
		glVertex3f(x1+2.0,y1+1.0,z1);
	glEnd();

	glDisable(GL_TEXTURE_2D);
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
	
	glBindTexture(GL_TEXTURE_2D, text_wall[0]);   // 2d texture (x and y size)
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(x1+0.4,y1,z1-1.0f);

		glTexCoord2f(8,0);
		glVertex3f(x1+2.0,y1,z1-1.0f);

		glTexCoord2f(8,1);
		glVertex3f(x1+2.0,y1+1.0,z1-1.0f);

		glTexCoord2f(0,1);
		glVertex3f(x1+0.4,y1+1.0,z1-1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
/////////////////////////////////////////////////////////////////////////////////



	glBegin(GL_QUADS);

//		glTexCoord2f(0,0);
		glVertex3f(x1+1.0,y1+0.8,z1);

//		glTexCoord2f(6,0);
		glVertex3f(x1+1.4,y1+0.8,z1);

//		glTexCoord2f(6,6);
		glVertex3f(x1+1.4,y1+1.0,z1);

//		glTexCoord2f(0,6);
		glVertex3f(x1+1.0,y1+1.0,z1);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, text_wall[1]);   // 2d texture (x and y size)
	glBegin(GL_QUADS);

		glTexCoord2f(0,0);
		glVertex3f(x1+2.0,y1,z1);

		glTexCoord2f(8,0);
		glVertex3f(x1+2.0,y1,z2);

		glTexCoord2f(8,1);
		glVertex3f(x1+2.0,y1+1.0,z2);
		
		glTexCoord2f(0,1);
		glVertex3f(x1+2.0,y1+1.0,z1);
		


	glEnd();

	glDisable(GL_TEXTURE_2D);
}


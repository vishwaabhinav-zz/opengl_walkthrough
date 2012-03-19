/**Header Files including libraries of opengl and c**/

#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header file for sleeping.
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>       // Header file for trigonometric functions.

/**Header Files Including parts of Guest House**/

#include "pil.cpp"
#include "imageloader.cpp"
#include "railing.cpp"
#include "model.cpp"

/**defining codes for key movement**/

#define ESCAPE 27
#define PAGE_UP 73
#define PAGE_DOWN 81
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

/* The number of our GLUT window */
int window; 

//GLuint texture[3];       // storage for 3 textures;
//GLuint texture[3];       // storage for 3 textures;

int light = 0;           // lighting on/off
int blend = 0;        // blending on/off

GLfloat xrot;            // x rotation
GLfloat yrot;            // y rotation
GLfloat xspeed;          // x rotation speed
GLfloat yspeed;          // y rotation speed

GLfloat walkbias = 0;
GLfloat walkbiasangle = 0;

GLfloat lookupdown = 0.0;
const float piover180 = 0.0174532925f;

float heading, xpos, zpos;

GLfloat camx = 0, camy = 0, camz = 0; // camera location.
GLfloat therotate;

GLfloat z=0.0f;                       // depth into the screen.

GLfloat LightAmbient[]  = {0.5f, 0.5f, 0.5f, 1.0f}; 
GLfloat LightDiffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f}; 
GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f};

GLuint filter = 0;       // texture filtering method to use (nearest, linear, linear + mipmaps)
// degrees to radians...2 PI radians = 360 degrees
float rad(float angle)
{
	return angle * piover180;
}
// Load Bitmaps And Convert To Textures
/*GLvoid LoadGLTextures(GLvoid) 
{	
	// Load Texture
	Image *image1;

	// allocate space for texture
	image1 = (Image *) malloc(sizeof(Image));
	if (image1 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("Data/lesson10/mud.bmp", image1)) {
		exit(1);
	}        

	// Create Textures	
	glGenTextures(3, &texture[0]);

	// nearest filtered texture
	glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // scale cheaply when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // scale cheaply when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);

	// linear filtered texture
	glBindTexture(GL_TEXTURE_2D, texture[1]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);

	// mipmapped texture
	glBindTexture(GL_TEXTURE_2D, texture[2]);   // 2d texture (x and y size)
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST); // scale mipmap when image smalled than texture
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image1->sizeX, image1->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
};*/

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
GLvoid InitGL(GLsizei Width, GLsizei Height)	// We call this right after our OpenGL window is created.
{
	LoadGLTextures();                           // load the textures.
	glEnable(GL_TEXTURE_2D);                    // Enable texture mapping.

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);          // Set the blending function for translucency (note off at init time)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// This Will Clear The Background Color To Black
	glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);                       // type of depth test to do.
	glEnable(GL_DEPTH_TEST);                    // enables depth testing.
	glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				// Reset The Projection Matrix

	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

	glMatrixMode(GL_MODELVIEW);

	// set up lights.
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
GLvoid ReSizeGLScene(GLsizei Width, GLsizei Height)
{
	if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
		Height=1;

	glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
GLvoid DrawGLScene(GLvoid)
{
	GLfloat xtrans, ztrans, ytrans;
	GLfloat sceneroty,scenerotx;

	// calculate translations and rotations.
	xtrans = -xpos;
	ztrans = -zpos;
	ytrans = -walkbias-0.25f;
	sceneroty = 360.0f - yrot;
	scenerotx = 360.0f - xrot;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
	glLoadIdentity();

	glRotatef(lookupdown, 1.0f, 0, 0);
	glRotatef(sceneroty, 0, 1.0f, 0);
	glRotatef(scenerotx,1.0f,0,0);

	glTranslatef(xtrans, ytrans, ztrans);    

	glBindTexture(GL_TEXTURE_2D, texture[filter]);    // pick the texture.


	model();  // create the external model of the house

	make_Railing(); // create the railing on the first floor of the house
	
	float i;

	/**Code for making pillars in lower floor**/
	for(i = -2.9533333;i <= 2.95 ; i += 0.85){
		renderCylinder_convenient(i,0,3,i,1,3,0.04,16);
	}
	/**Code ends for pillars on low floor**/

	/**Code for making pillars in first floor**/
	for(i = -2.9533333;i <= 2.95 ; i += 0.85){
		renderCylinder_convenient(i,1,2,i,2,2,0.04,16);
	}
	/**Code ends for pillars on first floor**/

	// since this is double buffered, swap the buffers to display what just got drawn.
	
	glutSwapBuffers();
}


/* The function called whenever a normal key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{
	/* avoid thrashing this procedure */
	usleep(100);

	switch (key) {    
		case ESCAPE: // kill everything.
			/* exit the program...normal termination. */
			exit(1);                   	
			break; // redundant.

		case 'b': 
		case 'B': // switch the blending
			printf("B/b pressed; blending is: %d\n", blend);
			blend = blend ? 0 : 1;              // switch the current value of blend, between 0 and 1.
			if (blend) {
				glEnable(GL_BLEND);
				glDisable(GL_DEPTH_TEST);
			} else {
				glDisable(GL_BLEND);
				glEnable(GL_DEPTH_TEST);
			}
			printf("Blending is now: %d\n", blend);
			break;

		case 'f': 
		case 'F': // switch the filter
			printf("F/f pressed; filter is: %d\n", filter);
			filter++;                           // switch the current value of filter, between 0/1/2;
			if (filter > 2) {
				filter = 0;
			}
			printf("Filter is now: %d\n", filter);
			break;

		case 'l': 
		case 'L': // switch the lighting
			printf("L/l pressed; lighting is: %d\n", light);
			light = light ? 0 : 1;              // switch the current value of light, between 0 and 1.
			if (light) {
				glEnable(GL_LIGHTING);
			} else {
				glDisable(GL_LIGHTING);
			}
			printf("Lighting is now: %d\n", light);
			break;

		case 'w':
		case 'W':
			walkbias += 0.05f;
			break;	

		case 's':
		case 'S':
			walkbias -= 0.05f;
			break;

		default:
			printf ("Key %d pressed. No action there yet.\n", key);
			break;
	}	
}

/* The function called whenever a normal key is pressed. */
void specialKeyPressed(int key, int x, int y) 
{
	/* avoid thrashing this procedure */
	usleep(100);

	switch (key) {    
		case GLUT_KEY_PAGE_UP: // tilt up
			z -= 0.2f;
			lookupdown -= 1.0f;
			break;

		case GLUT_KEY_PAGE_DOWN: // tilt down
			z += 0.2f;
			lookupdown += 1.0f;
			break;

		case GLUT_KEY_UP: // walk forward (bob head)
			xpos -= (float)sin(yrot*piover180) * 0.05f;
			zpos -= (float)cos(yrot*piover180) * 0.05f;	
			if (walkbiasangle >= 359.0f)
				walkbiasangle = 0.0f;	
			else 
				walkbiasangle+= 10;
//			walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
			break;

		case GLUT_KEY_DOWN: // walk back (bob head)
			xpos += (float)sin(yrot*piover180) * 0.05f;
			zpos += (float)cos(yrot*piover180) * 0.05f;	
			if (walkbiasangle <= 1.0f)
				walkbiasangle = 359.0f;	
			else 
				walkbiasangle-= 10;
//			walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
			break;

		case GLUT_KEY_LEFT: // look left
			yrot += 1.5f;
			break;

		case GLUT_KEY_RIGHT: // look right
			yrot -= 1.5f;
			break;

		default:
			printf ("Special key %d pressed. No action there yet.\n", key);
			break;
	}	
}

int main(int argc, char **argv) 
{  
	/* load our world from disk */
	SetupWorld();

	/* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
	   X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
	glutInit(&argc, argv);  

	/* Select type of Display mode:   
	   Double buffer 
	   RGBA color
	   Depth buffer 
	   Alpha blending */  
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);  
glEnable(GL_MULTISAMPLE);
  glEnable(GL_POLYGON_SMOOTH);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);



	/* get a 640 x 480 window */
	glutInitWindowSize(640, 480);  

	/* the window starts at the upper left corner of the screen */
	glutInitWindowPosition(0, 0);  

	/* Open a window */  
	window = glutCreateWindow("GVC GuestHouse Project");  

	/* Register the function to do all our OpenGL drawing. */
	glutDisplayFunc(&DrawGLScene);  

	/* Go fullscreen.  This is as soon as possible. */
	glutFullScreen();

	/* Even if there are no events, redraw our gl scene. */
	glutIdleFunc(&DrawGLScene); 

	/* Register the function called when our window is resized. */
	glutReshapeFunc(&ReSizeGLScene);

	/* Register the function called when the keyboard is pressed. */
	glutKeyboardFunc(&keyPressed);

	/* Register the function called when special keys (arrows, page down, etc) are pressed. */
	glutSpecialFunc(&specialKeyPressed);

	/* Initialize our window. */
	InitGL(640, 480);

	/* Start Event Processing Engine */  
	glutMainLoop();  

	return 1;
}

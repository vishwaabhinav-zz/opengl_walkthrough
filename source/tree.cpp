#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>           /* ULONG_MAX is defined here */
#include <float.h>            /* FLT_MAX is atleast defined here */

#include <time.h>  /* for random seed */

//#include "fracviewer.h"

#ifdef WIN32
#define drand48() (((float) rand())/((float) RAND_MAX))
#define srand48(x) (srand((x)))
#endif

typedef enum { NOTALLOWED, MOUNTAIN, TREE, ISLAND, BIGMTN, STEM, LEAF, 
               MOUNTAIN_MAT, WATER_MAT, LEAF_MAT, TREE_MAT, STEMANDLEAVES,
               AXES } DisplayLists;

#define MAXLEVEL 8

int Rebuild = 1,        /* Rebuild display list in next display? */
    Fract   = TREE,     /* What fractal are we building */
    Level   = 4;        /* levels of recursion for fractals */     

int DrawAxes = 0;       

/***************************************************************/
/************************* VECTOR JUNK *************************/
/***************************************************************/

  /* print vertex to stderr */
void printvert(float v[3])
{
  fprintf(stderr, "(%f, %f, %f)\n", v[0], v[1], v[2]);
}

  /* normalizes v */
void normalize(GLfloat v[3])
{
  GLfloat d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

  if (d == 0)
    fprintf(stderr, "Zero length vector in normalize\n");
  else
    v[0] /= d; v[1] /= d; v[2] /= d;
}

  /* calculates a normalized crossproduct to v1, v2 */
void ncrossprod(float v1[3], float v2[3], float cp[3])
{
  cp[0] = v1[1]*v2[2] - v1[2]*v2[1];
  cp[1] = v1[2]*v2[0] - v1[0]*v2[2];
  cp[2] = v1[0]*v2[1] - v1[1]*v2[0];
  normalize(cp);
}

  /* calculates normal to the triangle designated by v1, v2, v3 */
void triagnormal(float v1[3], float v2[3], float v3[3], float norm[3])
{
  float vec1[3], vec2[3];

  vec1[0] = v3[0] - v1[0];  vec2[0] = v2[0] - v1[0];
  vec1[1] = v3[1] - v1[1];  vec2[1] = v2[1] - v1[1];
  vec1[2] = v3[2] - v1[2];  vec2[2] = v2[2] - v1[2];

  ncrossprod(vec2, vec1, norm);
}

float xzlength(float v1[3], float v2[3])
{
  return sqrt((v1[0] - v2[0])*(v1[0] - v2[0]) +
              (v1[2] - v2[2])*(v1[2] - v2[2]));
}

float xzslope(float v1[3], float v2[3])
{
  return ((v1[0] != v2[0]) ? ((v1[2] - v2[2]) / (v1[0] - v2[0]))
	                   : FLT_MAX);
}



/***************************************************************/
/***************************** TREE ****************************/
/***************************************************************/

long TreeSeed;   /* for srand48 - remember so we can build "same tree"
                     at a different level */

 /*
  * recursive tree drawing thing, fleshed out from class notes pseudocode 
  */
void FractalTree(int level)
{
  long savedseed;  /* need to save seeds while building tree too */

  if (level == Level) {
      glPushMatrix();
        glRotatef(drand48()*180, 0, 1, 0);
        glCallList(STEMANDLEAVES);
      glPopMatrix();
  } else {
    glCallList(STEM);
    glPushMatrix();
    glRotatef(drand48()*180, 0, 1, 0);
    glTranslatef(0, 1, 0);
    glScalef(0.7, 0.7, 0.7);

      savedseed = (long) drand48()*ULONG_MAX;    /* recurse on a 3-way branching */
      glPushMatrix();    
        glRotatef(110 + drand48()*40, 0, 1, 0);
        glRotatef(30 + drand48()*20, 0, 0, 1);
        FractalTree(level + 1);

      glPopMatrix();

      srand48(savedseed);
      savedseed = (long) drand48()*ULONG_MAX;
      glPushMatrix();
        glRotatef(-130 + drand48()*40, 0, 1, 0);
        glRotatef(30 + drand48()*20, 0, 0, 1);
        FractalTree(level + 1);
      glPopMatrix();

      srand48(savedseed);
      glPushMatrix();
        glRotatef(-20 + drand48()*40, 0, 1, 0);
        glRotatef(30 + drand48()*20, 0, 0, 1);
        FractalTree(level + 1);
      glPopMatrix();

    glPopMatrix();
  }
}

  /*
   * Create display lists for a leaf, a set of leaves, and a stem
   */
void CreateTreeLists(void)
{
  GLUquadricObj *cylquad = gluNewQuadric();
  int i;

  glNewList(STEM, GL_COMPILE);
  glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    gluCylinder(cylquad, 0.1, 0.08, 1, 10, 2 );
  glPopMatrix();
  glEndList();

  glNewList(LEAF, GL_COMPILE);  /* I think this was jeff allen's leaf idea */
    glBegin(GL_TRIANGLES);
      glNormal3f(-0.1, 0, 0.25);  /* not normalized */
      glVertex3f(0, 0, 0);
      glVertex3f(0.25, 0.25, 0.1);
      glVertex3f(0, 0.5, 0);

      glNormal3f(0.1, 0, 0.25);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0.5, 0);
      glVertex3f(-0.25, 0.25, 0.1);
    glEnd();
  glEndList();

  glNewList(STEMANDLEAVES, GL_COMPILE);
  glPushMatrix();
  glPushAttrib(GL_LIGHTING_BIT);
    glCallList(STEM);
    glCallList(LEAF_MAT);
    for(i = 0; i < 3; i++) {
      glTranslatef(0, 0.333, 0);
      glRotatef(90, 0, 1, 0);
      glPushMatrix();
        glRotatef(0, 0, 1, 0);
        glRotatef(50, 1, 0, 0);
        glCallList(LEAF);
      glPopMatrix();
      glPushMatrix();
        glRotatef(180, 0, 1, 0);
        glRotatef(60, 1, 0, 0);
        glCallList(LEAF);
      glPopMatrix();
    }
  glPopAttrib();
  glPopMatrix();
  glEndList();
}

 /*
  * draw and build display list for tree
  */
void CreateTree(void)
{
  srand48(TreeSeed);

  glNewList(TREE, GL_COMPILE);
    glPushMatrix();
    glPushAttrib(GL_LIGHTING_BIT);
    glCallList(TREE_MAT);
    glTranslatef(0, 0, 0);
    FractalTree(2);
    glPopAttrib();
    glPopMatrix();
  glEndList();  
}

 /*
  * new seed for a new tree (groan)
  */
void NewTree(void)
{
  TreeSeed = time(NULL);
}

/***************************************************************/
/*********************** FRACTAL PLANET ************************/
/***************************************************************/

void NewFractals(void)
{
  NewTree();
}

void Create(int fract)
{
  switch(fract) {
    case TREE:
      CreateTree();
      break;
  }
}



/***************************************************************/
/**************************** OPENGL ***************************/
/***************************************************************/


void SetupMaterials(void)
{
  GLfloat tree_ambuse[] =   { 0.4, 0.25, 0.1, 1.0 };
  GLfloat tree_specular[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat tree_shininess[] = { 0 };

  GLfloat leaf_ambuse[] =   { 0.0, 0.8, 0.0, 1.0 };
  GLfloat leaf_specular[] = { 0.0, 0.8, 0.0, 1.0 };
  GLfloat leaf_shininess[] = { 10 };

  glNewList(TREE_MAT, GL_COMPILE);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, tree_ambuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, tree_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, tree_shininess);
  glEndList();

  glNewList(LEAF_MAT, GL_COMPILE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, leaf_ambuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, leaf_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, leaf_shininess);
  glEndList();
}

void myGLInit(void)
{
  GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light_position[] = { 0.0, 0.3, 0.3, 0.0 };

  GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_NORMALIZE);
#if 0
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
#endif

  glShadeModel(GL_SMOOTH);
#if 0
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif

  SetupMaterials();
  CreateTreeLists();

  glFlush();
} 

/***************************************************************/
/************************ GLUT STUFF ***************************/
/***************************************************************/

void reshape(GLsizei w, GLsizei h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLdouble)w/h, 0.01, 100);
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glFlush();
}

void display(void)
{ 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glFlush();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glPushMatrix();  /* clear of last viewing xform, leaving perspective */


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  CreateTree();
  
  glutSwapBuffers();
  glFlush();
}



/***************************************************************/
/******************* MENU SETUP & HANDLING *********************/
/***************************************************************/

typedef enum { MENU_QUIT, MENU_RAND, MENU_MOVE, MENU_AXES } MenuChoices;

void setlevel(int value)
{
  Level = value;
  Rebuild = 1;
  glutPostRedisplay();
}

void choosefract(int value)
{
  Fract = value;
  Rebuild = 1;
  glutPostRedisplay();
}

void handlemenu(int value)
{
  switch (value) {
    case MENU_QUIT:
      exit(0);
      break;
    case MENU_RAND:
      NewFractals();
      Rebuild = 1;
      glutPostRedisplay();
      break;
    case MENU_AXES:
      DrawAxes = !DrawAxes;
      glutPostRedisplay();
      break;
    }
}
/***************************************************************/
/**************************** MAIN *****************************/
/***************************************************************/

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(512, 512);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
  glutCreateWindow("Fractal Planet?");


  glutReshapeFunc(reshape);
  glutDisplayFunc(display);

  myGLInit(); 

  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}

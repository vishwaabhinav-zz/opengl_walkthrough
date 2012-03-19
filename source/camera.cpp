#include "math.h"
#define false 0
#define true 1
#define PI 3.141
typedef struct SF3dVector  //Float 3d-vect, normally used
{
	GLfloat x,y,z;
}SF3dVector;

typedef struct SF2dVector
{
	GLfloat x,y;
}SF2dVector;




SF3dVector ViewDir;	/*	Not used for rendering the camera, but for "moveforwards"
				  So it is not necessary to "actualize" it always. It is only
				  actualized when ViewDirChanged is true and moveforwards is called*/
SF3dVector Position;/*
Position.x = 0.0;
Position.y = 0.0;
Position.z = 0.0;
ViewDir.x = 0.0;
ViewDir.y = 0.0;
ViewDir.z = -1.0;
*/
void GetViewDir ( void );
void Render ( void );
void Move ( SF3dVector Direction );
void RotateX ( GLfloat Angle );
void RotateY ( GLfloat Angle );
void RotateZ ( GLfloat Angle );
void RotateXYZ ( SF3dVector Angles );
void MoveForwards ( GLfloat Distance );
void StrafeRight ( GLfloat Distance );

SF3dVector F3dVector(GLfloat,GLfloat,GLfloat);
int ViewDirChanged;
GLfloat RotatedX =0, RotatedY=0, RotatedZ=0;	

ViewDirChanged = false;


SF3dVector F3dVector ( GLfloat x, GLfloat y, GLfloat z )
{
	SF3dVector tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}
SF3dVector AddF3dVectors (SF3dVector* u, SF3dVector* v)
{
	SF3dVector result;
	result.x = u->x + v->x;
	result.y = u->y + v->y;
	result.z = u->z + v->z;
	return result;
}
void AddF3dVectorToVector ( SF3dVector * Dst, SF3dVector * V2)
{
	Dst->x += V2->x;
	Dst->y += V2->y;
	Dst->z += V2->z;
}


void GetViewDir( void )
{
	SF3dVector Step1, Step2;
	//Rotate around Y-axis:
	Step1.x = cos( (RotatedY + 90.0) * PI/180);
	Step1.z = -sin( (RotatedY + 90.0) * PI/180);
	//Rotate around X-axis:
	double cosX = cos (RotatedX * PI/180);
	Step2.x = Step1.x * cosX;
	Step2.z = Step1.z * cosX;
	Step2.y = sin(RotatedX * PI/180);
	//Rotation around Z-axis not yet implemented, so:
	ViewDir = Step2;
}
void Move (SF3dVector Direction)
{
	AddF3dVectorToVector(&Position, &Direction );
}

void RotateY (GLfloat Angle)
{
	RotatedY += Angle;
	ViewDirChanged = true;
}

void RotateX (GLfloat Angle)
{
	RotatedX += Angle;
	ViewDirChanged = true;
}

void Render( void )
{
	glRotatef(-RotatedX , 1.0, 0.0, 0.0);
	glRotatef(-RotatedY , 0.0, 1.0, 0.0);
	glRotatef(-RotatedZ , 0.0, 0.0, 1.0);
	glTranslatef( -Position.x, -Position.y, -Position.z );
}

void MoveForwards( GLfloat Distance )
{
	if (ViewDirChanged) GetViewDir();
	SF3dVector MoveVector;
	MoveVector.x = ViewDir.x * -Distance;
	MoveVector.y = ViewDir.y * -Distance;
	MoveVector.z = ViewDir.z * -Distance;
	AddF3dVectorToVector(&Position, &MoveVector );
}

void StrafeRight ( GLfloat Distance )
{
	if (ViewDirChanged) GetViewDir();
	SF3dVector MoveVector;
	MoveVector.z = -ViewDir.x * -Distance;
	MoveVector.y = 0.0;
	MoveVector.x = ViewDir.z * -Distance;
	AddF3dVectorToVector(&Position, &MoveVector );
}

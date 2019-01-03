////////////////////////////////////////////////////////////////////
//								  //
//			OpenGl Camera			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined COpenGl_Camera_H
#define COpenGl_Camera_H

//----------------------------------//
//--------- Library files ----------//
//----------------------------------//

#pragma comment(linker, "/defaultlib:Glu32.lib")

//----------------------------------//
//------------ Defines -------------//
//----------------------------------//

//----------------------------------//
//--------- Include files ----------//
//----------------------------------//

#include <gl\glaux.h>
#include <math.h>

//----------------------------------//
//------- Prototypes files ---------//
//----------------------------------//

//----------------------------------//
//------------- Class --------------//
//----------------------------------//

class COpenGl_Camera
{
public:

COpenGl_Camera();
~COpenGl_Camera();

void ReSizeGLScene       (int,int);
void InitGL_Values       ();

void Look	   ();
void Update	   ();
void MoveCamera    (float speed);
void StrafeCamera  (float speed);
void RotateView    (float angle, float x, float y, float z);
void PositionCamera(float positionX, float positionY, float positionZ,
	            float viewX,     float viewY,     float viewZ,
		    float upVectorX, float upVectorY, float upVectorZ);

bool  Error_Check         ();
char *Get_Error_Message   ();

protected:

private:

CVector3 Croos       (CVector3 vVector1,CVector3 vVector2);
float    Magnitude   (CVector3 vNormal);
CVector3 Normalize   (CVector3 vVector);

CVector3 m_vPosition;
CVector3 m_vView;
CVector3 m_vUpVector;
CVector3 m_vStrafe;

bool    Error_Detected;
char	Error_Message[50];
};

#endif


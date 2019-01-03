////////////////////////////////////////////////////////////////////
//								  //
//			OpenGl Camera			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "COpenGL_Math.h"
#include "COpenGl_Camera.h"

//--------------------------------------------------------------------------------
char *COpenGl_Camera::Get_Error_Message(){return Error_Message;}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
bool COpenGl_Camera::Error_Check(){return Error_Detected;}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
CVector3 COpenGl_Camera::Normalize(CVector3 vVector)
//--------------------------------------------------------------------------------
{
float magnitude = Magnitude(vVector);				
vVector = vVector / magnitude;		
return vVector;	
}

//--------------------------------------------------------------------------------
float COpenGl_Camera::Magnitude(CVector3 vNormal)
//--------------------------------------------------------------------------------
{
// Here is the equation:  magnitude = sqrt(V.x^2 + V.y^2 + V.z^2) : Where V is the vector
return (float)sqrt( (vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z));
}

//--------------------------------------------------------------------------------
void COpenGl_Camera::PositionCamera(float Pos_X,float Pos_Y,float Pos_Z,float View_X,float View_Y,float View_Z,float Vec_X,float Vec_Y,float Vec_Z)
//--------------------------------------------------------------------------------
{
CVector3 vPosition	= CVector3(Pos_X, Pos_Y, Pos_Z);
CVector3 vView		= CVector3(View_X, View_Y, View_Z);
CVector3 vUpVector	= CVector3(Vec_X, Vec_Y, Vec_Z);

m_vPosition = vPosition;
m_vView     = vView;
m_vUpVector = vUpVector;
}

//--------------------------------------------------------------------------------
void COpenGl_Camera::Look()
//--------------------------------------------------------------------------------
{
gluLookAt(m_vPosition.x, m_vPosition.y, m_vPosition.z,	
	  m_vView.x,	 m_vView.y,     m_vView.z,	
	  m_vUpVector.x, m_vUpVector.y, m_vUpVector.z);
}

//--------------------------------------------------------------------------------
void COpenGl_Camera::Update()
//--------------------------------------------------------------------------------
{
CVector3 vCross = Croos(m_vView - m_vPosition, m_vUpVector);
m_vStrafe = Normalize(vCross);
}

//--------------------------------------------------------------------------------
void COpenGl_Camera::MoveCamera(float speed)
//--------------------------------------------------------------------------------
{
CVector3 vVector = m_vView - m_vPosition;

vVector = Normalize(vVector);
	
m_vPosition.x += vVector.x * speed;
m_vPosition.z += vVector.z * speed;
m_vView.x += vVector.x * speed;
m_vView.z += vVector.z * speed;
}

//--------------------------------------------------------------------------------
void COpenGl_Camera::StrafeCamera(float speed)
//--------------------------------------------------------------------------------
{
m_vPosition.x += m_vStrafe.x * speed;
m_vPosition.z += m_vStrafe.z * speed;

m_vView.x += m_vStrafe.x * speed;
m_vView.z += m_vStrafe.z * speed;
}

//--------------------------------------------------------------------------------
void COpenGl_Camera::RotateView(float angle,float x,float y,float z)
//--------------------------------------------------------------------------------
{
CVector3 vNewView;
CVector3 vView = m_vView - m_vPosition;		

float cosTheta = (float)cos(angle);
float sinTheta = (float)sin(angle);

vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)	* vView.x;
vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;

vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
vNewView.y += (cosTheta + (1 - cosTheta) * y * y)	* vView.y;
vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;

vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
vNewView.z += (cosTheta + (1 - cosTheta) * z * z)	* vView.z;

m_vView = m_vPosition + vNewView;
}

//--------------------------------------------------------------------------------
CVector3 COpenGl_Camera::Croos(CVector3 vVector1,CVector3 vVector2)
//--------------------------------------------------------------------------------
{
CVector3 vNormal;
if(Error_Detected == true)return vNormal;

try
  {
  vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
  vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
  vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

  return vNormal;	
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Croos",45);
  }
return vNormal;
}


//--------------------------------------------------------------------------------
void COpenGl_Camera::ReSizeGLScene(int width,int height)		
//--------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  if(height <= 0)height = 1;
  glViewport(0, 0, width, height);					
  glMatrixMode(GL_PROJECTION);						
  glLoadIdentity();							

  gluPerspective(45.0f,(float)width/(float)height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();							
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in COpenGl_Camera::ResizeGlScene",45);
  }
}

//--------------------------------------------------------------------------------
void COpenGl_Camera::InitGL_Values()					  
//--------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glEnable(GL_TEXTURE_2D);
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in COpenGl_Camera::InitGl",45);
  }
}

//--------------------------------------------------------------------------------
COpenGl_Camera::COpenGl_Camera()								
//--------------------------------------------------------------------------------
{
Error_Detected = false;

CVector3 vZero = CVector3(0.0, 0.0, 0.0);
CVector3 vView = CVector3(0.0, 1.0, 0.5);
CVector3 vUp   = CVector3(0.0, 0.0, 1.0);

m_vPosition	= vZero;					// Init the position to zero
m_vView		= vView;					// Init the view to a std starting view
m_vUpVector	= vUp;						// Init the UpVector
}
//--------------------------------------------------------------------------------
COpenGl_Camera::~COpenGl_Camera()								
//--------------------------------------------------------------------------------
{
}

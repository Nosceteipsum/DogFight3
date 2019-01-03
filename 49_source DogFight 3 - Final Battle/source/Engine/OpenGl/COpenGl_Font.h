////////////////////////////////////////////////////////////////////
//								  //
//			OpenGl Font			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined COpenGl_Font_H
#define COpenGl_Font_H

//----------------------------------//
//--------- Library files ----------//
//----------------------------------//

#pragma comment(linker, "/defaultlib:GlAux.lib")

//----------------------------------//
//------------ Defines -------------//
//----------------------------------//

//----------------------------------//
//--------- Include files ----------//
//----------------------------------//

#include <gl\glaux.h>

//----------------------------------//
//------- Prototypes files ---------//
//----------------------------------//

//----------------------------------//
//------------- Class --------------//
//----------------------------------//

class COpenGl_Font
{
public:

COpenGl_Font();
~COpenGl_Font();

void LoadGLFont(char *FileName);
void BuildFont ();
void KillFont  ();                                                      
void glPrint   (int x, int y, char *string, int set);


bool  Error_Check         ();
char *Get_Error_Message   ();

protected:

private:

GLuint	          texture;
int	          base;

bool    Error_Detected;
char	Error_Message[50];
};

#endif


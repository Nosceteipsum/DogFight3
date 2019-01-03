////////////////////////////////////////////////////////////////////
//								  //
//			OpenGl Texture_TGA		  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined COpenGl_Texture_TGA_H
#define COpenGl_Texture_TGA_H

//----------------------------------//
//--------- Library files ----------//
//----------------------------------//

//----------------------------------//
//------------ Defines -------------//
//----------------------------------//

//----------------------------------//
//--------- Include files ----------//
//----------------------------------//

#include <stdio.h>
#include <gl\glaux.h>

//----------------------------------//
//------- Prototypes files ---------//
//----------------------------------//

//----------------------------------//
//------------- Class --------------//
//----------------------------------//

struct	TextureImageTGA												
{
GLubyte	*imageData;											
GLuint	bpp;												
GLuint	width;												
GLuint	height;								
GLuint	texID;		
};

class COpenGl_Texture_TGA
{
public:

COpenGl_Texture_TGA();
~COpenGl_Texture_TGA();

void FreeTGA    (TextureImageTGA *texture);
void LoadTGA    (TextureImageTGA *texture, char *filename,char TextureLoadWay);
void Draw_QuadTexture(TextureImageTGA *TextureUse,float X,float Y,float Z,char Texture);

bool  Error_Check         ();
char *Get_Error_Message   ();

protected:

private:

bool    Error_Detected;
char	Error_Message[50];
};

#endif


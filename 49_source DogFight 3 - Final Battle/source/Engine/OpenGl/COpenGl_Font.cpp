////////////////////////////////////////////////////////////////////
//								  //
//			OpenGl Font			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "COpenGl_Font.h"

//--------------------------------------------------------------------------------
char *COpenGl_Font::Get_Error_Message(){return Error_Message;}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
bool COpenGl_Font::Error_Check(){return Error_Detected;}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
COpenGl_Font::COpenGl_Font()								
//--------------------------------------------------------------------------------
{
Error_Detected = false;
}
//--------------------------------------------------------------------------------
COpenGl_Font::~COpenGl_Font()								
//--------------------------------------------------------------------------------
{

}

//--------------------------------------------------------------------------------
void COpenGl_Font::BuildFont()								
//--------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  int loop;
  float	cx;						
  float	cy;							

  base=glGenLists(256);								
  glBindTexture(GL_TEXTURE_2D, texture);			
  for (loop=0; loop<256; loop++)						
    {
    cx=float(loop%16)/16.0f;						
    cy=float(loop/16)/16.0f;					

    glNewList(base+loop,GL_COMPILE);				
    glBegin(GL_QUADS); 
    glTexCoord2f(cx,1-cy-0.0625f);			
    glVertex2i(0,0);						
    glTexCoord2f(cx+0.0625f,1-cy-0.0625f);	
    glVertex2i(16,0);						
    glTexCoord2f(cx+0.0625f,1-cy);			
    glVertex2i(16,16);						
    glTexCoord2f(cx,1-cy);					
    glVertex2i(0,16);						
    glEnd();									
    glTranslated(10,0,0);						
    glEndList();									
    }													
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in BuildFont",45);
  }
}

//--------------------------------------------------------------------------------
void COpenGl_Font::KillFont()								
//--------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  glDeleteLists(base,256);
  glDeleteTextures(1, &texture);
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in KillFont",45);
  }
}

//--------------------------------------------------------------------------------
void COpenGl_Font::glPrint(int x,int y,char *string,int set)	
//--------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  if(set > 1)set=1;

  glBlendFunc(GL_SRC_ALPHA,GL_ONE);

  glBindTexture(GL_TEXTURE_2D, texture);	
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);	
  glPushMatrix();
  glMatrixMode(GL_PROJECTION);	
  glLoadIdentity();									

  glOrtho(0,640,0,480,-1,1);							
  glMatrixMode(GL_MODELVIEW);							

  glPushMatrix();									

  glLoadIdentity();									
  glTranslated(x,y,0.0f);								
  glListBase(base-32+(128*set));	

  glCallLists(strlen(string),GL_BYTE,string);			

  glMatrixMode(GL_PROJECTION);						

  glPopMatrix();										

  glMatrixMode(GL_MODELVIEW);							
  glPopMatrix();										
  glEnable(GL_DEPTH_TEST);							
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in glPrint",45);
  }
}
//--------------------------------------------------------------------------------
void COpenGl_Font::LoadGLFont(char *FileName)                              
//--------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  AUX_RGBImageRec *TextureFont;         
  TextureFont=auxDIBImageLoad(FileName);

  glGenTextures(1, &texture);          

  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureFont->sizeX, TextureFont->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureFont->data);

  if(TextureFont && TextureFont->data)		
    {
    free(TextureFont->data);	
    }

  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in LoadGLFont",45);
  }
}
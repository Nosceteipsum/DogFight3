////////////////////////////////////////////////////////////////////
//								  //
//			OpenGl Texture_TGA		  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "COpenGl_Texture_TGA.h"

//--------------------------------------------------------------------------------
char *COpenGl_Texture_TGA::Get_Error_Message(){return Error_Message;}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
bool COpenGl_Texture_TGA::Error_Check(){return Error_Detected;}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
void COpenGl_Texture_TGA::FreeTGA(TextureImageTGA *texture)
//--------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  if(texture->imageData != NULL)free(texture->imageData);
  }

catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in FreeTGA",45);
  }
}

//--------------------------------------------------------------------------------
void COpenGl_Texture_TGA::LoadTGA(TextureImageTGA *texture, char *filename,char Texture_Quility)
//--------------------------------------------------------------------------------
{    
if(Error_Detected == true)return;

try
  {
  GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};		
  GLubyte		TGAcompare[12];									
  GLubyte		header[6];										
  GLuint		bytesPerPixel;									
  GLuint		imageSize;										
  GLuint		type = GL_RGBA;									

  FILE *file = fopen(filename, "rb");							

  if(file==NULL                                                        ||
  fread (TGAcompare,1,sizeof(TGAcompare),file)   != sizeof(TGAcompare) ||	
  memcmp(TGAheader,TGAcompare,sizeof(TGAheader)) != 0	               ||	
  fread (header,1,sizeof(header),file)           != sizeof(header))				
    {
    if(file == NULL)return;										
    else													
      {
      fclose(file);										
      Error_Detected = true;
      memcpy(Error_Message,"Error in LoadTGA (Bad File)",45);
      return;										
      }
    }
  texture->width  = header[1] * 256 + header[0];				
  texture->height = header[3] * 256 + header[2];				
  
  if(	texture->width	<=0	||									
	texture->height	<=0	||									
	(header[4]!=24 && header[4]!=32))	
	  {
          fclose(file);
          Error_Detected = true;
          memcpy(Error_Message,"Error in LoadTGA (Wrong File format)",45);
	  return;
	  }
  texture->bpp	= header[4];
  bytesPerPixel	= texture->bpp/8;
  imageSize	= texture->width*texture->height*bytesPerPixel;	

  texture->imageData=(GLubyte *)malloc(imageSize);

  if(	texture->imageData==NULL ||		
	fread(texture->imageData, 1, imageSize, file)!=imageSize)
	  {
	  if(texture->imageData!=NULL)free(texture->imageData);
          fclose(file);
          Error_Detected = true;
          memcpy(Error_Message,"Error in LoadTGA (Malloc or fread fail)",45);
	  return;
	  }

  GLuint		temp;
  for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)
    {
    temp=texture->imageData[i];
    texture->imageData[i] = texture->imageData[i + 2];
    texture->imageData[i + 2] = temp;
    }

  fclose (file);

  glGenTextures(1, &texture[0].texID);
  glBindTexture(GL_TEXTURE_2D, texture[0].texID);
  if(Texture_Quility == 0)
    {
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
    }
  if(Texture_Quility == 1)
    {
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    }
  if(Texture_Quility == 2)
    {
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, texture[0].width, texture[0].height, GL_RGBA, GL_UNSIGNED_BYTE, texture[0].imageData);
    }
  if (texture[0].bpp==24)
    {
    type=GL_RGB;
    }
  if(Texture_Quility != 2)glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in LoadTGA",45);
  } 
}
//--------------------------------------------------------------------------------
void COpenGl_Texture_TGA::Draw_QuadTexture(TextureImageTGA *TextureUse,float X,float Y,float Z,char Texture)
//--------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  if(Texture == 1)
    {
    glBindTexture(GL_TEXTURE_2D, TextureUse->texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-X-0.0f,-Y-0.0f,+Z+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+X+0.0f,-Y-0.0f,+Z+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+X+0.0f,+Y+0.0f,-Z-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-X-0.0f,+Y+0.0f,-Z-0.0f);	
    glEnd(); 
    return;
    }
  if(Texture == 0)glBegin(GL_QUADS);	
  if(Texture == 2)glBegin(GL_LINES);	
  glVertex3f(-X-0.0f,-Y-0.0f,+Z+0.0f);
  glVertex3f(+X+0.0f,-Y-0.0f,+Z+0.0f);
  glVertex3f(+X+0.0f,+Y+0.0f,-Z-0.0f);
  glVertex3f(-X-0.0f,+Y+0.0f,-Z-0.0f);	
  glEnd();
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error In Draw_QuadTexture",45);
  }
}

//--------------------------------------------------------------------------------
COpenGl_Texture_TGA::COpenGl_Texture_TGA()
//--------------------------------------------------------------------------------
{

}

//--------------------------------------------------------------------------------
COpenGl_Texture_TGA::~COpenGl_Texture_TGA()
//--------------------------------------------------------------------------------
{

}

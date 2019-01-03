////////////////////////////////////////////////////////////////////
//                                                                //
//	  	  DF 3: Map_CPP                                           //
//                                                                //
//	     Made By: Tommy Kobberø Andersen                          //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "../../../global.h"

//------------------------------------------------------------------
CMap::CMap()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
CMap::~CMap()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
void CMap::Draw(SData *Data)
//------------------------------------------------------------------
  {
  glPushMatrix();
  glTranslatef(8.0f,-6.05f,-15.0f); 

  for(char i=0;i<=14;i++)
    {
    if(m_cMapType == MAP_TYPE_GRASS){glBindTexture(GL_TEXTURE_2D,Data->Tex_Grass.texID);}
    if(m_cMapType == MAP_TYPE_FARM) {glBindTexture(GL_TEXTURE_2D,Data->Tex_Farm.texID);}
    if(m_cMapType == MAP_TYPE_ICE)
      {
      if(m_baField_Destroyed[i] == false)glBindTexture(GL_TEXTURE_2D,Data->Tex_Ice.texID);
      if(m_baField_Destroyed[i] == true) glBindTexture(GL_TEXTURE_2D,Data->Tex_Ice_DeaD.texID);
      }
    if(m_cMapType == MAP_TYPE_WILD_GRASS){glBindTexture(GL_TEXTURE_2D,Data->Tex_WildGrass.texID);}
    if(m_cMapType == MAP_TYPE_ADV_GRASS)
      {
      if(i == 3 || i == 4 || i == 10 || i == 11)glBindTexture(GL_TEXTURE_2D,Data->Tex_Grass.texID);
      else                          
        {
        if(m_baField_Destroyed[i] == false)glBindTexture(GL_TEXTURE_2D,Data->Tex_Bridge.texID);
        if(m_baField_Destroyed[i] == true) glBindTexture(GL_TEXTURE_2D,Data->Tex_Bridge_DeaD.texID);
        }
      }
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.6f,-0.19f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.6f,-0.19f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.6f,+0.19f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.6f,+0.19f,-0.0f);	
    glEnd();

    glTranslatef(-1.20f,0.0f,0.0f); 
    }
  glPopMatrix();
  }

//------------------------------------------------------------------
void CMap::Draw_Tree(SData *Data)
//------------------------------------------------------------------
  {
  for(int i=0;i < 3;i++)
    {
    if(m_cMapType != MAP_TYPE_ADV_GRASS && m_cMapType != MAP_TYPE_ICE && m_bTreeActivate[i] == true)
      {
      glPushMatrix();

      if(m_cTreeType[i] == 0){glTranslatef(m_fTreeX[i],-4.83f,-15.0f);glBindTexture(GL_TEXTURE_2D,Data->Tex_Tree1.texID);}
      if(m_cTreeType[i] == 1){glTranslatef(m_fTreeX[i],-4.82f,-15.0f);glBindTexture(GL_TEXTURE_2D,Data->Tex_Tree2.texID);}
      if(m_cTreeType[i] == 2){glTranslatef(m_fTreeX[i],-4.80f,-15.0f);glBindTexture(GL_TEXTURE_2D,Data->Tex_Tree3.texID);}

      glBegin(GL_QUADS);						
      glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.9f,-1.3f,+0.0f);	
      glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.9f,-1.3f,+0.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.9f,+1.3f,-0.0f);
      glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.9f,+1.3f,-0.0f);	
      glEnd();
      glPopMatrix();
      }
    }
  }

//------------------------------------------------------------------
void CMap::Init()
//------------------------------------------------------------------
  {
  m_cMapType  = (rand()%5)+1;

  m_fTreeX[0] = (-900.0f+(+(rand()%1800))) * 0.01f;
  if(rand()%2 == 0)m_bTreeActivate[0] =  true;
  else             m_bTreeActivate[0] =  false;
  m_fTreeX[1] = (-900.0f+(+(rand()%1800))) * 0.01f;
  if(rand()%2 == 0)m_bTreeActivate[1] =  true;
  else             m_bTreeActivate[1] =  false;
  m_fTreeX[2] = (-900.0f+(+(rand()%1800))) * 0.01f;
  if(rand()%2 == 0)m_bTreeActivate[2] =  true;
  else             m_bTreeActivate[2] =  false;

  m_cTreeType[0]  = rand()%3;
  m_cTreeType[1]  = rand()%3;
  m_cTreeType[2]  = rand()%3;

  for(int i = 0;i < 15;i++)
    {
    m_baField_Destroyed[i] = false;
    }
  }



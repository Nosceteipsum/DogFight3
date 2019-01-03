////////////////////////////////////////////////////////////////////
//                                                                //
//               DF 3: Sky_CPP                                    //
//                                                                //
//         Made By: Tommy Kobberø Andersen                        //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "../../../global.h"

//------------------------------------------------------------------
CSky::CSky()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
CSky::~CSky()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
void CSky::Move(SEngine *Temp_Engine,CGameHandler *GameHandler)
//------------------------------------------------------------------
  {
  if(m_bActive == false)return;

  m_fX += m_fSpeed * 16.0f * 0.0001f * (float)Temp_Engine->Timer.GetDeltaMs();

  if(m_fX >  30.0f && m_fSpeed >  0.0f)Init(Temp_Engine,GameHandler);
  if(m_fX < -30.0f && m_fSpeed < -0.0f)Init(Temp_Engine,GameHandler);
  }

//------------------------------------------------------------------
void CSky::Init(SEngine *Temp_Engine,CGameHandler *GameHandler)
//------------------------------------------------------------------
  {
  if(Temp_Engine->Server == false)return;

  m_fY = ((rand()%100)-50)*0.1f;

  m_fBlend = 0.5f + ((rand()%100) * 0.01f);
  if(rand()%2 == 0)
    {
    m_fSpeed =  0.2f + ((rand()%80) * 0.01f);
    m_fX = -10.0f - ((rand()%300) * 0.1f);
    }

  else             
    {
    m_fSpeed = -0.2f - ((rand()%80) * 0.01f);
    m_fX = 10.0f + ((rand()%300) * 0.1f);
    }

  m_fSize  = (rand()%50)*0.1f;

  if(rand()%2 == 0)m_bConfuse = true;
  else             m_bConfuse = false;

  if(rand()%2 == 0)m_bActive = true;
  else             m_bActive = false;

  GameHandler->Server_Network_Send(PACKET_SERVER_SYNCSKY,Temp_Engine);
  }

//------------------------------------------------------------------
void CSky::Draw(SData *Data)
//------------------------------------------------------------------
  {
  if(m_bActive == false)return;
  if(m_fX > 12.0f || m_fX < -12.0f)return;

  glPushMatrix();
  glTranslatef(m_fX,m_fY,-15.0f);

  if(m_bConfuse == false)glBindTexture(GL_TEXTURE_2D,Data->Tex_Sky.texID);
  if(m_bConfuse == true )glBindTexture(GL_TEXTURE_2D,Data->Tex_Sky_Dark.texID);

  glColor4f(1.0f,1.0f,1.0f,m_fBlend);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3f-m_fSize,-0.3f-m_fSize,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.3f+m_fSize,-0.3f-m_fSize,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.3f+m_fSize,+0.3f+m_fSize,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3f-m_fSize,+0.3f+m_fSize,-0.0f);	
  glEnd();

  glColor4f(1.0f,1.0f,1.0f,1.0f);

  glPopMatrix();
  }


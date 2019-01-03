////////////////////////////////////////////////////////////////////
//                                                                //
//               DF 3: Fire_CPP                                   //
//                                                                //
//         Made By: Tommy Kobberø Andersen                        //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "../../../global.h"

//------------------------------------------------------------------
CFire::CFire()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
CFire::~CFire()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
void CFire::Draw(SData *Data,bool YourSelf)
//------------------------------------------------------------------
  {
  if(m_bActive == false)return;

  glPushMatrix();							
  glTranslatef(m_fx,m_fy,-15.0f);

  glBindTexture(GL_TEXTURE_2D,Data->Tex_Fire_Particle.texID);
  if(m_cType >= 4 && YourSelf == true) glColor4f(1.0f,1.0f,1.0f,0.3f);
  if(m_cType >= 4 && YourSelf == false)glColor4f(1.0f,1.0f,1.0f,0.0f);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_fSize,-m_fSize,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+m_fSize,-m_fSize,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+m_fSize,+m_fSize,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_fSize,+m_fSize,-0.0f);	
  glEnd();

  if(m_cType >= 4)glColor4f(1.0f,1.0f,1.0f,1.0f);

  glPopMatrix();
  }

//------------------------------------------------------------------
void CFire::Create(float x,float y,float Rotate,float Speed)
//------------------------------------------------------------------
  {
  if(m_bActive == true)return;

  m_fx      = x;
  m_fy      = y;
  m_fRotate = Rotate;
  m_fSpeed  = Speed;
  if(m_fSpeed <= 1.2f)m_fSpeed = 1.2f;

  if(m_cType <= 2)m_fSize = 0.05f;
  if(m_cType >  2)m_fSize = 0.10f;

  m_bActive = true;

  m_fx -= 10.0f * (float)sin(0.017453 * m_fRotate) * 0.017f;
  m_fy += 10.0f * (float)cos(0.017453 * m_fRotate) * 0.017f;
  }

//------------------------------------------------------------------
void CFire::Move(CGameHandler *GameHandler,SEngine *Temp_Engine)
//------------------------------------------------------------------
  {
  if(m_bActive == false)return;

  //-------------------------------------------------------//
  //                 Moving Projectile                     //
  //-------------------------------------------------------//

  if(m_cType > 0)
    {
    m_fx -= (m_fSpeed+2.25f) * (float)sin(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();
    m_fy += (m_fSpeed+2.25f) * (float)cos(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();
    }

  if(m_cType <= 0)
    {
    m_fx -= (m_fSpeed+1.75f) * (float)sin(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();
    m_fy += (m_fSpeed+1.75f) * (float)cos(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();
    }

  //-------------------------------------------------------//
  //                 CHECKING COLLISION                    //
  //-------------------------------------------------------//

  //--------------- Collision Right/Left ------------------//

  if(m_fx >  8.31f){m_bActive = false;}
  if(m_fx < -8.36f){m_bActive = false;}

  //--------------- Collision Top        ------------------//

  if(m_fy > 6.3   ){m_bActive = false;}

  //--------------- Collision Down       ------------------//

  if(m_fy < -6.5f ){m_bActive = false;}
  }

//------------------------------------------------------------------
void CFire::SetType(char Type)
//------------------------------------------------------------------
  {
  m_cType = Type;
  }

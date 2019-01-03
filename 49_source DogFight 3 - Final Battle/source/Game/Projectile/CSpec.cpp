////////////////////////////////////////////////////////////////////
//                                                                //
//               DF 3: Spec_CPP                                   //
//                                                                //
//         Made By: Tommy Kobberø Andersen                        //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "../../../global.h"

//------------------------------------------------------------------
CSpec::CSpec()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
CSpec::~CSpec()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
void CSpec::Draw(SData *Data)
//------------------------------------------------------------------
  {
  if(m_bActive == false || m_cType == 0)return;

  glPushMatrix();							
  glTranslatef(m_fx,m_fy,-15.0f);

  if(m_bStun_Active == true)
    {
    glColor4f(1.0f,1.0f,1.0f,m_fStun);

    glBindTexture(GL_TEXTURE_2D,Data->Tex_Spec_Particle.texID);
    gluSphere(Data->Sphere,0.3f + (1.0f-m_fStun),16,16);

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    }

  if(m_bStun_Active == false)
    {
    glBindTexture(GL_TEXTURE_2D,Data->Tex_Spec_Particle.texID);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_fSize,-m_fSize,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+m_fSize,-m_fSize,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+m_fSize,+m_fSize,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_fSize,+m_fSize,-0.0f);	
    glEnd();
    }

  glPopMatrix();
  }

//------------------------------------------------------------------
void CSpec::Create(float x,float y,float Rotate,float Speed)
//------------------------------------------------------------------
  {
  if(m_bActive == true || m_cType == 0)return;

  m_fx      = x;
  m_fy      = y;
  m_fRotate = Rotate;

  m_fSize   = 0.05f;
  m_fSpeed  = Speed;
  if(m_fSpeed <= 1.3f)m_fSpeed = 1.3f;

  m_bActive = true;
  m_fStun   = 0.0f;
  m_bStun_Active = false;

  m_fx -= 10.0f * (float)sin(0.017453 * m_fRotate) * 0.017f;
  m_fy += 10.0f * (float)cos(0.017453 * m_fRotate) * 0.017f;
  }

//------------------------------------------------------------------
void CSpec::Move(SEngine *Temp_Engine)
//------------------------------------------------------------------
  {
  if(m_bActive == false || m_cType == 0)return;


  //-------------------------------------------------------//
  //                   Handling Stun                       //
  //-------------------------------------------------------//

  if(m_bStun_Active == true)
    {
    if(m_fStun > 0.0f)m_fStun -= 0.001f * (float)Temp_Engine->Timer.GetDeltaMs();
    if(m_fStun <= 0.0f)m_bActive = false;
    return;
    }

  //-------------------------------------------------------//
  //                 Moving Projectile                     //
  //-------------------------------------------------------//

  m_fx -= (m_fSpeed + 2.5f) * (float)sin(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();
  m_fy += (m_fSpeed + 2.5f) * (float)cos(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();

  //-------------------------------------------------------//
  //                 CHECKING COLLISION                    //
  //-------------------------------------------------------//

  //--------------- Collision Right/Left ------------------//

  if(m_fx >  8.31f){m_bActive = false;}
  if(m_fx < -8.36f){m_bActive = false;}

  //--------------- Collision Top        ------------------//

  if(m_fy > 6.3   ){m_bActive = false;}

  //--------------- Collision Down       ------------------//

  if(m_fy < -6.0f )
    {
    if(m_cType >= 3)
      {
      m_fStun        = 1.0f;
      m_bStun_Active = true;
      return;
      }
    m_bActive = false;
    }
  }

//------------------------------------------------------------------
void CSpec::SetType(char Type)
//------------------------------------------------------------------
  {
  m_cType = Type;
  }


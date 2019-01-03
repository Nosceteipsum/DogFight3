////////////////////////////////////////////////////////////////////
//                                                                //
//               DF 3: Man_CPP                                    //
//                                                                //
//         Made By: Tommy Kobberø Andersen                        //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "../../../global.h"

//------------------------------------------------------------------
CMan::CMan()
//------------------------------------------------------------------
  {

  }

//------------------------------------------------------------------
CMan::~CMan()
//------------------------------------------------------------------
  {

  }

//------------------------------------------------------------------
void CMan::Draw(SData *Data,bool DrawArrow)
//------------------------------------------------------------------
  {
  if(m_bActive == false)return;

  glPushMatrix();							
  glTranslatef(m_fx,m_fy,-15.0f);

  if((m_cStartNR % 2) == 0 && (m_cType != 5 || m_cStatus != MAN_STATUS_FLYING)) // Green
    {
    glBindTexture(GL_TEXTURE_2D,Data->Tex_Green_Man.texID);
    }
  if((m_cStartNR % 2) == 1 && (m_cType != 5 || m_cStatus != MAN_STATUS_FLYING)) // Red
    {
    glBindTexture(GL_TEXTURE_2D,Data->Tex_Red_Man.texID);
    }
  if(m_cType == 5 && m_cStatus != MAN_STATUS_GROUND && m_cStatus != MAN_STATUS_DEAD) // Red
    {
    glBindTexture(GL_TEXTURE_2D,Data->Tex_Ball.texID);
    }

  if(m_cType == 4 && m_cStatus == MAN_STATUS_PARACHUTING && DrawArrow == true) glColor4f(1.0,1.0f,1.0f,0.3f);
  if(m_cType == 4 && m_cStatus == MAN_STATUS_PARACHUTING && DrawArrow == false)glColor4f(1.0,1.0f,1.0f,0.0f);

  glRotatef(m_fManRotate+180.0f,0.0f,0.0f,1.0f);
  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.09f,-0.09f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.09f,-0.09f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.09f,+0.09f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.09f,+0.09f,-0.0f);	
  glEnd();

  if(m_cType == 4)glColor4f(1.0,1.0f,1.0f,1.0f);

  glPopMatrix();

  if(m_cStatus == MAN_STATUS_DEAD)Draw_Blood(Data);

  if((m_cStatus == MAN_STATUS_BEHIND_PLANE || m_cStatus == MAN_STATUS_GROUND) && DrawArrow == true)
    {
    glPushMatrix();
    if(m_cStatus == MAN_STATUS_GROUND)      glTranslatef(m_fx,-5.90f,-15.0f);
    if(m_cStatus == MAN_STATUS_BEHIND_PLANE)glTranslatef(m_fx,m_fy,-15.0f);

    glBindTexture(GL_TEXTURE_2D,Data->Tex_Point.texID);

    glRotatef(m_fRotate+180.0f,0.0f,0.0f,1.0f);

    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.09f,-0.16f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.09f,-0.16f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.09f,+0.16f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.09f,+0.16f,-0.0f);	
    glEnd();
    glPopMatrix();
    }

  if(m_cStatus == MAN_STATUS_PARACHUTING || m_bSplashPara == true)
    {
    glPushMatrix();							
    if(m_bSplashPara == false)glTranslatef(m_fx,m_fy,-15.0f);
    if(m_bSplashPara == true)glTranslatef(m_fx + (((rand()%10)-5)*0.01f),m_fy + (((rand()%10)-5)*0.01f),-15.0f);

    if((m_cStartNR % 2) == 0) // Green
      {
      glBindTexture(GL_TEXTURE_2D,Data->Tex_Green_Para.texID);
      }
    if((m_cStartNR % 2) == 1) // Red
      {
      glBindTexture(GL_TEXTURE_2D,Data->Tex_Red_Para.texID);
      }

    if(m_cType >= 4 && DrawArrow == true) glColor4f(1.0,1.0f,1.0f,0.3f);
    if(m_cType >= 4 && DrawArrow == false)glColor4f(1.0,1.0f,1.0f,0.0f);

    if(m_bSplashPara == false)glRotatef(m_fManRotate+180.0f,0.0f,0.0f,1.0f);
	if(m_bSplashPara == true) glRotatef(m_fRotate+180.0f,0.0f,0.0f,1.0f);
    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.09f,+0.05f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.09f,+0.05f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.09f,+0.05f+m_fPara_Folding_Out,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.09f,+0.05f+m_fPara_Folding_Out,-0.0f);	
    glEnd();

    if(m_cType >= 4)glColor4f(1.0,1.0f,1.0f,1.0f);

    glPopMatrix();
    }
  }

//------------------------------------------------------------------
void CMan::Draw_Blood(SData *Data)
//------------------------------------------------------------------
  {
  for(int i = 0;i < 100;i++)
    {
    if(m_bBlood[i] == false)continue;

    glPushMatrix();							
    glTranslatef(m_fBloodX[i],m_fBloodY[i]-0.03f,-15.0f);
    glColor4f(1.0f,0.0f,0.0f,0.7f);

    glBindTexture(GL_TEXTURE_2D,Data->Tex_Blood_Particle.texID);

    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.11f,-0.05f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.11f,-0.05f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.11f,+0.05f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.11f,+0.05f,-0.0f);	
    glEnd();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glPopMatrix();
    }
  }

//------------------------------------------------------------------
void CMan::Move(CGameHandler *GameHandler,SEngine *Temp_Engine,bool Left,bool Right,bool Up,bool Down,char ID)
//------------------------------------------------------------------
  {
  if(m_bActive == false)return;

  int i;

  if(m_cStatus == MAN_STATUS_DEAD)m_cType = 3;

  //-------------------------------------------------------//
  //               Man Sitting Behind plane                //
  //-------------------------------------------------------//

  if(m_cStatus == MAN_STATUS_BEHIND_PLANE)
  {
	m_fx = GameHandler->Plane[m_cSittingBackPlane].m_fx;
	m_fy = GameHandler->Plane[m_cSittingBackPlane].m_fy;
	m_fManRotate = GameHandler->Plane[m_cSittingBackPlane].m_fRotate;

	m_fx += -(5.0f * (float)sin(0.017453 * m_fManRotate) * 0.0017f);
	m_fy += -(5.0f * (float)cos(0.017453 * m_fManRotate) * 0.0017f);

	if(GameHandler->Plane[m_cSittingBackPlane].m_cDamage == PLANE_DAMAGE_CRASHED || GameHandler->Plane[m_cSittingBackPlane].m_cDamage == PLANE_DAMAGE_APART)
	{
      m_cStatus = MAN_STATUS_FLYING;
	}
  }

  //-------------------------------------------------------//
  //               Man Splased on plane                    //
  //-------------------------------------------------------//

  if(m_cSplash != -1)
    {
		m_fx = GameHandler->Plane[m_cSplash].m_fx;
		m_fy = GameHandler->Plane[m_cSplash].m_fy;
		m_fRotate = GameHandler->Plane[m_cSplash].m_fRotate;
		m_fSpeed = GameHandler->Plane[m_cSplash].m_fSpeed;

		m_fManSlidingOf -= 0.5f * (float)Temp_Engine->Timer.GetDeltaMs() * 0.005f;

		if(m_fManSlidingOf <= -15.0f)
		{
			m_cSplash = -1;
			m_bSplashPara = false;
		}
	}  

  //-------------------------------------------------------//
  //           Man Normalysing up with PARA                //
  //-------------------------------------------------------//

  if(m_cStatus == MAN_STATUS_PARACHUTING)
    {
    if(m_fPara_Folding_Out <= 0.3f)
      {
      if(m_cType <= 2)m_fPara_Folding_Out += (float)Temp_Engine->Timer.GetDeltaMs() * 0.00030f;
      if(m_cType >= 3)m_fPara_Folding_Out += (float)Temp_Engine->Timer.GetDeltaMs() * 0.00050f;
      }
    if(m_fManRotate < 177.0f)m_fManRotate += (float)Temp_Engine->Timer.GetDeltaMs() * 0.2f;
    if(m_fManRotate > 183.0f)m_fManRotate -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.2f;

    if(m_fManRotate >= 177.0f && m_fManRotate <= 183.0f)
      {
      if(m_fRotate < 180)m_fRotate += (float)Temp_Engine->Timer.GetDeltaMs() * 0.1f;
      if(m_fRotate > 180)m_fRotate -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.1f;
      }
    }

  //-------------------------------------------------------//
  //             Moving Left/Right with PARA               //
  //-------------------------------------------------------//

  if(m_cStatus == MAN_STATUS_PARACHUTING)
    {
    if(m_fPara_Folding_Out >  0.3f)
      {
      if(m_cType <= 1 && Left) m_fx -= 0.0001f * (float)Temp_Engine->Timer.GetDeltaMs();
      if(m_cType <= 1 && Right)m_fx += 0.0001f * (float)Temp_Engine->Timer.GetDeltaMs();
      if(m_cType >= 2 && Left) m_fx -= 0.0002f * (float)Temp_Engine->Timer.GetDeltaMs();
      if(m_cType >= 2 && Right)m_fx += 0.0002f * (float)Temp_Engine->Timer.GetDeltaMs();
      }
    }

  //-------------------------------------------------------//
  //             PARA Landing Safe on Ground               //
  //-------------------------------------------------------//

  if(m_cStatus == MAN_STATUS_PARACHUTING)
    {
    if(m_fy < -6.0f && m_fPara_Folding_Out >  0.3f)
      {
      m_cStatus = MAN_STATUS_GROUND;
      }
    }

  //-------------------------------------------------------//
  //          Man Warp with X-Coordinate                 //
  //-------------------------------------------------------//

  if(m_fx >  8.21f){m_fx = -8.25f;}
  if(m_fx < -8.26f){m_fx =  8.20f;}

  //-------------------------------------------------------//
  //               Man Flying Slowy Down                   //
  //-------------------------------------------------------//

  if(m_cStatus == MAN_STATUS_PARACHUTING)
    {
    if(m_fPara_Folding_Out >  0.3f)
      {
      m_fy -= 0.0003f * (float)Temp_Engine->Timer.GetDeltaMs();

      return;
      }
    }

  //-------------------------------------------------------//
  //               Man Rotating in Air                     //
  //-------------------------------------------------------//

  if(m_cStatus == MAN_STATUS_FLYING)m_fManRotate += (float)Temp_Engine->Timer.GetDeltaMs() * 0.5f;

  //-------------------------------------------------------//
  //               Handle Man on Ground                    //
  //-------------------------------------------------------//

  if(m_cStatus == MAN_STATUS_GROUND)
    {
    if(m_cType <= 2 && Left) m_fx -= 0.0001f * (float)Temp_Engine->Timer.GetDeltaMs();
    if(m_cType <= 2 && Right)m_fx += 0.0001f * (float)Temp_Engine->Timer.GetDeltaMs();
    if(m_cType >= 3 && Left) m_fx -= 0.0002f * (float)Temp_Engine->Timer.GetDeltaMs();
    if(m_cType >= 3 && Right)m_fx += 0.0002f * (float)Temp_Engine->Timer.GetDeltaMs();
    }

  if(m_cStatus == MAN_STATUS_GROUND || m_cStatus == MAN_STATUS_BEHIND_PLANE)
  {
    if(Up)  m_fRotate -= 0.05f * (float)Temp_Engine->Timer.GetDeltaMs();
    if(Down)m_fRotate += 0.05f * (float)Temp_Engine->Timer.GetDeltaMs();
    return;
  }

  //-------------------------------------------------------//
  //                    Man moving                         //
  //-------------------------------------------------------//

  if(m_cType != 5 && m_fSpeed > 0.0f)
  {
	  m_fx -= m_fSpeed * (float)sin(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();
	  m_fy += m_fSpeed * (float)cos(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();
  }
  if(m_cType == 5)
  {
	  m_fx -= m_fSpeedBx * (float)sin(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();
	  m_fy += m_fSpeed * (float)cos(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();
  }


  //-------------------------------------------------------//
  //		       Players Man Turn bettwen 0-360	     //
  //-------------------------------------------------------//

  if(m_fRotate <   0)m_fRotate = 360;
  if(m_fRotate > 360)m_fRotate =   0;
  if(m_fManRotate <   0)m_fManRotate = 360;
  if(m_fManRotate > 360)m_fManRotate =   0;

  //-------------------------------------------------------//
  //           Man Dead and Blood spawning                 //
  //-------------------------------------------------------//

  if(m_cStatus == MAN_STATUS_DEAD)
    {
	for(i = 0;i < 100;i++)
    {
      if(m_bBlood[i] == false && (rand()%40) == 0)
        {
        m_fBloodX[i]    = m_fx;
        m_fBloodY[i]    = m_fy;
        m_bBlood[i]     = true;
        break;
        }
	  if(m_bBlood[i] == true && m_fBloodY[i] >= -6.0)
	  {
		m_fBloodY[i] -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.001f;
	  }
    }
	  
	if(m_fy <  -5.8f)m_fy  = -6.0f;
    if(m_fy >  -5.8f)//m_fy -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.005f;
      {
      if(m_fRotate < 180.0f)m_fRotate += (float)Temp_Engine->Timer.GetDeltaMs() * 0.05f;
      if(m_fRotate > 180.0f)m_fRotate -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.05f;
      return;
      }

    if(m_fManRotate < 270.0f && m_fManRotate >= 180.0f)m_fManRotate += (float)Temp_Engine->Timer.GetDeltaMs() * 0.2f;
    if(m_fManRotate >  90.0f && m_fManRotate < 180.0f) m_fManRotate -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.2f;

    if(m_fSpeed < 0.0f)m_fSpeed = 0.0f;
    if(m_fSpeed > 0.0f)
      {
      m_fx -= m_fSpeed * (float)sin(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();
      m_fSpeed -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.01f;
      }
    return;
    }

  //-------------------------------------------------------//
  //		       Players Man Stopping		     //
  //-------------------------------------------------------//
if(m_cType != 5)
{
  if((m_fSpeed > 0.15f && m_fRotate < 150 || m_fRotate > 210))m_fSpeed -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.0005f;
}
  //-------------------------------------------------------//
  //		       Players Man Force Turn		     //
  //-------------------------------------------------------//
if(m_cType != 5)
{
  if(m_fRotate < 180.0f)m_fRotate += (float)Temp_Engine->Timer.GetDeltaMs() * 0.02f;
  if(m_fRotate > 180.0f)m_fRotate -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.02f;
}
if(m_cType == 5)
{
  if(m_fRotate < 180.0f)m_fRotate += (float)Temp_Engine->Timer.GetDeltaMs() * 0.01f;
  if(m_fRotate > 180.0f)m_fRotate -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.01f;
}

  //-------------------------------------------------------//
  //		         Players Man Speed down	               //
  //-------------------------------------------------------//

  m_fSpeed += (float)Temp_Engine->Timer.GetDeltaMs() * 0.0005f;
  if(m_cType == 5)
  {
	  m_fSpeed += (float)Temp_Engine->Timer.GetDeltaMs() * 0.002f;

	  if(m_fSpeed >  7.5f)m_fSpeed =  7.5f;
	  if(m_fSpeed < -7.5f)m_fSpeed = -7.5f;
  
  }
  //-------------------------------------------------------//
  //		         Players Man Hit Ground	               //
  //-------------------------------------------------------//

  if((m_fPara_Folding_Out <= 0.3f || m_cStatus == MAN_STATUS_FLYING))
    {
    if(m_fy < -6.0f && m_cType != 5 && Temp_Engine->Server == true)
      {
      m_cStatus = MAN_STATUS_DEAD;
      GameHandler->Add_ToStats(GameHandler->Find_Owner(ID),-1,4,Temp_Engine);
	  GameHandler->Server_Network_ManParaHit(-2,ID,-1,Temp_Engine);
      }
	if(m_fy < -6.0f && m_cType == 5)
	{
		if(m_fSpeed <= 1.0f && m_fSpeed >= -1.0f)
		{
			m_cStatus = MAN_STATUS_GROUND;
 		    m_fManRotate = 180.0f;
		}
		else
		{
			m_fSpeed = -m_fSpeed * 0.6f;
			m_fy     += 0.1f;
		}
	}
    }
  }

//------------------------------------------------------------------
void CMan::JumpOut(float x,float y,float Speed,float Rotate)
//------------------------------------------------------------------
  {
  m_fManRotate = 0.0f;
  m_fx         = x;
  m_fy         = y;
  m_fSpeed     = Speed;
  m_fSpeedBx   = Speed;
  m_fRotate    = Rotate;
  m_cStatus    = MAN_STATUS_FLYING;
  m_bActive    = true;

  m_fSize      = 0.09f;

  for(int i=0;i < 100;i++)
    {
    m_bBlood[i] = false;
    }
  }

//------------------------------------------------------------------
void CMan::SetType(char Type)
//------------------------------------------------------------------
  {
  m_cType = Type;
  m_cSplash = -1;
  m_bSplashPara = false;
  m_fManSlidingOf = -5.0f;
  m_cSittingBackPlane = -1;
  }

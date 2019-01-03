////////////////////////////////////////////////////////////////////
//                                                                //
//               DF 3: Plane_CPP                                  //
//                                                                //
//         Made By: Tommy Kobberø Andersen                        //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "../../../global.h"

//------------------------------------------------------------------
CPlane::CPlane()
//------------------------------------------------------------------
  {
  m_bInGame  = false;
  m_bOcupied = false;
  m_bAppartDontFall = false;
  m_bPunish  = false;
  }

//------------------------------------------------------------------
CPlane::~CPlane()
//------------------------------------------------------------------
  {

  }

//------------------------------------------------------------------
void CPlane::Init(SEngine *Temp_Engine,char StartNr)
//------------------------------------------------------------------
  {
  m_cStartNR = StartNr;

  for(int i=0;i < 100;i++)
    {
    m_fSmokeLife[i] = 0.0f;
    m_fFireLife[i] = 0.0f;
    }

  if((m_cStartNR % 2) == 0) 
    {
    m_fx = -7.0f;
    m_fRotate = 270.0f;

    if(StartNr ==  0)m_fy =  5.0f;
    if(StartNr ==  2)m_fy =  3.5f;
    if(StartNr ==  4)m_fy =  2.0f;
    if(StartNr ==  6)m_fy =  0.5f;
    if(StartNr ==  8)m_fy = -1.0f;
    if(StartNr == 10)m_fy = -2.5f;
    if(StartNr == 12)m_fy = -4.0f;
    if(StartNr == 14)m_fy = -5.5f;
    }

  if((m_cStartNR % 2) == 1) 
    {
    m_fx =  7.0f;
    m_fRotate = 90.0f;

    if(StartNr ==  1)m_fy =  5.0f;
    if(StartNr ==  3)m_fy =  3.5f;
    if(StartNr ==  5)m_fy =  2.0f;
    if(StartNr ==  7)m_fy =  0.5f;
    if(StartNr ==  9)m_fy = -1.0f;
    if(StartNr == 11)m_fy = -2.5f;
    if(StartNr == 13)m_fy = -4.0f;
    if(StartNr == 15)m_fy = -5.5f;
    }
  m_fSpeed        = 1.0f;
  m_cDamage       = PLANE_DAMAGE_NONE;
  m_cType         = PLANE_TYPE_NORMAL;
  m_fTop_Punish   = 0.0f;
  m_fxApartLenght = 0.0f;
  m_fShield       = 0.0f;

  m_fStealth      = 1.0f;
  m_bStealthUp    = true;

  m_fPoision      = 0.0f;
  m_bPoision_Soft_Active = false;
  m_bPoision_Hard_Active = false;

  m_fSize = 0.15f;

  m_bPilot  = true;
  /*
  if(m_bPunish)
    {
      m_cDamage = PLANE_DAMAGE_FIRE;
    }
   */
  }

//------------------------------------------------------------------
void CPlane::Draw_Fire(SData *Data)
//------------------------------------------------------------------
  {
  for(int i = 0;i < 100;i++)
    {
    if(m_fFireLife[i] <= 0.0f)continue;

    glPushMatrix();							
    glTranslatef(m_fFireX[i],m_fFireY[i],-15.0f);
    glColor4f(1.0f,1.0f,1.0f,m_fFireLife[i]);

    glBindTexture(GL_TEXTURE_2D,Data->Tex_Fire_Particle.texID);

    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.05f,-0.05f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.05f,-0.05f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.05f,+0.05f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.05f,+0.05f,-0.0f);	
    glEnd();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glPopMatrix();
    }
  }

//------------------------------------------------------------------
void CPlane::Draw_Shield(SData *Data)
//------------------------------------------------------------------
  {
  if(m_fShield > 0.0f)
    {
    glColor4f(1.0f,1.0f,1.0f,m_fShield);

    glBindTexture(GL_TEXTURE_2D,Data->Tex_Blood_Particle.texID);
    gluSphere(Data->Sphere,0.3f,16,16);

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    }
  }

//------------------------------------------------------------------
void CPlane::Draw_Smoke(SData *Data)
//------------------------------------------------------------------
  {
  for(int i = 0;i < 100;i++)
    {
    if(m_fSmokeLife[i] <= 0.0f)continue;

    glPushMatrix();							
    glTranslatef(m_fSmokeX[i],m_fSmokeY[i],-15.0f);
    glColor4f(1.0f,1.0f,1.0f,m_fSmokeLife[i]);

    glBindTexture(GL_TEXTURE_2D,Data->Tex_Smoke_Particle.texID);

    glBegin(GL_QUADS);						
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.15f,-0.15f,+0.0f);	
    glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.15f,-0.15f,+0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.15f,+0.15f,-0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.15f,+0.15f,-0.0f);	
    glEnd();

    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glPopMatrix();
    }
  }

//------------------------------------------------------------------
void CPlane::Draw_Plane(SData *Data,bool YourSelf)
//------------------------------------------------------------------
  {
  glPushMatrix();							
  glTranslatef(m_fx,m_fy,-15.0f);

  Draw_Shield(Data);

  if((m_cStartNR % 2) == 0) // Green
    {
    glBindTexture(GL_TEXTURE_2D,Data->Tex_Green_Plane.texID);
    }
  if((m_cStartNR % 2) == 1) // Red
    {
    glBindTexture(GL_TEXTURE_2D,Data->Tex_Red_Plane.texID);
    }

  if(m_cType >= 4 && YourSelf == false)glColor4f(1.0f,1.0f,1.0f,m_fStealth);
  if(m_cType >= 4 && YourSelf == true )
    {
    if(m_fStealth >= 0.5f)glColor4f(1.0f,1.0f,1.0f,m_fStealth);
    if(m_fStealth <  0.5f)glColor4f(1.0f,1.0f,1.0f,0.5f);
    }

  if(m_cType < 4 && YourSelf == false)glColor3f(0.7f,0.7f,0.7f);

  glRotatef(m_fRotate+90.0f,0.0f,0.0f,1.0f);
  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.15f,-0.15f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.15f,-0.15f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.15f,+0.15f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.15f,+0.15f,-0.0f);	
  glEnd();

  if(m_cType >= 4)glColor4f(1.0f,1.0f,1.0f,1.0f);
  if(m_cType < 4 && YourSelf == false)glColor3f(1.0f,1.0f,1.0f);

  glPopMatrix();
  }

//------------------------------------------------------------------
void CPlane::Hit(CGameHandler *GameHandler,char ID,char Damage,char Projectile,SEngine *Temp_Engine)
//------------------------------------------------------------------
  {
  if(Temp_Engine->Server == true)GameHandler->Server_Network_SendPlaneHit(ID,Damage,Projectile,Temp_Engine);

  if(m_cDamage == PLANE_DAMAGE_CRASHED || m_cDamage == PLANE_DAMAGE_APART)return;

  if(m_cDamage == PLANE_DAMAGE_SHIELD)
    {
    m_cDamage = PLANE_DAMAGE_NONE;
    FSOUND_PlaySound(FSOUND_FREE,GameHandler->m_sData.Snd_Plane_Shield);
    m_fShield = 1.0f;
    return;
    }

  m_cDamage += Damage;

  if(m_cDamage == PLANE_DAMAGE_CRASHED || m_cDamage >= PLANE_DAMAGE_APART)
    {
    if(m_bPilot == true)
      {
      GameHandler->Man[ID].JumpOut(m_fx,m_fy,m_fSpeed,m_fRotate);
      m_bPilot   = false;
      char Rand_Sound = rand()%5;
      if(Rand_Sound == 0)FSOUND_PlaySound(FSOUND_FREE,GameHandler->m_sData.Snd_Man_Falling01);
      if(Rand_Sound == 1)FSOUND_PlaySound(FSOUND_FREE,GameHandler->m_sData.Snd_Man_Falling02);
      if(Rand_Sound == 2)FSOUND_PlaySound(FSOUND_FREE,GameHandler->m_sData.Snd_Man_Falling03);
      if(Rand_Sound == 3)FSOUND_PlaySound(FSOUND_FREE,GameHandler->m_sData.Snd_Man_Falling04);
      if(Rand_Sound == 4)FSOUND_PlaySound(FSOUND_FREE,GameHandler->m_sData.Snd_Man_Falling05);
      }
    m_cDamage = PLANE_DAMAGE_APART;
    }
  }

//------------------------------------------------------------------
void CPlane::Draw_PlaneApart(SData *Data)
//------------------------------------------------------------------
  {
  glPushMatrix();							
  glTranslatef(m_fx-m_fxApartLenght,m_fy+m_fxApartLenght,-15.0f);

  if((m_cStartNR % 2) == 0){glBindTexture(GL_TEXTURE_2D,Data->Tex_Green_Plane_Part1.texID);}
  if((m_cStartNR % 2) == 1){glBindTexture(GL_TEXTURE_2D,Data->Tex_Red_Plane_Part1.texID);}

  glRotatef(m_fRotate+90.0f,0.0f,0.0f,1.4f);
  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.09f,-0.09f,+0.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.09f,-0.09f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.09f,+0.09f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.09f,+0.09f,-0.0f);
  glEnd();
  glPopMatrix();

  glPushMatrix();							
  glTranslatef(m_fx-m_fxApartLenght,m_fy-m_fxApartLenght,-15.0f);

  if((m_cStartNR % 2) == 0){glBindTexture(GL_TEXTURE_2D,Data->Tex_Green_Plane_Part2.texID);}
  if((m_cStartNR % 2) == 1){glBindTexture(GL_TEXTURE_2D,Data->Tex_Red_Plane_Part2.texID);}

  glRotatef(m_fRotate+90.0f,0.0f,0.0f,1.0f);
  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.09f,-0.09f,+0.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.09f,-0.09f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.09f,+0.09f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.09f,+0.09f,-0.0f);
  glEnd();
  glPopMatrix();

  glPushMatrix();							
  glTranslatef(m_fx+m_fxApartLenght,m_fy+m_fxApartLenght,-15.0f);

  if((m_cStartNR % 2) == 0){glBindTexture(GL_TEXTURE_2D,Data->Tex_Green_Plane_Part3.texID);}
  if((m_cStartNR % 2) == 1){glBindTexture(GL_TEXTURE_2D,Data->Tex_Red_Plane_Part3.texID);}

  glRotatef(m_fRotate+90.0f,0.0f,0.0f,0.7f);
  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.09f,-0.09f,+0.0f);
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.09f,-0.09f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.09f,+0.09f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.09f,+0.09f,-0.0f);
  glEnd();
  glPopMatrix();
  }

//------------------------------------------------------------------
void CPlane::Draw(SData *Data,bool YourSelf)
//------------------------------------------------------------------
  {
  if(m_bInGame == false)return;

  if(m_cDamage != PLANE_DAMAGE_APART)Draw_Plane(Data,YourSelf);
  if(m_cDamage == PLANE_DAMAGE_APART)
    {
    Draw_PlaneApart(Data);
    }

  if(m_cDamage != PLANE_DAMAGE_NONE)
    {
    Draw_Smoke(Data);
    Draw_Fire(Data);
    }
  }

//------------------------------------------------------------------
void CPlane::Move(SData *Data,CGameHandler *GameHandler,SEngine *Temp_Engine,bool Up,bool Left,bool Right,char ID,char PlayerID)
//------------------------------------------------------------------
  {
  if(m_bInGame == false)return;

  //-------------------------------------------------------//
  //                   Handle Stealth                       //
  //-------------------------------------------------------//

  if(m_cType >= 4)
    {
    if(m_bStealthUp == false)m_fStealth -= 0.001f * (float)Temp_Engine->Timer.GetDeltaMs();
    if(m_bStealthUp == true) m_fStealth += 0.001f * (float)Temp_Engine->Timer.GetDeltaMs();

    if(m_bStealthUp == false && m_fStealth <= -2.0f)m_bStealthUp = true;
    if(m_bStealthUp == true  && m_fStealth >   2.0f && GameHandler->Player[PlayerID].m_bKey_4 == true)m_bStealthUp = false;
    }

  //-------------------------------------------------------//
  //                   Handle Poison                       //
  //-------------------------------------------------------//

  if(m_bPoision_Soft_Active == false && m_bPoision_Hard_Active == false)
    {
    if(m_fPoision > 0.0f)m_fPoision -= 0.001f * (float)Temp_Engine->Timer.GetDeltaMs();
    }

  if(m_bPoision_Soft_Active == true && m_bPoision_Hard_Active == false)
    {
    m_fPoision += 0.001f * (float)Temp_Engine->Timer.GetDeltaMs();

    if(m_fPoision >= 3.0f)
      {
      m_bPoision_Soft_Active = false;
      m_bPoision_Hard_Active = false;
      }
    }

  if(m_bPoision_Hard_Active == true)
    {
    m_fPoision += 0.0005f * (float)Temp_Engine->Timer.GetDeltaMs();

    if(m_fPoision >= 4.0f)
      {
      m_bPoision_Soft_Active = false;
      m_bPoision_Hard_Active = false;
      }
    }

  //-------------------------------------------------------//
  //                  Shield Disseaper                     //
  //-------------------------------------------------------//

  if(m_fShield > 0.0)m_fShield -= 0.001f * (float)Temp_Engine->Timer.GetDeltaMs();

  //-------------------------------------------------------//
  //                 Plane On Fire/Smoke                   //
  //-------------------------------------------------------//

  if(m_cDamage > 0) // Not shield and NoDamage
    {
    int i;

    //----- PLANE_DAMAGE_SMOKE -----//
    for(i = 0;i < 100;i++)
      {
      if(m_fSmokeLife[i] > 0.0)
        {
        m_fSmokeLife[i]   -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.0005f;
        }
      }

    if(m_cDamage == PLANE_DAMAGE_SMOKE)
      {
      for(i = 0;i < 100;i++)
        {
        if(m_fSmokeLife[i] < 0.1)
          {
          m_fSmokeX[i] = m_fx + (((rand()%10)-5) * 0.01f);
          m_fSmokeY[i] = m_fy + (((rand()%10)-5) * 0.01f);
          m_fSmokeLife[i]   = 0.3f;
          break;
          }
        }
      }
    //----- PLANE_DAMAGE_FIRE -----//
    for(i = 0;i < 100;i++)
      {
      if(m_fFireLife[i] > 0.0)
        {
        m_fFireLife[i]   -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.005f;
        }
      }
    if(m_cDamage == PLANE_DAMAGE_FIRE)
      {
      for(i = 0;i < 100;i++)
        {
        if(m_fFireLife[i] < 0.1)
          {
          m_fFireX[i] = m_fx + (((rand()%10)-5) * 0.01f);
          m_fFireY[i] = m_fy + (((rand()%10)-5) * 0.01f);
          m_fFireLife[i]   = 1.5f;
          break;
          }
        }
      }
    }

  //-------------------------------------------------------//
  //    Stopping The Plane-Apparts in falling more Down    //
  //-------------------------------------------------------//

  if(m_cDamage == PLANE_DAMAGE_APART)
    {
    if((m_fy+(m_fxApartLenght-0.07f)) < -6.0f || m_bAppartDontFall == true)
      {
		if(m_bAppartDontFall == false && Temp_Engine->Server == true)
		{
			m_bAppartDontFall = true;
			GameHandler->Server_Network_StopAppart(ID,Temp_Engine);
		}
		return;
      }
    }

  if(m_bPilot == true && m_cDamage != PLANE_DAMAGE_CRASHED && m_cDamage != PLANE_DAMAGE_APART)
    {
    //-------------------------------------------------------//
    //                    UP-Key Speed                       //
    //-------------------------------------------------------//

	int i;
	bool bParaTrue = false;

	for(i = 0;i < 16;i++)
	{
		if(ID != -1 && GameHandler->Player[ID].m_iPlayerID != -1)
		{
			if(GameHandler->Man[i].m_cSplash == ID && GameHandler->Man[i].m_bSplashPara == true)
			{
				bParaTrue = true;
			}
		}
	}

	if(bParaTrue == true)
	{
      if(Up == true && m_fSpeed <= 0.60f){m_fSpeed += 0.00060f * (float)Temp_Engine->Timer.GetDeltaMs();}
 	}

    if(bParaTrue == false && m_cType <= 0)
      {
      if(m_cDamage == PLANE_DAMAGE_SHIELD && Up    == true && m_fSpeed <= 1.00f){m_fSpeed += 0.00070f * (float)Temp_Engine->Timer.GetDeltaMs();}
      if(m_cDamage == PLANE_DAMAGE_NONE   && Up    == true && m_fSpeed <= 1.00f){m_fSpeed += 0.00070f * (float)Temp_Engine->Timer.GetDeltaMs();}
      if(m_cDamage == PLANE_DAMAGE_SMOKE  && Up    == true && m_fSpeed <= 0.60f){m_fSpeed += 0.00070f * (float)Temp_Engine->Timer.GetDeltaMs();}
      }

    if(bParaTrue == false && m_cType > 0)
      {
      if(m_cDamage == PLANE_DAMAGE_SHIELD && Up    == true && m_fSpeed <= 1.50f){m_fSpeed += 0.00080f * (float)Temp_Engine->Timer.GetDeltaMs();}
      if(m_cDamage == PLANE_DAMAGE_NONE   && Up    == true && m_fSpeed <= 1.50f){m_fSpeed += 0.00080f * (float)Temp_Engine->Timer.GetDeltaMs();}
      if(m_cDamage == PLANE_DAMAGE_SMOKE  && Up    == true && m_fSpeed <= 0.80f){m_fSpeed += 0.00075f * (float)Temp_Engine->Timer.GetDeltaMs();}
      }
    //-------------------------------------------------------//
    //                LEFT/RIGHT-Key Turn                    //
    //-------------------------------------------------------//

	if(bParaTrue == true)
	{
      if(Left  == true)m_fRotate += 0.0004f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
      if(Right == true)m_fRotate -= 0.0004f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
	}

    if(bParaTrue == false && m_cType <= 2)
      {
      if(m_cDamage == PLANE_DAMAGE_SHIELD && Left  == true)m_fRotate +=  0.001f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
      if(m_cDamage == PLANE_DAMAGE_SHIELD && Right == true)m_fRotate -=  0.001f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();

      if(m_cDamage == PLANE_DAMAGE_NONE && Left  == true)m_fRotate +=  0.001f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
      if(m_cDamage == PLANE_DAMAGE_NONE && Right == true)m_fRotate -=  0.001f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();

      if(m_cDamage == PLANE_DAMAGE_SMOKE && Left  == true)m_fRotate += 0.0006f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
      if(m_cDamage == PLANE_DAMAGE_SMOKE && Right == true)m_fRotate -= 0.0006f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();

      if(m_cDamage == PLANE_DAMAGE_FIRE && Left  == true)m_fRotate +=  0.0003f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
      if(m_cDamage == PLANE_DAMAGE_FIRE && Right == true)m_fRotate -=  0.0003f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
      }
    if(bParaTrue == false && m_cType >  2)
      {
      if(m_cDamage == PLANE_DAMAGE_SHIELD && Left  == true)m_fRotate +=  0.0015f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
      if(m_cDamage == PLANE_DAMAGE_SHIELD && Right == true)m_fRotate -=  0.0015f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();

      if(m_cDamage == PLANE_DAMAGE_NONE && Left  == true)m_fRotate +=  0.0015f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
      if(m_cDamage == PLANE_DAMAGE_NONE && Right == true)m_fRotate -=  0.0015f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();

      if(m_cDamage == PLANE_DAMAGE_SMOKE && Left  == true)m_fRotate += 0.0009f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
      if(m_cDamage == PLANE_DAMAGE_SMOKE && Right == true)m_fRotate -= 0.0009f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();

      if(m_cDamage == PLANE_DAMAGE_FIRE && Left  == true)m_fRotate +=  0.00045f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
      if(m_cDamage == PLANE_DAMAGE_FIRE && Right == true)m_fRotate -=  0.00045f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
      }

    }

  //-------------------------------------------------------//
  //                    Moving Plane                       //
  //-------------------------------------------------------//

  m_fx -= m_fSpeed * (float)sin(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();
  m_fy += m_fSpeed * (float)cos(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();

  //-------------------------------------------------------//
  //          Plane Warp with X-Coordinate                 //
  //-------------------------------------------------------//

  if(m_fx >  8.31f){m_fx = -8.35f;}
  if(m_fx < -8.36f){m_fx =  8.30f;}

  //-------------------------------------------------------//
  //		       Players Plane Turn bettwen 0-360	     //
  //-------------------------------------------------------//

  if(m_fRotate <   0)m_fRotate = 360;
  if(m_fRotate > 360)m_fRotate =   0;

  //-------------------------------------------------------//
  //               Plane Crashed with the Ground           //
  //-------------------------------------------------------//

  if(m_cDamage == PLANE_DAMAGE_CRASHED)
    {
    int i;

    for(i = 0;i < 100;i++)
      {
      if(m_fSmokeLife[i] > 0.0)
        {
        m_fSmokeLife[i] -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.005f;
        m_fSmokeY[i]    += (float)Temp_Engine->Timer.GetDeltaMs() * 0.001f;
        }
      }

    m_fy = -6.0f;
    if(m_fSpeed > 0.0f)
      {
      m_fSpeed -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.002f;

      for(i = 0;i < 100;i++)
        {
        if(m_fSmokeLife[i] < 0.1)
          {
          m_fSmokeX[i]    = m_fx;
          m_fSmokeY[i]    = m_fy;
          m_fSmokeLife[i] = 1.0f;
          break;
          }
        }
      }
    if(m_fSpeed < 0.0f)m_fSpeed  = 0.0f;
    return;
    }

  //-------------------------------------------------------//
  //               Plane Aparts flying Away                //
  //-------------------------------------------------------//

  if(m_cDamage == PLANE_DAMAGE_APART)
    {
    m_fxApartLenght += 0.00070f * (float)Temp_Engine->Timer.GetDeltaMs();
    if(m_fSpeed <= 3.0f)m_fSpeed += (float)Temp_Engine->Timer.GetDeltaMs() * 0.0005f;
    if(m_fRotate < 150)m_fRotate += (float)Temp_Engine->Timer.GetDeltaMs() * 0.1f;
    if(m_fRotate > 210)m_fRotate -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.1f;
    return;
    }

  //-------------------------------------------------------//
  //		       Players Plane Stopping		     //
  //-------------------------------------------------------//

  if((m_fSpeed > 0.15f && m_fRotate < 150 || m_fRotate > 210))m_fSpeed -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.0005f;

  //-------------------------------------------------------//
  //		       Players Plane Force Turn		     //
  //-------------------------------------------------------//

  if(m_fSpeed < 0.35f)
    {
    if(m_fRotate < 180)m_fRotate += (float)Temp_Engine->Timer.GetDeltaMs() * 0.2f;
    if(m_fRotate > 180)m_fRotate -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.2f;
    }

  //-------------------------------------------------------//
  //		       Players Plane Speed-up down	     //
  //-------------------------------------------------------//

  if(m_fRotate > 140 && m_fRotate < 220){m_fSpeed += (float)Temp_Engine->Timer.GetDeltaMs() * 0.0012f;}

  //-------------------------------------------------------//
  //             Collision With Up Wall                    //
  //-------------------------------------------------------//

  if(m_bPilot == true && m_fTop_Punish < 1.5f && m_fy > 6.2)m_fTop_Punish += (float)Temp_Engine->Timer.GetDeltaMs() * 0.0015f;
  if(m_fTop_Punish > 0.0f)                                  m_fTop_Punish -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.0006f;

  if(m_fy > 6.8)
    {
	  if(m_bPilot == true){m_fTop_Punish = 1.5f;m_bPoision_Hard_Active = true;}
    m_fRotate = 180;
    m_fSpeed = 1.2f;
    }

  //-------------------------------------------------------//
  //            Collision With Down Wall                   //
  //-------------------------------------------------------//

  if(m_fy < -6.0f && Temp_Engine->Server == true && m_cDamage != PLANE_DAMAGE_CRASHED)
    {
    m_cDamage = PLANE_DAMAGE_CRASHED;
    FSOUND_PlaySound(FSOUND_FREE,Data->Snd_Plane_Crash);
    GameHandler->Add_ToStats(GameHandler->Find_Owner(ID),-1,5,Temp_Engine);
	GameHandler->Server_Network_PlaneHitGround(ID,Temp_Engine);
    }

  }

//------------------------------------------------------------------
void CPlane::SetType(char Type)
//------------------------------------------------------------------
{
  m_cType = Type;
  m_bAppartDontFall = false;


  
  if(m_cType >= 2)
  {
		m_cDamage = PLANE_DAMAGE_SHIELD;

  }
}










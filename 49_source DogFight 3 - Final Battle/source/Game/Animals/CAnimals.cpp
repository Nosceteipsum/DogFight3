////////////////////////////////////////////////////////////////////
//                                                                //
//               DF 3: Animal_CPP                                 //
//                                                                //
//         Made By: Tommy Kobberø Andersen                        //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "../../../global.h"

//------------------------------------------------------------------
CAnimal::CAnimal()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
CAnimal::~CAnimal()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
void CAnimal::Init()
//------------------------------------------------------------------
  {
  if(rand()%2 == 0)m_bActive = true;
  else             m_bActive = false;

  m_fMove = (rand()%100) * 0.1f;
  m_cType = rand()%4;
  m_fSize = 0.13f;
  if(m_cType == 3)m_fSize = 1.0f;
  if(m_cType == 4)m_fSize = 0.5f;

  m_bJumpUp = false;;
  m_fJump = 0.0f;

  m_bDead = false;
  m_bLeft = true;

  m_fMove = (rand()%300) * 0.01f;

  m_fX      = (-900.0f+(+(rand()%1800))) * 0.01f;
  m_fX_Dest = (-900.0f+(+(rand()%1800))) * 0.01f;
  }

//------------------------------------------------------------------
void CAnimal::Draw(SData *Data)
//------------------------------------------------------------------
  {
  if(m_bActive == false)return;

  glPushMatrix();

  glTranslatef(m_fX,-5.95f+(m_fJump*0.75f),-15.0f); 
  if(m_cType == 3)
  {
	  glTranslatef(0.0f,0.45f,0.0f); 
	  if( m_bLeft)glRotatef(-4.0f,0.0f,0.0f,1.0f);
	  if(!m_bLeft)glRotatef(+4.0f,0.0f,0.0f,1.0f);
  }

  if(m_cType == 0) // Sheep
    {
    if(m_bDead)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_SheepD.texID);
    else
      {
      if(m_bLeft)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_SheepL.texID);
      else       glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_SheepR.texID);
      }
    }
  if(m_cType == 1) // Lion
    {
    if(m_bDead)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_LionD.texID);
    else
      {
      if(m_bLeft)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_LionL.texID);
      else       glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_LionR.texID);
      }
    }
  if(m_cType == 2) // Cow
    {
    if(m_bDead)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_CowD.texID);
    else
      {
      if(m_bLeft)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_CowL.texID);
      else       glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_CowR.texID);
      }
    }
  if(m_cType == 3) // Elephant
    {
      if(m_bLeft)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_ElephantL.texID);
      else       glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_ElephantR.texID);
	}
  
  if(m_cType == 4) // Giraf
    {
	  //if(m_bLeft == true)glScalef(0.0f,0.0f,-1.0f);
	  int iTemp = (rand()%3);
      if(iTemp == 0)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_Giraf1R.texID);
      if(iTemp == 1)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_Giraf2R.texID);
      if(iTemp == 2)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_Giraf3R.texID);
	}
  
{
  if(m_fJump > 0.0f && m_bJumpUp == true) glRotatef(m_fJump  * 60.0f,0.0f,0.0f,1.0f);
  if(m_fJump > 0.0f && m_bJumpUp == false)glRotatef(m_fJump  * 60.0f,0.0f,0.0f,1.0f);
}
if(m_bLeft == true)
{
  if(m_fJump > 0.0f && m_bJumpUp == true) glRotatef(-(m_fJump  * 60.0f),0.0f,0.0f,1.0f);
  if(m_fJump > 0.0f && m_bJumpUp == false)glRotatef(-(m_fJump  * 60.0f),0.0f,0.0f,1.0f);
}
  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_fSize,-m_fSize,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+m_fSize,-m_fSize,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+m_fSize,+m_fSize,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_fSize,+m_fSize,-0.0f);	
  glEnd();
  glPopMatrix();

  }

//------------------------------------------------------------------
void CAnimal::Move(SData *Data,SEngine *Temp_Engine,CGameHandler *GameHandler)
//------------------------------------------------------------------
  {
  if(m_cType == 3 && m_bDead == true){m_bJumpUp = true;m_bDead = false;m_fMove = 0.0f;}

  if(m_bActive == false || m_bDead == true)return;

  //-------------------------------------------------------//
  //          Man Warp with X-Coordinate                 //
  //-------------------------------------------------------//

  if(m_fX >  8.21f){m_fX = -8.25f;}
  if(m_fX < -8.26f){m_fX =  8.20f;}

  //-------------------------------------------------------//
  //          Normal Animal Code                 //
  //-------------------------------------------------------//


  if(m_cType == 0) // Sheep
    {
    if(m_fX < m_fX_Dest){m_fX += 0.00005f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();m_bLeft = false;}
    if(m_fX > m_fX_Dest){m_fX -= 0.00005f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();m_bLeft = true;}
    }

  if(m_cType == 1) // Lion
    {
	if(m_fJump <= 0.0f)
	{
	  if(m_fX < m_fX_Dest){m_fX += 0.00015f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();m_bLeft = false;}
    if(m_fX > m_fX_Dest){m_fX -= 0.00015f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();m_bLeft = true;}
	}
	if(m_fJump > 0.0f)
	{
		if(m_bLeft == true)m_fX  -= 0.00005f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();
		if(m_bLeft == false)m_fX += 0.00005f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();
	}
    }

  if(m_cType == 2) // Cow
    {
    if(m_fX < m_fX_Dest){m_fX += 0.00001f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();m_bLeft = false;}
    if(m_fX > m_fX_Dest){m_fX -= 0.00001f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();m_bLeft = true;}
    }

  if(m_cType == 3) // Elephant
    {
    if(m_fX < m_fX_Dest){m_fX += 0.0001f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();m_bLeft = false;}
    if(m_fX > m_fX_Dest){m_fX -= 0.0001f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();m_bLeft = true;}
	}

  if(m_cType == 4) // Giraf
    {
    if(m_fX < m_fX_Dest){m_fX += 0.0001f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();m_bLeft = false;}
    if(m_fX > m_fX_Dest){m_fX -= 0.0001f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();m_bLeft = true;}
	}

  m_fMove -= 0.00001f * 16.0f *  (float)Temp_Engine->Timer.GetDeltaMs();

	if(m_bJumpUp == true)
	{
		m_fJump += (float)Temp_Engine->Timer.GetDeltaMs() * 0.001f;
		if(m_fJump >= 0.5f)m_bJumpUp = false;
	}

	if(m_fJump > 0.0f && m_bJumpUp == false)
	{
		m_fJump -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.001f;
	}
  
  if(m_fMove <= 0.0 && Temp_Engine->Server == true)
    {
    if(m_cType != 1)m_fMove = (rand()%300) * 0.01f;
    if(m_cType == 1)m_fMove = (rand()%70) * 0.01f;
    m_fX_Dest = (-1200.0f+(+(rand()%2400))) * 0.01f;

    if(m_cType == 0) // Sheep
      {
      char Rand_Sound = rand()%3;
      if(Rand_Sound == 0)FSOUND_PlaySound(FSOUND_FREE,Data->Snd_Animal_Sheep1);
      if(Rand_Sound == 1)FSOUND_PlaySound(FSOUND_FREE,Data->Snd_Animal_Sheep2);
      if(Rand_Sound == 2)FSOUND_PlaySound(FSOUND_FREE,Data->Snd_Animal_Sheep3);
      }

    if(m_cType == 1) // Tiger
      {
      char Prey = -1;
      Prey = Find_PreyMan(GameHandler);
      if(Prey != -1)
        {
			m_fX_Dest = GameHandler->Man[Prey].m_fx + (((rand()%100)-50)* 0.01f);

			m_bJumpUp = true;
			m_fJump = 0.0f;
	  
		}
	}

    if(m_cType == 2) // Cow
      {
      char Rand_Sound = rand()%3;
      if(Rand_Sound == 0)FSOUND_PlaySound(FSOUND_FREE,Data->Snd_Animal_Cow1);
      if(Rand_Sound == 1)FSOUND_PlaySound(FSOUND_FREE,Data->Snd_Animal_Cow2);
      if(Rand_Sound == 2)FSOUND_PlaySound(FSOUND_FREE,Data->Snd_Animal_Cow3);
      }
	GameHandler->Server_Network_Send(PACKET_SERVER_SYNCANIMAL,Temp_Engine);
	}
  }

//------------------------------------------------------------------
char CAnimal::Find_PreyMan(CGameHandler *GameHandler)
//------------------------------------------------------------------
  {
  char  Target_ID = -1;
  float Lenght = 100.0f;
  int i;

  float m_fx = m_fX;

  for(i = 0;i< 16;i++)
    {
    if(GameHandler->Plane[i].m_bPilot == false && GameHandler->Man[i].m_bActive == true && GameHandler->Man[i].m_cStatus != MAN_STATUS_DEAD)
      {
      if(((m_fx - GameHandler->Man[i].m_fx)) < Lenght)
        {
        Lenght    = fabs(((fabs(m_fx) - fabs(GameHandler->Man[i].m_fx))));
        Target_ID = i;
        }
      }
    }

  return Target_ID;
  }
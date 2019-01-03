////////////////////////////////////////////////////////////////////
//                                                                //
//               DF 3: Animal_CPP                                 //
//                                                                //
//         Made By: Tommy Kobberø Andersen                        //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "../../../global.h"

//------------------------------------------------------------------
CSeaGull::CSeaGull()
//------------------------------------------------------------------
{
    m_fFlyValue = 1.0f;
	m_fSize = 0.4f;
	m_cFlyState = 1;
	m_bDead = false;
    m_fRotate = 0.0f;
}

//------------------------------------------------------------------
CSeaGull::~CSeaGull()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
void CSeaGull::Init()
//------------------------------------------------------------------
  {
  for(int i=0;i < 200;i++)
    {
    m_bBlood[i] = false;
    }

  m_fSize = 0.25f;
  m_fFlyValue = 1.0f;
  m_cFlyState = 1;
  m_bDead = false;
  m_fRotate = 0.0f;
  m_fRotateBird = 0.0f;
  m_fSpeed = 1.0f;
  m_cWhoHittedMe = -1;

  m_fGullSliding = 0.0f;
  m_cType        = 1;
  m_bGullSplash  = false;
  m_bWake = false;
  m_bLeft = true;
  }

//------------------------------------------------------------------
void CSeaGull::Draw(SData *Data)
//------------------------------------------------------------------
  {
  if(m_bActive == false)return;

  glPushMatrix();

  glTranslatef(m_fX,m_fY,-15.0f); 

  if(m_bLeft == false)
  {
  if(m_cFlyState == 0)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_SeaGull1.texID);
  if(m_cFlyState == 1)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_SeaGull2.texID);
  }
  else
  {

  if(m_cFlyState == 0)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_SeaGull1L.texID);
  if(m_cFlyState == 1)glBindTexture(GL_TEXTURE_2D,Data->Tex_Animal_SeaGull2L.texID);
  }

  glRotatef(m_fRotateBird,0.0f,0.0f,1.0f);
  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_fSize,-m_fSize,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+m_fSize,-m_fSize,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+m_fSize,+m_fSize,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_fSize,+m_fSize,-0.0f);	
  glEnd();
  glPopMatrix();

  if(m_bDead == true)Draw_Blood(Data);
  }

//------------------------------------------------------------------
void CSeaGull::Draw_Blood(SData *Data)
//------------------------------------------------------------------
  {
  for(int i = 0;i < 200;i++)
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
void CSeaGull::Move(SData *Data,SEngine *Temp_Engine,CGameHandler *GameHandler,char ID)
//------------------------------------------------------------------
  {
  if(m_bActive == false || m_bWake == false)return;
  int i;

  //-------------------------------//
  //-------- Splash Handle --------//
  //-------------------------------//

	if(m_bGullSplash == true)
	{
		m_fX = GameHandler->Plane[m_cWhoHittedMe].m_fx;
		m_fY = GameHandler->Plane[m_cWhoHittedMe].m_fy;
		m_fRotate = GameHandler->Plane[m_cWhoHittedMe].m_fRotate;
		m_fSpeed = GameHandler->Plane[m_cWhoHittedMe].m_fSpeed;

		m_fGullSliding -= 0.75f * (float)Temp_Engine->Timer.GetDeltaMs() * 0.005f;

		if(GameHandler->Plane[m_cWhoHittedMe].m_bPilot == false || m_fGullSliding <= -15.0f)
		{
			//m_cWhoHittedMe = 0;
			m_bGullSplash = false;
		}
	}
  
  //-------------------------------------------------------//
  //		       Players Plane Speed-up down	     //
  //-------------------------------------------------------//

  if(m_fRotate > 140 && m_fRotate < 220){m_fSpeed += (float)Temp_Engine->Timer.GetDeltaMs() * 0.0005f;}

  //-------------------------------------------------------//
  //          Man Warp with X-Coordinate                 //
  //-------------------------------------------------------//

  if(m_fX >  8.21f){m_fX = -8.25f;}
  if(m_fX < -8.26f){m_fX =  8.20f;}

  //-------------------------------//
  //-------- Blood Handle ---------//
  //-------------------------------//

  if(m_bDead == true)
    {
	  if(m_fY >= -6.0f)
	  {
		if(m_bGullSplash == false)m_fRotateBird += (float)Temp_Engine->Timer.GetDeltaMs() * 0.4f;
		m_fX -= m_fSpeed * (float)sin(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();
		m_fY += m_fSpeed * (float)cos(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();

		  if(m_fRotate < 180.0f)m_fRotate += (float)Temp_Engine->Timer.GetDeltaMs() * 0.05f;
		  if(m_fRotate > 180.0f)m_fRotate -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.05f;
	  }

	for(i = 0;i < 200;i++)
	{
      if(m_bBlood[i] == false && (rand()%150) == 0)
        {
        m_fBloodX[i]    = m_fX;
        m_fBloodY[i]    = m_fY;
        m_bBlood[i]     = true;
        break;
        }
	  if(m_bBlood[i] == true && m_fBloodY[i] >= -6.0)
	  {
		m_fBloodY[i] -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.001f;
	  }
    }

  
	return;
  }

  //-------------------------------------------------------//
  //		       SeaGull Man Turn bettwen 0-360	     //
  //-------------------------------------------------------//

  if(m_fRotate <   0)m_fRotate = 360;
  if(m_fRotate > 360)m_fRotate =   0;
  if(m_fRotateBird <   0)m_fRotateBird = 360;
  if(m_fRotateBird > 360)m_fRotateBird =   0;

  //-------------------------------//
  //-------- Switch Image ---------//
  //-------------------------------//

	if(m_bWake == true)m_fFlyValue -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.0075f;

    if(m_fFlyValue <= 0.0f)
	{
		  m_fFlyValue = 1.0f;
		  if(m_cFlyState == 0)
			  m_cFlyState = 1;
		  else
			  m_cFlyState = 0;
	}

  //-------------------------------//
  //--------- Fly SeaGull ---------//
  //-------------------------------//

	if(m_bWake == true)
	{
		if(m_fX < m_fDX){m_fX += 0.000075f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();m_bLeft = false;}
		if(m_fX > m_fDX){m_fX -= 0.000075f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();m_bLeft = true;}
		if(m_fY < m_fDY){m_fY += 0.000075f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();}
		if(m_fY > m_fDY){m_fY -= 0.000075f * 16.0f * (float)Temp_Engine->Timer.GetDeltaMs();}

		if((Temp_Engine->Server == true && m_fX+0.5f > m_fDX && m_fX < m_fDX + 0.5f) || (m_fY < -4.0f))
		{
			if(m_fY+0.5f > m_fDY && m_fY < m_fDY + 0.5f || (m_fY < -4.0f))
			{
				m_fDX = (((rand()%1400)-700)*0.01f);
				m_fDY = (((rand()%1300)-500)*0.01f);
				m_bWake = true;

				GameHandler->Server_Network_SeaGullMove(ID,m_fDX,m_fDY,Temp_Engine);
			}

		}

	}




}
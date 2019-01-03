////////////////////////////////////////////////////////////////////
//                                                                //
//               DF 3: Missile_CPP                                //
//                                                                //
//         Made By: Tommy Kobberø Andersen                        //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "../../../global.h"

//------------------------------------------------------------------
CMissile::CMissile()
//------------------------------------------------------------------
{
	m_bPlasma = false;
}

//------------------------------------------------------------------
CMissile::~CMissile()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
void CMissile::Draw_Fuel(SData *Data)
//------------------------------------------------------------------
  {
  for(int i = 0;i < 50;i++)
    {
    if(m_fFuelSkyLife[i] <= 0.0f)continue;

    glPushMatrix();							
    glTranslatef(m_fFuelSkyX[i],m_fFuelSkyY[i],-15.0f);
    glColor4f(1.0f,1.0f,1.0f,m_fFuelSkyLife[i]);

    if(m_cType != 6)glBindTexture(GL_TEXTURE_2D,Data->Tex_Fire_Particle.texID);
    if(m_cType == 6)glBindTexture(GL_TEXTURE_2D,Data->Tex_Plasma_Particle.texID);

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
void CMissile::Draw(SData *Data)
//------------------------------------------------------------------
  {
  if(m_bDead == true || m_bUsed == false)return;

  Draw_Fuel(Data);

  glPushMatrix();							
  glTranslatef(m_fx,m_fy,-15.0f);

  if(m_bPlasma == false)glBindTexture(GL_TEXTURE_2D,Data->Tex_Missile_Particle.texID);
  if(m_bPlasma == true) glBindTexture(GL_TEXTURE_2D,Data->Tex_Plasma_Particle.texID);

  glRotatef(m_fRotate,0.0f,0.0f,1.0f);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-m_fSize,-m_fSize,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+m_fSize,-m_fSize,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+m_fSize,+m_fSize,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-m_fSize,+m_fSize,-0.0f);	
  glEnd();

  glPopMatrix();
  }

//------------------------------------------------------------------
void CMissile::Create(float x,float y,float Rotate,char Lock,CGameHandler *GameHandler,int ID)
//------------------------------------------------------------------
  {
  if(m_bUsed == true)return;

  m_bPlasma = false;

  m_fx      = x;
  m_fy      = y;
  m_fRotate = Rotate;

  GameHandler->Plane[ID].m_fSpeed *= 0.5f;

  if(m_cType != 6)m_fSize = 0.10f;
  if(m_cType == 6)m_fSize = 0.25f;

  if(m_cType == 1)m_fFuel =  3.0f;
  if(m_cType == 2)m_fFuel =  5.0f;
  if(m_cType == 3)m_fFuel =  7.0f;
  if(m_cType == 4)m_fFuel =  8.0f;
  if(m_cType == 5)m_fFuel = 10.0f;
  if(m_cType == 6)m_fFuel = 10.0f;

  if(m_cType == 1)m_fSpeed = 3.0f;
  if(m_cType == 2)m_fSpeed = 3.25f;
  if(m_cType == 3)m_fSpeed = 3.5f;
  if(m_cType == 4)m_fSpeed = 3.75f;
  if(m_cType == 5)m_fSpeed = 3.75f;
  if(m_cType == 6)m_fSpeed = 1.25f;

  m_cGuided_Lock = -1;

	if(m_cType >= 2)
	{
		//m_cGuided_Lock = Find_Prey(GameHandler,ID);
		m_cGuided_Lock = 1;
	}

  m_bUsed = true;
  m_bDead = false;

  m_fx -= 10.0f * (float)sin(0.017453 * m_fRotate) * 0.017f;
  m_fy += 10.0f * (float)cos(0.017453 * m_fRotate) * 0.017f;
  }

//------------------------------------------------------------------
void CMissile::Move(CGameHandler *GameHandler,SEngine *Temp_Engine,char ID)
//------------------------------------------------------------------
  {
  if(m_bDead == true || m_bUsed == false)return;


  //-------------------------------------------------------//
  //                   Plasma Handle                       //
  //-------------------------------------------------------//

  if(GameHandler->Player[ID].m_bKey_2 == true && m_bPlasma == false && m_cType == 6)
  {
	m_fSize   = 0.0f;
	m_bPlasma = true;
	m_fPlasmaLife = 10.0f;
  }

  if(m_bPlasma == true)
  {
		int i;
	  
		m_fSize += 0.0005f * (float)Temp_Engine->Timer.GetDeltaMs();

		for(i = 0;i < 16;i++)
		{
			if(GameHandler->Plane[i].m_bInGame == false || GameHandler->Plane[i].m_cDamage == PLANE_DAMAGE_APART || GameHandler->Plane[i].m_cDamage == PLANE_DAMAGE_CRASHED)continue;
/*
			if(GameHandler->Collision_Detect(GameHandler->Plane[i].m_fx,GameHandler->Plane[i].m_fy,GameHandler->Plane[i].m_fSize,GameHandler->Plane[i].m_fSize,m_fx,m_fy,3.0f,3.0f))
			{
				if(GameHandler->Plane[i].m_fx < m_fx)GameHandler->Plane[i].m_fx += 0.0275f;
				if(GameHandler->Plane[i].m_fx > m_fx)GameHandler->Plane[i].m_fx -= 0.0275f;
				if(GameHandler->Plane[i].m_fy < m_fy)GameHandler->Plane[i].m_fy += 0.0275f;
				if(GameHandler->Plane[i].m_fy > m_fy)GameHandler->Plane[i].m_fy -= 0.0275f;
			}
*/
			if(GameHandler->Plane[i].m_fSpeed > 1.0f)GameHandler->Plane[i].m_fSpeed = 1.0f;
		}
		for(i = 0;i < 16;i++)
		{
			if(GameHandler->Man[i].m_bActive == false)continue;

			if(GameHandler->Man[i].m_cStatus == MAN_STATUS_PARACHUTING)
			{
				GameHandler->Man[i].m_cStatus = MAN_STATUS_FLYING;
			}

			if(GameHandler->Man[i].m_cStatus == MAN_STATUS_GROUND)
			{
				GameHandler->Man[i].m_cStatus = MAN_STATUS_FLYING;
				GameHandler->Man[i].m_fy      = -5.75f;
			}

			if(GameHandler->Man[i].m_fx < m_fx)GameHandler->Man[i].m_fx += 0.0015f * (float)Temp_Engine->Timer.GetDeltaMs();
			if(GameHandler->Man[i].m_fx > m_fx)GameHandler->Man[i].m_fx -= 0.0015f * (float)Temp_Engine->Timer.GetDeltaMs();
			if(GameHandler->Man[i].m_fy < m_fy)GameHandler->Man[i].m_fy += 0.0020f * (float)Temp_Engine->Timer.GetDeltaMs();
			if(GameHandler->Man[i].m_fy > m_fy)GameHandler->Man[i].m_fy -= 0.0020f * (float)Temp_Engine->Timer.GetDeltaMs();

			GameHandler->Man[i].m_fManRotate += 1.0f;
			//GameHandler->Man[i].m_fRotate += 1.0f;
			
			if(GameHandler->Man[i].m_fSpeed > 1.0f)GameHandler->Man[i].m_fSpeed = 1.0f;
		}


		m_fRotate += (float)0.5f * (float)Temp_Engine->Timer.GetDeltaMs();
		m_fPlasmaLife -= (float)0.001f * (float)Temp_Engine->Timer.GetDeltaMs();

		if(m_fPlasmaLife <= 0.0f)
		{
			m_bPlasma = false;
			m_bDead   = true;
		}
		return;
  }

  //-------------------------------------------------------//
  //                 Moving Projectile                     //
  //-------------------------------------------------------//

  m_fx -= m_fSpeed * (float)sin(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();
  m_fy += m_fSpeed * (float)cos(0.017453 * m_fRotate) * 0.0017f * (float)Temp_Engine->Timer.GetDeltaMs();

  if(m_fRotate > 140 && m_fRotate < 220){m_fSpeed += (float)Temp_Engine->Timer.GetDeltaMs() * 0.0012f;}

  if(m_fFuel <= 0.0f)
    {
    if(m_fRotate < 180)m_fRotate += (float)Temp_Engine->Timer.GetDeltaMs() * 0.025f;
    if(m_fRotate > 180)m_fRotate -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.025f;
    }

  if(m_fFuel > 0.0f)
    {
    if(m_fSpeed < 3.0f && m_cType != 6)m_fSpeed += 0.001f * (float)Temp_Engine->Timer.GetDeltaMs();

    m_fFuel -= 0.001f * (float)Temp_Engine->Timer.GetDeltaMs();
    }

  ////////////////////////////////
  //----- Create Particles -----//
  ////////////////////////////////

  int i;

  for(i = 0;i < 50;i++)
    {
    if(m_fFuelSkyLife[i] > 0.0)
      {
      m_fFuelSkyLife[i]   -= (float)Temp_Engine->Timer.GetDeltaMs() * 0.001f;
      }
    }

  for(i = 0;i < 50;i++)
    {
    if(m_fFuel >= 0.0f && m_fFuelSkyLife[i] <= 0.0f)
      {
      m_fFuelSkyX[i]    = m_fx + (((rand()%10)-5) * 0.01f);
      m_fFuelSkyY[i]    = m_fy + (((rand()%10)-5) * 0.01f);
      m_fFuelSkyLife[i] = 0.3f;
      break;
      }
    }

  //-------------------------------------------------------//
  //                  Turn Projectile                     //
  //-------------------------------------------------------//

  if(m_cType > 0 && m_cGuided_Lock != -1 && m_fFuel > 0.0f)
    {
      if(GameHandler->Player[ID].m_bKey_1 == true)
	  {
		if(m_cType == 2)m_fRotate += 0.001f *  20.0f *(float)Temp_Engine->Timer.GetDeltaMs();
		if(m_cType == 3)m_fRotate += 0.001f *  25.0f *(float)Temp_Engine->Timer.GetDeltaMs();
		if(m_cType == 4)m_fRotate += 0.001f *  35.0f *(float)Temp_Engine->Timer.GetDeltaMs();
		if(m_cType == 5)m_fRotate += 0.001f *  40.0f *(float)Temp_Engine->Timer.GetDeltaMs();
		if(m_cType == 6)m_fRotate += 0.001f *  30.0f *(float)Temp_Engine->Timer.GetDeltaMs();
	  }
      if(GameHandler->Player[ID].m_bKey_3 == true)
	  {
		if(m_cType == 2)m_fRotate -= 0.001f *  20.0f *(float)Temp_Engine->Timer.GetDeltaMs();
		if(m_cType == 3)m_fRotate -= 0.001f *  25.0f *(float)Temp_Engine->Timer.GetDeltaMs();
		if(m_cType == 4)m_fRotate -= 0.001f *  35.0f *(float)Temp_Engine->Timer.GetDeltaMs();
		if(m_cType == 5)m_fRotate -= 0.001f *  40.0f *(float)Temp_Engine->Timer.GetDeltaMs();
		if(m_cType == 6)m_fRotate -= 0.001f *  30.0f *(float)Temp_Engine->Timer.GetDeltaMs();
	  }
/*
    float m_fAimx;
    float m_fAimy;
    float Rotate_Cosinus;

    /////////////////////////////////////////////
    //----- Finder afstanden til objectet -----//
    /////////////////////////////////////////////

	if(m_fx < GameHandler->Plane[m_cGuided_Lock].m_fx)
	{
	    m_fAimx = m_fx - GameHandler->Plane[m_cGuided_Lock].m_fx;
	}
	else
	{
	    m_fAimx =  GameHandler->Plane[m_cGuided_Lock].m_fx - m_fx;
	}

	if(m_fy < GameHandler->Plane[m_cGuided_Lock].m_fy)
	{
	    m_fAimy = m_fy - GameHandler->Plane[m_cGuided_Lock].m_fy;
	}
	else
	{
	    m_fAimy =  GameHandler->Plane[m_cGuided_Lock].m_fy - m_fy;
	}

    ////////////////////////////////////////////////////////////////
    //----- Finder afstanden På hyponessen, den aflange side -----//
    ////////////////////////////////////////////////////////////////

	Rotate_Cosinus = atan(m_fAimy/m_fAimx) * (180.0f/3.14159265);
//    Hypo           = sqrt(((Temp_x*Temp_x)+(Temp_y*Temp_y)));

    ////////////////////////////////////////////////////////////////
    //-----    Udregner Rotationen for at følge hyponessen   -----//
    ////////////////////////////////////////////////////////////////

//    Rotate_Cosinus = (((acos ((Temp_y / Hypo))))* 57.0f);

  //  if(Rotate_Cosinus > 360.0f)Rotate_Cosinus -= 360.0f;
   // if(Rotate_Cosinus <   0.0f)Rotate_Cosinus += 360.0f;
   // if(Rotate_Cosinus > 360.0f)Rotate_Cosinus -= 360.0f;
  //  if(Rotate_Cosinus <   0.0f)Rotate_Cosinus += 360.0f;
  //  if(m_fRotate > 360.0f)m_fRotate -= 360.0f;
 //   if(m_fRotate <   0.0f)m_fRotate += 360.0f;
 //   if(m_fRotate > 360.0f)m_fRotate -= 360.0f;
 //   if(m_fRotate <   0.0f)m_fRotate += 360.0f;


//	if(m_fRotate <= Rotate_Cosinus)m_fRotate -= 0.001f * 150.0f *(float)Temp_Engine->Timer.GetDeltaMs();
//	if(m_fRotate >= Rotate_Cosinus)m_fRotate += 0.001f * 150.0f *(float)Temp_Engine->Timer.GetDeltaMs();

// 45   = 7
// 135  = 1
// 225  = 3
// 315  = 9

	m_fRotate = Rotate_Cosinus ;

    ////////////////////////////////////////////////////////////////
    //-----       Finder hvilke vej Rotation Skal sigte      -----//
    ////////////////////////////////////////////////////////////////

//    if(m_fx >  GameHandler->Plane[m_cGuided_Lock].m_fx && m_fy >  GameHandler->Plane[m_cGuided_Lock].m_fy){Rotate_Cosinus = 180.0f-Rotate_Cosinus;}
//    if(m_fx >  GameHandler->Plane[m_cGuided_Lock].m_fx && m_fy <= GameHandler->Plane[m_cGuided_Lock].m_fy){} // Højre-Bund

//    if(m_fx <= GameHandler->Plane[m_cGuided_Lock].m_fx && m_fy >  GameHandler->Plane[m_cGuided_Lock].m_fy){Rotate_Cosinus = 180.0f+Rotate_Cosinus;} // Venstre-Top
//    if(m_fx <= GameHandler->Plane[m_cGuided_Lock].m_fx && m_fy <= GameHandler->Plane[m_cGuided_Lock].m_fy){Rotate_Cosinus = 180.0f+Rotate_Cosinus;Rotate_Cosinus = 180.0f-Rotate_Cosinus;} // Venstre-Bund

//    if(Rotate_Cosinus > 360.0)Rotate_Cosinus -= 360.0f;
//    if(Rotate_Cosinus <   0.0)Rotate_Cosinus += 360.0f;

    ////////////////////////////////////////////////////////////////
    //-----       Finder hvilke vej Missilen skal dreje      -----//
    ////////////////////////////////////////////////////////////////


    float Right = m_fRotate,Left = m_fRotate,Long = 0.0f;

    while(Long < 360.0f)
      {
      if(Rotate_Cosinus <= Right+1.0f && Rotate_Cosinus >= Right-1.0f)
        {
        if(m_cType == 2)m_fRotate += 0.001f *  30.0f *(float)Temp_Engine->Timer.GetDeltaMs();
        if(m_cType == 3)m_fRotate += 0.001f *  60.0f *(float)Temp_Engine->Timer.GetDeltaMs();
        if(m_cType >= 4)m_fRotate += 0.001f * 150.0f *(float)Temp_Engine->Timer.GetDeltaMs();

        break;
        }
      if(Rotate_Cosinus <= Left+1.0f && Rotate_Cosinus >= Left-1.0f)
        {
        if(m_cType == 2)m_fRotate -= 0.001f *  30.0f *(float)Temp_Engine->Timer.GetDeltaMs();
        if(m_cType == 3)m_fRotate -= 0.001f *  60.0f *(float)Temp_Engine->Timer.GetDeltaMs();
        if(m_cType >= 4)m_fRotate -= 0.001f * 150.0f *(float)Temp_Engine->Timer.GetDeltaMs();

        break;
        }

      Right += 1.0f;
      Left  -= 1.0f;
      Long  += 1.0f;

      if(Right > 360.0)Right -= 360.0f;
      if(Right <   0.0)Right += 360.0f;
      if(Left > 360.0 )Left  -= 360.0f;
      if(Left <   0.0) Left  += 360.0f;
      }
*/
   }

  //-------------------------------------------------------//
  //                 CHECKING COLLISION                    //
  //-------------------------------------------------------//

  //--------------- Collision Right/Left ------------------//

  if(m_fx >  8.31f){m_fx = -8.35f;}
  if(m_fx < -8.36f){m_fx =  8.30f;}

  //--------------- Collision Top        ------------------//

  if(m_fy > 6.3   ){m_bDead = true;}

  //--------------- Collision Down       ------------------//

  if(m_fy < -6.0f ){m_bDead = true;}
  }

//------------------------------------------------------------------
void CMissile::SetType(char Type)
//------------------------------------------------------------------
{
	m_cType = Type;

}

//------------------------------------------------------------------
char CMissile::Find_Prey(CGameHandler *GameHandler,int ID)
//------------------------------------------------------------------
  {
  char  Target_ID = -1;
  float Lenght = 100.0f;
  int i;
  float m_fx = GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID].m_fx;
  float m_fy = GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID].m_fy;

  if((GameHandler->Player[ID].m_iPlayerID % 2) == 0) // Green
    {
    for(i=1;i< 16;i+=2)
      {
      if(GameHandler->Plane[i].m_bOcupied == true && GameHandler->Plane[i].m_bInGame == true && GameHandler->Plane[i].m_bPilot == true)
        {
        if(((m_fx - GameHandler->Plane[i].m_fx) + (m_fy - GameHandler->Plane[i].m_fy)) < Lenght)
          {
          Lenght    = fabs(((fabs(m_fx) - fabs(GameHandler->Plane[i].m_fx)) + (fabs(m_fy) - fabs(GameHandler->Plane[i].m_fy))));
          Target_ID = i;
          }
        }
      }
    }

  if((GameHandler->Player[ID].m_iPlayerID % 2) == 1) // Red
    {
    for(i=0;i< 16;i+=2)
      {
      if(GameHandler->Plane[i].m_bOcupied == true && GameHandler->Plane[i].m_bInGame == true && GameHandler->Plane[i].m_bPilot == true)
        {
        if((fabs(((fabs(m_fx) - fabs(GameHandler->Plane[i].m_fx)) + (fabs(m_fy) - fabs(GameHandler->Plane[i].m_fy))))) < Lenght)
          {
          Lenght    = fabs(((fabs(m_fx) - fabs(GameHandler->Plane[i].m_fx)) + (fabs(m_fy) - fabs(GameHandler->Plane[i].m_fy))));
          Target_ID = i;
          }
        }
      }
    }

  return Target_ID;
  }
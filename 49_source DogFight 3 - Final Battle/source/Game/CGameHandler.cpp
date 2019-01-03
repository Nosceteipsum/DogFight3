////////////////////////////////////////////////////////////////////
//								  //
//	  	  DF 3: CGameHandler_h			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "../../global.h"

#include <assert.h>

#define MONEY_PER_HIT     100

#define PARA_PRICE       100
#define PARA_PRICE_TEXT "100"
#define PARA_STEALH_PRICE 1000
#define PARA_STEALH_TEXT "1000"

#define PARA2_PRICE       300
#define PARA2_PRICE_TEXT "300"
#define PARA3_PRICE       500
#define PARA3_PRICE_TEXT "500"

#define PLANE_SHIELD_PRICE       1000
#define PLANE_SHIELD_PRICE_TEXT "1000"

#define PLANE_MISSILE_LEVEL1       300
#define PLANE_MISSILE_LEVEL1_TEXT "300"
#define PLANE_MISSILE_LEVEL2       500
#define PLANE_MISSILE_LEVEL2_TEXT "500"
#define PLANE_MISSILE_LEVEL3       500
#define PLANE_MISSILE_LEVEL3_TEXT "500"
#define PLANE_MISSILE_LEVEL4       750
#define PLANE_MISSILE_LEVEL4_TEXT "750"
#define PLANE_MISSILE_LEVEL5       1000
#define PLANE_MISSILE_LEVEL5_TEXT "1000"
#define PLANE_MISSILE_LEVEL6       1500
#define PLANE_MISSILE_LEVEL6_TEXT "1500"

#define SHOT_LEVEL1       500
#define SHOT_LEVEL1_TEXT "500"
#define SHOT_LEVEL2       1000
#define SHOT_LEVEL2_TEXT "1000"
#define SHOT_LEVEL3       1000
#define SHOT_LEVEL3_TEXT "1000"
#define SHOT_LEVEL4       2500
#define SHOT_LEVEL4_TEXT "2500"

//------------------------------------------------------------------
CGameHandler::CGameHandler()
//------------------------------------------------------------------
  {
  m_bCOLLISION_Show  = false;
  m_bFPS_Show        = false;
  m_fFPS_Second      = 1.0f;
  m_iFPS_Frames      = 0;
  m_iFPS_Temp_Frames = 0;
  m_fGlobalDataPacket = 0.0f;
  m_bWaitingOnReset   = true;
  m_bBailActivate     = false;
  m_cManHit			  = -1;
  }

//------------------------------------------------------------------
CGameHandler::~CGameHandler()
//------------------------------------------------------------------
  {

  }

//------------------------------------------------------------------
bool CGameHandler::Main_Handle(SEngine *Engine) // Draw All Graphics, Handle Every Update/Moves...
//------------------------------------------------------------------
  {
  bool Status_Exit = false;

  if(Engine->Key.Key_Down(VK_ESCAPE) == true){return true;}

	if(m_iNetWorkID == -1)
	{
		if(Engine->Server == false)
		{
			if(m_bBailActivate == false)glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			else						glClear(GL_COLOR_BUFFER_BIT);
			glLoadIdentity();
			gluLookAt(0.0f,0.0f,0.0f,	
					  0.0f,0.0f,-100.0f,
					  0.0f,1.0f,0.0f);

			glColor3f(1.0f,1.0f,1.0f);
			if(m_bBailActivate == false)glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
			else						glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

			Engine->OpenGl_Font.glPrint(200,200,"Trying to connect... ",0);

			Status_Exit = Client_Handle(Engine);

			//-------- Switch Buffer --------//
			Engine->OpenGl_Window.SwapBuffers_hdc();

			return Status_Exit;
		}
	}

	if(m_bSelectingTeam == false && (Player[m_iNetWorkID].m_iPlayerID < 0 || Player[m_iNetWorkID].m_iPlayerID > 15))
		assert(false);

  if(m_bWaitingOnReset == true && Engine->Server == false && m_bSelectingTeam == false)
  {
		if(m_bBailActivate == false)glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		else						glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(0.0f,0.0f,0.0f,	
					  0.0f,0.0f,-100.0f,
					  0.0f,1.0f,0.0f);

		glColor3f(1.0f,1.0f,1.0f);
		if(m_bBailActivate == false)glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
		else						glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		Engine->OpenGl_Font.glPrint(200,200,"Waiting for next round... ",0);

		Status_Exit = Client_Handle(Engine);

		//-------- Switch Buffer --------//
		Engine->OpenGl_Window.SwapBuffers_hdc();

		return Status_Exit;
  }


  int ID = Player[m_iNetWorkID].m_iPlayerID;

  Engine->Timer.Run();


  if(Engine->Key.Key_Down(VK_F1) == true){m_bFPS_Show = true;}
  if(Engine->Key.Key_Down(VK_F2) == true){m_bFPS_Show = false;}
//  if(Engine->Key.Key_Down(VK_F3) == true){m_bCOLLISION_Show = true;}
//  if(Engine->Key.Key_Down(VK_F4) == true){m_bCOLLISION_Show = false;}
/*
  if(Engine->Key.Key_Down(VK_F5) == false &&
     Engine->Key.Key_Down(VK_F6) == false &&
     Engine->Key.Key_Down(VK_F7) == false &&
     Engine->Key.Key_Down(VK_F8) == false   )m_bAI_KeyPress = false;
                                         
  if(Engine->Key.Key_Down(VK_F5) == true && m_bAI_KeyPress == false){Add_AI(true ,false,true); m_bAI_KeyPress = true;} // green,red,add
  if(Engine->Key.Key_Down(VK_F6) == true && m_bAI_KeyPress == false){Add_AI(true ,false,false);m_bAI_KeyPress = true;}
  if(Engine->Key.Key_Down(VK_F7) == true && m_bAI_KeyPress == false){Add_AI(false,true ,true); m_bAI_KeyPress = true;}
  if(Engine->Key.Key_Down(VK_F8) == true && m_bAI_KeyPress == false){Add_AI(false,true ,false);m_bAI_KeyPress = true;}
*/
  //--------------------------------//
  //--- Handling Network Engine ---//
  //--------------------------------//

  if(Engine->Server == true) Server_Handle(Engine);
  if(Engine->Server == false)Status_Exit = Client_Handle(Engine);

  //--------------------------------//
  //---      Handling Game       ---//
  //--------------------------------//

  m_dTime       += Engine->Timer.GetDeltaMs();
  m_fFPS_Second -= 0.001f * (float)Engine->Timer.GetDeltaMs();

  //--------------------------------//
  //---       Update Game        ---//
  //--------------------------------//

  Main_Handle_Update(Engine);    

  if(m_bSelectingTeam == true && Engine->Server == true)
    {
    if(Player[m_iNetWorkID].m_bKey_Left  == true){Player[m_iNetWorkID].m_iPlayerID = Join_Team(true,false);m_bSelectingTeam = false;}
    if(Player[m_iNetWorkID].m_bKey_Right == true){Player[m_iNetWorkID].m_iPlayerID = Join_Team(false,true);m_bSelectingTeam = false;}

    if(Player[m_iNetWorkID].m_iPlayerID == -1)m_bSelectingTeam = true; // Team Full
	else if(GAME_STATE_PREPARE == m_cGameState || GAME_STATE_BUYMENU == m_cGameState)
	{
      m_fBuyMenuTimer = (float)Engine->m_sSettings.BuyTime;
      m_cGameState    = GAME_STATE_BUYMENU;
      GameReset(Engine);
      Server_Network_Send(PACKET_SERVER_DATARESET,Engine);
	}
    ID = Player[m_iNetWorkID].m_iPlayerID;
    }

  //--------------------------------//
  //---        Draw Game         ---//
  //--------------------------------//

  if(m_dTime > (1000.0 / (double)m_iFPS))
    {
    Engine->Timer.DTick = m_dTime;
    m_dTime             = 0.0;

    //--------------------------------//
    //---      Prepare graphic     ---//
    //--------------------------------//

    //----- Clear Screen -----//

    if(m_bBailActivate == false)glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	else						glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f,0.0f,0.0f,	
              0.0f,0.0f,-100.0f,
              0.0f,1.0f,0.0f);

    //----- Drawing Status -----//

    if(m_bFPS_Show     == true)DrawFPS(Engine);

    //--------------------------------//
    //---     Selective Team       ---//
    //--------------------------------//

    if(m_bSelectingTeam == true)
      {
      glColor3f(1.0f,1.0f,1.0f);
      if(m_bBailActivate == false)glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
	  else						  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      // Skriv alle navne og vis flyene ved siden af static!

      Draw_Names(Engine);
      Draw_TeamSelect();
      }
    else
      {
      Main_Handle_Graphics(Engine);    
      }

    //-------- Switch Buffer --------//
    Engine->OpenGl_Window.SwapBuffers_hdc();


    } // Frame-Limiter End
  //--- Don't make anything after this linie, which are using timer!!!

  return Status_Exit;
  }

//------------------------------------------------------------------
void CGameHandler::Main_Handle_Graphics(SEngine *Engine)
//------------------------------------------------------------------
  {
  int i;
  int ID = Player[m_iNetWorkID].m_iPlayerID;

  switch(m_cGameState)
    {
    //---------------------------------------------------------------------
    case GAME_STATE_BUYMENU:
    //---------------------------------------------------------------------
      {
      BuyMenu_Draw(Engine);
      Animal[0].Draw(&m_sData);Animal[1].Draw(&m_sData);

      Map.Draw_Tree(&m_sData);
      Map.Draw(&m_sData);

      SeaGull[0].Draw(&m_sData);SeaGull[1].Draw(&m_sData);SeaGull[2].Draw(&m_sData);
      SeaGull[3].Draw(&m_sData);SeaGull[4].Draw(&m_sData);SeaGull[5].Draw(&m_sData);
      SeaGull[6].Draw(&m_sData);SeaGull[7].Draw(&m_sData);SeaGull[8].Draw(&m_sData);
      
	  }
    break;

    //---------------------------------------------------------------------
    case GAME_STATE_PREPARE:
    //---------------------------------------------------------------------
      {
      for(i=0;i < 16;i++)
        {
        if(m_bSelectingTeam == false && ID != -1)
          {
          Plane[i].Draw(&m_sData,(i == Player[m_iNetWorkID].m_iPlayerID));
          }
        }
      Draw_GameScore(Engine);
      Draw_Names(Engine);

      Animal[0].Draw(&m_sData);Animal[1].Draw(&m_sData);

      Map.Draw_Tree(&m_sData);
      Map.Draw(&m_sData);

      SeaGull[0].Draw(&m_sData);SeaGull[1].Draw(&m_sData);SeaGull[2].Draw(&m_sData);
      SeaGull[3].Draw(&m_sData);SeaGull[4].Draw(&m_sData);SeaGull[5].Draw(&m_sData);
      SeaGull[6].Draw(&m_sData);SeaGull[7].Draw(&m_sData);SeaGull[8].Draw(&m_sData);

	  }
    break;

    //---------------------------------------------------------------------
    case GAME_STATE_GAMING:
    //---------------------------------------------------------------------
      {
      //--------------------------------//
      //------  Draw Every Things  -----//
      //--------------------------------//
      if(m_bSelectingTeam == false && ID != -1)
        {
        gluLookAt(0.0f,0.0f,0.0f-Plane[ID].m_fPoision,	
                  0.0f,0.0f,-100.0f,
                  0.0f+Plane[ID].m_fPoision,1.0f,0.0f);

		if(Plane[ID].m_bPoision_Hard_Active == true && Plane[ID].m_bPilot == true)glTranslatef(rand()%10 * 0.1f,rand()%10 * 0.1f,0.0f);

        if(m_bBailActivate == false)glClearColor(0.0f, 0.0f, 0.3f-(Plane[ID].m_fTop_Punish * 0.3f), 0.0f);
		else						glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glColor3f(1.0f-(Plane[ID].m_fTop_Punish * 1.0f),1.0f-(Plane[ID].m_fTop_Punish * 1.0f),1.0f-(Plane[ID].m_fTop_Punish * 1.0f));

		Draw_KillBox(Engine);

        for(i=0;i < 16;i++)
          {
//			if(Missile[i].m_bPlasma == true)glTranslatef(rand()%2 * 0.1f,rand()%2 * 0.1f,0.0f);

          Man[i].Draw(&m_sData,(i == Player[m_iNetWorkID].m_iPlayerID));
          Plane[i].Draw(&m_sData,(i == Player[m_iNetWorkID].m_iPlayerID));
          Fire[i].Draw(&m_sData,(i == Player[m_iNetWorkID].m_iPlayerID));
          Spec[i].Draw(&m_sData);
          Missile[i].Draw(&m_sData);
          }
        Animal[0].Draw(&m_sData);Animal[1].Draw(&m_sData);

        Map.Draw_Tree(&m_sData);
        Map.Draw(&m_sData);

        SeaGull[0].Draw(&m_sData);SeaGull[1].Draw(&m_sData);SeaGull[2].Draw(&m_sData);
        SeaGull[3].Draw(&m_sData);SeaGull[4].Draw(&m_sData);SeaGull[5].Draw(&m_sData);
        SeaGull[6].Draw(&m_sData);SeaGull[7].Draw(&m_sData);SeaGull[8].Draw(&m_sData);

        Sky[0].Draw(&m_sData);Sky[1].Draw(&m_sData);Sky[2].Draw(&m_sData);

        Collision_Handle_Draw(Engine);
        Draw_Score(Engine);

		if(m_cManHit != -1)
		{
			if(m_iNetWorkID != -1)
			{
				if(Plane[Player[m_iNetWorkID].m_iPlayerID].m_bInGame == true && Plane[Player[m_iNetWorkID].m_iPlayerID].m_bPilot == true)
				{

			glPushMatrix();							
			glTranslatef(0.0f,Man[m_cManHit].m_fManSlidingOf,-15.0f);

			if((m_cManHit % 2) == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_Red_Man.texID);
			if((m_cManHit % 2) == 0)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_Green_Man.texID);
			glBegin(GL_QUADS);						
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-7.0f,-7.0f,+0.0f);	
			glTexCoord2f(1.0f, 0.0f); glVertex3f(+7.0f,-7.0f,+0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(+7.0f,+7.0f,-0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-7.0f,+7.0f,-0.0f);	
			glEnd();

			Engine->OpenGl_Font.glPrint(270,230+(int)((float)(Man[m_cManHit].m_fManSlidingOf*38.0f)),Player[Find_Owner(m_cManHit)].m_caName,1);

			glPopMatrix();
				}
			}
		}

		if(m_iNetWorkID != -1)
		{
			for(i = 0;i < 9;i++){
			if(SeaGull[i].m_bGullSplash == true && SeaGull[i].m_bActive == true && SeaGull[i].m_cWhoHittedMe == Player[m_iNetWorkID].m_iPlayerID && Plane[Player[m_iNetWorkID].m_iPlayerID].m_bInGame == true && Plane[Player[m_iNetWorkID].m_iPlayerID].m_bPilot == true)
			{
				glPushMatrix();							
				glTranslatef(-1.0f,SeaGull[i].m_fGullSliding,-15.0f);

				if(SeaGull[i].m_cType == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_Animal_GullSplash1.texID);
				if(SeaGull[i].m_cType == 2)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_Animal_GullSplash2.texID);
				glBegin(GL_QUADS);						
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-13.0f,-13.0f,+0.0f);	
				glTexCoord2f(1.0f, 0.0f); glVertex3f(+13.0f,-13.0f,+0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(+13.0f,+13.0f,-0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-13.0f,+13.0f,-0.0f);	
				glEnd();

				glPopMatrix();
			}
			}
			}
		}
      }
    break;
    //---------------------------------------------------------------------
    case GAME_STATE_GAMEOVER:
    //---------------------------------------------------------------------
      {
      for(i=0;i < 16;i++)
        {
        Man[i].Draw(&m_sData,(i == Player[m_iNetWorkID].m_iPlayerID));
        Plane[i].Draw(&m_sData,(i == Player[m_iNetWorkID].m_iPlayerID));
        Fire[i].Draw(&m_sData,true);
        Spec[i].Draw(&m_sData);
        Missile[i].Draw(&m_sData);
        }
      Animal[0].Draw(&m_sData);Animal[1].Draw(&m_sData);

      Map.Draw_Tree(&m_sData);
      Map.Draw(&m_sData);

      Draw_KillBox(Engine);

      SeaGull[0].Draw(&m_sData);SeaGull[1].Draw(&m_sData);SeaGull[2].Draw(&m_sData);
      SeaGull[3].Draw(&m_sData);SeaGull[4].Draw(&m_sData);SeaGull[5].Draw(&m_sData);
      SeaGull[6].Draw(&m_sData);SeaGull[7].Draw(&m_sData);SeaGull[8].Draw(&m_sData);

      Sky[0].Draw(&m_sData);Sky[1].Draw(&m_sData);Sky[2].Draw(&m_sData);

      Draw_Score(Engine);

	  if(m_bGreenWin == false){glColor3f(1.0f,0.0f,0.0f);Engine->OpenGl_Font.glPrint(250,200,"Red Team Win!!!",1);}
      else                    {glColor3f(0.0f,1.0f,0.0f);Engine->OpenGl_Font.glPrint(250,200,"Green Team Win!!!",1);}
	  glColor3f(1.0f,1.0f,1.0f);

		if(m_cManHit != -1)
		{
			if(m_iNetWorkID != -1)
			{
				if(Plane[Player[m_iNetWorkID].m_iPlayerID].m_bInGame == true && Plane[Player[m_iNetWorkID].m_iPlayerID].m_bPilot == true)
				{

			glPushMatrix();							
			glTranslatef(0.0f,Man[m_cManHit].m_fManSlidingOf,-15.0f);

			if((m_cManHit % 2) == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_Red_Man.texID);
			if((m_cManHit % 2) == 0)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_Green_Man.texID);
			glBegin(GL_QUADS);						
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-7.0f,-7.0f,+0.0f);	
			glTexCoord2f(1.0f, 0.0f); glVertex3f(+7.0f,-7.0f,+0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(+7.0f,+7.0f,-0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-7.0f,+7.0f,-0.0f);	
			glEnd();
	
			Engine->OpenGl_Font.glPrint(270,230+(int)((float)(Man[m_cManHit].m_fManSlidingOf*38.0f)),Player[Find_Owner(m_cManHit)].m_caName,1);

			glPopMatrix();
				}
			}
		}

	  
	  }
    break;
    }
  }

//------------------------------------------------------------------
void CGameHandler::Main_Handle_Update(SEngine *Engine)
//------------------------------------------------------------------
  {
  int i;
  int ID = Player[m_iNetWorkID].m_iPlayerID;

  switch(m_cGameState)
    {
    //---------------------------------------------------------------------
    case GAME_STATE_BUYMENU:
    //---------------------------------------------------------------------
      {
      for(i=0;i < 16;i++)
        {
        //----- Update Thing which requirer Player controls -----//
/*
		  if(Player[i].m_bActive == true && Player[i].m_iPlayerID != -1)
          {
          if(Player[i].m_bAI == true)Bot.Handle(this,i);
          }
*/
		}

      BuyMenu_Handle(Engine);
      }
    break;

    //---------------------------------------------------------------------
    case GAME_STATE_PREPARE:
    //---------------------------------------------------------------------
      {
      Handle_Prepare(Engine);
      }
    break;

    //---------------------------------------------------------------------
    case GAME_STATE_GAMING:
    //---------------------------------------------------------------------
      {
      //--------------------------------//
      //------ Update Every Things -----//
      //--------------------------------//

      for(i=0;i < 16;i++)
        {
        //----- Update Thing which requirer Player controls -----//
        if(Player[i].m_bActive == true && Player[i].m_iPlayerID != -1)
          {
//          if(Player[i].m_bAI == true)Bot.Handle(this,i);

          Plane[Player[i].m_iPlayerID].Move(&m_sData,this,Engine,Player[i].m_bKey_Speed,Player[i].m_bKey_Left, Player[i].m_bKey_Right,Player[i].m_iPlayerID,i);
          Man[  Player[i].m_iPlayerID].Move(this,Engine,Player[i].m_bKey_Left, Player[i].m_bKey_Right,Player[i].m_bKey_Speed,Player[i].m_bKey_Down,Player[i].m_iPlayerID);




			//////////////////////////////////////
			//-------- Collision with Sky ------//
			 //////////////////////////////////////
			 for(int ii = 0;ii <  3;ii++)
			  {
			  if(Sky[ii].m_bActive == false || Sky[ii].m_bConfuse == false || Plane[i].m_bPilot == false)continue;

			  if(Collision_Detect(Plane[i].m_fx,Plane[i].m_fy,Plane[i].m_fSize,Plane[i].m_fSize,Sky[ii].m_fX,Sky[ii].m_fY,Sky[ii].m_fSize,Sky[ii].m_fSize))
			   {
			   Plane[i].m_fTop_Punish += (float)Engine->Timer.GetDeltaMs() * 0.0010f;
			  }
		 }

		}
        Fire[i].Move(this,Engine);
        Spec[i].Move(Engine);
        if(Player[i].m_iPlayerID != -1)Missile[Player[i].m_iPlayerID].Move(this,Engine,i);
        }
      Sky[0].Move(Engine,this);Sky[1].Move(Engine,this);Sky[2].Move(Engine,this);
      Animal[0].Move(&m_sData,Engine,this);Animal[1].Move(&m_sData,Engine,this);

      SeaGull[0].Move(&m_sData,Engine,this,0);SeaGull[1].Move(&m_sData,Engine,this,1);SeaGull[2].Move(&m_sData,Engine,this,2);
      SeaGull[3].Move(&m_sData,Engine,this,3);SeaGull[4].Move(&m_sData,Engine,this,4);SeaGull[5].Move(&m_sData,Engine,this,5);
      SeaGull[6].Move(&m_sData,Engine,this,6);SeaGull[7].Move(&m_sData,Engine,this,7);SeaGull[8].Move(&m_sData,Engine,this,8);

	  if(Engine->Server == true)
	  {
	      Collision_Handle(Engine);
		  if(Check_GameOver() == true)
		  {
			  m_cGameState = GAME_STATE_GAMEOVER;
			  m_fGameOverTimer = 3.0f;
			  Server_Network_Send(PACKET_SERVER_GAMEOVER,Engine);
		  }
	  }

      }
    break;
    //---------------------------------------------------------------------
    case GAME_STATE_GAMEOVER:
    //---------------------------------------------------------------------
      {
      gluLookAt(0.0f,0.0f,0.0f-Plane[ID].m_fPoision,	
                0.0f,0.0f,-100.0f,
                0.0f+Plane[ID].m_fPoision,1.0f,0.0f);

      if(m_bBailActivate == false)glClearColor(0.0f, 0.0f, 0.3f-(0.0f * 0.3f), 0.0f);
	  else						  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glColor3f(1.0f-(0.0f * 1.0f),1.0f-(0.0f * 1.0f),1.0f-(0.0f * 1.0f));

      //--------------------------------//
      //------ Update Every Things -----//
      //--------------------------------//

      for(i=0;i < 16;i++)
        {
        //----- Update Thing which requirer Player controls -----//
        if(Player[i].m_bActive == true && Player[i].m_iPlayerID != -1)
          {
//          if(Player[i].m_bAI == true)Bot.Handle(this,i);

          Plane[Player[i].m_iPlayerID].Move(&m_sData,this,Engine,Player[i].m_bKey_Speed,Player[i].m_bKey_Left, Player[i].m_bKey_Right,Player[i].m_iPlayerID,i);
          Man[  Player[i].m_iPlayerID].Move(this,Engine,Player[i].m_bKey_Left, Player[i].m_bKey_Right,Player[i].m_bKey_Speed,Player[i].m_bKey_Down,Player[i].m_iPlayerID);
          }
        Fire[i].Move(this,Engine);
        Spec[i].Move(Engine);
        if(Player[i].m_iPlayerID != -1)Missile[Player[i].m_iPlayerID].Move(this,Engine,i);
        }
      Sky[0].Move(Engine,this);Sky[1].Move(Engine,this);Sky[2].Move(Engine,this);
      Animal[0].Move(&m_sData,Engine,this);Animal[1].Move(&m_sData,Engine,this);

      SeaGull[0].Move(&m_sData,Engine,this,0);SeaGull[1].Move(&m_sData,Engine,this,1);SeaGull[2].Move(&m_sData,Engine,this,2);
      SeaGull[3].Move(&m_sData,Engine,this,3);SeaGull[4].Move(&m_sData,Engine,this,4);SeaGull[5].Move(&m_sData,Engine,this,5);
      SeaGull[6].Move(&m_sData,Engine,this,6);SeaGull[7].Move(&m_sData,Engine,this,7);SeaGull[8].Move(&m_sData,Engine,this,8);

	  if(Engine->Server == true)
	  {
	      Collision_Handle(Engine);
		  Handle_GameOver(Engine);
	  }
      }
    break;
    }
  }

//------------------------------------------------------------------
bool CGameHandler::Server_Handle(SEngine *Engine)
//------------------------------------------------------------------
  {
  int i;

  //---------- Ping Master Server ----------//

  if(Engine->m_sSettings.AddToMasterServer == 1){Ping_MasterServer(Engine);}

  //---------- Handle Server Network ----------//

  Server_Network_Handle(Engine);

  //---------- Handle Server Weapon overhead ----------//

  for(i = 0;i < 16;i++)
  {
	if(Player[i].m_fFireOverload > 0.0f)Player[i].m_fFireOverload -= (float)Engine->Timer.GetDeltaMs() * 0.001f;
	if(Player[i].m_fSpecOverload > 0.0f)Player[i].m_fSpecOverload -= (float)Engine->Timer.GetDeltaMs() * 0.001f;
  }
  //---------- Check if Server push a button -----------//

				 if(m_cGameState == GAME_STATE_BUYMENU)
				 {
				   if(Engine->Key.Key_Down('1') == false)Player[0].m_bKeyPress_1 = false;
				   if(Engine->Key.Key_Down('2') == false)Player[0].m_bKeyPress_2 = false;
				   if(Engine->Key.Key_Down('3') == false)Player[0].m_bKeyPress_3 = false;
				   if(Engine->Key.Key_Down('4') == false)Player[0].m_bKeyPress_4 = false;
				   if(Engine->Key.Key_Down('5') == false)Player[0].m_bKeyPress_5 = false;

				   if(Engine->Key.Key_Down('1') == true && Player[0].m_bKeyPress_1 == false){Player[0].m_bKey_1 = true;Player[0].m_bKeyPress_1 = true;}
				   if(Engine->Key.Key_Down('2') == true && Player[0].m_bKeyPress_2 == false){Player[0].m_bKey_2 = true;Player[0].m_bKeyPress_2 = true;}
				   if(Engine->Key.Key_Down('3') == true && Player[0].m_bKeyPress_3 == false){Player[0].m_bKey_3 = true;Player[0].m_bKeyPress_3 = true;}
				   if(Engine->Key.Key_Down('4') == true && Player[0].m_bKeyPress_4 == false){Player[0].m_bKey_4 = true;Player[0].m_bKeyPress_4 = true;}
				   if(Engine->Key.Key_Down('5') == true && Player[0].m_bKeyPress_5 == false){Player[0].m_bKey_5 = true;Player[0].m_bKeyPress_5 = true;}
				 }


			if(Player[0].m_bKey_1 != Engine->Key.Key_Down('1') ||
			   Player[0].m_bKey_2 != Engine->Key.Key_Down('2') ||
			   Player[0].m_bKey_3 != Engine->Key.Key_Down('3') ||
			   Player[0].m_bKey_4 != Engine->Key.Key_Down('4') ||
			   Player[0].m_bKey_5 != Engine->Key.Key_Down('5') ||

			   Player[0].m_bKey_Down  != Engine->Key.Key_Down(VK_DOWN)  ||
			   Player[0].m_bKey_Right != Engine->Key.Key_Down(VK_RIGHT) ||
			   Player[0].m_bKey_Left  != Engine->Key.Key_Down(VK_LEFT)  ||
			   Player[0].m_bKey_Speed != Engine->Key.Key_Down(VK_UP)    ||

			   Player[0].m_bKey_Fire    != Engine->Key.Key_Down(VK_SPACE)   ||
			   Player[0].m_bKey_Spec    != Engine->Key.Key_Down(VK_CONTROL) ||
			   Player[0].m_bKey_Missile != Engine->Key.Key_Down(VK_SHIFT)   ||
			   Player[0].m_bKey_Para    != (
											  Engine->Key.Key_Down('W') || Engine->Key.Key_Down('E') || Engine->Key.Key_Down('R') ||
											  Engine->Key.Key_Down('S') || Engine->Key.Key_Down('D') || Engine->Key.Key_Down('F'))    )
			{
				if(Engine->Key.Key_Down(VK_LEFT))   Player[0].m_bKey_Left  = true;
				else                                Player[0].m_bKey_Left  = false;
				if(Engine->Key.Key_Down(VK_RIGHT))  Player[0].m_bKey_Right = true;
				else                                Player[0].m_bKey_Right = false;

				 //---------- Handle Server Key -----------//

				if(m_cGameState == GAME_STATE_GAMING) 
				{
					if(Engine->Key.Key_Down('1'))Player[0].m_bKey_1 = true;
					else						 Player[0].m_bKey_1 = false;
					if(Engine->Key.Key_Down('2'))Player[0].m_bKey_2 = true;
					else						 Player[0].m_bKey_2 = false;
					if(Engine->Key.Key_Down('3'))Player[0].m_bKey_3 = true;
					else						 Player[0].m_bKey_3 = false;
					if(Engine->Key.Key_Down('4'))Player[0].m_bKey_4 = true;
					else						 Player[0].m_bKey_4 = false;
					if(Engine->Key.Key_Down('5'))Player[0].m_bKey_5 = true;
					else						 Player[0].m_bKey_5 = false;
				}

				else if(m_bSelectingTeam == false)
				{
					if(Engine->Key.Key_Down(VK_UP))     Player[0].m_bKey_Speed = true;
					else                                Player[0].m_bKey_Speed = false;
					if(Engine->Key.Key_Down(VK_DOWN))   Player[0].m_bKey_Down  = true;
					else                                Player[0].m_bKey_Down  = false;
					if(Engine->Key.Key_Down(VK_SPACE))  Player[0].m_bKey_Fire  = true;
					else                                Player[0].m_bKey_Fire  = false;
					if(Engine->Key.Key_Down(VK_CONTROL))Player[0].m_bKey_Spec  = true;
					else                                Player[0].m_bKey_Spec  = false;
					if((
											  Engine->Key.Key_Down('W') || Engine->Key.Key_Down('E') || Engine->Key.Key_Down('R') ||
											  Engine->Key.Key_Down('S') || Engine->Key.Key_Down('D') || Engine->Key.Key_Down('F')))       Player[0].m_bKey_Para  = true;
					else                                Player[0].m_bKey_Para  = false;
					if(Engine->Key.Key_Down(VK_SHIFT))  Player[0].m_bKey_Missile  = true;
					else                                Player[0].m_bKey_Missile  = false;
				}				
				
				Server_Network_KeyUpdate(0,Engine);
				 if(m_cGameState != GAME_STATE_BUYMENU)
				 {
 				 Player[0].m_bKey_1 = Engine->Key.Key_Down('1');
			      Player[0].m_bKey_2 = Engine->Key.Key_Down('2');
			      Player[0].m_bKey_3 = Engine->Key.Key_Down('3');
			      Player[0].m_bKey_4 = Engine->Key.Key_Down('4');
			      Player[0].m_bKey_5 = Engine->Key.Key_Down('5');
				 }
			      Player[0].m_bKey_Down  = Engine->Key.Key_Down(VK_DOWN);
			      Player[0].m_bKey_Right = Engine->Key.Key_Down(VK_RIGHT);
			      Player[0].m_bKey_Left  = Engine->Key.Key_Down(VK_LEFT);
			      Player[0].m_bKey_Speed = Engine->Key.Key_Down(VK_UP);

			      Player[0].m_bKey_Fire    = Engine->Key.Key_Down(VK_SPACE);
			      Player[0].m_bKey_Spec    = Engine->Key.Key_Down(VK_CONTROL);
			      Player[0].m_bKey_Missile = Engine->Key.Key_Down(VK_SHIFT);
			      Player[0].m_bKey_Para    = (
											  Engine->Key.Key_Down('W') || Engine->Key.Key_Down('E') || Engine->Key.Key_Down('R') ||
											  Engine->Key.Key_Down('S') || Engine->Key.Key_Down('D') || Engine->Key.Key_Down('F'));

			}



  //---------- Handle All Players Key -----------//

  for(i = 0;i < 16;i++)
    {
    if(Player[i].m_bActive == false || Player[i].m_iPlayerID == -1)continue;

    ///////////////////////////////////////////////
    //---------- Handle BuyMenu-Logic -----------//
    ///////////////////////////////////////////////
    if(m_cGameState == GAME_STATE_BUYMENU)
      {
      if(Player[i].m_bKey_1 == true) // Buy Plane
        {
        if(     Player[i].m_iMoney >=  500 && Player[i].m_cUpgrade_Plane == 0){Player[i].m_iMoney -=  500;Player[i].m_cUpgrade_Plane++;Server_Network_SendBuyMenu(i,10,Engine);}
        else if(Player[i].m_iMoney >=  PLANE_SHIELD_PRICE && Player[i].m_cUpgrade_Plane == 1){Player[i].m_iMoney -=  PLANE_SHIELD_PRICE;Player[i].m_cUpgrade_Plane++;Server_Network_SendBuyMenu(i,11,Engine);}
        else if(Player[i].m_iMoney >= 1500 && Player[i].m_cUpgrade_Plane == 2){Player[i].m_iMoney -= 1500;Player[i].m_cUpgrade_Plane++;Server_Network_SendBuyMenu(i,12,Engine);}
        else if(Player[i].m_iMoney >= 2000 && Player[i].m_cUpgrade_Plane == 3){Player[i].m_iMoney -= 2000;Player[i].m_cUpgrade_Plane++;Server_Network_SendBuyMenu(i,13,Engine);}

        Player[i].m_bKey_1 = false;
        }
      if(Player[i].m_bKey_2 == true) // Para Plane
        {
        if(     Player[i].m_iMoney >=  PARA_PRICE && Player[i].m_cUpgrade_Para == 0){Player[i].m_iMoney -=  PARA_PRICE;Player[i].m_cUpgrade_Para++;Server_Network_SendBuyMenu(i,20,Engine);}
        else if(Player[i].m_iMoney >=  PARA2_PRICE && Player[i].m_cUpgrade_Para == 1){Player[i].m_iMoney -=  PARA2_PRICE;Player[i].m_cUpgrade_Para++;Server_Network_SendBuyMenu(i,21,Engine);}
        else if(Player[i].m_iMoney >=  PARA3_PRICE && Player[i].m_cUpgrade_Para == 2){Player[i].m_iMoney -=  PARA3_PRICE;Player[i].m_cUpgrade_Para++;Server_Network_SendBuyMenu(i,22,Engine);}
        else if(Player[i].m_iMoney >= PARA_STEALH_PRICE && Player[i].m_cUpgrade_Para == 3){Player[i].m_iMoney -= PARA_STEALH_PRICE;Player[i].m_cUpgrade_Para++;Server_Network_SendBuyMenu(i,23,Engine);}
        else if(Player[i].m_iMoney >= 1500 && Player[i].m_cUpgrade_Para == 4){Player[i].m_iMoney -= 1500;Player[i].m_cUpgrade_Para++;Server_Network_SendBuyMenu(i,24,Engine);}

        Player[i].m_bKey_2 = false;
        }
      if(Player[i].m_bKey_3 == true) // Fire 
        {
        if(     Player[i].m_iMoney >= SHOT_LEVEL1 && Player[i].m_cUpgrade_Fire == 0){Player[i].m_iMoney -= SHOT_LEVEL1;Player[i].m_cUpgrade_Fire++;Server_Network_SendBuyMenu(i,30,Engine);}
        else if(Player[i].m_iMoney >= SHOT_LEVEL2 && Player[i].m_cUpgrade_Fire == 1){Player[i].m_iMoney -= SHOT_LEVEL2;Player[i].m_cUpgrade_Fire++;Server_Network_SendBuyMenu(i,31,Engine);}
        else if(Player[i].m_iMoney >= SHOT_LEVEL3 && Player[i].m_cUpgrade_Fire == 2){Player[i].m_iMoney -= SHOT_LEVEL3;Player[i].m_cUpgrade_Fire++;Server_Network_SendBuyMenu(i,32,Engine);}
        else if(Player[i].m_iMoney >= SHOT_LEVEL4 && Player[i].m_cUpgrade_Fire == 3){Player[i].m_iMoney -= SHOT_LEVEL4;Player[i].m_cUpgrade_Fire++;Server_Network_SendBuyMenu(i,33,Engine);}

        Player[i].m_bKey_3 = false;
        }
      if(Player[i].m_bKey_4 == true) // Spec 
        {
        if(     Player[i].m_iMoney >=  200 && Player[i].m_cUpgrade_Spec == 0){Player[i].m_iMoney -=  200;Player[i].m_cUpgrade_Spec++;Server_Network_SendBuyMenu(i,40,Engine);}
        else if(Player[i].m_iMoney >=  300 && Player[i].m_cUpgrade_Spec == 1){Player[i].m_iMoney -=  300;Player[i].m_cUpgrade_Spec++;Server_Network_SendBuyMenu(i,41,Engine);}
        else if(Player[i].m_iMoney >=  600 && Player[i].m_cUpgrade_Spec == 2){Player[i].m_iMoney -=  600;Player[i].m_cUpgrade_Spec++;Server_Network_SendBuyMenu(i,42,Engine);}
        else if(Player[i].m_iMoney >= 1000 && Player[i].m_cUpgrade_Spec == 3){Player[i].m_iMoney -= 1000;Player[i].m_cUpgrade_Spec++;Server_Network_SendBuyMenu(i,43,Engine);}
        else if(Player[i].m_iMoney >= 1500 && Player[i].m_cUpgrade_Spec == 4){Player[i].m_iMoney -= 1500;Player[i].m_cUpgrade_Spec++;Server_Network_SendBuyMenu(i,44,Engine);}

        Player[i].m_bKey_4 = false;
        }
      if(Player[i].m_bKey_5 == true) // Missile 
        {
        if(     Player[i].m_iMoney >=  PLANE_MISSILE_LEVEL1 && Player[i].m_cUpgrade_Missile == 0){Player[i].m_iMoney -=  PLANE_MISSILE_LEVEL1;Player[i].m_cUpgrade_Missile++;Server_Network_SendBuyMenu(i,50,Engine);}
        else if(Player[i].m_iMoney >=  PLANE_MISSILE_LEVEL2 && Player[i].m_cUpgrade_Missile == 1){Player[i].m_iMoney -=  PLANE_MISSILE_LEVEL2;Player[i].m_cUpgrade_Missile++;Server_Network_SendBuyMenu(i,51,Engine);}
        else if(Player[i].m_iMoney >=  PLANE_MISSILE_LEVEL3 && Player[i].m_cUpgrade_Missile == 2){Player[i].m_iMoney -=  PLANE_MISSILE_LEVEL3;Player[i].m_cUpgrade_Missile++;Server_Network_SendBuyMenu(i,52,Engine);}
        else if(Player[i].m_iMoney >=  PLANE_MISSILE_LEVEL4 && Player[i].m_cUpgrade_Missile == 3){Player[i].m_iMoney -=  PLANE_MISSILE_LEVEL4;Player[i].m_cUpgrade_Missile++;Server_Network_SendBuyMenu(i,53,Engine);}
        else if(Player[i].m_iMoney >=  PLANE_MISSILE_LEVEL5 && Player[i].m_cUpgrade_Missile == 4){Player[i].m_iMoney -=  PLANE_MISSILE_LEVEL5;Player[i].m_cUpgrade_Missile++;Server_Network_SendBuyMenu(i,54,Engine);}
        else if(Player[i].m_iMoney >=  PLANE_MISSILE_LEVEL6 && Player[i].m_cUpgrade_Missile == 5){Player[i].m_iMoney -=  PLANE_MISSILE_LEVEL6;Player[i].m_cUpgrade_Missile++;Server_Network_SendBuyMenu(i,55,Engine);}

        Player[i].m_bKey_5 = false;
        }
      }

    ////////////////////////////////////////////
    //---------- Handle Game-Logic -----------//
    ////////////////////////////////////////////
    if(m_cGameState == GAME_STATE_GAMING)
      {
      char Temp_ID = Player[i].m_iPlayerID;

      if(Player[i].m_bKey_Missile == true && Player[i].m_cUpgrade_Missile != 0)
        {
        if(Plane[Temp_ID].m_bPilot == true)
          {
          if(Missile[Temp_ID].m_bUsed == false)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Missile);
		  if(Missile[Temp_ID].m_bUsed == false)Server_Network_SendShot(3,Temp_ID,Engine);
          Missile[Temp_ID].Create(Plane[Temp_ID].m_fx,Plane[Temp_ID].m_fy,Plane[Temp_ID].m_fRotate,-1,this,Temp_ID);
		}

        if(Man[Temp_ID].m_cStatus == MAN_STATUS_GROUND || Man[Temp_ID].m_cStatus == MAN_STATUS_BEHIND_PLANE)
          {
          if(Missile[Temp_ID].m_bUsed == false)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Missile);
		  if(Missile[Temp_ID].m_bUsed == false)Server_Network_SendShot(13,Temp_ID,Engine);
          Missile[Temp_ID].Create(Man[Temp_ID].m_fx,Man[Temp_ID].m_fy+0.1f,Man[Temp_ID].m_fRotate+180.0f,-1,this,Temp_ID);
		}

        Plane[Temp_ID].m_fStealth   = 0.0f;
        Plane[Temp_ID].m_bStealthUp = true;
        }

      if(Player[i].m_bKey_Fire == true && Player[i].m_fFireOverload <= 0.0f)
        {
			Player[i].m_fFireOverload = 0.5f;
        if(Plane[Temp_ID].m_bPilot == true)
          {
          if(Fire[Temp_ID].m_bActive == false){FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Shot);}
  		  if(Fire[Temp_ID].m_bActive == false)Server_Network_SendShot(1,Temp_ID,Engine);
          Fire[Temp_ID].Create(Plane[Temp_ID].m_fx,Plane[Temp_ID].m_fy,Plane[Temp_ID].m_fRotate,Plane[Temp_ID].m_fSpeed);
          }

        if(Man[Temp_ID].m_cStatus == MAN_STATUS_GROUND || Man[Temp_ID].m_cStatus == MAN_STATUS_BEHIND_PLANE)
          {
          if(Fire[Temp_ID].m_bActive == false){FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Shot);}
		  if(Fire[Temp_ID].m_bActive == false)Server_Network_SendShot(11,Temp_ID,Engine);
          Fire[Temp_ID].Create   (Man[Temp_ID].m_fx,Man[Temp_ID].m_fy+0.1f,Man[Temp_ID].m_fRotate+180.0f,1.0f);
		}
        Plane[Temp_ID].m_fStealth   = 0.0f;
        Plane[Temp_ID].m_bStealthUp = true;
        }

      if(Player[i].m_bKey_Spec == true && Player[i].m_cUpgrade_Spec != 0 && Player[i].m_fSpecOverload <= 0.0f)
        {
			Player[i].m_fSpecOverload = 0.5f;
        if(Plane[Temp_ID].m_bPilot == true)
          {
          if(Spec[Temp_ID].m_bActive == false){FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Spec);}
   		  if(Spec[Temp_ID].m_bActive == false && Spec[Temp_ID].m_cType != 0)Server_Network_SendShot(2,Temp_ID,Engine);
          Spec[Temp_ID].Create(Plane[Temp_ID].m_fx,Plane[Temp_ID].m_fy,Plane[Temp_ID].m_fRotate,Plane[Temp_ID].m_fSpeed);
          }
        if(Man[Temp_ID].m_cStatus == MAN_STATUS_GROUND || Man[Temp_ID].m_cStatus == MAN_STATUS_BEHIND_PLANE)
          {
          if(Spec[Temp_ID].m_bActive == false){FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Spec);}
  		  if(Spec[Temp_ID].m_bActive == false && Spec[Temp_ID].m_cType != 0)Server_Network_SendShot(12,Temp_ID,Engine);
          Spec[Temp_ID].Create   (Man[Temp_ID].m_fx,Man[Temp_ID].m_fy+0.1f,Man[Temp_ID].m_fRotate+180.0f,1.25f);
          }

        Plane[Temp_ID].m_fStealth   = 0.0f;
        Plane[Temp_ID].m_bStealthUp = true;
        }

      if(Player[i].m_bKey_Para == false)Player[i].m_bKey_ParaDown = false;
      if(Player[i].m_bKey_Para == true && Player[i].m_bKey_ParaDown == false)
        {
        if(Plane[Temp_ID].m_bPilot == false)
          {
          if(Man[Temp_ID].m_cStatus == MAN_STATUS_FLYING && Player[i].m_cUpgrade_Para != 0 && Player[i].m_cUpgrade_Para != 5)
            {
            Man[Temp_ID].m_cStatus           = MAN_STATUS_PARACHUTING;
            Man[Temp_ID].m_fPara_Folding_Out = 0.0f;

			Server_Network_ParachuteMan(Temp_ID,Engine);
            }
          if(Man[Temp_ID].m_fPara_Folding_Out >= 0.3f && Man[Temp_ID].m_cStatus == MAN_STATUS_PARACHUTING && Player[i].m_cUpgrade_Para != 5)
			{
            Man[Temp_ID].m_cStatus           = MAN_STATUS_FLYING;

			Server_Network_ParachuteMan(Temp_ID,Engine);
			}
			Player[i].m_bKey_ParaDown = true;
          }
        if(Plane[Temp_ID].m_bPilot == true && Plane[Temp_ID].m_cDamage != PLANE_DAMAGE_CRASHED)
          {
          Player[i].m_bKey_ParaDown = true;
          Man[Temp_ID].JumpOut(Plane[Temp_ID].m_fx,Plane[Temp_ID].m_fy,Plane[Temp_ID].m_fSpeed,Plane[Temp_ID].m_fRotate);
          Plane[Temp_ID].m_bPilot     = false;
		  Server_Network_EjectFromPlane(Temp_ID,Engine);
          char Rand_Sound = rand()%5;
          if(Rand_Sound == 0)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Falling01);
          if(Rand_Sound == 1)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Falling02);
          if(Rand_Sound == 2)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Falling03);
          if(Rand_Sound == 3)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Falling04);
          if(Rand_Sound == 4)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Falling05);
          }
        }
      }
    }

  return false;
  }

//------------------------------------------------------------------
bool CGameHandler::Client_Handle(SEngine *Engine)
//------------------------------------------------------------------
  {
  return Client_Network_Handle(Engine);
  }

//------------------------------------------------------------------
void CGameHandler::UnLoad(SEngine *Engine)
//------------------------------------------------------------------
  {
  Engine->OpenGl_Font.KillFont();

  FSOUND_Close();

  UnLoad_Data(Engine);

//if(m_sData.Sphere != NULL){gluDeleteQuadric(m_sData.Sphere);m_sData.Sphere = NULL;}
  }

//------------------------------------------------------------------
void CGameHandler::Load(SEngine *Engine)
//------------------------------------------------------------------
  {
  Engine->OpenGl_Font.LoadGLFont("data\\font\\font.dat");
  Engine->OpenGl_Font.BuildFont();

  if(Engine->m_sSettings.Resolution == 0)Engine->OpenGl_Camera.ReSizeGLScene( 640, 480);
  if(Engine->m_sSettings.Resolution == 1)Engine->OpenGl_Camera.ReSizeGLScene( 640, 480);
  if(Engine->m_sSettings.Resolution == 2)Engine->OpenGl_Camera.ReSizeGLScene( 800, 600);
  if(Engine->m_sSettings.Resolution == 3)Engine->OpenGl_Camera.ReSizeGLScene( 800, 600);
  if(Engine->m_sSettings.Resolution == 4)Engine->OpenGl_Camera.ReSizeGLScene(1024, 768);
  if(Engine->m_sSettings.Resolution == 5)Engine->OpenGl_Camera.ReSizeGLScene(1024, 768);
  if(Engine->m_sSettings.Resolution == 6)Engine->OpenGl_Camera.ReSizeGLScene(1280,1024);
  if(Engine->m_sSettings.Resolution == 7)Engine->OpenGl_Camera.ReSizeGLScene(1280,1024);

  if(Engine->m_sSettings.FrameLimiter == 0)m_iFPS = 5;
  if(Engine->m_sSettings.FrameLimiter == 1)m_iFPS = 10;
  if(Engine->m_sSettings.FrameLimiter == 2)m_iFPS = 25;
  if(Engine->m_sSettings.FrameLimiter == 3)m_iFPS = 33;
  if(Engine->m_sSettings.FrameLimiter == 4)m_iFPS = 50;
  if(Engine->m_sSettings.FrameLimiter == 5)m_iFPS = 60;
  if(Engine->m_sSettings.FrameLimiter == 6)m_iFPS = 66;
  if(Engine->m_sSettings.FrameLimiter == 7)m_iFPS = 75;
  if(Engine->m_sSettings.FrameLimiter == 8)m_iFPS = 999;

  Engine->OpenGl_Camera.InitGL_Values();

  FSOUND_Init(44100, 64, 0);

  Load_Data(Engine);

  m_sData.Sphere    = NULL;
  m_sData.Sphere    = gluNewQuadric();
  if(m_sData.Sphere != NULL)
    {
    gluQuadricNormals(m_sData.Sphere, GLU_SMOOTH);		
    gluQuadricTexture(m_sData.Sphere, GL_TRUE);
    //gluQuadricDrawStyle(m_sData.Sphere, GLU_LINE);
    }

  if(m_bBailActivate == false)glClearColor(0.0f, 0.0f, 0.3f, 0.0f);
  else						  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			
  glEnable(GL_BLEND);										
  glAlphaFunc(GL_GREATER,0.1f);							
  glEnable(GL_ALPHA_TEST);								
  glEnable(GL_TEXTURE_2D);								
  glEnable(GL_CULL_FACE);	

  Red_Score      = 0;
  Green_Score    = 0;
  m_dTime        = 0;

  for(int i = 0;i < 16;i++) // Reset All Player information
    {
	Player[i].m_iPunish = 0;
    Player[i].m_bActive       = false;
    Player[i].m_bKey_Down     = false;
    Player[i].m_bKey_Fire     = false;
    Player[i].m_bKey_Left     = false;
    Player[i].m_bKey_Missile  = false;
    Player[i].m_bKey_Para     = false;
    Player[i].m_bKey_ParaDown = false;
    Player[i].m_bKey_Right    = false;
    Player[i].m_bKey_Spec     = false;
    Player[i].m_bKey_Speed    = false;
    Player[i].m_bAI           = false;
    Player[i].m_iHits         = 0;
    Player[i].m_iMoney        = 0;
    Player[i].m_iPlayerID     = -1;
    Player[i].m_cUpgrade_Plane   = 0;
    Player[i].m_cUpgrade_Para    = 0;
    Player[i].m_cUpgrade_Fire    = 0;
    Player[i].m_cUpgrade_Spec    = 0;
    Player[i].m_cUpgrade_Missile = 0;
	for(int ii = 0;ii < 16;ii++)Player[i].m_bHitMe[ii] = false;
    }
  Player[0].m_bActive = true; // Server is always Active

  m_fMasterServerTimer = 30.0f;
  m_fBuyMenuTimer  = (float)Engine->m_sSettings.BuyTime;
  m_cGameState     = GAME_STATE_BUYMENU;
  m_bSelectingTeam = true;

  srand( (unsigned)time( NULL ) );

  GameReset(Engine);

  Engine->Timer.Init();

  }

//------------------------------------------------------------------
void CGameHandler::Load_Data(SEngine *Engine)
//------------------------------------------------------------------
  {

  //---------- Textures ----------//

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_SeaGull1L,  "data\\Animal\\Seagull1L.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_SeaGull2L,  "data\\Animal\\Seagull2L.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_SeaGull1,   "data\\Animal\\Seagull1.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_SeaGull2,   "data\\Animal\\Seagull2.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_GullSplash1,"data\\Animal\\gullsplash1.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_GullSplash2,"data\\Animal\\gullsplash2.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_Giraf1R,"data\\Animal\\Giraf1_R.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_Giraf2R,"data\\Animal\\Giraf2_R.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_Giraf3R,"data\\Animal\\Giraf3_R.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_ElephantR,"data\\Animal\\Elephant_R.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_ElephantL,"data\\Animal\\Elephant_L.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_SheepD,"data\\Animal\\Sheep_D.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_SheepR,"data\\Animal\\Sheep_R.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_SheepL,"data\\Animal\\Sheep_L.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_LionD, "data\\Animal\\Lion_D.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_LionR, "data\\Animal\\Lion_R.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_LionL, "data\\Animal\\Lion_L.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_CowD,  "data\\Animal\\Cow_D.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_CowR,  "data\\Animal\\Cow_R.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Animal_CowL,  "data\\Animal\\Cow_L.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Sky,         "data\\map\\sky.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Sky_Dark,    "data\\map\\sky_Dark.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Plane_Normal,  "data\\menu\\Menu_Plane_Normal.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Plane_Speed,   "data\\menu\\Menu_Plane_Speed.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Plane_Shield,  "data\\menu\\Menu_Plane_Shield.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Plane_TurnRate,"data\\menu\\Menu_Plane_TurnRate.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Plane_Stealth, "data\\menu\\Menu_Plane_Stealth.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Para_Normal,   "data\\menu\\Menu_Para_Normal.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Para_Faster,   "data\\menu\\Menu_Para_Speed.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Para_QuickMove,"data\\menu\\Menu_Para_Quick.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Para_Stealth,  "data\\menu\\Menu_Para_Stealth.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Para_Ball,     "data\\menu\\Menu_Para_Ball.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Fire_Normal,   "data\\menu\\Menu_Fire_Normal.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Fire_Faster,   "data\\menu\\Menu_Fire_Speed.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Fire_Damagex2, "data\\menu\\Menu_Fire_Damagex2.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Fire_Sizex2,   "data\\menu\\Menu_Fire_Sizex2.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Fire_Stealth,  "data\\menu\\Menu_Fire_Stealth.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Spec_Invert,     "data\\menu\\Menu_Spec_Invert.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Spec_Poision,    "data\\menu\\Menu_Spec_Poison.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Spec_Stun,       "data\\menu\\Menu_Spec_Stun.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Spec_Adv_Poision,"data\\menu\\Menu_Spec_AdvPoison.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Spec_AutoJump,   "data\\menu\\Menu_Spec_AutoJump.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Missile_Normal,   "data\\menu\\Menu_Missile_Level1.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Missile_L_Guided, "data\\menu\\Menu_Missile_Level2.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Missile_Guided,   "data\\menu\\Menu_Missile_Level3.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Missile_Angry,    "data\\menu\\Menu_Missile_Level4.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Missile_Bounce,   "data\\menu\\Menu_Missile_Level5.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Missile_Plasma,   "data\\menu\\Menu_Missile_Level6.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_None,   "data\\menu\\Menu_None.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_BuyMenu_Full,   "data\\menu\\Menu_Full.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Buy_Menu,       "data\\menu\\Buy_Menu.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Menu_Select,    "data\\menu\\Team_Select.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Point,          "data\\man\\Pointer.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Plasma_Particle,"data\\fx\\plasma_particle.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Spec_Particle,  "data\\fx\\Spec_particle.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Blood_Particle, "data\\fx\\blood_particle.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Smoke_Particle, "data\\fx\\smoke_particle.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Fire_Particle,  "data\\fx\\fire_particle.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Missile_Particle,"data\\fx\\Missile_particle.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Ball, "data\\Man\\Sphere.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Green_Man, "data\\Man\\Green_Man.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Green_Para,"data\\Man\\Green_Para.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Green_Plane, "data\\plane\\Green_Plane.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Green_Plane_Part1, "data\\plane\\Green_Plane_Part1.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Green_Plane_Part2, "data\\plane\\Green_Plane_Part2.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Green_Plane_Part3, "data\\plane\\Green_Plane_Part3.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Red_Man, "data\\Man\\Red_Man.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Red_Para,"data\\Man\\Red_Para.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Red_Plane, "data\\plane\\Red_Plane.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Red_Plane_Part1, "data\\plane\\Red_Plane_Part1.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Red_Plane_Part2, "data\\plane\\Red_Plane_Part2.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Red_Plane_Part3, "data\\plane\\Red_Plane_Part3.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Tree1, "data\\map\\Tree1.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Tree2, "data\\map\\Tree2.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Tree3, "data\\map\\Tree3.dat",0);

  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Grass, "data\\map\\Grass.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Farm, "data\\map\\Farm.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Ice, "data\\map\\Ice.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Ice_DeaD,"data\\map\\IceD.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_WildGrass,  "data\\map\\Wild_Grass.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Bridge,     "data\\map\\Bridge.dat",0);
  Engine->OpenGl_Texture_TGA.LoadTGA(&m_sData.Tex_Bridge_DeaD,"data\\map\\BridgeD.dat",0);

  //---------- Sound ----------//

  m_sData.Snd_Animal_Cow1          = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Animal_cow1.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Animal_Cow2          = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Animal_cow2.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Animal_Cow3          = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Animal_cow3.dat", FSOUND_NORMAL, 0);

  m_sData.Snd_Animal_Sheep1        = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Animal_sheep1.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Animal_Sheep2        = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Animal_sheep2.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Animal_Sheep3        = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Animal_sheep3.dat", FSOUND_NORMAL, 0);

  m_sData.Snd_Animal_Hit           = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Animal_Hit.dat", FSOUND_NORMAL, 0);

  m_sData.Snd_Man_Die01            = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Man_Die_01.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Man_Die02            = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Man_Die_02.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Man_Die03            = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Man_Die_03.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Man_Die04            = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Man_Die_04.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Man_Die05            = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Man_Die_05.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Man_Die06            = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Man_Die_06.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Man_Die07            = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Man_Die_07.dat", FSOUND_NORMAL, 0);

  m_sData.Snd_Man_Falling01        = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Man_Falling_Down_01.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Man_Falling02        = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Man_Falling_Down_02.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Man_Falling03        = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Man_Falling_Down_03.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Man_Falling04        = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Man_Falling_Down_04.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Man_Falling05        = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Man_Falling_Down_05.dat", FSOUND_NORMAL, 0);

  m_sData.Snd_Plane_Crash          = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Plane_crash.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Plane_Hit_Spec       = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Plane_hit_Spec.dat", FSOUND_NORMAL, 0);

  m_sData.Snd_Plane_Hit1           = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Plane_Hit1.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Plane_Hit2           = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Plane_Hit2.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Plane_Hit3           = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Plane_Hit3.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Plane_Hit4           = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Plane_Hit4.dat", FSOUND_NORMAL, 0);

  m_sData.Snd_Plane_Missile        = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Plane_Missile.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Plane_Shot           = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Plane_shot.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Plane_Spec           = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Plane_Spec.dat", FSOUND_NORMAL, 0);

  m_sData.Snd_Plane_Shield         = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Plane_Shield.dat", FSOUND_NORMAL, 0);

  m_sData.Snd_Plane_Collision      = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Player_Collision.dat", FSOUND_NORMAL, 0);
  m_sData.Snd_Plane_Join           = FSOUND_Sample_Load(FSOUND_UNMANAGED, "data/sound/Player_Join.dat", FSOUND_NORMAL, 0);
  }

//------------------------------------------------------------------
void CGameHandler::UnLoad_Data(SEngine *Engine)
//------------------------------------------------------------------
  {
  //---------- Textures ----------//

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_SeaGull1L);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_SeaGull2L);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_SeaGull1);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_SeaGull2);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_GullSplash1);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_GullSplash2);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_Giraf1R);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_Giraf2R);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_Giraf3R);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_ElephantR);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_ElephantL);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_SheepD);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_SheepR);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_SheepL);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_LionD);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_LionR);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_LionL);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_CowD);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_CowR);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Animal_CowL);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Sky);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Sky_Dark);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Plane_Normal);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Plane_Speed);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Plane_Shield);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Plane_TurnRate);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Plane_Stealth);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Para_Normal);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Para_Faster);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Para_QuickMove);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Para_Stealth);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Para_Ball);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Fire_Normal);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Fire_Faster);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Fire_Damagex2);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Fire_Sizex2);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Fire_Stealth);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Spec_Invert);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Spec_Poision);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Spec_Stun);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Spec_Adv_Poision);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Spec_AutoJump);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Missile_Normal);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Missile_L_Guided);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Missile_Guided);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Missile_Angry);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Missile_Bounce);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Missile_Plasma);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_None);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_BuyMenu_Full);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Buy_Menu);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Menu_Select);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Point);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Plasma_Particle);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Spec_Particle);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Blood_Particle);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Smoke_Particle);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Fire_Particle);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Missile_Particle);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Ball);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Green_Man);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Green_Para);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Green_Plane);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Green_Plane_Part1);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Green_Plane_Part2);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Green_Plane_Part3);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Red_Man);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Red_Para);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Red_Plane);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Red_Plane_Part1);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Red_Plane_Part2);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Red_Plane_Part3);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Grass);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Farm);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Ice);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Ice_DeaD);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_WildGrass);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Bridge);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Bridge_DeaD);

  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Tree1);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Tree2);
  Engine->OpenGl_Texture_TGA.FreeTGA(&m_sData.Tex_Tree3);

  //---------- Sound ----------//

  FSOUND_Sample_Free(m_sData.Snd_Animal_Cow1);
  FSOUND_Sample_Free(m_sData.Snd_Animal_Cow2);
  FSOUND_Sample_Free(m_sData.Snd_Animal_Cow3);

  FSOUND_Sample_Free(m_sData.Snd_Animal_Sheep1);
  FSOUND_Sample_Free(m_sData.Snd_Animal_Sheep2);
  FSOUND_Sample_Free(m_sData.Snd_Animal_Sheep3);

  FSOUND_Sample_Free(m_sData.Snd_Animal_Hit);

  FSOUND_Sample_Free(m_sData.Snd_Man_Die01);
  FSOUND_Sample_Free(m_sData.Snd_Man_Die02);
  FSOUND_Sample_Free(m_sData.Snd_Man_Die03);
  FSOUND_Sample_Free(m_sData.Snd_Man_Die04);
  FSOUND_Sample_Free(m_sData.Snd_Man_Die05);
  FSOUND_Sample_Free(m_sData.Snd_Man_Die06);
  FSOUND_Sample_Free(m_sData.Snd_Man_Die07);

  FSOUND_Sample_Free(m_sData.Snd_Man_Falling01);
  FSOUND_Sample_Free(m_sData.Snd_Man_Falling02);
  FSOUND_Sample_Free(m_sData.Snd_Man_Falling03);
  FSOUND_Sample_Free(m_sData.Snd_Man_Falling04);
  FSOUND_Sample_Free(m_sData.Snd_Man_Falling05);

  FSOUND_Sample_Free(m_sData.Snd_Plane_Crash);
  FSOUND_Sample_Free(m_sData.Snd_Plane_Hit_Spec);

  FSOUND_Sample_Free(m_sData.Snd_Plane_Hit1);
  FSOUND_Sample_Free(m_sData.Snd_Plane_Hit2);
  FSOUND_Sample_Free(m_sData.Snd_Plane_Hit3);
  FSOUND_Sample_Free(m_sData.Snd_Plane_Hit4);

  FSOUND_Sample_Free(m_sData.Snd_Plane_Missile);
  FSOUND_Sample_Free(m_sData.Snd_Plane_Shot);
  FSOUND_Sample_Free(m_sData.Snd_Plane_Spec);

  FSOUND_Sample_Free(m_sData.Snd_Plane_Shield);

  FSOUND_Sample_Free(m_sData.Snd_Plane_Collision);
  FSOUND_Sample_Free(m_sData.Snd_Plane_Join);
  }

//------------------------------------------------------------------
void CGameHandler::GameReset(SEngine *Engine)
//------------------------------------------------------------------
  {
  if(Engine->Server == false)return;
	
  int i;

  Map.Init();
  Sky[0].Init(Engine,this);
  Sky[1].Init(Engine,this);
  Sky[2].Init(Engine,this);

  Animal[0].Init();
  Animal[1].Init();

  for(i=0;i< 16;i++)
  {
	if(Player[i].m_iPunish >= 2)
	{
		Plane[Player[i].m_iPlayerID].m_bPunish = true;
	}
	else
	{
		Plane[Player[i].m_iPlayerID].m_bPunish = false;
	}
  }

  for(i=0;i< 16;i++)
    {
    Plane[i].Init(Engine,i);
    Man[i].m_cStartNR = i;
    Man[i].m_bActive = false;
    Missile[i].m_bUsed = false;
    Missile[i].m_bDead = false;
    Fire[i].m_bActive  = false;
    Spec[i].m_bActive  = false;
	if(Player[i].m_iMoney > 3000)Player[i].m_iMoney = 3000;
	Player[i].m_fFireOverload = -1.0f;
	Player[i].m_fSpecOverload = -1.0f;
  }

  for(i=0;i< 10;i++)
  {
    m_iStatsByWho[i]  = -1;
    m_iStatsByWhat[i] = -1;
    m_iStatsWhoHit[i] = -1;
    m_fStatsLife[i]   = -1.0f;
  }

  for(i=0;i < 9;i++)
  {
	SeaGull[i].m_bActive = false;
  }

  for(i=0;i < 3;i++)
  {
	if(Map.m_cMapType != MAP_TYPE_ADV_GRASS && Map.m_cMapType != MAP_TYPE_ICE && Map.m_bTreeActivate[i] == true)
	{
		SeaGull[(i*3)].  m_bActive = true;
		SeaGull[(i*3)+1].m_bActive = true;
		SeaGull[(i*3)+2].m_bActive = true;

		SeaGull[(i*3)].  m_fX = Map.m_fTreeX[i];
		SeaGull[(i*3)+1].m_fX = Map.m_fTreeX[i]+0.2f;
		SeaGull[(i*3)+2].m_fX = Map.m_fTreeX[i]-0.35f;

		SeaGull[(i*3)].  m_fY = -3.8f;
		SeaGull[(i*3)+1].m_fY = -4.0f;
		SeaGull[(i*3)+2].m_fY = -4.15f;

		SeaGull[(i*3)].  Init();
		SeaGull[(i*3)+1].Init();
		SeaGull[(i*3)+2].Init();
	}
  }

  m_cManHit = -1;

  Server_Network_Send(PACKET_SERVER_INITUPDATE,Engine);
  }

//------------------------------------------------------------------
void CGameHandler::DrawFPS(SEngine *Engine)
//------------------------------------------------------------------
{
m_iFPS_Frames++;

if(m_fFPS_Second <= 0.0f)
  {
  m_iFPS_Temp_Frames = m_iFPS_Frames;
  m_iFPS_Frames = 0;
  m_fFPS_Second = 1.0f;
  }

Engine->OpenGl_Font.glPrint(540,430,"FPS: ",0);
char Temp_Text[12];
itoa(m_iFPS_Temp_Frames,Temp_Text,10);
Engine->OpenGl_Font.glPrint(590,430,Temp_Text,0);
}

//------------------------------------------------------------------
void CGameHandler::Draw_TeamSelect()
//------------------------------------------------------------------
  {
  glPushMatrix();							
  glTranslatef(0.0f,-0.0f,-15.0f);

  glBindTexture(GL_TEXTURE_2D,m_sData.Tex_Menu_Select.texID);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0f,-2.0f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+4.0f,-2.0f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+4.0f,+2.0f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.0f,+2.0f,-0.0f);	
  glEnd();

  glPopMatrix();
  }

//------------------------------------------------------------------
int  CGameHandler::Join_Team(bool Green,bool Red)
//------------------------------------------------------------------
  {
  int i;

  if(Green == true)
    {
    for(i=0;i < 16;i+=2)
      {
      if(Plane[i].m_bOcupied == false){Plane[i].m_bOcupied = true;Plane[i].m_bInGame = false;return i;}
      }
    }

  if(Red == true)
    {
    for(i=1;i < 16;i+=2)
      {
      if(Plane[i].m_bOcupied == false){Plane[i].m_bOcupied = true;Plane[i].m_bInGame = false;return i;}
      }
    }

  return -1; // No target Found
  }

//------------------------------------------------------------------
void CGameHandler::Handle_GameOver(SEngine *Engine)
//------------------------------------------------------------------
  {
  m_fGameOverTimer -= (float)Engine->Timer.GetDeltaMs() * 0.001f;

  if(m_fGameOverTimer <= 0.0)
    {
    m_fBuyMenuTimer = (float)Engine->m_sSettings.BuyTime;
    m_cGameState    = GAME_STATE_BUYMENU;
    GameReset(Engine);

	Server_Network_Send(PACKET_SERVER_DATARESET,Engine);
	
		for(int i=0;i< 16;i++)
		{
		  Player[i].m_iPunish = 0;
		}
    }
  }

//------------------------------------------------------------------
void CGameHandler::Handle_Prepare(SEngine *Engine)
//------------------------------------------------------------------
  {
  int i;
  bool Green = false
      ,Red  = false;

  for(i=0;i< 16;i++){if(Player[i].m_bActive == true && Player[i].m_iPlayerID != -1){Plane[Player[i].m_iPlayerID].m_bInGame = true;}}

  if(Engine->Server == false)return;

  if(Plane[ 0].m_bInGame == true)Green = true;if(Plane[ 2].m_bInGame == true)Green = true;
  if(Plane[ 4].m_bInGame == true)Green = true;if(Plane[ 6].m_bInGame == true)Green = true;
  if(Plane[ 8].m_bInGame == true)Green = true;if(Plane[10].m_bInGame == true)Green = true;
  if(Plane[12].m_bInGame == true)Green = true;if(Plane[14].m_bInGame == true)Green = true;

  if(Plane[ 1].m_bInGame == true)Red = true;if(Plane[ 3].m_bInGame == true)Red = true;
  if(Plane[ 5].m_bInGame == true)Red = true;if(Plane[ 7].m_bInGame == true)Red = true;
  if(Plane[ 9].m_bInGame == true)Red = true;if(Plane[11].m_bInGame == true)Red = true;
  if(Plane[13].m_bInGame == true)Red = true;if(Plane[15].m_bInGame == true)Red = true;

  m_fPrepareTimer -= (float)Engine->Timer.GetDeltaMs() * 0.001f;

  if(Green == false || Red == false)
    {
    m_fPrepareTimer = 3.0f;
    }

  if(m_fPrepareTimer <= 0.0 && Green == true && Red == true)
    {
		for(i = 0;i < 16;i++)
		{
			for(int ii=0;ii < 16;ii++)Player[i].m_bHitMe[ii] = false;
		}


    m_cGameState = GAME_STATE_GAMING;
	Server_Network_Send(PACKET_SERVER_GAMEBEGIN,Engine);
    }
  }

//------------------------------------------------------------------
void CGameHandler::Add_AI(bool Green,bool Red,bool Add)
//------------------------------------------------------------------
  {
	/*
  int i;
  //////////////////////
  //----- ADD AI -----//
  //////////////////////

  if(Add == true)
    {
    //----- Find Player ID -----//
    for(i=0;i< 16;i++)
      {
      if(Player[i].m_bActive == false)
        {
        Player[i].Init();
        Player[i].m_bActive = true;
        Player[i].m_bAI     = true;
        memcpy(Player[i].m_caName,"AI",8);
        Player[i].m_caName[8] = NULL;
        break;
        }
      }

    if(Green)
      {
      if((Player[i].m_iPlayerID = Join_Team(true,false)) != -1)
        {

        }
      else
        {
        Player[i].m_bActive = false;
        Player[i].m_bAI     = false;
        }
      }
    if(Red)
      {
      if((Player[i].m_iPlayerID = Join_Team(false,true)) != -1)
        {
        }
      else
        {
        Player[i].m_bActive = false;
        Player[i].m_bAI     = false;
        }
      }
    }

  //////////////////////
  //--- REMOVE AI ----//
  //////////////////////

  if(Add == false)
    {
    if(Green)
      {
      for(i=0;i< 16;i++)
        {
        if(((Player[i].m_iPlayerID % 2) == 0) && Player[i].m_bActive == true && Player[i].m_bAI == true)
          {
          Plane[Player[i].m_iPlayerID].m_bInGame  = false;
          Plane[Player[i].m_iPlayerID].m_bOcupied = false;
          Man[Player[i].m_iPlayerID].m_bActive    = false;
          Player[i].m_bActive = false;
          break;
          }
        }
      }
    if(Red)
      {
      for(i=1;i< 16;i++)
        {
        if(((Player[i].m_iPlayerID % 2) == 1) && Player[i].m_bActive == true && Player[i].m_bAI == true)
          {
          Plane[Player[i].m_iPlayerID].m_bInGame  = false;
          Plane[Player[i].m_iPlayerID].m_bOcupied = false;
          Man[Player[i].m_iPlayerID].m_bActive    = false;
          Player[i].m_bActive = false;
          break;
          }
        }
      }
    }
	*/
  }

//------------------------------------------------------------------
void CGameHandler::Collision_Draw(SEngine *Engine,float x,float y,float xSize,float ySize)
//------------------------------------------------------------------
  {
  glPushMatrix();

  glDisable(GL_TEXTURE_2D); 
  glDisable(GL_TEXTURE);
  glLoadIdentity();
  glTranslatef(x,y,-15.00);
  glColor3f(1.0f,1.0f,0.0f);
  glBegin(GL_LINE_STRIP);				
  glVertex3f(-xSize,+ySize,  0.0f);	
  glVertex3f(+xSize,+ySize,  0.0f);	
  glVertex3f(+xSize,-ySize,  0.0f);
  glVertex3f(-xSize,-ySize,  0.0f);
  glVertex3f(-xSize,+ySize,  0.0f);	
  glEnd();   	
  glColor3f(1.0f,1.0f,1.0f);
  glEnable(GL_TEXTURE);
  glEnable(GL_TEXTURE_2D);
  glPopMatrix();

  }

//------------------------------------------------------------------
bool CGameHandler::Collision_Detect(float x_1,float y_1,float x_Size,float y_Size,float x_2,float y_2,float x_2Size,float y_2Size)
//------------------------------------------------------------------
  {
  float xl1 = x_1 - x_Size;
  float xr1 = x_1 + x_Size;

  float xl2 = x_2 - x_2Size;
  float xr2 = x_2 + x_2Size;

  float yd1 = y_1 - y_Size;
  float yu1 = y_1 + y_Size;

  float yd2 = y_2 - y_2Size;
  float yu2 = y_2 + y_2Size;

  //          2    
  //
  //          1
  //
  //   -2 -1  0  1  2
  //                              xl1  xr1       
  //         -1                 yu1+-----+
  //                               |     |
  //         -2                    |  O  |
  //                               |     |
  //                            yd1+-----+
  //
  //
  //
  //                                      xl2  xr2       
  //                                    yu2+-----+
  //                                       |     |
  //                                       |  O  |
  //                                       |     |
  //                                    yd2+-----+

  if(xr1 > xl2 && xl1 < xr2)
    {
    if(yd1 < yu2 && yu1 > yd2)
      {
      return true;
      }
    }
  return false;
  }

//------------------------------------------------------------------
void CGameHandler::Collision_Handle_Draw(SEngine *Engine)
//------------------------------------------------------------------
  {
  if(m_bCOLLISION_Show == false)return;

  int i;

  for(i = 0;i < 16;i++)
    {
    if(Plane[i].m_bInGame   == true)Collision_Draw(Engine,Plane[i].m_fx,Plane[i].m_fy,Plane[i].m_fSize,Plane[i].m_fSize);
    if(Fire[i].m_bActive    == true)Collision_Draw(Engine,Fire[i].m_fx ,Fire[i].m_fy ,Fire[i].m_fSize,Fire[i].m_fSize);
    if(Spec[i].m_bActive    == true)Collision_Draw(Engine,Spec[i].m_fx,Spec[i].m_fy,Spec[i].m_fSize,Spec[i].m_fSize);
    if(Man[i].m_bActive     == true)Collision_Draw(Engine,Man[i].m_fx,Man[i].m_fy,Man[i].m_fSize,Man[i].m_fSize);
    if(Missile[i].m_bUsed   == true)Collision_Draw(Engine,Missile[i].m_fx,Missile[i].m_fy,Missile[i].m_fSize,Missile[i].m_fSize);
    }

  if(Sky[0].m_bActive == true)Collision_Draw(Engine,Sky[0].m_fX,Sky[0].m_fY,Sky[0].m_fSize,Sky[0].m_fSize);
  if(Sky[1].m_bActive == true)Collision_Draw(Engine,Sky[1].m_fX,Sky[1].m_fY,Sky[1].m_fSize,Sky[1].m_fSize);
  if(Sky[2].m_bActive == true)Collision_Draw(Engine,Sky[2].m_fX,Sky[2].m_fY,Sky[2].m_fSize,Sky[2].m_fSize);

  if(Animal[0].m_bActive == true)Collision_Draw(Engine,Animal[0].m_fX,-5.95f,Animal[0].m_fSize,Animal[0].m_fSize);
  if(Animal[1].m_bActive == true)Collision_Draw(Engine,Animal[1].m_fX,-5.95f,Animal[1].m_fSize,Animal[1].m_fSize);
  }

//------------------------------------------------------------------
void CGameHandler::Collision_Handle(SEngine *Engine)
//------------------------------------------------------------------
  {
  int i,ii;

  //////////////////////////////////////////////
  //////////////////////////////////////////////
  //--------------- COLLISION ----------------//
  //////////////////////////////////////////////
  //////////////////////////////////////////////

  //////////////////////////////////////////////
  //----------- COLLISION WITH FIRE ----------//
  //////////////////////////////////////////////

  for(i = 0;i < 16;i++)
    {
    if(Fire[i].m_bActive == true)
      {
      ////////////////////////////////////
      //----- Collision with Plane -----//
      ////////////////////////////////////

      for(ii = 0;ii < 16;ii++)
        {
        if(i == ii || Plane[ii].m_bInGame == false || Plane[ii].m_cDamage == PLANE_DAMAGE_APART || Plane[ii].m_cDamage == PLANE_DAMAGE_CRASHED)continue;

        if(Collision_Detect(Fire[i].m_fx,Fire[i].m_fy,Fire[i].m_fSize,Fire[i].m_fSize,Plane[ii].m_fx,Plane[ii].m_fy,Plane[ii].m_fSize,Plane[ii].m_fSize))
          {
          char Owner = Find_Owner(i);
          char Target_Owner = Find_Owner(ii);

			if(Man[i].m_cSittingBackPlane == ii)continue;

          Add_ToStats(Target_Owner,Owner,1,Engine);
		  Player[Target_Owner].m_bHitMe[Owner] = true;

          if(Owner != -1 && Target_Owner != -1)
            {
            if((i % 2) == (ii % 2))
              {
              Player[Owner].m_iHits--;
              Player[Owner].m_iPunish++;
              }
            else
              {
              Player[Owner].m_iHits++;
              Player[Owner].m_iMoney += MONEY_PER_HIT;
              }
            if(Player[Owner].m_cUpgrade_Fire > 1)Plane[ii].Hit(this,ii,1,i,Engine);

            char Rand_Sound = rand()%4;
            if(Rand_Sound == 0)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Hit1);
            if(Rand_Sound == 1)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Hit2);
            if(Rand_Sound == 2)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Hit3);
            if(Rand_Sound == 3)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Hit4);
            }

          Fire[i].m_bActive = false;
          Plane[ii].Hit(this,ii,1,i,Engine);

          }
        }
      /////////////////////////////////////
      //----- Collision with Animal -----//
      /////////////////////////////////////
      for(ii = 0;ii < 2;ii++)
        {
        if(Animal[ii].m_bActive == false || Animal[ii].m_bDead == true)continue;

        if(Collision_Detect(Fire[i].m_fx,Fire[i].m_fy,Fire[i].m_fSize,Fire[i].m_fSize,Animal[ii].m_fX,-5.95f,Animal[ii].m_fSize,Animal[ii].m_fSize))
          {

          Fire[i].m_bActive  = false;
          Animal[ii].m_bDead = true;

          if(Animal[ii].m_cType != 3)
		  {
	          FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Animal_Hit);			
          char Owner = Find_Owner(i);
          if(Owner != -1)
            {
            Player[Owner].m_iMoney += 25;
            }
		  }

          Server_Network_AnimalCollision(ii,i,Engine);

          }
        }


    //////////////////////////////////////
    //----- Collision with SeaGull -----//
    //////////////////////////////////////

    for(ii = 0;ii < 9;ii++)
      {
      if(SeaGull[ii].m_bActive == true && SeaGull[ii].m_bDead == false)
        {
        if(Collision_Detect(SeaGull[ii].m_fX,SeaGull[ii].m_fY,SeaGull[ii].m_fSize,SeaGull[ii].m_fSize,Fire[i].m_fx,Fire[i].m_fy,Fire[i].m_fSize,Fire[i].m_fSize))
          {
			Fire[i].m_bActive  = false;
			SeaGull[ii].m_bDead = true;
			SeaGull[ii].m_bWake = true;

			SeaGull[ii].m_fX      = Fire[i].m_fx;
			SeaGull[ii].m_fY      = Fire[i].m_fy;
			SeaGull[ii].m_fRotate = Fire[i].m_fRotate;
			SeaGull[ii].m_fSpeed  = 2.0f * 1.5f;

			  Server_Network_SeaGullShotHit(ii,1,i,Engine);
          }
        }
      }

      ////////////////////////////////////
      //----- Collision with Spec  -----//
      ////////////////////////////////////
      for(ii = 0;ii < 16;ii++)
        {
        if(i == ii || Spec[ii].m_bActive == false)continue;

        if(Collision_Detect(Fire[i].m_fx,Fire[i].m_fy,Fire[i].m_fSize,Fire[i].m_fSize,Spec[ii].m_fx,Spec[ii].m_fy,Spec[ii].m_fSize,Spec[ii].m_fSize))
          {
			if((Spec[ii].m_cType-1) >= Fire[i].m_cType)
			{
		      Fire[i].m_bActive  = false;
			  Server_Network_RemoveShot(1,i,Engine);
			}

          //Spec[ii].m_bActive = false;
          }
        }
/*
      //////////////////////////////////////
      //----- Collision with Missile -----//
      //////////////////////////////////////

      for(ii = 0;ii < 16;ii++)
        {
        if(i == ii || Missile[ii].m_bDead == true || Missile[ii].m_bUsed == false)continue;

        if(Collision_Detect(Fire[i].m_fx,Fire[i].m_fy,Fire[i].m_fSize,Fire[i].m_fSize,Missile[ii].m_fx,Missile[ii].m_fy,Missile[ii].m_fSize,Missile[ii].m_fSize))
          {
          Fire[i].m_bActive  = false;
          Missile[ii].m_bDead = true;
          }
        }
*/

      //////////////////////////////////////
      //-----   Collision with Map   -----//
      //////////////////////////////////////

      for(ii = 0;ii < 15;ii++)
        {
        if(Collision_Detect(Fire[i].m_fx,Fire[i].m_fy,Fire[i].m_fSize,Fire[i].m_fSize,8.0f+(-1.20f*ii),-6.10f,0.6f,0.05f))
          {
          Fire[i].m_bActive           = false;
          Map.m_baField_Destroyed[ii] = true;

		  Server_Network_IceMelt(ii,i,Engine);
          }
        }

      //////////////////////////////////////
      //----- Collision with Man/Para ----//
      //////////////////////////////////////

      for(ii = 0;ii < 16;ii++)
        {
        if(i == ii || Man[ii].m_bActive == false || Man[ii].m_cStatus == MAN_STATUS_DEAD)continue;

        if(Collision_Detect(Fire[i].m_fx,Fire[i].m_fy,Fire[i].m_fSize,Fire[i].m_fSize,Man[ii].m_fx,Man[ii].m_fy,Man[ii].m_fSize,Man[ii].m_fSize))
          {
          char Owner = Find_Owner(i);
          char Target_Owner = Find_Owner(ii);

          Add_ToStats(Target_Owner,Owner,1,Engine);
		  Player[Target_Owner].m_bHitMe[Owner] = true;

          if(Owner != -1 && Target_Owner != -1 && Man[ii].m_cType != 5)
            {
            if((i % 2) == (ii % 2))
              {
              Player[Owner].m_iHits--;
              Player[Owner].m_iPunish++;
              }
            else
              {
              Player[Owner].m_iHits++;
              Player[Owner].m_iMoney += MONEY_PER_HIT;
              }
            }
          Fire[i].m_bActive  = false;
          Man[ii].m_fRotate = Fire[i].m_fRotate;
          Man[ii].m_fSpeed  = /*Fire[i].m_fSpeed*/ 2.0f * 1.5f;
          Man[ii].m_fSpeedBx  = /*Fire[i].m_fSpeed*/ 2.0f * 1.5f;
          if(Man[ii].m_cType != 5 || Man[ii].m_cStatus != MAN_STATUS_FLYING)Man[ii].m_cStatus = MAN_STATUS_DEAD;

		  Server_Network_ManParaHit(1,ii,i,Engine);

          char Rand_Sound = rand()%7;
          if(Rand_Sound == 0)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die01);
          if(Rand_Sound == 1)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die02);
          if(Rand_Sound == 2)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die03);
          if(Rand_Sound == 3)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die04);
          if(Rand_Sound == 4)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die05);
          if(Rand_Sound == 5)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die06);
          if(Rand_Sound == 6)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die07);
          }
        }
      }
    }
  //////////////////////////////////////////////
  //----------- COLLISION WITH Spec ----------//
  //////////////////////////////////////////////

  for(i = 0;i < 16;i++)
    {
    if(Spec[i].m_bActive == true)
      {
      ////////////////////////////////////
      //----- Collision with Plane -----//
      ////////////////////////////////////

      for(ii = 0;ii < 16;ii++)
        {
        if(i == ii || Plane[ii].m_bInGame == false || Plane[ii].m_cDamage == PLANE_DAMAGE_APART || Plane[ii].m_cDamage == PLANE_DAMAGE_CRASHED)continue;

        if(Collision_Detect(Spec[i].m_fx,Spec[i].m_fy,Spec[i].m_fSize,Spec[i].m_fSize,Plane[ii].m_fx,Plane[ii].m_fy,Plane[ii].m_fSize,Plane[ii].m_fSize))
          {
          if(Man[i].m_cSittingBackPlane == ii)continue;

          Spec[i].m_bActive = false;

		  Server_Network_SpecHit(ii,i,Engine);

          char Owner = Find_Owner(i);
          char Target_Owner = Find_Owner(ii);
          Add_ToStats(Target_Owner,Owner,2,Engine);

          if(Spec[i].m_cType >= 5 && Plane[ii].m_bPilot == true)
            {
            Plane[ii].m_bPilot = false;
            Man[ii].JumpOut(Plane[ii].m_fx,Plane[ii].m_fy,Plane[ii].m_fSpeed,Plane[ii].m_fRotate);
            Server_Network_EjectFromPlane(ii,Engine);
			continue;
		  }
          if(Spec[i].m_cType >= 1)Plane[ii].m_fSpeed = 0.0f;
          if(Spec[i].m_cType >= 2)Plane[ii].m_bPoision_Soft_Active = true;
          if(Spec[i].m_cType >= 4)Plane[ii].m_bPoision_Hard_Active = true;

          FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Hit_Spec);
          }
        }
      /////////////////////////////////////
      //----- Collision with Animal -----//
      /////////////////////////////////////
      /*
      for(ii = 0;ii < 2;ii++)
        {
        if(Animal[ii].m_bActive == false || Animal[ii].m_bDead == true)continue;

		float fsize;

		if(Spec[i].m_bStun_Active)fsize = Spec[i].m_fSize+ ((1.0f) - (Spec[i].m_fStun));
		else					  fsize = Spec[i].m_fSize;

        if(Collision_Detect(Spec[i].m_fx,Spec[i].m_fy,fsize,fsize,Animal[ii].m_fX,-5.95f,Animal[ii].m_fSize,Animal[ii].m_fSize))
          {

          Spec[i].m_bActive  = false;
          Animal[ii].m_bDead = true;
          Server_Network_AnimalCollision(ii,i+30,Engine);
          if(Animal[ii].m_cType != 3)
		  {
	          FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Animal_Hit);			
          char Owner = Find_Owner(i);
          if(Owner != -1)
            {
            Player[Owner].m_iMoney += 25;
            }

		  }
          }
        }
*/
		
    //////////////////////////////////////
    //----- Collision with SeaGull -----//
    //////////////////////////////////////
/*
    for(ii = 0;ii < 9;ii++)
      {
      if(SeaGull[ii].m_bActive == true && SeaGull[ii].m_bDead == false)
        {
        if(Collision_Detect(SeaGull[ii].m_fX,SeaGull[ii].m_fY,SeaGull[ii].m_fSize,SeaGull[ii].m_fSize,Spec[i].m_fx,Spec[i].m_fy,Spec[i].m_fSize,Spec[i].m_fSize))
          {
			Spec[i].m_bActive  = false;
			SeaGull[ii].m_bDead = true;
			SeaGull[ii].m_bWake = true;

			SeaGull[ii].m_fX      = Spec[i].m_fx;
			SeaGull[ii].m_fY      = Spec[i].m_fy;
			SeaGull[ii].m_fRotate = Spec[i].m_fRotate;
			SeaGull[ii].m_fSpeed  = 2.0f * 1.5f;

			  Server_Network_SeaGullShotHit(ii,2,i,Engine);
          }
        }
      }		
		*/
		
		/*
      ////////////////////////////////////
      //----- Collision with Spec  -----//
      ////////////////////////////////////
      for(ii = 0;ii < 16;ii++)
        {
        if(i == ii || Spec[ii].m_bActive == false)continue;

        if(Collision_Detect(Spec[i].m_fx,Spec[i].m_fy,Spec[i].m_fSize,Spec[i].m_fSize,Spec[ii].m_fx,Spec[ii].m_fy,Spec[ii].m_fSize,Spec[ii].m_fSize))
          {
          Spec[i].m_bActive  = false;
          Spec[ii].m_bActive = false;

		  Server_Network_RemoveShot(3+ii,i,Engine);
          }
        }
*/
      //////////////////////////////////////
      //----- Collision with Missile -----//
      //////////////////////////////////////

      for(ii = 0;ii < 16;ii++)
        {
        if(i == ii || Missile[ii].m_bDead == true || Missile[ii].m_bUsed == false)continue;

        if(Collision_Detect(Spec[i].m_fx,Spec[i].m_fy,Spec[i].m_fSize,Spec[i].m_fSize,Missile[ii].m_fx,Missile[ii].m_fy,Missile[ii].m_fSize,Missile[ii].m_fSize))
          {
          //Spec[i].m_bActive  = false;
          Missile[ii].m_bDead = true;

  		  Server_Network_RemoveShot(2,ii,Engine);
          }
        }

      //////////////////////////////////////
      //----- Collision with Man/Para ----//
      //////////////////////////////////////
if(Spec[i].m_bStun_Active)
{
      for(ii = 0;ii < 16;ii++)
        {
        if(i == ii || Man[ii].m_bActive == false || Man[ii].m_cStatus == MAN_STATUS_DEAD)continue;

		float fsize;

		if(Spec[i].m_bStun_Active)fsize = Spec[i].m_fSize+ ((1.0f) - (Spec[i].m_fStun));
		else					  fsize = Spec[i].m_fSize;

        if(Collision_Detect(Spec[i].m_fx,Spec[i].m_fy,fsize,fsize,Man[ii].m_fx,Man[ii].m_fy,Man[ii].m_fSize,Man[ii].m_fSize))
          {
          char Owner = Find_Owner(i);
          char Target_Owner = Find_Owner(ii);

          Add_ToStats(Target_Owner,Owner,2,Engine);

		  Player[Target_Owner].m_bHitMe[Owner] = true;

          if(Owner != -1 && Target_Owner != -1 && Man[ii].m_cType != 5)
            {
            if((i % 2) == (ii % 2))
              {
              Player[Owner].m_iHits--;
              Player[Owner].m_iPunish++;
              }
            else
              {
              Player[Owner].m_iHits++;
              Player[Owner].m_iMoney += MONEY_PER_HIT;
              }
            }

          Spec[i].m_bActive  = false;
          Man[ii].m_fRotate = Spec[i].m_fRotate;
          Man[ii].m_fSpeed  = /*Fire[i].m_fSpeed*/ 2.0f * 1.5f;
		  Man[ii].m_fSpeedBx  = /*Fire[i].m_fSpeed*/ 2.0f * 1.5f;
          if(Man[ii].m_cType != 5 || Man[ii].m_cStatus != MAN_STATUS_FLYING)Man[ii].m_cStatus = MAN_STATUS_DEAD;

		  Server_Network_ManParaHit(2,ii,i,Engine);

          char Rand_Sound = rand()%7;
          if(Rand_Sound == 0)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die01);
          if(Rand_Sound == 1)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die02);
          if(Rand_Sound == 2)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die03);
          if(Rand_Sound == 3)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die04);
          if(Rand_Sound == 4)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die05);
          if(Rand_Sound == 5)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die06);
          if(Rand_Sound == 6)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die07);
          }
        }
      }
    }
}
  //////////////////////////////////////////////
  //--------- COLLISION WITH Missile ---------//
  //////////////////////////////////////////////

  for(i = 0;i < 16;i++)
    {
    if(Missile[i].m_bDead == false && Missile[i].m_bUsed == true)
      {
      ////////////////////////////////////
      //----- Collision with Plane -----//
      ////////////////////////////////////

      for(ii = 0;ii < 16;ii++)
        {
        if(Plane[ii].m_bInGame == false || Plane[ii].m_cDamage == PLANE_DAMAGE_APART || Plane[ii].m_cDamage == PLANE_DAMAGE_CRASHED)continue;

        if(Collision_Detect(Missile[i].m_fx,Missile[i].m_fy,Missile[i].m_fSize,Missile[i].m_fSize,Plane[ii].m_fx,Plane[ii].m_fy,Plane[ii].m_fSize,Plane[ii].m_fSize))
          {
          if(Man[i].m_cSittingBackPlane == ii)continue;

          char Owner = Find_Owner(i);
          char Target_Owner = Find_Owner(ii);

		  Player[Target_Owner].m_bHitMe[Owner] = true;

          if(i == ii && Missile[i].m_bPlasma == false)continue;

          Add_ToStats(Target_Owner,Owner,3,Engine);

          if(Owner != -1 && Target_Owner != -1)
            {
            if((i % 2) == (ii % 2))
              {
              Player[Owner].m_iHits--;
              Player[Owner].m_iPunish++;
              }
            else
              {
              Player[Owner].m_iHits++;
              Player[Owner].m_iMoney += MONEY_PER_HIT;
              }
            }
/*
          if(Missile[i].m_cType != 5)Missile[i].m_bDead = true;
          if(Missile[i].m_cType == 5)Missile[i].m_fFuel -= 1.0f;
*/
          if(Missile[i].m_bPlasma == false)Missile[i].m_bDead = true;

		  if(Missile[i].m_cType == 5)Plane[ii].Hit(this,ii,1,i+30,Engine);
          Plane[ii].Hit(this,ii,1,i+30,Engine);

          char Rand_Sound = rand()%4;
          if(Rand_Sound == 0)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Hit1);
          if(Rand_Sound == 1)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Hit2);
          if(Rand_Sound == 2)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Hit3);
          if(Rand_Sound == 3)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Hit4);
          }
        }
      /////////////////////////////////////
      //----- Collision with Animal -----//
      /////////////////////////////////////
      for(ii = 0;ii < 2;ii++)
        {
        if(Animal[ii].m_bActive == false || Animal[ii].m_bDead == true)continue;

        if(Collision_Detect(Missile[i].m_fx,Missile[i].m_fy,Missile[i].m_fSize,Missile[i].m_fSize,Animal[ii].m_fX,-5.95f,Animal[ii].m_fSize,Animal[ii].m_fSize))
          {

          if(Missile[i].m_bPlasma == false)Missile[i].m_bDead  = true;
          Animal[ii].m_bDead  = true;

          Server_Network_AnimalCollision(ii,i+60,Engine);

          if(Animal[ii].m_cType != 3)
		  {
	          FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Animal_Hit);			
          char Owner = Find_Owner(i);
          if(Owner != -1)
            {
            Player[Owner].m_iMoney += 25;
            }

		  }
          }
        }

		
    //////////////////////////////////////
    //----- Collision with SeaGull -----//
    //////////////////////////////////////

    for(ii = 0;ii < 9;ii++)
      {
      if(SeaGull[ii].m_bActive == true && SeaGull[ii].m_bDead == false)
        {
        if(Collision_Detect(SeaGull[ii].m_fX,SeaGull[ii].m_fY,SeaGull[ii].m_fSize,SeaGull[ii].m_fSize,Missile[i].m_fx,Missile[i].m_fy,Missile[i].m_fSize,Missile[i].m_fSize))
          {
			SeaGull[ii].m_bDead = true;
			SeaGull[ii].m_bWake = true;

			SeaGull[ii].m_fX      = Missile[i].m_fx;
			SeaGull[ii].m_fY      = Missile[i].m_fy;
			SeaGull[ii].m_fRotate = Missile[i].m_fRotate;
			SeaGull[ii].m_fSpeed  = 2.0f * 1.5f;

			  Server_Network_SeaGullShotHit(ii,3,i,Engine);
          }
        }
      }		
		


/*
      //////////////////////////////////////
      //----- Collision with Missile -----//
      //////////////////////////////////////

      for(ii = 0;ii < 16;ii++)
        {
        if(i == ii || Missile[ii].m_bDead == true || Missile[ii].m_bUsed == false)continue;

        if(Collision_Detect(Missile[i].m_fx,Missile[i].m_fy,Missile[i].m_fSize,Missile[i].m_fSize,Missile[ii].m_fx,Missile[ii].m_fy,Missile[ii].m_fSize,Missile[ii].m_fSize))
          {
          Missile[i].m_bDead  = true;
          Missile[ii].m_bDead = true;
          }
        }
*/
      //////////////////////////////////////
      //----- Collision with Man/Para ----//
      //////////////////////////////////////

      for(ii = 0;ii < 16;ii++)
        {
        if(Missile[i].m_bPlasma == true || i == ii || Man[ii].m_bActive == false || Man[ii].m_cStatus == MAN_STATUS_DEAD)continue;

        if(Collision_Detect(Missile[i].m_fx,Missile[i].m_fy,Missile[i].m_fSize,Missile[i].m_fSize,Man[ii].m_fx,Man[ii].m_fy,Man[ii].m_fSize,Man[ii].m_fSize))
          {
          char Owner = Find_Owner(i);
          char Target_Owner = Find_Owner(ii);

          Add_ToStats(Target_Owner,Owner,3,Engine);

		  Player[Target_Owner].m_bHitMe[Owner] = true;

          if(Owner != -1 && Target_Owner != -1)
            {
            if((i % 2) == (ii % 2))
              {
              Player[Owner].m_iHits--;
              Player[Owner].m_iPunish++;
              }
            else
              {
              Player[Owner].m_iHits++;
              Player[Owner].m_iMoney += MONEY_PER_HIT;
              }
            }
          //Missile[i].m_bDead = true;
          Man[ii].m_fRotate = Missile[i].m_fRotate;
          Man[ii].m_fSpeed  = /*Fire[i].m_fSpeed*/ 2.0f * 1.5f;
		  Man[ii].m_fSpeedBx  = /*Fire[i].m_fSpeed*/ 2.0f * 1.5f;
          if(Man[ii].m_cType != 5 || Man[ii].m_cStatus != MAN_STATUS_FLYING)Man[ii].m_cStatus = MAN_STATUS_DEAD;

		  Server_Network_ManParaHit(3,ii,i,Engine);

          char Rand_Sound = rand()%7;
          if(Rand_Sound == 0)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die01);
          if(Rand_Sound == 1)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die02);
          if(Rand_Sound == 2)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die03);
          if(Rand_Sound == 3)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die04);
          if(Rand_Sound == 4)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die05);
          if(Rand_Sound == 5)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die06);
          if(Rand_Sound == 6)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die07);
          }
        }
      }
    }
  //////////////////////////////////////////////
  //---------- COLLISION WITH Plane ----------//
  //////////////////////////////////////////////

  for(i = 0;i < 16;i++)
    {
    if(Plane[i].m_bInGame == true && Plane[i].m_cDamage != PLANE_DAMAGE_APART && (Plane[i].m_cDamage != PLANE_DAMAGE_CRASHED || Plane[i].m_fSpeed >= 0.2f))
      {
      ////////////////////////////////////
      //----- Collision with Plane -----//
      ////////////////////////////////////

      for(ii = 0;ii < 16;ii++)
        {
        if(i == ii || Plane[ii].m_bInGame == false || Plane[ii].m_cDamage == PLANE_DAMAGE_APART || Plane[ii].m_cDamage == PLANE_DAMAGE_CRASHED || Plane[i].m_cDamage == PLANE_DAMAGE_CRASHED)continue;
        if(Plane[i].m_cDamage  == PLANE_DAMAGE_APART)continue;
        if(Plane[ii].m_cDamage == PLANE_DAMAGE_APART)continue;

        if(Collision_Detect(Plane[i].m_fx,Plane[i].m_fy,Plane[i].m_fSize,Plane[i].m_fSize,Plane[ii].m_fx,Plane[ii].m_fy,Plane[ii].m_fSize,Plane[ii].m_fSize))
          {
          char Owner = Find_Owner(i);
          char Target_Owner = Find_Owner(ii);

          Add_ToStats(Target_Owner,Owner,5,Engine);

		  Plane[i].Hit (this,i ,1,-1,Engine);
          Plane[ii].Hit(this,ii,1,-1,Engine);

		  Plane[i].Hit (this,i ,4,-1,Engine);
          Plane[ii].Hit(this,ii,4,-1,Engine);

          FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Plane_Collision);
			}
        }
      /////////////////////////////////////
      //----- Collision with Animal -----//
      /////////////////////////////////////
      for(ii = 0;ii < 2;ii++)
        {
        if(Animal[ii].m_bActive == false || Animal[ii].m_bDead == true)continue;

        if(Collision_Detect(Plane[i].m_fx,Plane[i].m_fy,Plane[i].m_fSize,Plane[i].m_fSize,Animal[ii].m_fX,-5.95f,Animal[ii].m_fSize,Animal[ii].m_fSize))
          {

          Server_Network_AnimalCollision(ii,-1,Engine);

          Animal[ii].m_bDead  = true;
          if(Animal[ii].m_cType != 3)
		  {
	          FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Animal_Hit);			
          char Owner = Find_Owner(i);
          if(Owner != -1)
            {
            Player[Owner].m_iMoney += 25;
            }
		  }
		  else if(Animal[ii].m_cType == 3)
		  {
			 Plane[i].Hit (this,i ,1,-1,Engine);
			 Plane[i].Hit (this,i ,4,-1,Engine);
		  }
          }
        }

      //////////////////////////////////////
      //----- Collision with Man/Para ----//
      //////////////////////////////////////

      for(ii = 0;ii < 16;ii++)
        {
        if(i == ii || Man[ii].m_bActive == false || Man[ii].m_cStatus == MAN_STATUS_DEAD || Man[ii].m_cStatus == MAN_STATUS_BEHIND_PLANE)continue;

        if(Collision_Detect(Plane[i].m_fx,Plane[i].m_fy,Plane[i].m_fSize,Plane[i].m_fSize,Man[ii].m_fx,Man[ii].m_fy,Man[ii].m_fSize,Man[ii].m_fSize))
          {
          char Owner = Find_Owner(i);
          char Target_Owner = Find_Owner(ii);

          Add_ToStats(Target_Owner,Owner,4,Engine);

          if((Man[ii].m_cStatus == MAN_STATUS_GROUND || Man[ii].m_cStatus == MAN_STATUS_FLYING) && Plane[i].m_fSpeed <= 0.7f)
		  {
			Man[ii].m_cStatus = MAN_STATUS_BEHIND_PLANE;
			Man[ii].m_cSittingBackPlane = i;

			Server_Network_PlanePickUp(i,ii,Engine);

			continue;
		  }

		  Player[Target_Owner].m_bHitMe[Owner] = true;

          if(Owner != -1 && Target_Owner != -1 && Man[ii].m_cType != 5)
            {
            if((i % 2) == (ii % 2))
              {
              Player[Owner].m_iHits--;
              Player[Owner].m_iPunish++;
              }
            else
              {
              Player[Owner].m_iHits++;
              Player[Owner].m_iMoney += MONEY_PER_HIT;
              }
            }

          Man[ii].m_fRotate = Plane[i].m_fRotate;
          Man[ii].m_fSpeed  = /*Fire[i].m_fSpeed*/ 2.0f * 1.5f;
          Man[ii].m_fSpeedBx  = /*Fire[i].m_fSpeed*/ 2.0f * 1.5f;

		  if(Man[ii].m_cType != 5)
		  {
		    Man[ii].m_cSplash = i;
		    Man[ii].m_fManSlidingOf = 1.0f;

		 	  if(Man[ii].m_cStatus == MAN_STATUS_PARACHUTING)Man[ii].m_bSplashPara = true;
			  else Man[ii].m_bSplashPara = false;

				if(m_iNetWorkID != -1)
				{
				   if(i == Player[m_iNetWorkID].m_iPlayerID)
					  {
						  m_cManHit = ii;
					}
				 }		  
		  }

          if(Man[ii].m_cType != 5 || Man[ii].m_cStatus != MAN_STATUS_FLYING)Man[ii].m_cStatus = MAN_STATUS_DEAD;

		  Server_Network_ManParaHit(4,ii,i,Engine);

          char Rand_Sound = rand()%7;
          if(Rand_Sound == 0)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die01);
          if(Rand_Sound == 1)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die02);
          if(Rand_Sound == 2)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die03);
          if(Rand_Sound == 3)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die04);
          if(Rand_Sound == 4)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die05);
          if(Rand_Sound == 5)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die06);
          if(Rand_Sound == 6)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die07);
          }
        }

      }
    }

  //////////////////////////////////////////////
  //--------- COLLISION WITH Map Hole --------//
  //////////////////////////////////////////////
  if(Map.m_cMapType == MAP_TYPE_ICE || Map.m_cMapType == MAP_TYPE_ADV_GRASS)
    {
    for(i = 0;i < 15;i++)
      {
      if(Map.m_baField_Destroyed[i] == false)continue;


	  if(Map.m_cMapType == MAP_TYPE_ADV_GRASS)
	  {
		if(i ==  3)continue;
		if(i ==  4)continue;
		if(i == 10)continue;
		if(i == 11)continue;
	  }


      //////////////////////////////////////
      //----- Collision with Man/Para ----//
      //////////////////////////////////////

      for(ii = 0;ii < 16;ii++)
        {
        if(Man[ii].m_bActive == false || Man[ii].m_cStatus == MAN_STATUS_DEAD)continue;

        if(Man[ii].m_cStatus == MAN_STATUS_GROUND && Collision_Detect(8.0f+(-1.20f*i),-6.10f,0.6f,5.05f,Man[ii].m_fx,Man[ii].m_fy,Man[ii].m_fSize,Man[ii].m_fSize))
          {
          Man[ii].m_cStatus = MAN_STATUS_DEAD;
          Man[ii].m_fx      = 15.0f;

          char Target_Owner = Find_Owner(ii);
          Add_ToStats(Target_Owner,-1,4,Engine);

		  Server_Network_ManParaHit(-1,ii,-1,Engine);
          }
        }

      /////////////////////////////////////
      //----- Collision with Animal -----//
      /////////////////////////////////////

      for(ii = 0;ii < 2;ii++)
        {
        if(Animal[ii].m_cType == 3 || Animal[ii].m_bActive == false || Animal[ii].m_bDead == true)continue;

        if(Collision_Detect(8.0f+(-1.20f*i),-6.10f,0.6f,5.05f,Animal[ii].m_fX,-5.95f,Animal[ii].m_fSize,Animal[ii].m_fSize))
          {
          Animal[ii].m_bDead  = true;
          Animal[ii].m_fX     = 15.0f;

          Server_Network_AnimalCollision(ii,-2,Engine);
          }
        }
      }
    }

  //////////////////////////////////////////////
  //--------- COLLISION WITH Animals ---------//
  //////////////////////////////////////////////
  for(i = 0;i < 2;i++)
    {
    //////////////////////////////////////
    //----- Collision with Man/Para ----//
    //////////////////////////////////////

    for(ii = 0;ii < 16;ii++)
      {
      if(Man[ii].m_bActive == false || Man[ii].m_cStatus == MAN_STATUS_DEAD)continue;

      if(Animal[i].m_bActive == true && Animal[i].m_bDead == false && (Animal[i].m_cType == 1 || Animal[i].m_cType == 3))
        {
        if(Collision_Detect(Animal[i].m_fX,-5.95f+(Animal[i].m_fJump*0.75f),Animal[i].m_fSize,Animal[i].m_fSize,Man[ii].m_fx,Man[ii].m_fy,Man[ii].m_fSize,Man[ii].m_fSize))
          {
          if(Man[ii].m_cType != 5 || Man[ii].m_cStatus != MAN_STATUS_FLYING)Man[ii].m_cStatus = MAN_STATUS_DEAD;

          char Target_Owner = Find_Owner(ii);
          Add_ToStats(Target_Owner,-1,4,Engine);

		  Server_Network_ManParaHit(-2,ii,-1,Engine);

          char Rand_Sound = rand()%7;
          if(Rand_Sound == 0)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die01);
          if(Rand_Sound == 1)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die02);
          if(Rand_Sound == 2)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die03);
          if(Rand_Sound == 3)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die04);
          if(Rand_Sound == 4)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die05);
          if(Rand_Sound == 5)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die06);
          if(Rand_Sound == 6)FSOUND_PlaySound(FSOUND_FREE,m_sData.Snd_Man_Die07);
          }
        }
      }
    }
  //////////////////////////////////////////////
  //--------- COLLISION WITH SeaGull ---------//
  //////////////////////////////////////////////
  for(i = 0;i < 9;i++)
    {
    //////////////////////////////////////
    //------ Collision with Plane ------//
    //////////////////////////////////////

	  //--------------- Hit SeaGull ------------------//
    for(ii = 0;ii < 16;ii++)
      {
      if(Plane[ii].m_bInGame == false || Plane[ii].m_cDamage == PLANE_DAMAGE_APART || Plane[ii].m_cDamage == PLANE_DAMAGE_CRASHED)continue;

      if(SeaGull[i].m_bActive == true && (SeaGull[i].m_bDead == false || SeaGull[i].m_cWhoHittedMe != ii))
        {
        if(Collision_Detect(SeaGull[i].m_fX,SeaGull[i].m_fY,SeaGull[i].m_fSize,SeaGull[i].m_fSize,Plane[ii].m_fx,Plane[ii].m_fy,Plane[ii].m_fSize,Plane[ii].m_fSize))
          {
          Plane[ii].Hit(this,ii,1,-1,Engine);
          SeaGull[i].m_bDead = true;

			SeaGull[i].m_fGullSliding = 6.8f;
			SeaGull[i].m_cType = (rand()%2)+1;
			SeaGull[i].m_bGullSplash = true;
			SeaGull[i].m_cWhoHittedMe = ii;

		  Server_Network_SeaGullPlaneHit(ii,i,Engine);
          }
        }
      }
	  //--------------- Wake SeaGull ------------------//
    for(ii = 0;ii < 16;ii++)
      {
      if(Plane[ii].m_bInGame == false || Plane[ii].m_cDamage == PLANE_DAMAGE_APART || Plane[ii].m_cDamage == PLANE_DAMAGE_CRASHED)continue;

      if(SeaGull[i].m_bActive == true && SeaGull[i].m_bDead == false && SeaGull[i].m_bWake == false)
        {
        if(Collision_Detect(SeaGull[i].m_fX,SeaGull[i].m_fY,SeaGull[i].m_fSize + 1.5f,SeaGull[i].m_fSize + 1.5f,Plane[ii].m_fx,Plane[ii].m_fy,Plane[ii].m_fSize,Plane[ii].m_fSize))
          {
			SeaGull[i].m_fDX = (((rand()%1400)-700)*0.01f);
			SeaGull[i].m_fDY = (((rand()%1300)-500)*0.01f);
			SeaGull[i].m_bWake = true;

			  Server_Network_SeaGullMove(i,SeaGull[i].m_fDX,SeaGull[i].m_fDY,Engine);
          }
        }
      }
	  //--------------- Wake SeaGull ------------------//
    for(ii = 0;ii < 16;ii++)
      {
      if(Man[ii].m_bActive == false)continue;

      if(SeaGull[i].m_bActive == true && SeaGull[i].m_bDead == false && SeaGull[i].m_bWake == false)
        {
        if(Collision_Detect(SeaGull[i].m_fX,SeaGull[i].m_fY,SeaGull[i].m_fSize + 1.5f,SeaGull[i].m_fSize + 1.5f,Man[ii].m_fx,Man[ii].m_fy,Man[ii].m_fSize,Man[ii].m_fSize))
          {
			SeaGull[i].m_fDX = (((rand()%1400)-700)*0.01f);
			SeaGull[i].m_fDY = (((rand()%1300)-500)*0.01f);
			SeaGull[i].m_bWake = true;

			  Server_Network_SeaGullMove(i,SeaGull[i].m_fDX,SeaGull[i].m_fDY,Engine);
          }
        }
      }
  
  
  
  }




  }

//------------------------------------------------------------------
void CGameHandler::Draw_Score(SEngine *Engine)
//------------------------------------------------------------------
  {
  char Temp_Text[64];

  sprintf(Temp_Text,"Money: %05i Hits: %03i",Player[m_iNetWorkID].m_iMoney,Player[m_iNetWorkID].m_iHits);
  Engine->OpenGl_Font.glPrint(400,450,Temp_Text,1);
  }

//------------------------------------------------------------------
void CGameHandler::Draw_Names(SEngine *Engine)
//------------------------------------------------------------------
  {
  char Temp_Text[32];

  for(int i=0;i< 16;i++)
    {
    if(Player[i].m_bActive == true && Player[i].m_iPlayerID != -1)
      {
		if(m_iNetWorkID != -1 && i != m_iNetWorkID){if(Player[m_iNetWorkID].m_bHitMe[i] == true)glColor3f(1.0f,0.0f,0.0f);}

      if((Player[i].m_iPlayerID % 2) == 0)
        {
        Engine->OpenGl_Font.glPrint( 70,425-((Player[i].m_iPlayerID-0)*29),Player[i].m_caName,1);
        sprintf(Temp_Text,"Hits: %d",Player[i].m_iHits);
        Engine->OpenGl_Font.glPrint( 70,405-((Player[i].m_iPlayerID-0)*29),Temp_Text,1);
        }
      if((Player[i].m_iPlayerID % 2) == 1)
        {
        Engine->OpenGl_Font.glPrint(350,425-((Player[i].m_iPlayerID-1)*29),Player[i].m_caName,1);
        sprintf(Temp_Text,"Hits: %d",Player[i].m_iHits);
        Engine->OpenGl_Font.glPrint(350,405-((Player[i].m_iPlayerID-1)*29),Temp_Text,1);
        }
	  if(m_iNetWorkID != -1 && i != m_iNetWorkID){if(Player[m_iNetWorkID].m_bHitMe[i] == true)glColor3f(1.0f,1.0f,1.0f);}
	}
    }
  }

//------------------------------------------------------------------
bool CGameHandler::Check_GameOver()
//------------------------------------------------------------------
  {
  int  Green = 0
      ,Red   = 0;
  int  i;

  for(i=0;i < 16;i++) // Green Check
    {
    if(Player[i].m_bActive == true && Player[i].m_iPlayerID != -1)
      {
      if((Player[i].m_iPlayerID % 2) == 0) // Green
        {
        if(Plane[Player[i].m_iPlayerID].m_bInGame != false && Plane[Player[i].m_iPlayerID].m_bPilot == true && Plane[Player[i].m_iPlayerID].m_cDamage != PLANE_DAMAGE_CRASHED && Plane[Player[i].m_iPlayerID].m_cDamage != PLANE_DAMAGE_APART || (Man[Player[i].m_iPlayerID].m_cStatus != MAN_STATUS_DEAD && Plane[Player[i].m_iPlayerID].m_bPilot == false))
          {
          Green++;
          }
        }
      if((Player[i].m_iPlayerID % 2) == 1) // Red
        {
        if(Plane[Player[i].m_iPlayerID].m_bInGame != false && Plane[Player[i].m_iPlayerID].m_bPilot == true && Plane[Player[i].m_iPlayerID].m_cDamage != PLANE_DAMAGE_CRASHED && Plane[Player[i].m_iPlayerID].m_cDamage != PLANE_DAMAGE_APART || (Man[Player[i].m_iPlayerID].m_cStatus != MAN_STATUS_DEAD && Plane[Player[i].m_iPlayerID].m_bPilot == false))
          {
          Red++;
          }
        }
      }
    }

  if(Green == 0 || Red == 0)
    {
    if(Green == 0)
      {
      Red_Score++;
	  m_bGreenWin = false;
      for(i=0;i< 16;i++)
        {
        if(Player[i].m_bActive == true && Player[i].m_iPlayerID != -1 && (Player[i].m_iPlayerID % 2) == 1)Player[i].m_iMoney += 150;
        }
      }

    if(Red   == 0)
      {
      Green_Score++;
  	  m_bGreenWin = true;
      for(i=0;i< 16;i++)
        {
        if(Player[i].m_bActive == true && Player[i].m_iPlayerID != -1 && (Player[i].m_iPlayerID % 2) == 0)Player[i].m_iMoney += 150;
        }
      }

    for(i=0;i < 16;i++)
      {
      if(Player[i].m_bActive == true && Player[i].m_iPlayerID != -1)
        {
        Plane[Player[i].m_iPlayerID].m_fPoision    = 0.0f;
        Plane[Player[i].m_iPlayerID].m_fTop_Punish = 0.0f;

		Plane[Player[i].m_iPlayerID].m_bPoision_Soft_Active = false;
		Plane[Player[i].m_iPlayerID].m_bPoision_Hard_Active = false;

        Player[i].m_iMoney += 300;
        if(Plane[Player[i].m_iPlayerID].m_bInGame != false && Plane[Player[i].m_iPlayerID].m_bPilot == true && Plane[Player[i].m_iPlayerID].m_cDamage != PLANE_DAMAGE_CRASHED && Plane[Player[i].m_iPlayerID].m_cDamage != PLANE_DAMAGE_APART || (Man[Player[i].m_iPlayerID].m_cStatus != MAN_STATUS_DEAD && Plane[Player[i].m_iPlayerID].m_bPilot == false))
          {
          Player[i].m_iMoney += 150;
          }
        else
          {
          Player[i].m_cUpgrade_Plane   = 0;
          Player[i].m_cUpgrade_Para    = 0;
          Player[i].m_cUpgrade_Fire    = 0;
          Player[i].m_cUpgrade_Spec    = 0;
          Player[i].m_cUpgrade_Missile = 0;
          }
        }
      }

    return true;
    }

  return false;
  }

//------------------------------------------------------------------
void CGameHandler::Ping_MasterServer(SEngine *Engine)
//------------------------------------------------------------------
  {
  m_fMasterServerTimer -= (float)Engine->Timer.GetDeltaMs() * 0.001f;
 
  if(m_fMasterServerTimer <= 0.0f)
    {
    m_fMasterServerTimer = 30.0f;

    char TempText[128];
    int  Players = 0,i;
    for(i=0;i < 16;i++){if(Player[i].m_bActive == true && Player[i].m_iPlayerID != -1)Players++;}

    sprintf(TempText,"DF3/server.php?Port=%d&Players=%02i&Version=1001",Engine->m_sSettings.Port,Players);
    Engine->Internet.InitInternet();
    Engine->Internet.Connect("www.logicwork.net",TempText);
    Engine->Internet.DeInitInternet();
    }
  }

//------------------------------------------------------------------
void CGameHandler::BuyMenu_Draw(SEngine *Engine)
//------------------------------------------------------------------
  {
  glPushMatrix();							
  glTranslatef(0.0f,-0.0f,-15.0f);

  glBindTexture(GL_TEXTURE_2D,m_sData.Tex_Buy_Menu.texID);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0f,-2.0f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+4.0f,-2.0f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+4.0f,+2.0f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.0f,+2.0f,-0.0f);	
  glEnd();

  glPopMatrix();

  ///////////////////////////////////////////////////
  //            Draw Plane - Upgrade               //
  ///////////////////////////////////////////////////
  //////////////////////////////////
  //----- New Research Thing -----//
  //////////////////////////////////

  glPushMatrix();							
  glTranslatef(-3.08f,+0.35f,-15.0f);

  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 0)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Plane_Speed.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Plane_Shield.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 2)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Plane_TurnRate.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 3)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Plane_Stealth.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 4)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Full.texID);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.45f,-0.45f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.45f,-0.45f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.45f,+0.45f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.45f,+0.45f,-0.0f);	
  glEnd();

  glPopMatrix();

  //////////////////////////////////////
  //----- Current Research Thing -----//
  //////////////////////////////////////

  glPushMatrix();							
  glTranslatef(-3.08f,-0.75f,-15.0f);

  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 0)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Plane_Normal.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Plane_Speed.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 2)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Plane_Shield.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 3)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Plane_TurnRate.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 4)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Plane_Stealth.texID);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.45f,-0.45f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.45f,-0.45f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.45f,+0.45f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.45f,+0.45f,-0.0f);	
  glEnd();

  glPopMatrix();

  ///////////////////////////////////////////////////
  //            Draw Para  - Upgrade               //
  ///////////////////////////////////////////////////
  //////////////////////////////////
  //----- New Research Thing -----//
  //////////////////////////////////

  if(Player[m_iNetWorkID].m_cUpgrade_Para == 0)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Para_Normal.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Para_Faster.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 2)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Para_QuickMove.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 3)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Para_Stealth.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 4)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Para_Ball.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 5)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Full.texID);

  glPushMatrix();							
  glTranslatef(-1.53f,+0.35f,-15.0f);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.45f,-0.45f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.45f,-0.45f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.45f,+0.45f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.45f,+0.45f,-0.0f);	
  glEnd();

  glPopMatrix();

  //////////////////////////////////////
  //----- Current Research Thing -----//
  //////////////////////////////////////

  glPushMatrix();							
  glTranslatef(-1.53f,-0.75f,-15.0f);

  if(Player[m_iNetWorkID].m_cUpgrade_Para == 0)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_None.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Para_Normal.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 2)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Para_Faster.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 3)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Para_QuickMove.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 4)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Para_Stealth.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 5)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Para_Ball.texID);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.45f,-0.45f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.45f,-0.45f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.45f,+0.45f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.45f,+0.45f,-0.0f);	
  glEnd();

  glPopMatrix();

  ///////////////////////////////////////////////////
  //            Draw Fire  - Upgrade               //
  ///////////////////////////////////////////////////
  //////////////////////////////////
  //----- New Research Thing -----//
  //////////////////////////////////

  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 0)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Fire_Faster.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Fire_Damagex2.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 2)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Fire_Sizex2.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 3)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Fire_Stealth.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 4)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Full.texID);

  glPushMatrix();							
  glTranslatef(0.0f,+0.35f,-15.0f);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.45f,-0.45f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.45f,-0.45f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.45f,+0.45f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.45f,+0.45f,-0.0f);	
  glEnd();

  glPopMatrix();

  //////////////////////////////////////
  //----- Current Research Thing -----//
  //////////////////////////////////////

  glPushMatrix();							
  glTranslatef(-0.0f,-0.75f,-15.0f);

  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 0)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Fire_Normal.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Fire_Faster.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 2)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Fire_Damagex2.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 3)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Fire_Sizex2.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 4)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Fire_Stealth.texID);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.45f,-0.45f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.45f,-0.45f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.45f,+0.45f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.45f,+0.45f,-0.0f);	
  glEnd();

  glPopMatrix();

  ///////////////////////////////////////////////////
  //            Draw Spec  - Upgrade               //
  ///////////////////////////////////////////////////
  //////////////////////////////////
  //----- New Research Thing -----//
  //////////////////////////////////

  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 0)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Spec_Invert.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Spec_Poision.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 2)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Spec_Stun.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 3)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Spec_Adv_Poision.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 4)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Spec_AutoJump.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 5)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Full.texID);

  glPushMatrix();							
  glTranslatef(1.53f,+0.35f,-15.0f);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.45f,-0.45f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.45f,-0.45f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.45f,+0.45f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.45f,+0.45f,-0.0f);	
  glEnd();

  glPopMatrix();

  //////////////////////////////////////
  //----- Current Research Thing -----//
  //////////////////////////////////////

  glPushMatrix();							
  glTranslatef(1.53f,-0.75f,-15.0f);

  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 0)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_None.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Spec_Invert.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 2)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Spec_Poision.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 3)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Spec_Stun.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 4)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Spec_Adv_Poision.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 5)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Spec_AutoJump.texID);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.45f,-0.45f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.45f,-0.45f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.45f,+0.45f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.45f,+0.45f,-0.0f);	
  glEnd();

  glPopMatrix();

  ///////////////////////////////////////////////////
  //          Draw Missile - Upgrade               //
  ///////////////////////////////////////////////////
  //////////////////////////////////
  //----- New Research Thing -----//
  //////////////////////////////////

  glPushMatrix();							
  glTranslatef(3.08f,+0.35f,-15.0f);

  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 0)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Missile_Normal.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Missile_L_Guided.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 2)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Missile_Guided.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 3)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Missile_Angry.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 4)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Missile_Bounce.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 5)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Missile_Plasma.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 6)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Full.texID);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.45f,-0.45f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.45f,-0.45f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.45f,+0.45f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.45f,+0.45f,-0.0f);	
  glEnd();

  glPopMatrix();

  //////////////////////////////////////
  //----- Current Research Thing -----//
  //////////////////////////////////////

  glPushMatrix();							
  glTranslatef(3.08f,-0.75f,-15.0f);

  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 0)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_None.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Missile_Normal.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 2)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Missile_L_Guided.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 3)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Missile_Guided.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 4)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Missile_Angry.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 5)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Missile_Bounce.texID);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 6)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_BuyMenu_Missile_Plasma.texID);

  glBegin(GL_QUADS);						
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.45f,-0.45f,+0.0f);	
  glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.45f,-0.45f,+0.0f);
  glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.45f,+0.45f,-0.0f);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.45f,+0.45f,-0.0f);	
  glEnd();

  glPopMatrix();

  ///////////////////////////////////////////////////
  //              Draw Money/Watch                 //
  ///////////////////////////////////////////////////

  char TempText[32];

  sprintf(TempText,"%02d",(int)m_fBuyMenuTimer);
  Engine->OpenGl_Font.glPrint(298,300,TempText,1);
  sprintf(TempText,"%05d",Player[m_iNetWorkID].m_iMoney);
  Engine->OpenGl_Font.glPrint(337,300,TempText,1);

  //--- Plane ---//
  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 0)strcpy(TempText,"500");
  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 1)strcpy(TempText,PLANE_SHIELD_PRICE_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 2)strcpy(TempText,"1500");
  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 3)strcpy(TempText,"2000");
  if(Player[m_iNetWorkID].m_cUpgrade_Plane == 4)strcpy(TempText,"----");
  Engine->OpenGl_Font.glPrint(180,173,TempText,1);
  //--- Para ---//
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 0)strcpy(TempText,PARA_PRICE_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 1)strcpy(TempText,PARA2_PRICE_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 2)strcpy(TempText,PARA3_PRICE_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 3)strcpy(TempText,PARA_STEALH_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 4)strcpy(TempText,"1500");
  if(Player[m_iNetWorkID].m_cUpgrade_Para == 5)strcpy(TempText,"----");
  Engine->OpenGl_Font.glPrint(240,173,TempText,1);
  //--- Fire ---//
  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 0)strcpy(TempText,SHOT_LEVEL1_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 1)strcpy(TempText,SHOT_LEVEL2_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 2)strcpy(TempText,SHOT_LEVEL3_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 3)strcpy(TempText,SHOT_LEVEL4_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Fire == 4)strcpy(TempText,"----");
  Engine->OpenGl_Font.glPrint(300,173,TempText,1);
  //--- Spec ---//
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 0)strcpy(TempText,"200");
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 1)strcpy(TempText,"300");
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 2)strcpy(TempText,"600");
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 3)strcpy(TempText,"1000");
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 4)strcpy(TempText,"1500");
  if(Player[m_iNetWorkID].m_cUpgrade_Spec == 5)strcpy(TempText,"----");
  Engine->OpenGl_Font.glPrint(360,173,TempText,1);
  //--- Missile ---//
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 0)strcpy(TempText,PLANE_MISSILE_LEVEL1_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 1)strcpy(TempText,PLANE_MISSILE_LEVEL2_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 2)strcpy(TempText,PLANE_MISSILE_LEVEL3_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 3)strcpy(TempText,PLANE_MISSILE_LEVEL4_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 4)strcpy(TempText,PLANE_MISSILE_LEVEL5_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 5)strcpy(TempText,PLANE_MISSILE_LEVEL6_TEXT);
  if(Player[m_iNetWorkID].m_cUpgrade_Missile == 6)strcpy(TempText,"----");
  Engine->OpenGl_Font.glPrint(420,173,TempText,1);
  }

//------------------------------------------------------------------
void CGameHandler::BuyMenu_Handle(SEngine *Engine)
//------------------------------------------------------------------
  {
  m_fBuyMenuTimer -= (float)Engine->Timer.GetDeltaMs() * 0.001f;

  if(m_fBuyMenuTimer <= 0.0 && Engine->Server == true)
    {
    m_fPrepareTimer = 3.0f;
    m_cGameState = GAME_STATE_PREPARE;

    /////////////////////////////////////////
    //----- Give Items To all Players -----//
    /////////////////////////////////////////
    for(int i=0;i < 16;i++)
      {
      if(Player[i].m_bActive == false || Player[i].m_iPlayerID == -1)continue;

      //Player[i].m_cUpgrade_Para = 1;

      Spec   [Player[i].m_iPlayerID].SetType(Player[i].m_cUpgrade_Spec);
      Fire   [Player[i].m_iPlayerID].SetType(Player[i].m_cUpgrade_Fire);
      Plane  [Player[i].m_iPlayerID].SetType(Player[i].m_cUpgrade_Plane);
      Man    [Player[i].m_iPlayerID].SetType(Player[i].m_cUpgrade_Para);
      Missile[Player[i].m_iPlayerID].SetType(Player[i].m_cUpgrade_Missile);
      }
    Server_Network_Send(PACKET_SERVER_BUYMENUOVER,Engine);
    Server_Network_Send(PACKET_SERVER_UPDATEPLANESTATUS,Engine);
	}
  }

//------------------------------------------------------------------
void CGameHandler::Draw_GameScore(SEngine *Engine)
//------------------------------------------------------------------
  {
  char TempText[64];
  sprintf(TempText,"Green Score:%d    Red Score: %d",Green_Score,Red_Score);

  Engine->OpenGl_Font.glPrint(200,450,TempText,1);
  }

//------------------------------------------------------------------
char CGameHandler::Find_Owner(char a)
//------------------------------------------------------------------
  {
  for(int i=0;i < 16;i++)
    {
    if(Player[i].m_iPlayerID == a)return i;
    }
  return -1;
  }

//------------------------------------------------------------------
void CGameHandler::Server_Network_Handle(SEngine *Engine)
//------------------------------------------------------------------
{
	assert(Engine->WinSock.Server_CheckForError() == false);

	m_fGlobalDataPacket -= 0.001f * (float)Engine->Timer.GetDeltaMs();

	if(m_fGlobalDataPacket <= 0.0f)
	{
		Server_Network_Send(PACKET_SERVER_SYNCPLANE,Engine);
		m_fGlobalDataPacket = 1.0f;
	}

	while(Engine->WinSock.Server_CheckObject() == true)
	{
		char DataRecv[200];
		char DataSend[200];

		Engine->WinSock.Server_GetData(DataRecv);

		//----------------------------------------------------------------
		if(DataRecv[0] == PACKET_CLIENT_JOIN) // Client Join
		//----------------------------------------------------------------
		{
			if(DataRecv[1] != VERSIONNUMBER)
			{
				char Packet[2];
				Packet[0] = PACKET_SERVER_WRONGVERSION;
				Engine->WinSock.Server_SendData(Packet,1);
				return;
			}
			// Find a Free place
			for(int i = 1;i < 16;i++)
			{
				if(Player[i].m_bActive == false)
				{

					Player[i].m_bActive = true;
					memcpy(Player[i].m_caName,DataRecv+2,19);

					Engine->WinSock.Server_SaveIP(i);

					//----------------- Send Player Data

					char* BigData = new char[(sizeof(CPlayer)*16)+2];
					BigData[0] = PACKET_SERVER_JOIN_ACCEPTED;
					BigData[1] = i;
					memcpy(BigData+2,Player,sizeof(CPlayer)*16);
					Engine->WinSock.Server_SendData(BigData,(sizeof(CPlayer)*16)+2);
					delete []BigData;

					break;
				}
			}
		}

		//----------------------------------------------------------------
		if(DataRecv[0] == PACKET_CLIENT_JOINTEAM) // Client Select Team
		//----------------------------------------------------------------
		{
			if(DataRecv[1] == 1)
			{
				Player[DataRecv[2]].m_iPlayerID = Join_Team(true,false);

				if(Player[DataRecv[2]].m_iPlayerID != -1)
				{
					DataSend[0] = PACKET_SERVER_JOINTEAM_ANSWER;
					DataSend[1] = Player[DataRecv[2]].m_iPlayerID;
					Engine->WinSock.Server_SendData(DataSend,2);

					if(GAME_STATE_PREPARE == m_cGameState || GAME_STATE_BUYMENU == m_cGameState)
					{
						m_fBuyMenuTimer = (float)Engine->m_sSettings.BuyTime;
						m_cGameState    = GAME_STATE_BUYMENU;
						GameReset(Engine);

						Server_Network_Send(PACKET_SERVER_DATARESET,Engine);
					}
				}
			}
			if(DataRecv[1] == 2)
			{
				Player[DataRecv[2]].m_iPlayerID = Join_Team(false,true);

				if(Player[DataRecv[2]].m_iPlayerID != -1)
				{
					DataSend[0] = PACKET_SERVER_JOINTEAM_ANSWER;
					DataSend[1] = Player[DataRecv[2]].m_iPlayerID;

					Engine->WinSock.Server_SendData(DataSend,2);

					if(GAME_STATE_PREPARE == m_cGameState || GAME_STATE_BUYMENU == m_cGameState)
					{
						m_fBuyMenuTimer = (float)Engine->m_sSettings.BuyTime;
						m_cGameState    = GAME_STATE_BUYMENU;
						GameReset(Engine);

						Server_Network_Send(PACKET_SERVER_DATARESET,Engine);
					}
				}
			}
		}
		//----------------------------------------------------------------
		if(DataRecv[0] == PACKET_CLIENT_QUIT) // Client Quit
		//----------------------------------------------------------------
		{
			Player[DataRecv[1]].m_bActive = false;

            Player[DataRecv[1]].m_cUpgrade_Plane   = 0;
            Player[DataRecv[1]].m_cUpgrade_Para    = 0;
            Player[DataRecv[1]].m_cUpgrade_Fire    = 0;
            Player[DataRecv[1]].m_cUpgrade_Spec    = 0;
            Player[DataRecv[1]].m_cUpgrade_Missile = 0;
            Player[DataRecv[1]].m_iHits            = 0;
			Player[DataRecv[1]].m_iMoney           = 0;

			if(Player[DataRecv[1]].m_iPlayerID != -1)
			{
				Plane[Player[DataRecv[1]].m_iPlayerID].m_bOcupied = false;
				Plane[Player[DataRecv[1]].m_iPlayerID].m_bInGame  = false;
			}

			Player[DataRecv[1]].m_iPlayerID        = -1;

			memcpy(Player[DataRecv[1]].m_caName,"Empty",5);
		}


		//----------------------------------------------------------------
		if(DataRecv[0] == PACKET_CLIENT_KEYUPDATE) // Client KeyUpdate
		//----------------------------------------------------------------
		{
			if((DataRecv[1] & 0x01) == 0x01){Player[DataRecv[3]].m_bKey_1 = true;}else {Player[DataRecv[3]].m_bKey_1 = false;}
			if((DataRecv[1] & 0x02) == 0x02){Player[DataRecv[3]].m_bKey_2 = true;}else {Player[DataRecv[3]].m_bKey_2 = false;}
			if((DataRecv[1] & 0x04) == 0x04){Player[DataRecv[3]].m_bKey_3 = true;}else {Player[DataRecv[3]].m_bKey_3 = false;}
			if((DataRecv[1] & 0x08) == 0x08){Player[DataRecv[3]].m_bKey_4 = true;}else {Player[DataRecv[3]].m_bKey_4 = false;}

			if((DataRecv[1] & 0x10) == 0x10){Player[DataRecv[3]].m_bKey_Down  = true;}else {Player[DataRecv[3]].m_bKey_Down  = false;}
			if((DataRecv[1] & 0x20) == 0x20){Player[DataRecv[3]].m_bKey_Right = true;}else {Player[DataRecv[3]].m_bKey_Right = false;}
			if((DataRecv[1] & 0x40) == 0x40){Player[DataRecv[3]].m_bKey_Left  = true;}else {Player[DataRecv[3]].m_bKey_Left  = false;}
			if((DataRecv[1] & 0x80) == 0x80){Player[DataRecv[3]].m_bKey_Speed = true;}else {Player[DataRecv[3]].m_bKey_Speed = false;}

			if((DataRecv[2] & 0x01) == 0x01){Player[DataRecv[3]].m_bKey_Fire    = true;}else {Player[DataRecv[3]].m_bKey_Fire    = false;}
			if((DataRecv[2] & 0x02) == 0x02){Player[DataRecv[3]].m_bKey_Spec    = true;}else {Player[DataRecv[3]].m_bKey_Spec    = false;}
			if((DataRecv[2] & 0x04) == 0x04){Player[DataRecv[3]].m_bKey_Missile = true;}else {Player[DataRecv[3]].m_bKey_Missile = false;}
			if((DataRecv[2] & 0x08) == 0x08){Player[DataRecv[3]].m_bKey_Para    = true;}else {Player[DataRecv[3]].m_bKey_Para    = false;}
			if((DataRecv[2] & 0x10) == 0x10){Player[DataRecv[3]].m_bKey_5       = true;}else {Player[DataRecv[3]].m_bKey_5       = false;}

		
			Server_Network_KeyUpdate(DataRecv[3],Engine);
		}
	}
}

//------------------------------------------------------------------
bool CGameHandler::Client_Network_Handle(SEngine *Engine)
//------------------------------------------------------------------
{
	if(0 != Engine->WinSock.Get_Error_Type())
    {
      Engine->WinSock.Get_Error_Type();
      assert(false);
    }

	char DataSend[200];

	if(m_iNetWorkID != -1)
	{
		if(m_bSelectingTeam == true)
		{
			if(Engine->Key.Key_Down(VK_LEFT) && Player[m_iNetWorkID].m_bKey_Left == false)
			{
				Player[m_iNetWorkID].m_bKey_Left = true;

				DataSend[0] = PACKET_CLIENT_JOINTEAM;
				DataSend[1] = 1;
				DataSend[2] = m_iNetWorkID;

				Engine->WinSock.Client_SendData(DataSend,3);
			}
			else if(Engine->Key.Key_Down(VK_LEFT) == false)
			{
				Player[m_iNetWorkID].m_bKey_Left = false;
			}

			if(Engine->Key.Key_Down(VK_RIGHT) && Player[m_iNetWorkID].m_bKey_Right == false)
			{
				Player[m_iNetWorkID].m_bKey_Right = true;

				DataSend[0] = PACKET_CLIENT_JOINTEAM;
				DataSend[1] = 2;
				DataSend[2] = m_iNetWorkID;

				Engine->WinSock.Client_SendData(DataSend,3);
			}
			else if(Engine->Key.Key_Down(VK_RIGHT) == false)
			{
				Player[m_iNetWorkID].m_bKey_Right = false;
			}
		}
		else if(m_bWaitingOnReset == false) // Player joined and on a team
		{

			if(Player[m_iNetWorkID].m_bKey_1 != Engine->Key.Key_Down('1') ||
			   Player[m_iNetWorkID].m_bKey_2 != Engine->Key.Key_Down('2') ||
			   Player[m_iNetWorkID].m_bKey_3 != Engine->Key.Key_Down('3') ||
			   Player[m_iNetWorkID].m_bKey_4 != Engine->Key.Key_Down('4') ||
			   Player[m_iNetWorkID].m_bKey_5 != Engine->Key.Key_Down('5') ||

			   Player[m_iNetWorkID].m_bKey_Down  != Engine->Key.Key_Down(VK_DOWN)  ||
			   Player[m_iNetWorkID].m_bKey_Right != Engine->Key.Key_Down(VK_RIGHT) ||
			   Player[m_iNetWorkID].m_bKey_Left  != Engine->Key.Key_Down(VK_LEFT)  ||
			   Player[m_iNetWorkID].m_bKey_Speed != Engine->Key.Key_Down(VK_UP)    ||

			   Player[m_iNetWorkID].m_bKey_Fire    != Engine->Key.Key_Down(VK_SPACE)   ||
			   Player[m_iNetWorkID].m_bKey_Spec    != Engine->Key.Key_Down(VK_CONTROL) ||
			   Player[m_iNetWorkID].m_bKey_Missile != Engine->Key.Key_Down(VK_SHIFT)   ||
			   Player[m_iNetWorkID].m_bKey_Para    != (
											  Engine->Key.Key_Down('W') || Engine->Key.Key_Down('E') || Engine->Key.Key_Down('R') ||
											  Engine->Key.Key_Down('S') || Engine->Key.Key_Down('D') || Engine->Key.Key_Down('F'))    )
			{
				Player[m_iNetWorkID].m_bKey_1 = Engine->Key.Key_Down('1');
				Player[m_iNetWorkID].m_bKey_2 = Engine->Key.Key_Down('2');
				Player[m_iNetWorkID].m_bKey_3 = Engine->Key.Key_Down('3');
				Player[m_iNetWorkID].m_bKey_4 = Engine->Key.Key_Down('4');
				Player[m_iNetWorkID].m_bKey_5 = Engine->Key.Key_Down('5');

			  	Player[m_iNetWorkID].m_bKey_Down  = Engine->Key.Key_Down(VK_DOWN);
			  	Player[m_iNetWorkID].m_bKey_Right = Engine->Key.Key_Down(VK_RIGHT);
			  	Player[m_iNetWorkID].m_bKey_Left  = Engine->Key.Key_Down(VK_LEFT);
			  	Player[m_iNetWorkID].m_bKey_Speed = Engine->Key.Key_Down(VK_UP);

			   	Player[m_iNetWorkID].m_bKey_Fire    = Engine->Key.Key_Down(VK_SPACE);
			   	Player[m_iNetWorkID].m_bKey_Spec    = Engine->Key.Key_Down(VK_CONTROL);
			   	Player[m_iNetWorkID].m_bKey_Missile = Engine->Key.Key_Down(VK_SHIFT);
			   	Player[m_iNetWorkID].m_bKey_Para    = (
											  Engine->Key.Key_Down('W') || Engine->Key.Key_Down('E') || Engine->Key.Key_Down('R') ||
											  Engine->Key.Key_Down('S') || Engine->Key.Key_Down('D') || Engine->Key.Key_Down('F'));

				DataSend[0] = PACKET_CLIENT_KEYUPDATE;
				DataSend[1] = 0x00;
				if(Player[m_iNetWorkID].m_bKey_1     == true)DataSend[1] |= 0x01;
				if(Player[m_iNetWorkID].m_bKey_2     == true)DataSend[1] |= 0x02;
				if(Player[m_iNetWorkID].m_bKey_3     == true)DataSend[1] |= 0x04;
				if(Player[m_iNetWorkID].m_bKey_4     == true)DataSend[1] |= 0x08;
				if(Player[m_iNetWorkID].m_bKey_Down  == true)DataSend[1] |= 0x10;
				if(Player[m_iNetWorkID].m_bKey_Right == true)DataSend[1] |= 0x20;
				if(Player[m_iNetWorkID].m_bKey_Left  == true)DataSend[1] |= 0x40;
				if(Player[m_iNetWorkID].m_bKey_Speed == true)DataSend[1] |= 0x80;
				DataSend[2] = 0x00;
				if(Player[m_iNetWorkID].m_bKey_Fire    == true)DataSend[2] |= 0x01;
				if(Player[m_iNetWorkID].m_bKey_Spec    == true)DataSend[2] |= 0x02;
				if(Player[m_iNetWorkID].m_bKey_Missile == true)DataSend[2] |= 0x04;
				if(Player[m_iNetWorkID].m_bKey_Para    == true)DataSend[2] |= 0x08;
				if(Player[m_iNetWorkID].m_bKey_5       == true)DataSend[2] |= 0x10;

				DataSend[3] = m_iNetWorkID;

				Engine->WinSock.Client_SendData(DataSend,4);
			}
		}
	}

	//-----------------------------------------------------
	// Getting Data from server
	//-----------------------------------------------------

	while(Engine->WinSock.Client_CheckObject() == true)
	{
		char *GetData;

		GetData = Engine->WinSock.Client_RecvData();
		
		//----------------------------------------------------------------
		if(GetData[0] == PACKET_SERVER_JOIN_ACCEPTED) // Join Accepted
		//----------------------------------------------------------------
		{
			m_iNetWorkID = GetData[1];
			memcpy(Player,GetData+2,sizeof(CPlayer)*16);
		}

		//----------------------------------------------------------------
		if(GetData[0] == PACKET_SERVER_WRONGVERSION) // Server Quit
		//----------------------------------------------------------------
		{
			MessageBox(NULL,"Wrong Version! Get latest on www.logicwork.net","Error",MB_OK);
			return true;
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_JOINTEAM_ANSWER) // JoinTeam Accepted
		//----------------------------------------------------------------
		{
			Player[m_iNetWorkID].m_iPlayerID = GetData[1];
			m_bSelectingTeam = false;
		}
		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_QUIT) // Server Quit
		//----------------------------------------------------------------
		{
			MessageBox(NULL,"Server disconnected","Error",MB_OK);
			return true;
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_DATARESET)
		//----------------------------------------------------------------
		{
			m_bWaitingOnReset = false;
			m_fBuyMenuTimer = GetData[1];
			Red_Score       = GetData[2];
			Green_Score     = GetData[3];
			m_cGameState    = GAME_STATE_BUYMENU;
			memcpy(Player,GetData+4,sizeof(CPlayer)*16);
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && (GetData[0] == PACKET_SERVER_PLAYERUPDATE || GetData[0] == PACKET_SERVER_BUYMENUOVER))
		//----------------------------------------------------------------
		{
			memcpy(Player,GetData+1,sizeof(CPlayer)*16);
			if(GetData[0] == PACKET_SERVER_BUYMENUOVER)
			{
				int i;
				for(i=0;i< 16;i++)
				{
					if(Player[i].m_iPlayerID == -1)continue;

					 Spec   [Player[i].m_iPlayerID].SetType(Player[i].m_cUpgrade_Spec);
					 Fire   [Player[i].m_iPlayerID].SetType(Player[i].m_cUpgrade_Fire);
					 Plane  [Player[i].m_iPlayerID].SetType(Player[i].m_cUpgrade_Plane);
					 Man    [Player[i].m_iPlayerID].SetType(Player[i].m_cUpgrade_Para);
					 Missile[Player[i].m_iPlayerID].SetType(Player[i].m_cUpgrade_Missile);
				}
				m_cGameState = GAME_STATE_PREPARE;
			}
		}
						
		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_INITUPDATE)
		//----------------------------------------------------------------
		{
		  int i;

			for(i=0;i< 16;i++)
			{
				if(Player[i].m_iPunish >= 2)
				{
					//Plane[Player[i].m_iPlayerID].m_bPunish = true;
				}
				else
				{
					//Plane[Player[i].m_iPlayerID].m_bPunish = false;
				}
			}

          for(i=0;i< 16;i++)
		  {
            Plane[i].Init(Engine,i);
            Man[i].m_cStartNR = i;
            Man[i].m_bActive = false;
            Missile[i].m_bUsed = false;
            Missile[i].m_bDead = false;
            Fire[i].m_bActive  = false;
            Spec[i].m_bActive  = false;
			if(Player[i].m_iMoney > 3000)Player[i].m_iMoney = 3000;
		  }

          for(i=0;i< 10;i++)
		  {
		    m_iStatsByWho[i]  = -1;
            m_iStatsByWhat[i] = -1;
            m_iStatsWhoHit[i] = -1;
            m_fStatsLife[i]   = -1.0f;
		  }

		  m_cManHit = -1;

          memcpy(&Map  ,GetData+1                                 ,sizeof(CMap));
          memcpy(Animal,GetData+1+sizeof(CMap)                    ,(sizeof(CAnimal)*2));
          memcpy(Sky   ,GetData+1+sizeof(CMap)+(sizeof(CAnimal)*2),(sizeof(CSky)*3));

		  for(i=0;i < 9;i++)
			 {
				SeaGull[i].m_bActive = false;
			}

		  for(i=0;i < 3;i++)
		  {
			if(Map.m_cMapType != MAP_TYPE_ADV_GRASS && Map.m_cMapType != MAP_TYPE_ICE && Map.m_bTreeActivate[i] == true)
			{
			SeaGull[(i*3)].  m_bActive = true;
			SeaGull[(i*3)+1].m_bActive = true;
			SeaGull[(i*3)+2].m_bActive = true;

			SeaGull[(i*3)].  m_fX = Map.m_fTreeX[i];
			SeaGull[(i*3)+1].m_fX = Map.m_fTreeX[i]+0.2f;
			SeaGull[(i*3)+2].m_fX = Map.m_fTreeX[i]-0.35f;

			SeaGull[(i*3)].  m_fY = -3.8f;
			SeaGull[(i*3)+1].m_fY = -4.0f;
			SeaGull[(i*3)+2].m_fY = -4.15f;

			SeaGull[(i*3)].  Init();
			SeaGull[(i*3)+1].Init();
			SeaGull[(i*3)+2].Init();
			}
		}


		}
		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_UPDATEPLANESTATUS)
		//----------------------------------------------------------------
		{
		    int i;
			for(i = 0;i < 16;i++)
			{
				if(GetData[1+((i*3)+0)] == 1)Plane[i].m_bOcupied = true;
				else					     Plane[i].m_bOcupied = false;
				if(GetData[1+((i*3)+1)] == 1)Plane[i].m_bInGame  = true;
				else					     Plane[i].m_bInGame  = false;
				if(GetData[1+((i*3)+2)] == 1)Plane[i].m_bPilot   = true;
				else					     Plane[i].m_bPilot   = false;
			}
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_GAMEBEGIN)
		//----------------------------------------------------------------
		{
			m_cGameState = GAME_STATE_GAMING;
			int i=0;
			for(i = 0;i < 16;i++)
			{
				for(int ii = 0;ii < 16;ii++){Player[i].m_bHitMe[ii] = false;}
			}
		}
		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_SYNCSKY)
		//----------------------------------------------------------------
		{
			memcpy(Sky,GetData+1,(sizeof(CSky)*3));
		}
		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_GAMEOVER)
		//----------------------------------------------------------------
		{
			m_cGameState = GAME_STATE_GAMEOVER;
			if(GetData[1] == 1)m_bGreenWin = true;
			else			   m_bGreenWin = false;
		}
		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_SYNCANIMAL)
		//----------------------------------------------------------------
		{
			memcpy(Animal,GetData+1,(sizeof(CAnimal)*2));
		}

	
		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_BUYPACK) // fly fald skud spec mis
		//----------------------------------------------------------------
		{
			if(GetData[2] == 10){Player[GetData[1]].m_iMoney -=  500;Player[GetData[1]].m_cUpgrade_Plane = 1;}
			if(GetData[2] == 11){Player[GetData[1]].m_iMoney -=  PLANE_SHIELD_PRICE;Player[GetData[1]].m_cUpgrade_Plane = 2;}
			if(GetData[2] == 12){Player[GetData[1]].m_iMoney -= 1500;Player[GetData[1]].m_cUpgrade_Plane = 3;}
			if(GetData[2] == 13){Player[GetData[1]].m_iMoney -= 2000;Player[GetData[1]].m_cUpgrade_Plane = 4;}
				
			if(GetData[2] == 20){Player[GetData[1]].m_iMoney -=  PARA_PRICE;Player[GetData[1]].m_cUpgrade_Para = 1;}
			if(GetData[2] == 21){Player[GetData[1]].m_iMoney -=  PARA2_PRICE;Player[GetData[1]].m_cUpgrade_Para = 2;}
			if(GetData[2] == 22){Player[GetData[1]].m_iMoney -=  PARA3_PRICE;Player[GetData[1]].m_cUpgrade_Para = 3;}
			if(GetData[2] == 23){Player[GetData[1]].m_iMoney -= PARA_STEALH_PRICE;Player[GetData[1]].m_cUpgrade_Para = 4;}
			if(GetData[2] == 24){Player[GetData[1]].m_iMoney -= 1500;Player[GetData[1]].m_cUpgrade_Para = 5;}
				
			if(GetData[2] == 30){Player[GetData[1]].m_iMoney -= SHOT_LEVEL1;Player[GetData[1]].m_cUpgrade_Fire = 1;}
			if(GetData[2] == 31){Player[GetData[1]].m_iMoney -= SHOT_LEVEL2;Player[GetData[1]].m_cUpgrade_Fire = 2;}
			if(GetData[2] == 32){Player[GetData[1]].m_iMoney -= SHOT_LEVEL3;Player[GetData[1]].m_cUpgrade_Fire = 3;}
			if(GetData[2] == 33){Player[GetData[1]].m_iMoney -= SHOT_LEVEL4;Player[GetData[1]].m_cUpgrade_Fire = 4;}
			
			if(GetData[2] == 40){Player[GetData[1]].m_iMoney -=  200;Player[GetData[1]].m_cUpgrade_Spec = 1;}
			if(GetData[2] == 41){Player[GetData[1]].m_iMoney -=  300;Player[GetData[1]].m_cUpgrade_Spec = 2;}
			if(GetData[2] == 42){Player[GetData[1]].m_iMoney -=  600;Player[GetData[1]].m_cUpgrade_Spec = 3;}
			if(GetData[2] == 43){Player[GetData[1]].m_iMoney -= 1000;Player[GetData[1]].m_cUpgrade_Spec = 4;}
			if(GetData[2] == 44){Player[GetData[1]].m_iMoney -= 1500;Player[GetData[1]].m_cUpgrade_Spec = 5;}
			
			if(GetData[2] == 50){Player[GetData[1]].m_iMoney -=  PLANE_MISSILE_LEVEL1;Player[GetData[1]].m_cUpgrade_Missile = 1;}
			if(GetData[2] == 51){Player[GetData[1]].m_iMoney -=  PLANE_MISSILE_LEVEL2;Player[GetData[1]].m_cUpgrade_Missile = 2;}
			if(GetData[2] == 52){Player[GetData[1]].m_iMoney -=  PLANE_MISSILE_LEVEL3;Player[GetData[1]].m_cUpgrade_Missile = 3;}
			if(GetData[2] == 53){Player[GetData[1]].m_iMoney -=  PLANE_MISSILE_LEVEL4;Player[GetData[1]].m_cUpgrade_Missile = 4;}
			if(GetData[2] == 54){Player[GetData[1]].m_iMoney -=  PLANE_MISSILE_LEVEL5;Player[GetData[1]].m_cUpgrade_Missile = 5;}
			if(GetData[2] == 55){Player[GetData[1]].m_iMoney -=  PLANE_MISSILE_LEVEL6;Player[GetData[1]].m_cUpgrade_Missile = 6;}
		}


		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_SHOTPACK) // fly fald skud spec mis
		//----------------------------------------------------------------
		{
			float Tempx = 0.0f;
			float Tempy = 0.0f;
			float Tempr = 0.0f;

			if(GetData[1] < 10)
			{
				Tempx = Plane[GetData[2]].m_fx;
				Tempy = Plane[GetData[2]].m_fy;
				Tempr = Plane[GetData[2]].m_fRotate;
			}
			else
			{
				Tempx = Man[GetData[2]].m_fx;
				Tempy = Man[GetData[2]].m_fy+0.1f;
				Tempr = Man[GetData[2]].m_fRotate+180;
				GetData[1] -= 10;
			}
			if(GetData[1] == 1) // Fire
			{
		        if(Plane[GetData[2]].m_bPilot == true)
				{
					Fire[GetData[2]].Create(Tempx,Tempy,Tempr,Plane[GetData[2]].m_fSpeed);
				}

				if(Man[GetData[2]].m_cStatus == MAN_STATUS_GROUND || Man[GetData[2]].m_cStatus == MAN_STATUS_BEHIND_PLANE)
				{
					Fire[GetData[2]].Create(Tempx,Tempy,Tempr,1.0f);
				}
			}
			if(GetData[1] == 2) // Spec
			{
		        if(Plane[GetData[2]].m_bPilot == true)
				{
					Spec[GetData[2]].Create(Tempx,Tempy,Tempr,Plane[GetData[2]].m_fSpeed);
				}

				if(Man[GetData[2]].m_cStatus == MAN_STATUS_GROUND || Man[GetData[2]].m_cStatus == MAN_STATUS_BEHIND_PLANE)
				{
					Spec[GetData[2]].Create(Tempx,Tempy,Tempr,1.25f);
				}
			}

			if(GetData[1] == 3) // Missile
			{
              Missile[GetData[2]].Create(Tempx,Tempy,Tempr,-1,this,GetData[2]);
			}
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_KEYUPDATE) // fly fald skud spec mis
		//----------------------------------------------------------------
		{
			short TempInt;
			
			if((GetData[2] & 0x01) == 0x01){Player[GetData[1]].m_bKey_1 = true;}else {Player[GetData[1]].m_bKey_1 = false;}
			if((GetData[2] & 0x02) == 0x02){Player[GetData[1]].m_bKey_2 = true;}else {Player[GetData[1]].m_bKey_2 = false;}
			if((GetData[2] & 0x04) == 0x04){Player[GetData[1]].m_bKey_3 = true;}else {Player[GetData[1]].m_bKey_3 = false;}
			if((GetData[2] & 0x08) == 0x08){Player[GetData[1]].m_bKey_4 = true;}else {Player[GetData[1]].m_bKey_4 = false;}

			if((GetData[2] & 0x10) == 0x10){Player[GetData[1]].m_bKey_Down  = true;}else {Player[GetData[1]].m_bKey_Down  = false;}
			if((GetData[2] & 0x20) == 0x20){Player[GetData[1]].m_bKey_Right = true;}else {Player[GetData[1]].m_bKey_Right = false;}
			if((GetData[2] & 0x40) == 0x40){Player[GetData[1]].m_bKey_Left  = true;}else {Player[GetData[1]].m_bKey_Left  = false;}
			if((GetData[2] & 0x80) == 0x80){Player[GetData[1]].m_bKey_Speed = true;}else {Player[GetData[1]].m_bKey_Speed = false;}

			if((GetData[3] & 0x01) == 0x01){Player[GetData[1]].m_bKey_Fire    = true;}else {Player[GetData[1]].m_bKey_Fire    = false;}
			if((GetData[3] & 0x02) == 0x02){Player[GetData[1]].m_bKey_Spec    = true;}else {Player[GetData[1]].m_bKey_Spec    = false;}
			if((GetData[3] & 0x04) == 0x04){Player[GetData[1]].m_bKey_Missile = true;}else {Player[GetData[1]].m_bKey_Missile = false;}
			if((GetData[3] & 0x08) == 0x08){Player[GetData[1]].m_bKey_Para    = true;}else {Player[GetData[1]].m_bKey_Para    = false;}

		    memcpy(&Plane[Player[GetData[1]].m_iPlayerID].m_fx,GetData+1+(3),4);
			memcpy(&Plane[Player[GetData[1]].m_iPlayerID].m_fy,GetData+5+(3),4);
			memcpy(&TempInt,      GetData+9+(3),2);
			Plane[Player[GetData[1]].m_iPlayerID].m_fRotate = (float)(TempInt * 0.1f);

			memcpy(&Man[Player[GetData[1]].m_iPlayerID].m_fx,GetData+11+(3),4);
			memcpy(&Man[Player[GetData[1]].m_iPlayerID].m_fy,GetData+15+(3),4);
			memcpy(&TempInt,    GetData+19+(3),2);
			Man[Player[GetData[1]].m_iPlayerID].m_fRotate = (float)(TempInt * 0.1f);		
		
		
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_SYNCPLANE) // fly fald skud spec mis
		//----------------------------------------------------------------
		{

			int i;
			short TempInt;

			for(i = 0;i<=15;i++)
		    {
			    memcpy(&Plane[i].m_fx,GetData+1+(i*21),4);
				memcpy(&Plane[i].m_fy,GetData+5+(i*21),4);
				memcpy(&TempInt,      GetData+9+(i*21),2);
				Plane[i].m_fRotate = (float)(TempInt * 0.1f);

				memcpy(&Man[i].m_fx,GetData+11+(i*21),4);
				memcpy(&Man[i].m_fy,GetData+15+(i*21),4);
				memcpy(&TempInt,    GetData+19+(i*21),2);
				Man[i].m_fRotate = (float)(TempInt * 0.1f);
			}
			
		}
		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_PLANEHIT) // fly fald skud spec mis
		//----------------------------------------------------------------
		{
			Plane[GetData[1]].Hit(this,GetData[1],GetData[2],-1,Engine);

			if(GetData[3] != -1)
			{
				if(GetData[3] < 16)// Fire
				{
					  Fire[GetData[3]].m_bActive = false;
				}
				else // Missile
				{
			          if(Missile[GetData[3]-30].m_bPlasma == false)Missile[GetData[3]-30].m_bDead = true;
				}
			} 
		}
		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_PLANEHITGROUND)
		//----------------------------------------------------------------
		{
			Plane[GetData[1]].m_cDamage = PLANE_DAMAGE_CRASHED;		
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_EJECTMAN)
		//----------------------------------------------------------------
		{
			Man[GetData[1]].JumpOut(Plane[GetData[1]].m_fx,Plane[GetData[1]].m_fy,Plane[GetData[1]].m_fSpeed,Plane[GetData[1]].m_fRotate);		
			Plane[GetData[1]].m_bPilot     = false;
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_STATSLIST)
		//----------------------------------------------------------------
		{
			Add_ToStats(GetData[1],GetData[2],GetData[3],Engine);
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_PARACHUTEMAN)
		//----------------------------------------------------------------
		{
			if(Man[GetData[1]].m_cStatus == MAN_STATUS_FLYING)
			{
				Man[GetData[1]].m_cStatus           = MAN_STATUS_PARACHUTING;
				Man[GetData[1]].m_fPara_Folding_Out = 0.0f;
			}
			else if(Man[GetData[1]].m_cStatus == MAN_STATUS_PARACHUTING)
			{
				Man[GetData[1]].m_cStatus           = MAN_STATUS_FLYING;
			}
		}
		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_ANIMALCOLLISION)
		//----------------------------------------------------------------
		{
		    Animal[GetData[1]].m_bDead = true;	

			if(GetData[2] == -2) // Animal Drown
			{
				Animal[GetData[1]].m_fX     = 15.0f;
			}

			if(GetData[2] >= 0 && GetData[2] <= 15)
			{
              Fire[GetData[2]].m_bActive  = false;
			}

			if(GetData[2] >= 20 && GetData[2] <= 50)
			{
              Spec[GetData[2]].m_bActive  = false;
			}
			if(GetData[2] >=70 && GetData[2] <= 100)
			{
              if(Missile[GetData[2]].m_bPlasma == false)Missile[GetData[2]].m_bDead  = true;
			}
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_ICEMELT)
		//----------------------------------------------------------------
		{
          Fire[GetData[2]].m_bActive           = false;
          Map.m_baField_Destroyed[GetData[1]] = true;
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_REMOVESHOT)
		//----------------------------------------------------------------
		{
			if(GetData[1] == 1)Fire[GetData[2]].m_bActive  = false;
			if(GetData[1] == 2){if(Missile[GetData[2]].m_bPlasma == false)Missile[GetData[2]].m_bDead  = true;}
			if(GetData[1] >= 3)
			{
	          Spec[GetData[1]-3].m_bActive  = false;
			  Spec[GetData[2]  ].m_bActive  = false;
			}
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_HITMANPARA)
		//----------------------------------------------------------------
		{
			if(GetData[1] == -1) // Ice
			{
				Man[GetData[2]].m_cStatus = MAN_STATUS_DEAD;
				Man[GetData[2]].m_fx      = 15.0f;				
			}
			if(GetData[1] == -2) // Animal
			{
				if(Man[GetData[2]].m_cType != 5 || Man[GetData[2]].m_cStatus != MAN_STATUS_FLYING)Man[GetData[2]].m_cStatus = MAN_STATUS_DEAD;
			}

			if(GetData[1] == 1) // Fire
			{
				Fire[GetData[3]].m_bActive  = false;
				Man[GetData[2]].m_fRotate   = Fire[GetData[3]].m_fRotate;
				Man[GetData[2]].m_fSpeed    = 2.0f * 1.5f;
				if(Man[GetData[2]].m_cType != 5 || Man[GetData[2]].m_cStatus != MAN_STATUS_FLYING)Man[GetData[2]].m_cStatus   = MAN_STATUS_DEAD;
			}
			if(GetData[1] == 2) // Spec
			{
			    Spec[GetData[3]].m_bActive  = false;
				Man[GetData[2]].m_fRotate = Spec[GetData[3]].m_fRotate;
				Man[GetData[2]].m_fSpeed  = 2.0f * 1.5f;
				if(Man[GetData[2]].m_cType != 5 || Man[GetData[2]].m_cStatus != MAN_STATUS_FLYING)Man[GetData[2]].m_cStatus = MAN_STATUS_DEAD;
			}
			if(GetData[1] == 3) // Missile
			{
				Man[GetData[2]].m_fRotate = Missile[GetData[3]].m_fRotate;
				Man[GetData[2]].m_fSpeed  = 2.0f * 1.5f;
				if(Man[GetData[2]].m_cType != 5 || Man[GetData[2]].m_cStatus != MAN_STATUS_FLYING)Man[GetData[2]].m_cStatus = MAN_STATUS_DEAD;
			}
			if(GetData[1] == 4) // Plane
			{
				Man[GetData[2]].m_fRotate = Plane[GetData[3]].m_fRotate;
				Man[GetData[2]].m_fSpeed  = 2.0f * 1.5f;

				 if(Man[GetData[2]].m_cType != 5)
				 {
					Man[GetData[2]].m_cSplash = GetData[3];
					Man[GetData[2]].m_fManSlidingOf = 1.0f;

					if(Man[GetData[2]].m_cStatus == MAN_STATUS_PARACHUTING)Man[GetData[2]].m_bSplashPara = true;
					else Man[GetData[2]].m_bSplashPara = false;

					if(m_iNetWorkID != -1)
					{
						if(GetData[3] == Player[m_iNetWorkID].m_iPlayerID)
						{
							m_cManHit = GetData[2];
						}
					}
				 }
				if(Man[GetData[2]].m_cType != 5 || Man[GetData[2]].m_cStatus != MAN_STATUS_FLYING)Man[GetData[2]].m_cStatus = MAN_STATUS_DEAD;
			}
		}
		
		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_SPECHIT)
		//----------------------------------------------------------------
		{
          Spec[GetData[2]].m_bActive = false;

          if(Spec[GetData[2]].m_cType >= 5 && Plane[GetData[1]].m_bPilot == true)
            {
            Plane[GetData[1]].m_bPilot = false;
            Man[GetData[1]].JumpOut(Plane[GetData[1]].m_fx,Plane[GetData[1]].m_fy,Plane[GetData[1]].m_fSpeed,Plane[GetData[1]].m_fRotate);

			continue;
		  }

          if(Spec[GetData[2]].m_cType >= 1)Plane[GetData[1]].m_fSpeed = 0.0f;
          if(Spec[GetData[2]].m_cType >= 2)Plane[GetData[1]].m_bPoision_Soft_Active = true;
          if(Spec[GetData[2]].m_cType >= 4)Plane[GetData[1]].m_bPoision_Hard_Active = true;
		  
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_PLANEAPART)
		//----------------------------------------------------------------
		{
			Plane[GetData[1]].m_bAppartDontFall = true;

		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_SEAGULLWAKE)
		//----------------------------------------------------------------
		{
			struct STemp_Packet
			{
			char ID;
			char SeaGull;
			float x;
			float y;
			}Data;

			memcpy(&Data,GetData,sizeof(STemp_Packet));

			SeaGull[Data.SeaGull].m_bWake = true;
			SeaGull[Data.SeaGull].m_fDX = Data.x;
			SeaGull[Data.SeaGull].m_fDY = Data.y;
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_SEAGULLHIT)
		//----------------------------------------------------------------
		{
			SeaGull[GetData[2]].m_bDead = true;

			SeaGull[GetData[2]].m_fGullSliding = 6.8f;
			SeaGull[GetData[2]].m_cType = (rand()%2)+1;
			SeaGull[GetData[2]].m_bGullSplash = true;
			SeaGull[GetData[2]].m_cWhoHittedMe = GetData[1];
		}

		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_SEAGULLHITBYSHOOT)
		//----------------------------------------------------------------
		{
			if(GetData[2] == 1) // Fire
			{
				Fire[GetData[3]].m_bActive  = false;
				SeaGull[GetData[1]].m_bDead = true;
				SeaGull[GetData[1]].m_bWake = true;

				SeaGull[GetData[1]].m_fX      = Fire[GetData[3]].m_fx;
				SeaGull[GetData[1]].m_fY      = Fire[GetData[3]].m_fy;
				SeaGull[GetData[1]].m_fRotate = Fire[GetData[3]].m_fRotate;
				SeaGull[GetData[1]].m_fSpeed  = 2.0f * 1.5f;
			}
			if(GetData[2] == 2) // Spec
			{
				Spec[GetData[3]].m_bActive  = false;
				SeaGull[GetData[1]].m_bDead = true;
				SeaGull[GetData[1]].m_bWake = true;

				SeaGull[GetData[1]].m_fX      = Spec[GetData[3]].m_fx;
				SeaGull[GetData[1]].m_fY      = Spec[GetData[3]].m_fy;
				SeaGull[GetData[1]].m_fRotate = Spec[GetData[3]].m_fRotate;
				SeaGull[GetData[1]].m_fSpeed  = 2.0f * 1.5f;
			}
			if(GetData[2] == 3) // Missile
			{
				SeaGull[GetData[1]].m_bDead = true;
				SeaGull[GetData[1]].m_bWake = true;

				SeaGull[GetData[1]].m_fX      = Missile[GetData[3]].m_fx;
				SeaGull[GetData[1]].m_fY      = Missile[GetData[3]].m_fy;
				SeaGull[GetData[1]].m_fRotate = Missile[GetData[3]].m_fRotate;
				SeaGull[GetData[1]].m_fSpeed  = 2.0f * 1.5f;
			}
		}
		//----------------------------------------------------------------
		if(m_iNetWorkID != -1 && GetData[0] == PACKET_SERVER_PLANEPICKUP)
		//----------------------------------------------------------------
		{
			Man[GetData[2]].m_cStatus = MAN_STATUS_BEHIND_PLANE;
			Man[GetData[2]].m_cSittingBackPlane = GetData[1];
		}





}
	return false;
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_Send(char Status,SEngine *Engine)
//------------------------------------------------------------------
{
	char Data[200];
	int  Size = 0;
    int i;

	switch(Status)
	{
		//------------------------------------------
		case PACKET_SERVER_DATARESET:
		//------------------------------------------
		{
			
			char* BigData = new char[(sizeof(CPlayer)*16)+4];
			BigData[0] = Status;
			BigData[1] = Engine->m_sSettings.BuyTime;
			BigData[2] = Red_Score;
			BigData[3] = Green_Score;
			memcpy(BigData+4,Player,sizeof(CPlayer)*16);
			
			for(i = 1;i < 16;i++)
			{
				if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
				{
					Engine->WinSock.Server_LoadIP(i);
					Engine->WinSock.Server_SendData(BigData,(sizeof(CPlayer)*16)+4);
				 }
			}

			delete []BigData;
			
			return;
		}
		break;

		//------------------------------------------
		case PACKET_SERVER_PLAYERUPDATE:
		case PACKET_SERVER_BUYMENUOVER:
		//------------------------------------------
		{
			char* BigData = new char[(sizeof(CPlayer)*16)+1];
			BigData[0] = Status;
			memcpy(BigData+1,Player,sizeof(CPlayer)*16);

			
			for(i = 1;i < 16;i++)
			{
				if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
				{
					Engine->WinSock.Server_LoadIP(i);
					Engine->WinSock.Server_SendData(BigData,(sizeof(CPlayer)*16)+1);
				 }
			}

			delete []BigData;
			return;
		}
		break;

		//------------------------------------------
		case PACKET_SERVER_INITUPDATE:
		//------------------------------------------
		{
			char* BigData = new char[(sizeof(CMap) + (sizeof(CAnimal)*2) + (sizeof(CSky)*3))+1];
			BigData[0] = Status;

			memcpy(BigData+1                                 ,&Map,sizeof(CMap));
			memcpy(BigData+1+sizeof(CMap)                    ,Animal,(sizeof(CAnimal)*2));
			memcpy(BigData+1+sizeof(CMap)+(sizeof(CAnimal)*2),Sky,(sizeof(CSky)*3));
			
			for(i = 1;i < 16;i++)
			{
				if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
				{
					Engine->WinSock.Server_LoadIP(i);
					Engine->WinSock.Server_SendData(BigData,(sizeof(CMap) + (sizeof(CAnimal)*2) + (sizeof(CSky)*3))+1);
				}
			}


			delete []BigData;

		return;
		}
		break;

		//------------------------------------------
		case PACKET_SERVER_UPDATEPLANESTATUS:
		//------------------------------------------
		{
			Data[0] = Status;

			for(i = 0;i < 16;i++)
			{
				if(Plane[i].m_bOcupied == true)Data[1+((i*3)+0)] = 1;
				else                           Data[1+((i*3)+0)] = 0;
				if(Plane[i].m_bInGame == true) Data[1+((i*3)+1)] = 1;
				else                           Data[1+((i*3)+1)] = 0;
				if(Plane[i].m_bPilot == true)  Data[1+((i*3)+2)] = 1;
				else                           Data[1+((i*3)+2)] = 0;
			}

			Size    = 1+(16*3);
		}
		break;

		//------------------------------------------
		case PACKET_SERVER_GAMEBEGIN:
		//------------------------------------------
		{
			Data[0] = Status;
			Size    = 1;
		}
		break;

		//------------------------------------------
		case PACKET_SERVER_SYNCSKY:
		//------------------------------------------
		{
			Data[0] = Status;
			Size    = 1+(sizeof(CSky)*3);
			memcpy(Data+1,Sky,(sizeof(CSky)*3));
		}
		break;

		//------------------------------------------
		case PACKET_SERVER_GAMEOVER:
		//------------------------------------------
		{
			Data[0] = Status;
			Size    = 2;
			if(m_bGreenWin == true)Data[1] = 1;
			else				   Data[1] = 0;
		}
		break;

		//------------------------------------------
		case PACKET_SERVER_SYNCPLANE:
		//------------------------------------------
		{
			char Active_Players = 15;
			char Data_Packet[400];
			int  TempInt;

			for(i=15;i>=0;i--)
			{
				if(i >= 12 || Player[i].m_bActive == true){break;}
				if(Player[i].m_bActive == false)
				{
					Active_Players = i;
				}
			}

			Data_Packet[0] = PACKET_SERVER_SYNCPLANE;

			for(i=0;i<=Active_Players;i++)
			{
				memcpy(Data_Packet+   1+(i*21),&Plane[i].m_fx,4); 
				memcpy(Data_Packet+   5+(i*21),&Plane[i].m_fy,4); 
				TempInt           = (short)(((Plane[i].m_fRotate)) * 10);
				memcpy(Data_Packet+   9+(i*21),&TempInt,2); 
				memcpy(Data_Packet+  11+(i*21),&Man[i].m_fx,4); 
				memcpy(Data_Packet+  15+(i*21),&Man[i].m_fy,4); 
				TempInt           = (short)(((Man[i].m_fRotate)) * 10);
				memcpy(Data_Packet+  19+(i*21),&TempInt,2); 
			}

			for(i = 1;i < 16;i++)
			{
				if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
				{
					Engine->WinSock.Server_LoadIP(i);
					Engine->WinSock.Server_SendData(Data_Packet,2+((Active_Players++)*21));
				}
			}

			return;

		}
		break;

		//------------------------------------------
		case PACKET_SERVER_SYNCANIMAL:
		//------------------------------------------
		{
			char* BigData = new char[(sizeof(CAnimal)*2)+1];
			BigData[0] = Status;
			memcpy(BigData+1,Animal,(sizeof(CAnimal)*2));

			for(i = 1;i < 16;i++)
			{
				if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
				{
					Engine->WinSock.Server_LoadIP(i);
					Engine->WinSock.Server_SendData(BigData,(sizeof(CAnimal)*2)+1);
				}
			}

			delete []BigData;
			return;

		}
		break;


		default:
		{
			return;
		}
	}

	if(Size <= 0)
	{
		return;
	}

	for(i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Engine->WinSock.Server_LoadIP(i);

			Engine->WinSock.Server_SendData(Data,Size);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_SendBuyMenu(char PlayerNr,char Type,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[3];

	Data[0] = PACKET_SERVER_BUYPACK;
	Data[1] = PlayerNr;
	Data[2] = Type;

	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,3);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_SendShot(char Type,char PlaneNr,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[3];

	Data[0] = PACKET_SERVER_SHOTPACK;
	Data[1] = Type;
	Data[2] = PlaneNr;

	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,3);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_KeyUpdate(char PlayerNr,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[50];
	int  TempInt;
	//------------------------------------------------------//
	//------------------ Keyboard Update -------------------//
	//------------------------------------------------------//

	Data[0] = PACKET_SERVER_KEYUPDATE;
	Data[1] = PlayerNr;

	Data[2] = 0x00;
	if(Player[PlayerNr].m_bKey_1     == true)Data[2] |= 0x01;
	if(Player[PlayerNr].m_bKey_2     == true)Data[2] |= 0x02;
	if(Player[PlayerNr].m_bKey_3     == true)Data[2] |= 0x04;
	if(Player[PlayerNr].m_bKey_4     == true)Data[2] |= 0x08;
	if(Player[PlayerNr].m_bKey_Down  == true)Data[2] |= 0x10;
	if(Player[PlayerNr].m_bKey_Right == true)Data[2] |= 0x20;
	if(Player[PlayerNr].m_bKey_Left  == true)Data[2] |= 0x40;
	if(Player[PlayerNr].m_bKey_Speed == true)Data[2] |= 0x80;
	Data[3] = 0x00;
	if(Player[PlayerNr].m_bKey_Fire    == true)Data[3] |= 0x01;
	if(Player[PlayerNr].m_bKey_Spec    == true)Data[3] |= 0x02;
	if(Player[PlayerNr].m_bKey_Missile == true)Data[3] |= 0x04;
	if(Player[PlayerNr].m_bKey_Para    == true)Data[3] |= 0x08;

	//------------------------------------------------------//
	//-------------------- Plane Update --------------------//
	//------------------------------------------------------//

	memcpy(Data+   1+3,&Plane[Player[PlayerNr].m_iPlayerID].m_fx,4); 
	memcpy(Data+   5+3,&Plane[Player[PlayerNr].m_iPlayerID].m_fy,4); 
	TempInt           = (short)(((Plane[Player[PlayerNr].m_iPlayerID].m_fRotate)) * 10);
	memcpy(Data+   9+3,&TempInt,2); 
	memcpy(Data+  11+3,&Man[Player[PlayerNr].m_iPlayerID].m_fx,4); 
	memcpy(Data+  15+3,&Man[Player[PlayerNr].m_iPlayerID].m_fy,4); 
	TempInt           = (short)(((Man[Player[PlayerNr].m_iPlayerID].m_fRotate)) * 10);
	memcpy(Data+  19+3,&TempInt,2); 

	//------------------------------------------------------//
	//-------------------- Send Data -----------------------//
	//------------------------------------------------------//

	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,24);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_SendPlaneHit(char PlayerNr,char Damage,char Projectile,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[4];

	Data[0] = PACKET_SERVER_PLANEHIT;
	Data[1] = PlayerNr;
	Data[2] = Damage;
	Data[3] = Projectile;

	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,4);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_PlaneHitGround(char PlayerNr,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[2];

	Data[0] = PACKET_SERVER_PLANEHITGROUND;
	Data[1] = PlayerNr;
	
	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,2);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_EjectFromPlane(char PlayerNr,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[2];

	Data[0] = PACKET_SERVER_EJECTMAN;
	Data[1] = PlayerNr;
	
	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,2);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_ParachuteMan(char PlayerNr,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[2];

	Data[0] = PACKET_SERVER_PARACHUTEMAN;
	Data[1] = PlayerNr;
	
	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,2);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_AnimalCollision(char AnimalNr,char Projectile,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[3];

	Data[0] = PACKET_SERVER_ANIMALCOLLISION;
	Data[1] = AnimalNr;
	Data[2] = Projectile;
	
	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,3);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_IceMelt(char field,char FireNr,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[3];

	Data[0] = PACKET_SERVER_ICEMELT;
	Data[1] = field;
	Data[2] = FireNr;
	
	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,3);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_RemoveShot(char type,char Nr,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[3];

	Data[0] = PACKET_SERVER_REMOVESHOT;
	Data[1] = type;
	Data[2] = Nr;
	
	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,3);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_ManParaHit(char type,char ManNr,char SourceNr,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[4];

	Data[0] = PACKET_SERVER_HITMANPARA;
	Data[1] = type;
	Data[2] = ManNr;
	Data[3] = SourceNr;
		
	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,4);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_SpecHit(char PlaneNr,char SpecNr,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[3];

	Data[0] = PACKET_SERVER_SPECHIT;
	Data[1] = PlaneNr;
	Data[2] = SpecNr;

	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,3);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_StopAppart(char PlaneNr,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[2];

	Data[0] = PACKET_SERVER_PLANEAPART;
	Data[1] = PlaneNr;

	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,2);
		}
	}

}

//------------------------------------------------------------------
void CGameHandler::Server_Network_SeaGullShotHit(char SeaGull,char Projectile,char ProjectileNr,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[4];

	Data[0] = PACKET_SERVER_SEAGULLHITBYSHOOT;
	Data[1] = SeaGull;
	Data[2] = Projectile;
	Data[3] = ProjectileNr;

	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,4);
		}
	}

}

//------------------------------------------------------------------
void CGameHandler::Server_Network_SeaGullMove(char Seagull,float m_fx,float m_fy,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	struct STempPacket
	{
	char ID;
	char SeaGull;
	float x;
	float y;
	}Data;

	Data.ID = PACKET_SERVER_SEAGULLWAKE;
	Data.SeaGull = Seagull;
	Data.x = m_fx;
	Data.y = m_fy;

	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData((char *)&Data,sizeof(STempPacket));
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_SeaGullPlaneHit(char PlaneNr,char SeaGull,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[3];

	Data[0] = PACKET_SERVER_SEAGULLHIT;
	Data[1] = PlaneNr;
	Data[2] = SeaGull;

	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,3);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Server_Network_PlanePickUp(char PlaneNr,char Man,SEngine *Temp_Engine)
//------------------------------------------------------------------
{
	char Data[3];

	Data[0] = PACKET_SERVER_PLANEPICKUP;
	Data[1] = PlaneNr;
	Data[2] = Man;

	for(int i = 1;i < 16;i++)
	{
		if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
		{
			Temp_Engine->WinSock.Server_LoadIP(i);
			Temp_Engine->WinSock.Server_SendData(Data,3);
		}
	}
}

//------------------------------------------------------------------
void CGameHandler::Draw_KillBox(SEngine *Engine)
//------------------------------------------------------------------
{
/*
  int     m_iStatsByWho[10];
  int     m_iStatsByWhat[10];
  int     m_iStatsWhoHit[10];
  float   m_fStatsLife[10];
*/

	int i,iAntal = 0;
	char sSource[10];
	
	for(i = 0;i < 10;i++)
	{
		if(m_fStatsLife[i] > 0.0f)
		{
			iAntal++;
			m_fStatsLife[i] -= (float)Engine->Timer.GetDeltaMs() * 0.001f;

			// Source
			if(m_iStatsByWho[i] != -1)
			{



			  if(((Player[(m_iStatsByWho[i])].m_iPlayerID)%2) == 0)glColor3f(0.0f,1.0f,0.0f);
			  if(((Player[(m_iStatsByWho[i])].m_iPlayerID)%2) == 1)glColor3f(1.0f,0.0f,0.0f);
			
			  memcpy(sSource,Player[m_iStatsByWho[i]].m_caName,9);
			  sSource[9] = NULL;
			  Engine->OpenGl_Font.glPrint(390,430-(i*23),sSource,0);

			  glColor3f(1.0f,1.0f,1.0f);
            }
			// Target
			if(m_iStatsWhoHit[i] != -1)
			{
			  if(((Player[(m_iStatsWhoHit[i])].m_iPlayerID)%2) == 0)glColor3f(0.0f,1.0f,0.0f);
			  if(((Player[(m_iStatsWhoHit[i])].m_iPlayerID)%2) == 1)glColor3f(1.0f,0.0f,0.0f);

			  memcpy(sSource,Player[m_iStatsWhoHit[i]].m_caName,9);
			  sSource[9] = NULL;
			  Engine->OpenGl_Font.glPrint(515,430-(i*23),sSource,0);

			  glColor3f(1.0f,1.0f,1.0f);
			}
			// ByWhat
			glPushMatrix();
				glTranslatef(6.1f,6.7f-(i*0.78f),-19.5f);
				if(m_iStatsByWhat[i] == 1)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_Fire_Particle.texID);
				if(m_iStatsByWhat[i] == 2)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_Spec_Particle.texID);
				if(m_iStatsByWhat[i] == 3){glBindTexture(GL_TEXTURE_2D,m_sData.Tex_Missile_Particle.texID);glRotatef(-90.0f,0.0f,0.0f,1.0f);}
				if(m_iStatsByWhat[i] == 4)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_Blood_Particle.texID);
				if(m_iStatsByWhat[i] == 5)glBindTexture(GL_TEXTURE_2D,m_sData.Tex_Green_Plane.texID);

				if(m_iStatsByWhat[i] == 3)glScalef(2.0f,2.0f,2.0f);
				if(m_iStatsByWhat[i] == 4){glColor4f(1.0f,0.0f,0.0f,0.7f);glScalef(2.0f,2.0f,2.0f);}

				glBegin(GL_QUADS);						
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.15f,-0.15f,+0.0f);	
				glTexCoord2f(1.0f, 0.0f); glVertex3f(+0.15f,-0.15f,+0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(+0.15f,+0.15f,-0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.15f,+0.15f,-0.0f);	
				glEnd();				

				if(m_iStatsByWhat[i] == 3)glScalef(1.0f,1.0f,1.0f);
				if(m_iStatsByWhat[i] == 4){glColor4f(1.0f,1.0f,1.0f,1.0f);glScalef(1.0f,1.0f,1.0f);}

			glPopMatrix();

			
		}
	}

  //--------------------------------------------

  glBindTexture(GL_TEXTURE_2D,0);

  glPushMatrix();						
	glTranslatef(6.5f,6.4f,-20.0f);
	glDisable(GL_TEXTURE);

	glColor4f(0.0f,0.0f,0.0f,0.5f);

	glBegin(GL_QUADS);						
		glVertex3f(-4.0f,+0.8f-(iAntal*0.8f),+0.0f);	
		glVertex3f(+3.5f,+0.8f-(iAntal*0.8f),+0.0f);
		glVertex3f(+3.5f,+0.8f,-0.0f);
		glVertex3f(-4.0f,+0.8f,-0.0f);	
	glEnd();

	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glEnable(GL_TEXTURE);
  glPopMatrix();
}

void CGameHandler::Add_ToStats(int Target,int Source,int ByWhat,SEngine *Engine)
{
/*
  int     m_iStatsByWho[10];
  int     m_iStatsByWhat[10];
  int     m_iStatsWhoHit[10];
  float   m_fStatsLife[10];
*/
	int i;

	for(i = 8;i >= 0;i--)
	{
	  m_iStatsByWho[i+1]  = m_iStatsByWho[i];
      m_iStatsByWhat[i+1] = m_iStatsByWhat[i];
      m_iStatsWhoHit[i+1] = m_iStatsWhoHit[i];
      m_fStatsLife[i+1]   = m_fStatsLife[i];
	}
	
    m_iStatsByWho[0]  = Source;
    m_iStatsByWhat[0] = ByWhat;
    m_iStatsWhoHit[0] = Target;
    m_fStatsLife[0]   = 4.0f;
    
    if(Engine->Server == true)
    {
    	char Data[4];

		Data[0] = PACKET_SERVER_STATSLIST;
		Data[1] = Target;
		Data[2] = Source;
		Data[3] = ByWhat;
		
		for(int i = 1;i < 16;i++)
		{
			if(Player[i].m_bActive && Player[i].m_iPlayerID != -1)
			{
				Engine->WinSock.Server_LoadIP(i);
				Engine->WinSock.Server_SendData(Data,4);
			}
		}
    }
}
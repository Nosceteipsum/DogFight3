////////////////////////////////////////////////////////////////////
//                                                                //
//               DF 3: Bot_CPP                                    //
//                                                                //
//         Made By: Tommy Kobberø Andersen                        //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "../../../global.h"

//------------------------------------------------------------------
CBot::CBot()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
CBot::~CBot()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
char CBot::Find_PreyMan(CGameHandler *GameHandler,int ID)
//------------------------------------------------------------------
  {
  char  Target_ID = -1;
  float Lenght = 100.0f;
  int i;
  float m_fx = GameHandler->Man[GameHandler->Player[ID].m_iPlayerID].m_fx;
  float m_fy = GameHandler->Man[GameHandler->Player[ID].m_iPlayerID].m_fy;

  if((GameHandler->Player[ID].m_iPlayerID % 2) == 0) // Green
    {
    for(i=1;i< 16;i+=2)
      {
      if(GameHandler->Man[i].m_bActive == true && GameHandler->Man[i].m_cStatus != MAN_STATUS_DEAD)
        {
        if(((m_fx - GameHandler->Man[i].m_fx) + (m_fy - GameHandler->Man[i].m_fy)) < Lenght)
          {
          Lenght    = fabs(((fabs(m_fx) - fabs(GameHandler->Man[i].m_fx)) + (fabs(m_fy) - fabs(GameHandler->Man[i].m_fy))));
          Target_ID = i;
          }
        }
      }
    }

  if((GameHandler->Player[ID].m_iPlayerID % 2) == 1) // Red
    {
    for(i=0;i< 16;i+=2)
      {
      if(GameHandler->Man[i].m_bActive == true && GameHandler->Man[i].m_cStatus != MAN_STATUS_DEAD)
        {
        if((fabs(((fabs(m_fx) - fabs(GameHandler->Man[i].m_fx)) + (fabs(m_fy) - fabs(GameHandler->Man[i].m_fy))))) < Lenght)
          {
          Lenght    = fabs(((fabs(m_fx) - fabs(GameHandler->Man[i].m_fx)) + (fabs(m_fy) - fabs(GameHandler->Man[i].m_fy))));
          Target_ID = i;
          }
        }
      }
    }

  return Target_ID;
  }

//------------------------------------------------------------------
char CBot::Find_Prey(CGameHandler *GameHandler,int ID)
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

//------------------------------------------------------------------
void CBot::Handle(CGameHandler *GameHandler,int ID)
//------------------------------------------------------------------
  {
  ///////////////////////////////////////////////
  //             Reset All Keys                //
  ///////////////////////////////////////////////

  GameHandler->Player[ID].m_bKey_Down      = false;
  GameHandler->Player[ID].m_bKey_Right     = false;
  GameHandler->Player[ID].m_bKey_Left      = false;
  GameHandler->Player[ID].m_bKey_Speed     = false;

  GameHandler->Player[ID].m_bKey_Fire      = false;
  GameHandler->Player[ID].m_bKey_Spec      = false;
  GameHandler->Player[ID].m_bKey_Missile   = false;

  GameHandler->Player[ID].m_bKey_Para      = true;
  GameHandler->Player[ID].m_bKey_ParaDown  = false;
  ///////////////////////////////////////////////
  //             Handle BuyMenu                //
  ///////////////////////////////////////////////

  if(GameHandler->m_cGameState == GAME_STATE_BUYMENU)
    {
    GameHandler->Player[ID].m_bKey_1    = true;
    GameHandler->Player[ID].m_bKey_2    = true;
    GameHandler->Player[ID].m_bKey_3    = true;
    GameHandler->Player[ID].m_bKey_4    = true;
    GameHandler->Player[ID].m_bKey_5    = true;

    return;
    }

  ///////////////////////////////////////////////
  //             Handle Plane                  //
  ///////////////////////////////////////////////

  if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID].m_bPilot == true)
    {
    GameHandler->Player[ID].m_bKey_Speed     = true;

    ///////////////////////////////////////////////////
    //  Jump Out if on Fire/Smoke and to near ground //
    ///////////////////////////////////////////////////

    if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID].m_cDamage > 0)
      {
      if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID  ].m_fy <= -0.0f && GameHandler->Player[ID].m_cUpgrade_Para != 0)
        {
        GameHandler->Player[ID].m_bKey_Para        = true;
        GameHandler->Player[ID].m_bKey_ParaDown    = false;
        }
      }

    ///////////////////////////////////////////////
    //     Don't Use Speed when Pointing Down    //
    ///////////////////////////////////////////////

    if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID].m_fRotate > 140 && GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID  ].m_fRotate < 220)
      {
      GameHandler->Player[ID].m_bKey_Speed        = false;

      ///////////////////////////////////////////////
      //      If to fast/Speedy Down, Turn Up      //
      ///////////////////////////////////////////////
      if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID].m_fSpeed > 2.5f)
        {
        if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID  ].m_fRotate < 180)GameHandler->Player[ID].m_bKey_Right     = true;
        if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID  ].m_fRotate > 180)GameHandler->Player[ID].m_bKey_Left      = true;
        return;
        }
      }

    ///////////////////////////////////////////////
    //  Quick Turn When Plane is To near Ground  //
    ///////////////////////////////////////////////

    if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID  ].m_fy <= -3.0f)
      {
      ///////////////////////
      //----- AI Plan -----//
      ///////////////////////
      // AI Plane need to Point Up
      //-------------------//

      if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID  ].m_fRotate < 180)GameHandler->Player[ID].m_bKey_Right     = true;
      if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID  ].m_fRotate > 180)GameHandler->Player[ID].m_bKey_Left      = true;
      return;
      }


    ///////////////////////////////////////////////
    //    Quick Turn When Plane is To near Sky   //
    ///////////////////////////////////////////////

    if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID  ].m_fy >= 5.0f)
      {
      ///////////////////////
      //----- AI Plan -----//
      ///////////////////////
      // AI Plane need to Point down
      //-------------------//

      if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID  ].m_fRotate < 160)GameHandler->Player[ID].m_bKey_Left     = true;
      if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID  ].m_fRotate > 200)GameHandler->Player[ID].m_bKey_Right    = true;
      return;
      }

    ///////////////////////////////////////////////
    //          Find the nearest Prey            //
    ///////////////////////////////////////////////

    bool Man  = false;
    char Prey = Find_Prey(GameHandler,ID);
    if(Prey == -1)
      {
      Prey = Find_PreyMan(GameHandler,ID);
      Man = true;
      if(Prey == -1)return; // No Enemy?
      }

    ///////////////////////////////////////////////
    //    Find the Rotate radios agains Him      //
    ///////////////////////////////////////////////

    float m_fAimx;
    float m_fAimy;
    float Temp_x;
    float Temp_y;
    float Hypo;
    float Rotate_Cosinus;
    float m_fx = GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID].m_fx;
    float m_fy = GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID].m_fy;

    //----- Finder afstanden til objectet -----//

    if(Man == false)m_fAimx = GameHandler->Plane[Prey].m_fx - m_fx;
    if(Man == false)m_fAimy = GameHandler->Plane[Prey].m_fy - m_fy;
    if(Man == true) m_fAimx = GameHandler->Man[Prey].m_fx - m_fx;
    if(Man == true) m_fAimy = GameHandler->Man[Prey].m_fy - m_fy;

    //-----  Laver tallet om til IKKE minus  -----//

    Temp_x         = fabs(m_fAimx);
    Temp_y         = fabs(m_fAimy);

    //----- Finder afstanden På hyponessen, den aflange side -----//

    Hypo           = sqrt(((Temp_x*Temp_x)+(Temp_y*Temp_y)));

    //-----    Udregner Rotationen for at følge hyponessen   -----//

    Rotate_Cosinus = (((acos ((Temp_y / Hypo))))* 57.0f);

    //-----       Finder hvilke vej Rotation Skal sigte      -----//

    if(Man == false){if(m_fx >  GameHandler->Plane[Prey].m_fx && m_fy >  GameHandler->Plane[Prey].m_fy){Rotate_Cosinus = 180.0f-Rotate_Cosinus;}}
    if(Man == false){if(m_fx >  GameHandler->Plane[Prey].m_fx && m_fy <= GameHandler->Plane[Prey].m_fy){}} // Højre-Bund
    if(Man == false){if(m_fx <= GameHandler->Plane[Prey].m_fx && m_fy >  GameHandler->Plane[Prey].m_fy){Rotate_Cosinus = 180.0f+Rotate_Cosinus;}} // Venstre-Top
    if(Man == false){if(m_fx <= GameHandler->Plane[Prey].m_fx && m_fy <= GameHandler->Plane[Prey].m_fy){Rotate_Cosinus = 180.0f+Rotate_Cosinus;Rotate_Cosinus = 180.0f-Rotate_Cosinus;}} // Venstre-Bund

    if(Man == true){if(m_fx >  GameHandler->Man[Prey].m_fx && m_fy >  GameHandler->Man[Prey].m_fy){Rotate_Cosinus = 180.0f-Rotate_Cosinus;}}
    if(Man == true){if(m_fx >  GameHandler->Man[Prey].m_fx && m_fy <= GameHandler->Man[Prey].m_fy){}} // Højre-Bund
    if(Man == true){if(m_fx <= GameHandler->Man[Prey].m_fx && m_fy >  GameHandler->Man[Prey].m_fy){Rotate_Cosinus = 180.0f+Rotate_Cosinus;}} // Venstre-Top
    if(Man == true){if(m_fx <= GameHandler->Man[Prey].m_fx && m_fy <= GameHandler->Man[Prey].m_fy){Rotate_Cosinus = 180.0f+Rotate_Cosinus;Rotate_Cosinus = 180.0f-Rotate_Cosinus;}} // Venstre-Bund

    if(Rotate_Cosinus > 360.0)Rotate_Cosinus -= 360.0f;
    if(Rotate_Cosinus <   0.0)Rotate_Cosinus += 360.0f;

    //-----       Finder hvilke vej Missilen skal dreje      -----//

    float Right = GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID].m_fRotate,Left = GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID].m_fRotate,Long = 0.0f;

    while(Long < 360.0f)
      {
      if(Rotate_Cosinus <= Right+1.0f && Rotate_Cosinus >= Right-1.0f)
        {
        //m_fRotate += Long;//0.001f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
        GameHandler->Player[ID].m_bKey_Left        = true;
        break;
        }
      if(Rotate_Cosinus <= Left+1.0f && Rotate_Cosinus >= Left-1.0f)
        {
        //m_fRotate -= Long;//0.001f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
        GameHandler->Player[ID].m_bKey_Right        = true;
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

    ///////////////////////////////////////////////
    //            In Shooting Radios             //
    ///////////////////////////////////////////////

    if(Long < 7.5f)
      {
      GameHandler->Player[ID].m_bKey_Fire    = true;
      GameHandler->Player[ID].m_bKey_Spec    = true;
      GameHandler->Player[ID].m_bKey_Missile = true;
      }
    }

  ///////////////////////////////////////////////
  //             Handle Man/Para               //
  ///////////////////////////////////////////////

  if(GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID].m_bPilot == false && (GameHandler->Man[GameHandler->Player[ID].m_iPlayerID].m_cStatus != MAN_STATUS_DEAD))
    {

    ///////////////////////////////////////////////
    //                Man Flying                 //
    ///////////////////////////////////////////////

    if(GameHandler->Man[GameHandler->Player[ID].m_iPlayerID].m_cStatus == MAN_STATUS_FLYING)
      {
      ///////////////////////////////////////////////
      //                Use the Para               //
      ///////////////////////////////////////////////

      if(GameHandler->Man[GameHandler->Player[ID].m_iPlayerID].m_fy < 1.0f)
        {
        GameHandler->Player[ID].m_bKey_Para     = true;
        GameHandler->Player[ID].m_bKey_ParaDown = false;
        }

      }

    ///////////////////////////////////////////////
    //                 Man Para                  //
    ///////////////////////////////////////////////

    if(GameHandler->Man[GameHandler->Player[ID].m_iPlayerID].m_cStatus == MAN_STATUS_PARACHUTING)
      {
      ///////////////////////////////////////////////
      //                Avoid Planes               //
      ///////////////////////////////////////////////

      char Avoid = Find_Prey(GameHandler,ID);

      if(Avoid != -1)
        {
        if(GameHandler->Plane[Avoid].m_fx < GameHandler->Man[GameHandler->Player[ID].m_iPlayerID].m_fx)GameHandler->Player[ID].m_bKey_Right = true;
        if(GameHandler->Plane[Avoid].m_fx > GameHandler->Man[GameHandler->Player[ID].m_iPlayerID].m_fx)GameHandler->Player[ID].m_bKey_Left  = true;
        }
      }

    ///////////////////////////////////////////////
    //               Man On Ground               //
    ///////////////////////////////////////////////

    if(GameHandler->Man[GameHandler->Player[ID].m_iPlayerID].m_cStatus == MAN_STATUS_GROUND)
      {
      ///////////////////////////////////////////////
      //           Looking for Enemies             //
      ///////////////////////////////////////////////

      char Prey = -1;
      bool Man    = true;

      //----- Target Man/Para -----//

      Prey = Find_PreyMan(GameHandler,ID);

      //-----  Target Planes  -----//

      if(Prey == -1)
        {
        Prey = Find_Prey(GameHandler,ID);
        Man = false;
        }

      if(Prey != -1)
        {
        //-------  Rotate Gun  ------//

        float m_fAimx;
        float m_fAimy;
        float Temp_x;
        float Temp_y;
        float Hypo;
        float Rotate_Cosinus;
        float m_fx = GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID].m_fx;
        float m_fy = GameHandler->Plane[GameHandler->Player[ID].m_iPlayerID].m_fy;

        //----- Finder afstanden til objectet -----//

        if(Man == false)m_fAimx = GameHandler->Plane[Prey].m_fx - m_fx;
        if(Man == false)m_fAimy = GameHandler->Plane[Prey].m_fy - m_fy;
        if(Man == true) m_fAimx = GameHandler->Man[Prey].m_fx - m_fx;
        if(Man == true) m_fAimy = GameHandler->Man[Prey].m_fy - m_fy;

        //-----  Laver tallet om til IKKE minus  -----//

        Temp_x         = fabs(m_fAimx);
        Temp_y         = fabs(m_fAimy);

        //----- Finder afstanden På hyponessen, den aflange side -----//

        Hypo           = sqrt(((Temp_x*Temp_x)+(Temp_y*Temp_y)));

        //-----    Udregner Rotationen for at følge hyponessen   -----//

        Rotate_Cosinus = (((acos ((Temp_y / Hypo))))* 57.0f);

        //-----       Finder hvilke vej Rotation Skal sigte      -----//

        if(Man == false){if(m_fx >  GameHandler->Plane[Prey].m_fx && m_fy >  GameHandler->Plane[Prey].m_fy){Rotate_Cosinus = 0.0f-Rotate_Cosinus;}}
        if(Man == false){if(m_fx >  GameHandler->Plane[Prey].m_fx && m_fy <= GameHandler->Plane[Prey].m_fy){}} // Højre-Bund
        if(Man == false){if(m_fx <= GameHandler->Plane[Prey].m_fx && m_fy >  GameHandler->Plane[Prey].m_fy){Rotate_Cosinus = 0.0f+Rotate_Cosinus;}} // Venstre-Top
        if(Man == false){if(m_fx <= GameHandler->Plane[Prey].m_fx && m_fy <= GameHandler->Plane[Prey].m_fy){Rotate_Cosinus = 0.0f+Rotate_Cosinus;Rotate_Cosinus = 0.0f-Rotate_Cosinus;}} // Venstre-Bund

        if(Man == true){if(m_fx >  GameHandler->Man[Prey].m_fx && m_fy >  GameHandler->Man[Prey].m_fy){Rotate_Cosinus = 0.0f-Rotate_Cosinus;}}
        if(Man == true){if(m_fx >  GameHandler->Man[Prey].m_fx && m_fy <= GameHandler->Man[Prey].m_fy){}} // Højre-Bund
        if(Man == true){if(m_fx <= GameHandler->Man[Prey].m_fx && m_fy >  GameHandler->Man[Prey].m_fy){Rotate_Cosinus = 0.0f+Rotate_Cosinus;}} // Venstre-Top
        if(Man == true){if(m_fx <= GameHandler->Man[Prey].m_fx && m_fy <= GameHandler->Man[Prey].m_fy){Rotate_Cosinus = 0.0f+Rotate_Cosinus;Rotate_Cosinus = 0.0f-Rotate_Cosinus;}} // Venstre-Bund

        if(Rotate_Cosinus > 360.0)Rotate_Cosinus -= 360.0f;
        if(Rotate_Cosinus <   0.0)Rotate_Cosinus += 360.0f;

        //-----       Finder hvilke vej Missilen skal dreje      -----//

        float Right = GameHandler->Man[GameHandler->Player[ID].m_iPlayerID].m_fRotate,Left = GameHandler->Man[GameHandler->Player[ID].m_iPlayerID].m_fRotate,Long = 0.0f;

        while(Long < 360.0f)
          {
          if(Rotate_Cosinus <= Right+1.0f && Rotate_Cosinus >= Right-1.0f)
            {
            //m_fRotate += Long;//0.001f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
            GameHandler->Player[ID].m_bKey_Speed        = true;
            break;
            }
          if(Rotate_Cosinus <= Left+1.0f && Rotate_Cosinus >= Left-1.0f)
            {
            //m_fRotate -= Long;//0.001f * 80.0f *(float)Temp_Engine->Timer.GetDeltaMs();
            GameHandler->Player[ID].m_bKey_Down        = true;
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
        //------ Shot Constantly -----//

//        if(Long <= 10.0f)
//          {
          GameHandler->Player[ID].m_bKey_Fire    = true;
          GameHandler->Player[ID].m_bKey_Spec    = true;
          GameHandler->Player[ID].m_bKey_Missile = true;
//          }
        }
      }

    }
  }

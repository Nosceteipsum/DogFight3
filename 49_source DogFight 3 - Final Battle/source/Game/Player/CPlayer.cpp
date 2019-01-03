////////////////////////////////////////////////////////////////////
//                                                                //
//               DF 3: Player_CPP                                 //
//                                                                //
//         Made By: Tommy Kobberø Andersen                        //
//                                                                //
////////////////////////////////////////////////////////////////////

#include "../../../global.h"

//------------------------------------------------------------------
CPlayer::CPlayer()
//------------------------------------------------------------------
  {
  m_iPlayerID = -1;
  m_bActive   = false;
  }

//------------------------------------------------------------------
CPlayer::~CPlayer()
//------------------------------------------------------------------
  {

  }

//------------------------------------------------------------------
void CPlayer::Init()
//------------------------------------------------------------------
  {
  m_bActive          = true;
  m_bAI              = false;

  m_bKey_Down        = false;
  m_bKey_Right       = false;
  m_bKey_Left        = false;
  m_bKey_Speed       = false;

  m_bKey_Fire        = false;
  m_bKey_Spec        = false;
  m_bKey_Missile     = false;

  m_bKey_Para        = false;
  m_bKey_ParaDown    = false;
 
  m_iPlayerID        = -1;

  m_cUpgrade_Para    = 0;
  m_cUpgrade_Spec    = 0;
  m_cUpgrade_Fire    = 0;
  m_cUpgrade_Plane   = 0;
  m_cUpgrade_Missile = 0;

  m_iHits            = 0;
  m_iMoney           = 0;
  }
//------------------------------------------------------------------
void CPlayer::DeInit()
//------------------------------------------------------------------
  {
  m_iPlayerID = -1;
  m_bActive   = false;
  }


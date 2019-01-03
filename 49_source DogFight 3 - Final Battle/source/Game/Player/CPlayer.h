////////////////////////////////////////////////////////////////////
//                                                                //
//              DF 3: Player_h                                    //
//                                                                //
//           Made By: Tommy Kobberø Andersen                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#if!defined CPLAYER_H
#define CPLAYER_H

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

#pragma pack(push)
#pragma pack(1)


class CPlayer
{
public:

  CPlayer();
  ~CPlayer();

  void CheckKey();

  void Init();
  void DeInit();

  char  m_caName[22];

  bool  m_bActive;
  bool  m_bAI;

  bool  m_bKey_1;
  bool  m_bKey_2;
  bool  m_bKey_3;
  bool  m_bKey_4;
  bool  m_bKey_5;

  bool  m_bKeyPress_1;
  bool  m_bKeyPress_2;
  bool  m_bKeyPress_3;
  bool  m_bKeyPress_4;
  bool  m_bKeyPress_5;

  bool  m_bKey_Down;
  bool  m_bKey_Right;
  bool  m_bKey_Left;
  bool  m_bKey_Speed;

  bool  m_bKey_Fire;
  bool  m_bKey_Spec;
  bool  m_bKey_Missile;

  bool  m_bKey_Para;
  bool  m_bKey_ParaDown;

  char  m_iPlayerID;

  char  m_cUpgrade_Para;
  char  m_cUpgrade_Spec;
  char  m_cUpgrade_Fire;
  char  m_cUpgrade_Plane;
  char  m_cUpgrade_Missile;

  short m_iHits;
  short m_iMoney;
  char  m_iPunish;

  float m_fFireOverload;
  float m_fSpecOverload;

  bool  m_bHitMe[16];
protected:
private:
};
#pragma pack(pop)

#endif

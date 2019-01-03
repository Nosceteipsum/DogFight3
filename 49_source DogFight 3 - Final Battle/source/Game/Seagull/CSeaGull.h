////////////////////////////////////////////////////////////////////
//                                                                //
//              DF 3: Animal_h                                   //
//                                                                //
//           Made By: Tommy Kobberø Andersen                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#if!defined CSEAGULL_H
#define CSEAGULL_H

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

class CSeaGull
{
public:

  CSeaGull();
  ~CSeaGull();

  void Move(SData *Data,SEngine *Temp_Engine,CGameHandler *GameHandler,char ID);
  void Draw(SData *Data);
  void Draw_Blood(SData *Data);
  void Init();

  bool  m_bActive;
bool  m_bWake;
bool  m_bDead;
bool  m_bLeft;

float m_fSize;

float m_fSpeed;
float m_fRotateBird;
float m_fRotate;
float m_fMove;
float m_fX;
float m_fY;
float m_fDX;
float m_fDY;

float m_fFlyValue;
char  m_cFlyState;

bool  m_bBlood[200];
float m_fBloodX[200];
float m_fBloodY[200];

float   m_fGullSliding;
char    m_cType;
char    m_cWhoHittedMe;
bool    m_bGullSplash;

protected:
private:
};

#endif

////////////////////////////////////////////////////////////////////
//                                                                //
//             DF 3: Man_h                                        //
//                                                                //
//         Made By: Tommy Kobberø Andersen                        //
//                                                                //
////////////////////////////////////////////////////////////////////

#if!defined CMAN_H
#define CMAN_H

struct SData;

#define MAN_STATUS_FLYING            0
#define MAN_STATUS_PARACHUTING       1
#define MAN_STATUS_GROUND            2
#define MAN_STATUS_DEAD              3
#define MAN_STATUS_BEHIND_PLANE      4

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

class CMan
{
public:

  CMan();
  ~CMan();

  void JumpOut(float x,float y,float Speed,float Rotate);

  void Draw_Blood(SData *Data);

  void Draw(SData *Data,bool DrawArrow);
  void Move(CGameHandler *GameHandler,SEngine *Temp_Engine,bool Left,bool Right,bool Up,bool Down,char ID);

  void SetType(char Type);

  char  m_cStartNR;

  bool  m_bActive;
  char  m_cStatus;

  float m_fPara_Folding_Out;
  float m_fx,m_fy,m_fRotate,m_fManRotate;
  float m_fSpeed;

  char  m_cType;

  char  m_cSplash;
  bool  m_bSplashPara;
  
  float m_fManSlidingOf;

  float m_fSize;

  float m_fSpeedBx;

  char  m_cSittingBackPlane;

  bool  m_bBlood[100];
  float m_fBloodX[100];
  float m_fBloodY[100];

protected:
private:
};

#endif

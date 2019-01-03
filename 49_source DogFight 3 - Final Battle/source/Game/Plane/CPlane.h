////////////////////////////////////////////////////////////////////
//                                                                //
//             DF 3: Plane_h                                      //
//                                                                //
//         Made By: Tommy Kobberø Andersen                        //
//                                                                //
////////////////////////////////////////////////////////////////////

#if!defined CPLANE_H
#define CPLANE_H

#define PLANE_DAMAGE_SHIELD -1
#define PLANE_DAMAGE_NONE    0
#define PLANE_DAMAGE_SMOKE   1
#define PLANE_DAMAGE_FIRE    2
#define PLANE_DAMAGE_CRASHED 3
#define PLANE_DAMAGE_APART   4

#define PLANE_TYPE_NORMAL    0
#define PLANE_TYPE_SPEED     1
#define PLANE_TYPE_SHIELD    2
#define PLANE_TYPE_TURN_RATE 3
#define PLANE_TYPE_STEALTH   4

struct SData;
class CGameHandler;

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

class CPlane
{
public:

  CPlane();
  ~CPlane();

  void Init(SEngine *Temp_Engine,char StartNr);

  void Draw(SData *Data,bool YourSelf);

  void Draw_Plane(SData *Data,bool YourSelf);
  void Draw_PlaneApart(SData *Data);
  void Draw_Smoke(SData *Data);
  void Draw_Fire (SData *Data);
  void Draw_Shield(SData *Data);

  void Move(SData *Data,CGameHandler *GameHandler,SEngine *Temp_Engine,bool Up,bool Left,bool Right,char ID,char PlayerID);

  void Hit(CGameHandler *GameHandler,char ID,char Damage,char Projectile,SEngine *Temp_Engine);

  void SetType(char Type);

  float m_fShield;

  bool  m_bOcupied;
  bool  m_bInGame;
  bool  m_bPilot;

  char  m_cDamage;
  char  m_cType;
  char  m_cStartNR;

  float m_fx,m_fy,m_fRotate;
  float m_fSpeed;

  bool  m_bPunish;

  float m_fPoision;
  bool  m_bPoision_Soft_Active;
  bool  m_bPoision_Hard_Active;

  float m_fStealth;
  bool  m_bStealthUp;

  bool  m_bAppartDontFall;

  float m_fSize;

  float m_fTop_Punish;

  float m_fxApartLenght;

  float m_fSmokeLife[100];
  float m_fSmokeX[100];
  float m_fSmokeY[100];

  float m_fFireLife[100];
  float m_fFireX[100];
  float m_fFireY[100];

  bool  m_bBoostReady;
  float m_fBoostLive;

protected:
private:


};

#endif

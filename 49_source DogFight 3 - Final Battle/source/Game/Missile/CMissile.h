////////////////////////////////////////////////////////////////////
//                                                                //
//              DF 3: Missile_h                                   //
//                                                                //
//           Made By: Tommy Kobberø Andersen                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#if!defined CMISSILE_H
#define CMISSILE_H

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

class CMissile
{
public:

  CMissile();
  ~CMissile();

  void Draw_Fuel(SData *Data);
  void Draw(SData *Data);
  void Create(float x,float y,float Rotate,char Lock,CGameHandler *GameHandler,int ID);
  void Move(CGameHandler *GameHandler,SEngine *Temp_Engine,char ID);
  void FollowTarget(SEngine *Temp_Engine);
  void SetType(char Type);
  char Find_Prey(CGameHandler *GameHandler,int ID);

  bool  m_bDead;
  bool  m_bUsed;
  float m_fSpeed;

  float m_fFuel;

  char  m_cGuided_Lock;

  char  m_cType;

  float m_fSize;

  float m_fx;
  float m_fy;
  float m_fRotate;

  float m_fFuelSkyX[50];
  float m_fFuelSkyY[50];
  float m_fFuelSkyLife[50];

  bool  m_bPlasma;
  float m_fPlasmaLife;

protected:
private:
};

#endif

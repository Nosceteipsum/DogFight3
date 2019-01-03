////////////////////////////////////////////////////////////////////
//                                                                //
//              DF 3: Fire_h                                      //
//                                                                //
//           Made By: Tommy Kobberø Andersen                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#if!defined CFIRE_H
#define CFIRE_H

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

#define FIRE_TYPE_NORMAL   0

class CFire
{
public:

  CFire();
  ~CFire();

  void Draw(SData *Data,bool YourSelf);
  void Create(float x,float y,float Rotate,float Speed);
  void Move(CGameHandler *GameHandler,SEngine *Temp_Engine);
  void SetType(char Type);

  bool  m_bActive;

  char  m_cType;

  float m_fSize;
  float m_fSpeed;

  float m_fx;
  float m_fy;
  float m_fRotate;

protected:
private:
};

#endif

////////////////////////////////////////////////////////////////////
//                                                                //
//              DF 3: Spec_h                                      //
//                                                                //
//           Made By: Tommy Kobberø Andersen                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#if!defined CSPEC_H
#define CSPEC_H

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

class CSpec
{
public:

  CSpec();
  ~CSpec();

  void Draw(SData *Data);
  void Create(float x,float y,float Rotate,float Speed);
  void Move(SEngine *Temp_Engine);
  void SetType(char Type);

  bool  m_bActive;

  char  m_cType;

  float m_fSize;

  float m_fSpeed;
  float m_fx;
  float m_fy;
  float m_fRotate;

  float m_fStun;
  bool  m_bStun_Active;

protected:
private:
};

#endif

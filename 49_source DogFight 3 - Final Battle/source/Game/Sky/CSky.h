////////////////////////////////////////////////////////////////////
//                                                                //
//              DF 3: Sky_h                                       //
//                                                                //
//           Made By: Tommy Kobberø Andersen                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#if!defined CSKY_H
#define CSKY_H

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

class CSky
{
public:

  CSky();
  ~CSky();

  void Draw(SData *Data);
  void Init(SEngine *Temp_Engine,CGameHandler *GameHandler);
  void Move(SEngine *Temp_Engine,CGameHandler *GameHandler);

  bool  m_bActive;

  float m_fX;
  float m_fY;

  float m_fSize;
  float m_fSpeed;
  float m_fBlend;
  
  bool  m_bConfuse;

protected:
private:
};

#endif

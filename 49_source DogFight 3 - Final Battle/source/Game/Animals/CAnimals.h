////////////////////////////////////////////////////////////////////
//                                                                //
//              DF 3: Animal_h                                   //
//                                                                //
//           Made By: Tommy Kobberø Andersen                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#if!defined CANIMAL_H
#define CANIMAL_H

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

class CAnimal
{
public:

  CAnimal();
  ~CAnimal();

  void Move(SData *Data,SEngine *Temp_Engine,CGameHandler *GameHandler);
  void Draw(SData *Data);
  void Init();
  char Find_PreyMan(CGameHandler *GameHandler);

bool  m_bActive;

bool  m_bDead;
bool  m_bLeft;

float m_fSize;

char  m_cType;

float m_fMove;
float m_fX;
float m_fX_Dest;

bool  m_bJumpUp;
float m_fJump;

protected:
private:
};

#endif

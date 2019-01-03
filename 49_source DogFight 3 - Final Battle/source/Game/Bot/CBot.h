////////////////////////////////////////////////////////////////////
//                                                                //
//              DF 3: Bot_h                                       //
//                                                                //
//           Made By: Tommy Kobberø Andersen                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#if!defined CBot_H
#define CBot_H

class CGameHandler;

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

class CBot
{
public:

  CBot();
  ~CBot();

  void Handle(CGameHandler *GameHandler,int ID);
  char Find_Prey(CGameHandler *GameHandler,int ID);
  char Find_PreyMan(CGameHandler *GameHandler,int ID);

protected:
private:
};

#endif

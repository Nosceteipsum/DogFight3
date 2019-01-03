////////////////////////////////////////////////////////////////////
//                                                                //
//              DF 3: Network_h                                   //
//                                                                //
//           Made By: Tommy Kobberø Andersen                      //
//                                                                //
////////////////////////////////////////////////////////////////////

#if!defined CNETWORK_H
#define CNETWORK_H

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

//--------------------------------------------------------//
//--                       DEFINES                      --//
//--------------------------------------------------------//

#define PACKET_CLIENT_JOIN              - 1
#define PACKET_CLIENT_JOINTEAM          - 2
#define PACKET_CLIENT_QUIT              - 3
#define PACKET_CLIENT_KEYUPDATE         - 4
#define PACKET_CLIENT_DISABLESEAGULL    - 5
#define PACKET_CLIENT_SEAGULLMOVE       - 6

#define PACKET_SERVER_JOIN_ACCEPTED       1
#define PACKET_SERVER_JOINTEAM_ANSWER     2
#define PACKET_SERVER_QUIT                3
#define PACKET_SERVER_DATARESET           4
#define PACKET_SERVER_SHOTUPDATE          5
#define PACKET_SERVER_ANIMALUPDATE        6
#define PACKET_SERVER_PLANEUPDATE         7
#define PACKET_SERVER_PLAYERUPDATE        8
#define PACKET_SERVER_INITUPDATE          9
#define PACKET_SERVER_BUYMENUOVER        10  
#define PACKET_SERVER_UPDATEPLANESTATUS  11  
#define PACKET_SERVER_GAMEBEGIN          12  
#define PACKET_SERVER_SYNCSKY            13  
#define PACKET_SERVER_GAMEOVER           14  
#define PACKET_SERVER_SYNCANIMAL         15
#define PACKET_SERVER_BUYPACK            16
#define PACKET_SERVER_SHOTPACK           17
#define PACKET_SERVER_KEYUPDATE          18
#define PACKET_SERVER_SYNCPLANE          19
#define PACKET_SERVER_PLANEHIT           20
#define PACKET_SERVER_PLANEHITGROUND     21
#define PACKET_SERVER_EJECTMAN           22
#define PACKET_SERVER_PARACHUTEMAN       23
#define PACKET_SERVER_ANIMALCOLLISION    24
#define PACKET_SERVER_ICEMELT            25
#define PACKET_SERVER_REMOVESHOT         26
#define PACKET_SERVER_HITMANPARA         27
#define PACKET_SERVER_SPECHIT            28
#define PACKET_SERVER_PLANEAPART         29
#define PACKET_SERVER_WRONGVERSION       30
#define PACKET_SERVER_SEAGULLWAKE        31
#define PACKET_SERVER_SEAGULLHIT         32
#define PACKET_SERVER_SEAGULLHITBYSHOOT  33
#define PACKET_SERVER_PLANEPICKUP        34
#define PACKET_SERVER_STATSLIST          35

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

class CNetwork
{
public:

  CNetwork();
  ~CNetwork();

  void Read_Packet();

  void Server_RecvCheck(SEngine *Engine,CGameHandler *GameHandler);

  void Server_Sync(SEngine *Engine,CGameHandler *GameHandler);
  void Server_Update_MasterServer(SEngine *Engine,CGameHandler *GameHandler);

  void Client_RecvCheck(SEngine *Engine,CGameHandler *GameHandler);

  bool Informate_MasterServer;

protected:
private:
};

#endif

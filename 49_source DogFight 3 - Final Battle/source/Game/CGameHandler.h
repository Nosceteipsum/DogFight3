////////////////////////////////////////////////////////////////////
//                                                                //
//       DF 3: CGameHandler_h                                     //
//                                                                //
//       Made By: Tommy Kobberø Andersen                          //
//                                                                //
////////////////////////////////////////////////////////////////////

#if!defined CGameHandler_H
#define CGameHandler_H

#include "plane/CPlane.h"
#include "map/CMap.h"
#include "Player/CPlayer.h"
#include "Man/CMan.h"
#include "Animals/CAnimals.h"
#include "Network/CNetwork.h"
#include "Bot/CBot.h"
#include "Sky/CSky.h"
#include "Missile/CMissile.h"
#include "SeaGull/CSeaGull.h"

#include "Projectile/CFire.h"
#include "Projectile/CSpec.h"

#include <time.h>

#define GAME_STATE_BUYMENU     1
#define GAME_STATE_PREPARE     2
#define GAME_STATE_GAMING      3
#define GAME_STATE_GAMEOVER    4

#define VERSIONNUMBER 90

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

struct SData
{
  FSOUND_SAMPLE  *Snd_Animal_Cow1;
  FSOUND_SAMPLE  *Snd_Animal_Cow2;
  FSOUND_SAMPLE  *Snd_Animal_Cow3;

  FSOUND_SAMPLE  *Snd_Animal_Sheep1;
  FSOUND_SAMPLE  *Snd_Animal_Sheep2;
  FSOUND_SAMPLE  *Snd_Animal_Sheep3;

  FSOUND_SAMPLE  *Snd_Animal_Hit;

  FSOUND_SAMPLE  *Snd_Man_Die01;
  FSOUND_SAMPLE  *Snd_Man_Die02;
  FSOUND_SAMPLE  *Snd_Man_Die03;
  FSOUND_SAMPLE  *Snd_Man_Die04;
  FSOUND_SAMPLE  *Snd_Man_Die05;
  FSOUND_SAMPLE  *Snd_Man_Die06;
  FSOUND_SAMPLE  *Snd_Man_Die07;

  FSOUND_SAMPLE  *Snd_Man_Falling01;
  FSOUND_SAMPLE  *Snd_Man_Falling02;
  FSOUND_SAMPLE  *Snd_Man_Falling03;
  FSOUND_SAMPLE  *Snd_Man_Falling04;
  FSOUND_SAMPLE  *Snd_Man_Falling05;

  FSOUND_SAMPLE  *Snd_Plane_Crash;
  FSOUND_SAMPLE  *Snd_Plane_Hit_Spec;

  FSOUND_SAMPLE  *Snd_Plane_Hit1;
  FSOUND_SAMPLE  *Snd_Plane_Hit2;
  FSOUND_SAMPLE  *Snd_Plane_Hit3;
  FSOUND_SAMPLE  *Snd_Plane_Hit4;

  FSOUND_SAMPLE  *Snd_Plane_Missile;
  FSOUND_SAMPLE  *Snd_Plane_Shot;
  FSOUND_SAMPLE  *Snd_Plane_Spec;

  FSOUND_SAMPLE  *Snd_Plane_Shield;

  FSOUND_SAMPLE  *Snd_Plane_Collision;
  FSOUND_SAMPLE  *Snd_Plane_Join;

  TextureImageTGA Tex_Animal_SeaGull1L;
  TextureImageTGA Tex_Animal_SeaGull2L;
  TextureImageTGA Tex_Animal_SeaGull1;
  TextureImageTGA Tex_Animal_SeaGull2;
  TextureImageTGA Tex_Animal_GullSplash1;
  TextureImageTGA Tex_Animal_GullSplash2;

  TextureImageTGA Tex_Animal_Giraf1R;
  TextureImageTGA Tex_Animal_Giraf2R;
  TextureImageTGA Tex_Animal_Giraf3R;
  TextureImageTGA Tex_Animal_ElephantR;
  TextureImageTGA Tex_Animal_ElephantL;
  TextureImageTGA Tex_Animal_SheepD;
  TextureImageTGA Tex_Animal_SheepR;
  TextureImageTGA Tex_Animal_SheepL;
  TextureImageTGA Tex_Animal_LionD;
  TextureImageTGA Tex_Animal_LionR;
  TextureImageTGA Tex_Animal_LionL;
  TextureImageTGA Tex_Animal_CowD;
  TextureImageTGA Tex_Animal_CowR;
  TextureImageTGA Tex_Animal_CowL;

  TextureImageTGA Tex_Sky;
  TextureImageTGA Tex_Sky_Dark;

  TextureImageTGA Tex_BuyMenu_Plane_Normal;
  TextureImageTGA Tex_BuyMenu_Plane_Speed;
  TextureImageTGA Tex_BuyMenu_Plane_Shield;
  TextureImageTGA Tex_BuyMenu_Plane_TurnRate;
  TextureImageTGA Tex_BuyMenu_Plane_Stealth;

  TextureImageTGA Tex_BuyMenu_Para_Normal;
  TextureImageTGA Tex_BuyMenu_Para_Faster;
  TextureImageTGA Tex_BuyMenu_Para_QuickMove;
  TextureImageTGA Tex_BuyMenu_Para_Stealth;
  TextureImageTGA Tex_BuyMenu_Para_Ball;

  TextureImageTGA Tex_BuyMenu_Fire_Normal;
  TextureImageTGA Tex_BuyMenu_Fire_Faster;
  TextureImageTGA Tex_BuyMenu_Fire_Damagex2;
  TextureImageTGA Tex_BuyMenu_Fire_Sizex2;
  TextureImageTGA Tex_BuyMenu_Fire_Stealth;

  TextureImageTGA Tex_BuyMenu_Spec_Invert;
  TextureImageTGA Tex_BuyMenu_Spec_Poision;
  TextureImageTGA Tex_BuyMenu_Spec_Stun;
  TextureImageTGA Tex_BuyMenu_Spec_Adv_Poision;
  TextureImageTGA Tex_BuyMenu_Spec_AutoJump;

  TextureImageTGA Tex_BuyMenu_Missile_Normal;
  TextureImageTGA Tex_BuyMenu_Missile_L_Guided;
  TextureImageTGA Tex_BuyMenu_Missile_Guided;
  TextureImageTGA Tex_BuyMenu_Missile_Angry;
  TextureImageTGA Tex_BuyMenu_Missile_Bounce;
  TextureImageTGA Tex_BuyMenu_Missile_Plasma;

  TextureImageTGA Tex_BuyMenu_None;
  TextureImageTGA Tex_BuyMenu_Full;

  TextureImageTGA Tex_Buy_Menu;
  TextureImageTGA Tex_Menu_Select;

  TextureImageTGA Tex_Point;

  TextureImageTGA Tex_Plasma_Particle;
  TextureImageTGA Tex_Spec_Particle;
  TextureImageTGA Tex_Smoke_Particle;
  TextureImageTGA Tex_Fire_Particle;
  TextureImageTGA Tex_Blood_Particle;
  TextureImageTGA Tex_Missile_Particle;

  TextureImageTGA Tex_Grass;
  TextureImageTGA Tex_Farm;
  TextureImageTGA Tex_Ice;
  TextureImageTGA Tex_Ice_DeaD;
  TextureImageTGA Tex_WildGrass; 
  TextureImageTGA Tex_Bridge;
  TextureImageTGA Tex_Bridge_DeaD;

  TextureImageTGA Tex_Ball; 

  TextureImageTGA Tex_Green_Man; 
  TextureImageTGA Tex_Green_Para; 

  TextureImageTGA Tex_Green_Plane; 
  TextureImageTGA Tex_Green_Plane_Part1; 
  TextureImageTGA Tex_Green_Plane_Part2; 
  TextureImageTGA Tex_Green_Plane_Part3; 

  TextureImageTGA Tex_Red_Man; 
  TextureImageTGA Tex_Red_Para; 

  TextureImageTGA Tex_Red_Plane; 
  TextureImageTGA Tex_Red_Plane_Part1; 
  TextureImageTGA Tex_Red_Plane_Part2; 
  TextureImageTGA Tex_Red_Plane_Part3; 

  TextureImageTGA Tex_Tree1;
  TextureImageTGA Tex_Tree2;
  TextureImageTGA Tex_Tree3;

  GLUquadricObj     *Sphere;
};

#pragma pack(push)
#pragma pack(1)

class CGameHandler
{
public:

  CGameHandler();
  ~CGameHandler();

  char AI_FindPrey();
  void AI_Handle();

  void Ping_MasterServer(SEngine *Engine);

  void Collision_Draw(SEngine *Engine,float x,float y,float xSize,float ySize);
  bool Collision_Detect(float x_1,float y_1,float x_Size,float y_Size,float x_2,float y_2,float x_2Size,float y_2Size);
  void Collision_Handle(SEngine *Engine);
  void Collision_Handle_Draw(SEngine *Engine);

  void BuyMenu_Draw(SEngine *Engine);
  void BuyMenu_Handle(SEngine *Engine);

  void Draw_GameScore(SEngine *Engine);
  void Draw_Score(SEngine *Engine);
  void Draw_Names(SEngine *Engine);

  void Load(SEngine *Engine);
  void Load_Data(SEngine *Engine);

  void UnLoad_Data(SEngine *Engine);
  void UnLoad(SEngine *Engine);

  void Add_AI(bool Green,bool Red,bool Add);

  void GameReset(SEngine *Engine);

  bool Main_Handle(SEngine *Engine); // Draw All Graphics, Handle Every Update/Moves...
  void Main_Handle_Graphics(SEngine *Engine);
  void Main_Handle_Update(SEngine *Engine);

  bool Server_Handle(SEngine *Engine); // Handle Network
  bool Client_Handle(SEngine *Engine); // Handle Network

  void DrawFPS(SEngine *Engine);

  void Draw_TeamSelect();

  void Draw_KillBox(SEngine *Engine);
  void Add_ToStats(int Target,int Source,int ByWhat,SEngine *Engine);

  void Server_Network_Handle(SEngine *Engine);
  bool Client_Network_Handle(SEngine *Engine);

  void Handle_Prepare(SEngine *Engine); 
  void Handle_GameOver(SEngine *Engine);

  bool Check_GameOver();

  char Find_Owner(char a);

  void CheckLock(CGameHandler *GameHandler,SEngine *Temp_Engine);
  void DrawLock(SData *Data);

  int  Join_Team(bool Green,bool Red); // Returning ID, if -1 no room free!

  void Server_Network_Send(char Status,SEngine *Engine);
  void Server_Network_SendBuyMenu(char PlayerNr,char Type,SEngine *Temp_Engine);
  void Server_Network_SendShot(char Type,char PlaneNr,SEngine *Temp_Engine);
  void Server_Network_KeyUpdate(char PlayerNr,SEngine *Temp_Engine);
  void Server_Network_SendPlaneHit(char PlayerNr,char Damage,char Projectile,SEngine *Temp_Engine);
  void Server_Network_PlaneHitGround(char PlayerNr,SEngine *Temp_Engine);
  void Server_Network_EjectFromPlane(char PlayerNr,SEngine *Temp_Engine);
  void Server_Network_ParachuteMan(char PlayerNr,SEngine *Temp_Engine);
  void Server_Network_AnimalCollision(char AnimalNr,char Projectile,SEngine *Temp_Engine);
  void Server_Network_IceMelt(char field,char FireNr,SEngine *Temp_Engine);
  void Server_Network_RemoveShot(char type,char Nr,SEngine *Temp_Engine);
  void Server_Network_ManParaHit(char type,char ManNr,char SourceNr,SEngine *Temp_Engine);
  void Server_Network_SpecHit(char PlaneNr,char SpecNr,SEngine *Temp_Engine);
  void Server_Network_StopAppart(char PlaneNr,SEngine *Temp_Engine);

  void Server_Network_SeaGullShotHit(char SeaGull,char Projectile,char ProjectileNr,SEngine *Temp_Engine);
  void Server_Network_SeaGullMove(char Seagull,float m_fx,float m_fy,SEngine *Temp_Engine);
  void Server_Network_SeaGullPlaneHit(char PlaneNr,char SeaGull,SEngine *Temp_Engine);

  void Server_Network_PlanePickUp(char PlaneNr,char Man,SEngine *Temp_Engine);

  int     m_iNetWorkID;
  int     m_iFPS;

  unsigned char    m_cGameState;

  CPlayer  Player[16];
  CMan     Man[16];
  CPlane   Plane[16];
  CMap     Map;

  CFire    Fire[16];
  CSpec    Spec[16];
  CSky     Sky[3];
  CMissile Missile[16];

  CAnimal  Animal[2];

  unsigned char      Red_Score;
  unsigned char      Green_Score;

  SData   m_sData;

  CSeaGull SeaGull[9];

  int     m_iStatsByWho[10];
  int     m_iStatsByWhat[10];
  int     m_iStatsWhoHit[10];
  float   m_fStatsLife[10];

protected:
private:

  bool    m_bAI_KeyPress;
  bool    m_bBailActivate;

  bool    m_bCOLLISION_Show;

  bool    m_bWaitingOnReset;
  bool    m_bGreenWin;

  bool    m_bFPS_Show;
  float   m_fFPS_Second;
  int     m_iFPS_Frames,m_iFPS_Temp_Frames;

  bool    m_bSelectingTeam;

  float   m_fPrepareTimer;
  float   m_fGameOverTimer;
  float   m_fBuyMenuTimer;
  float   m_fMasterServerTimer;

  double  m_dTime;

  float   m_fGlobalDataPacket;

  char    m_cManHit;

  bool    m_bClientSeaGullCheat;
  bool    m_bServerSeaGullCheat;

  CBot    Bot;
};

#pragma pack(pop)

//--------------------------------------------------------//
//--			Prototypes			--//
//--------------------------------------------------------//


#endif

////////////////////////////////////////////////////////////////////
//								  //
//	  	     DF3 : WinMain_h   			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined WinMain_H
#define WinMain_H

//--------------------------------------------------------//
//--			Prototypes			--//
//--------------------------------------------------------//

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int);
int CALLBACK Window_Main(HWND,UINT,WPARAM,LPARAM);
int CALLBACK Window_AdvServer(HWND,UINT,WPARAM,LPARAM);
int CALLBACK Window_MasterServer(HWND hwnd,UINT msg,WPARAM wParam, LPARAM lParam);

//--------------------------------------------------------//
//--			Struct/classes			--//
//--------------------------------------------------------//

struct SSettings
{
int  AddToMasterServer;
int  FullScreen;
int  Resolution;
int  FrameLimiter;
int  BuyTime;
char NickName[75];
char Ip[22];
int  Port;
};

class SEngine
{
public:

  SEngine();
  ~SEngine();

  void Error_Check();

  SSettings m_sSettings;

  HWND          hwnd_Main;
  HWND	        hwnd_opengl;
  bool 		    Exit,Server;
  MSG	   	Msg;

  char                Nils_Protecting;

  COpenGl_Window      OpenGl_Window;
  COpenGl_Camera      OpenGl_Camera;
  COpenGl_Font        OpenGl_Font;
  COpenGl_Texture_TGA OpenGl_Texture_TGA;
  CRegEdit            RegEdit;
  CWinSock            WinSock;
  CTimer              Timer;
  CKey                Key;
  CInternet           Internet;
};


#endif

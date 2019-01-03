////////////////////////////////////////////////////////////////////
//								  //
//	  	  DF 3: WinMain_cpp			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "../../global.h"

//------------------------------------//
//--	      Global Data	    --//
////////////////////////////////////////

SEngine        *Engine;

//------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hinstance,HINSTANCE hprevinstance,LPSTR lpcmdline,int nshowcmd)
//------------------------------------------------------------------
{
Engine   =   new SEngine;

DialogBox(hinstance,MAKEINTRESOURCE(IDD_MAIN)  ,NULL,Window_Main);

if(Engine->Exit == false)
  {
  MSG          Msg;
  CGameHandler *GameHandler = new CGameHandler;

  //----- Settings Resoulution -----//

  int x,y,bits;
  bool Fullscreen = 0;

  if(Engine->m_sSettings.FullScreen == 1)Fullscreen = 1;
  else                                   Fullscreen = 0;
  if(Engine->m_sSettings.Resolution == 0){x =  640;y =  480;bits=16;}
  if(Engine->m_sSettings.Resolution == 1){x =  640;y =  480;bits=32;}
  if(Engine->m_sSettings.Resolution == 2){x =  800;y =  600;bits=16;}
  if(Engine->m_sSettings.Resolution == 3){x =  800;y =  600;bits=32;}
  if(Engine->m_sSettings.Resolution == 4){x = 1024;y =  768;bits=16;}
  if(Engine->m_sSettings.Resolution == 5){x = 1024;y =  768;bits=32;}
  if(Engine->m_sSettings.Resolution == 6){x = 1280;y = 1024;bits=16;}
  if(Engine->m_sSettings.Resolution == 7){x = 1280;y = 1024;bits=32;}

  Engine->OpenGl_Window.CreateGLWindow("DF3 - Final Battle",x,y,bits,Fullscreen,hinstance,&Engine->hwnd_opengl,Engine->Nils_Protecting);
  GameHandler->Load(Engine);

  //----- SERVER -----//

  if(Engine->Server == true)
    {
    GameHandler->m_iNetWorkID = 0; // Server ID. Always Zerro
    GameHandler->Player[0].Init();
    ZeroMemory(GameHandler->Player[0].m_caName,sizeof(GameHandler->Player[0].m_caName));
    memcpy(GameHandler->Player[0].m_caName,Engine->m_sSettings.NickName,19);

	Engine->WinSock.Server_StartServer(Engine->m_sSettings.Port);
    }

  //----- CLIENT -----//
  else
    {
	GameHandler->m_iNetWorkID = -1;

	Engine->WinSock.Client_Init();
	Engine->WinSock.Client_Connect(Engine->m_sSettings.Ip,Engine->m_sSettings.Port);

	char Packet[101];
	Packet[0] = PACKET_CLIENT_JOIN;
	Packet[1] = VERSIONNUMBER;
    memcpy(Packet+2,Engine->m_sSettings.NickName,sizeof(Engine->m_sSettings.NickName));

	Engine->WinSock.Client_SendData(Packet,76);
    }


  //----------------------------------------------------------------------------------
  while(Engine->Exit == false && Engine->OpenGl_Window.Error_Check() == false)
  //----------------------------------------------------------------------------------
    { 
    if(PeekMessage(&Msg,Engine->hwnd_opengl,0,0,PM_REMOVE))
      {
      TranslateMessage(&Msg);
      DispatchMessage(&Msg);
      }
    Engine->Exit = GameHandler->Main_Handle(Engine);
    }

  if(Engine->Server == false && GameHandler->m_iNetWorkID != -1)
  {
  char Packet[5];
  Packet[0] = PACKET_CLIENT_QUIT;
  Packet[1] = GameHandler->m_iNetWorkID;

  Engine->WinSock.Client_SendData(Packet,2);
  }

  if(Engine->Server == true && GameHandler->m_iNetWorkID != -1)
  {
  char Packet[3];
  Packet[0] = PACKET_SERVER_QUIT;

    for(int i=1;i < 16;i++)
    {
      if(GameHandler->Player[i].m_bActive == true)
      {
        Engine->WinSock.Server_LoadIP(i);
        Engine->WinSock.Server_SendData(Packet,1);
      }
    }
  }

  Engine->OpenGl_Window.KillGlWindow(Engine->hwnd_opengl,hinstance);
  GameHandler->UnLoad(Engine);
  delete GameHandler;
  }

  if(Engine->Server == true)
    {
	Engine->WinSock.Server_DeInit();
    }

  //----- CLIENT -----//
  else
    {
	Engine->WinSock.Client_ShutDown();
    }

delete Engine;

return 0;
}

//--------------------------------------------------------
int CALLBACK Window_Main(HWND hwnd,UINT msg,WPARAM wParam, LPARAM lParam)
//--------------------------------------------------------
{
switch(msg)
  {
  case WM_INITDIALOG:
    {
    SendMessage(hwnd,WM_SETICON,ICON_SMALL,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));
    SendMessage(hwnd,WM_SETICON,ICON_BIG,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));

    Engine->hwnd_Main = hwnd;

    PostMessage(GetDlgItem(hwnd,IDC_NICKNAME),EM_SETLIMITTEXT,70,0);
    PostMessage(GetDlgItem(hwnd,IDC_IP),EM_SETLIMITTEXT,19,0);
    PostMessage(GetDlgItem(hwnd,IDC_PORT),EM_SETLIMITTEXT,5,0);

    SendDlgItemMessage(hwnd,IDC_FRAMELIMITER,CB_ADDSTRING,0,(LPARAM)"05 Frames");
    SendDlgItemMessage(hwnd,IDC_FRAMELIMITER,CB_ADDSTRING,0,(LPARAM)"10 Frames");
    SendDlgItemMessage(hwnd,IDC_FRAMELIMITER,CB_ADDSTRING,0,(LPARAM)"25 Frames");
    SendDlgItemMessage(hwnd,IDC_FRAMELIMITER,CB_ADDSTRING,0,(LPARAM)"33 Frames");
    SendDlgItemMessage(hwnd,IDC_FRAMELIMITER,CB_ADDSTRING,0,(LPARAM)"50 Frames");
    SendDlgItemMessage(hwnd,IDC_FRAMELIMITER,CB_ADDSTRING,0,(LPARAM)"60 Frames");
    SendDlgItemMessage(hwnd,IDC_FRAMELIMITER,CB_ADDSTRING,0,(LPARAM)"66 Frames");
    SendDlgItemMessage(hwnd,IDC_FRAMELIMITER,CB_ADDSTRING,0,(LPARAM)"75 Frames");
    SendDlgItemMessage(hwnd,IDC_FRAMELIMITER,CB_ADDSTRING,0,(LPARAM)"Unlimitted");

    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)" 640*480*16");
    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)" 800*600*16");
    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)"1024*768*16");
    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)"1280*1024*16");

    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)" 640*480*32");
    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)" 800*600*32");
    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)"1024*768*32");
    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_ADDSTRING,0,(LPARAM)"1280*1024*32");

    memcpy(Engine->m_sSettings.NickName,"Death Knight",20);
    memcpy(Engine->m_sSettings.Ip,"www.logicwork.net",20);
    Engine->m_sSettings.FullScreen = 1;
    Engine->m_sSettings.Resolution = 4;
    Engine->m_sSettings.FrameLimiter = 8;
    Engine->m_sSettings.Port       = 5002;

    Engine->RegEdit.LoadText  ("DF3","NickName",       Engine->m_sSettings.NickName,70);
    Engine->RegEdit.LoadText  ("DF3","Ip",             Engine->m_sSettings.Ip,20);
    Engine->RegEdit.LoadNumber("DF3","FullScreen",    &Engine->m_sSettings.FullScreen);
    Engine->RegEdit.LoadNumber("DF3","Resolution",    &Engine->m_sSettings.Resolution);
    Engine->RegEdit.LoadNumber("DF3","Fps",           &Engine->m_sSettings.FrameLimiter);
    Engine->RegEdit.LoadNumber("DF3","Port"      ,    &Engine->m_sSettings.Port);

    char Temp_Text[12];
    itoa(Engine->m_sSettings.Port,Temp_Text,10);

	SetDlgItemText(hwnd,IDC_PROTECTION,"0");

    SetDlgItemText(hwnd,IDC_PORT,    Temp_Text);
    SetDlgItemText(hwnd,IDC_NICKNAME,Engine->m_sSettings.NickName);
    SetDlgItemText(hwnd,IDC_IP,      Engine->m_sSettings.Ip);
    if(Engine->m_sSettings.FullScreen == 1)CheckDlgButton(hwnd,IDC_FULLSCREEN,BST_CHECKED);
    if(Engine->m_sSettings.FullScreen == 0)CheckDlgButton(hwnd,IDC_FULLSCREEN,BST_UNCHECKED);

    SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_SETCURSEL,Engine->m_sSettings.Resolution, 0 );
    SendDlgItemMessage(hwnd,IDC_FRAMELIMITER,CB_SETCURSEL,Engine->m_sSettings.FrameLimiter, 0 );

    return true;
    }
  break;

  case WM_CLOSE:
    {
    Engine->m_sSettings.Resolution   = (char)SendDlgItemMessage(hwnd,IDC_RESOLUTION,CB_GETCURSEL, 0, 0 );
    Engine->m_sSettings.FrameLimiter = (char)SendDlgItemMessage(hwnd,IDC_FRAMELIMITER,CB_GETCURSEL, 0, 0 );

    if(BST_CHECKED == IsDlgButtonChecked(hwnd,IDC_FULLSCREEN)){Engine->m_sSettings.FullScreen = 1;}
    else {Engine->m_sSettings.FullScreen = 0;}

	char Temp_Text2[5];

	GetDlgItemText(hwnd,IDC_PROTECTION,Temp_Text2,3);
	Engine->Nils_Protecting = atoi(Temp_Text2);


    GetDlgItemText(hwnd,IDC_NICKNAME,Engine->m_sSettings.NickName,70);
    GetDlgItemText(hwnd,IDC_IP,Engine->m_sSettings.Ip,20);
    char Temp_Text[12];
    GetDlgItemText(hwnd,IDC_PORT,Temp_Text,6);
    Engine->m_sSettings.Port = atoi(Temp_Text);

    Engine->RegEdit.SaveText  ("DF3","NickName",		      Engine->m_sSettings.NickName,70);
    Engine->RegEdit.SaveText  ("DF3","Ip",		              Engine->m_sSettings.Ip,19);
    Engine->RegEdit.SaveNumber("DF3","FullScreen",    (char *)Engine->m_sSettings.FullScreen);
    Engine->RegEdit.SaveNumber("DF3","Resolution",    (char *)Engine->m_sSettings.Resolution);
    Engine->RegEdit.SaveNumber("DF3","Fps",           (char *)Engine->m_sSettings.FrameLimiter);
    Engine->RegEdit.SaveNumber("DF3","Port"      ,    (char *)Engine->m_sSettings.Port);

    EndDialog(hwnd,0);

    return false;
    }
  break;

  case WM_COMMAND:
    {
    if(wParam == IDC_MASTERSERVER)
      {
      DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_MASTER_SERVER),NULL,Window_MasterServer);

      }

    if(wParam == IDC_SERVER)
      {
		DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_ADV_SERVER),NULL,Window_AdvServer);
      if(Engine->Server == true)
        {
        Engine->Exit   = false;
        Engine->Server = true;
        SendMessage(hwnd,WM_CLOSE,NULL,NULL);
        }
      }

    if(wParam == IDC_CLIENT)
      {
      Engine->Exit   = false;
      Engine->Server = false;
      SendMessage(hwnd,WM_CLOSE,NULL,NULL);
      }
    }

  default:
  return false;
  break;
  }
return false;
}

//------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg,WPARAM wParam, LPARAM lParam)
//------------------------------------------------------------------
{
switch(msg)
  {
  case WM_DESTROY:
    {
    Engine->Exit = true;
    PostQuitMessage(0);
    return 0;
    }
  break;

  case WM_CREATE:
    {
    }
  break;

  default:
  return DefWindowProc(hwnd,msg,wParam,lParam);   
  break;
  }

return 0;
}

//------------------------------------------------------------------
SEngine::SEngine()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
SEngine::~SEngine()
//------------------------------------------------------------------
{

}

//------------------------------------------------------------------
void SEngine::Error_Check()
//------------------------------------------------------------------
  {

  }

//--------------------------------------------------------
int CALLBACK Window_MasterServer(HWND hwnd,UINT msg,WPARAM wParam, LPARAM lParam)
//--------------------------------------------------------
{

switch(msg)
  {

  case WM_INITDIALOG:
  {
  SendMessage(hwnd,WM_SETICON,ICON_SMALL,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));
  SendMessage(hwnd,WM_SETICON,ICON_BIG,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));

  SendMessage(GetDlgItem(hwnd,IDC_LIST),LB_RESETCONTENT,0,0);

  SetDlgItemText(hwnd,IDC_IP,"www.logicwork.net");
  SetDlgItemText(hwnd,IDC_PORT,"5002");

  //////////////////////////////
  //----- Receiving List -----//
  //////////////////////////////

  char *Text_Ptr,Formatted_Text[256];
  int  i;

  for(i=0;i< 255;i++){Formatted_Text[i] = ' ';}

  Engine->Internet.InitInternet();
  Engine->Internet.Connect("www.logicwork.net","DF3/client.php");
  Text_Ptr = Engine->Internet.GetData();
  for(i=0;i< 200;i++) // Max 200 (Tempory)
    {
    if(Text_Ptr[i*54] == '!')break; // EOF

    memcpy(Formatted_Text+ 7,(i*54) + Text_Ptr+ 1,15); // Getting IP
    memcpy(Formatted_Text+36,(i*54) + Text_Ptr+18, 6); // Getting Port
    memcpy(Formatted_Text+55,(i*54) + Text_Ptr+26, 2); // Getting Player

//  memcpy(Formatted_Text+30,(i*54) + Text_Ptr+29,12); // Getting Date
    memcpy(Formatted_Text+69,(i*54) + Text_Ptr+44, 5); // Getting Version

    Formatted_Text[80] = NULL;

    SendMessage(GetDlgItem(hwnd,IDC_LIST),LB_ADDSTRING,0,(LPARAM)Formatted_Text);
    }

  ///////////////////////////////////////
  //----- Receiving List (Finish) -----//
  ///////////////////////////////////////

  Engine->Internet.DeInitInternet();

  return true;
  }
  break;

  case WM_CLOSE:

  EndDialog(hwnd,0);

  return false;
  break;

  case WM_COMMAND:
    {
//    if(wParam == LBN_DBLCLK) // Duble click on a Item NOT WORKING!!! (Microsoft HELP suck!)
    if(wParam == 66548) // Duble click on a Item
      {
      char Formatted_Text[256],TempText[20];
      int Selected = 0;
      Selected = SendMessage(GetDlgItem(hwnd,IDC_LIST),LB_GETCURSEL,0,0); // LB_GETSEL
      SendMessage(GetDlgItem(hwnd,IDC_LIST),LB_GETTEXT,Selected,(long)Formatted_Text);
      memcpy(TempText,Formatted_Text+7,15);
      TempText[15] = NULL;
      SetDlgItemText(hwnd,IDC_IP,TempText);
      memcpy(TempText,Formatted_Text+36,6);
      TempText[6] = NULL;
      SetDlgItemText(hwnd,IDC_PORT,TempText);
      }

    if(wParam == IDC_REFRESH)
      {
      SendMessage(GetDlgItem(hwnd,IDC_LIST),LB_RESETCONTENT,0,0);

      //////////////////////////////
      //----- Receiving List -----//
      //////////////////////////////

      char *Text_Ptr,Formatted_Text[256];
      int  i;

      for(i=0;i< 255;i++){Formatted_Text[i] = ' ';}

      Engine->Internet.InitInternet();

      if(BST_UNCHECKED == IsDlgButtonChecked(hwnd,IDC_SHOWTIMEOUT))Engine->Internet.Connect("www.logicwork.net","DF3/client.php");
      if(BST_CHECKED   == IsDlgButtonChecked(hwnd,IDC_SHOWTIMEOUT))Engine->Internet.Connect("www.logicwork.net","DF3/client.php?TimeOut=true");
      Text_Ptr = Engine->Internet.GetData();
      for(i=0;i< 200;i++) // Max 200 (Tempory)
        {
        if(Text_Ptr[i*54] == '!')break; // EOF

        memcpy(Formatted_Text+ 7,(i*54) + Text_Ptr+ 1,15); // Getting IP
        memcpy(Formatted_Text+36,(i*54) + Text_Ptr+18, 6); // Getting Port
        memcpy(Formatted_Text+55,(i*54) + Text_Ptr+26, 2); // Getting Player
//  memcpy(Formatted_Text+30,(i*54) + Text_Ptr+29,12); // Getting Date
        memcpy(Formatted_Text+69,(i*54) + Text_Ptr+44, 5); // Getting Version

        Formatted_Text[80] = NULL;

        SendMessage(GetDlgItem(hwnd,IDC_LIST),LB_ADDSTRING,0,(LPARAM)Formatted_Text);
        }
      ///////////////////////////////////////
      //----- Receiving List (Finish) -----//
      ///////////////////////////////////////
      Engine->Internet.DeInitInternet();
      }
    if(wParam == IDC_USE)
      {
      char TempText[20];

      GetDlgItemText(hwnd,IDC_IP,TempText,15);
      SetDlgItemText(Engine->hwnd_Main,IDC_IP,TempText);
      GetDlgItemText(hwnd,IDC_PORT,TempText,15);
      SetDlgItemText(Engine->hwnd_Main,IDC_PORT,TempText);

      SendMessage(hwnd,WM_CLOSE,0,0);
      }
    if(wParam == IDC_QUIT)
      {
      SendMessage(hwnd,WM_CLOSE,0,0);
      }
    }
  default:
  return false;
  break;

  }
return false;
}


//--------------------------------------------------------
int CALLBACK Window_AdvServer(HWND hwnd,UINT msg,WPARAM wParam, LPARAM lParam)
//--------------------------------------------------------
{

switch(msg)
  {

  case WM_INITDIALOG:
  {
  SendMessage(hwnd,WM_SETICON,ICON_SMALL,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));
  SendMessage(hwnd,WM_SETICON,ICON_BIG,(LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON1)));

  PostMessage(GetDlgItem(hwnd,IDC_BUYTIME),EM_SETLIMITTEXT,2,0);
  PostMessage(GetDlgItem(hwnd,IDC_PORT),EM_SETLIMITTEXT,5,0);

  Engine->m_sSettings.BuyTime           = 5;
  Engine->m_sSettings.Port              = 5002;
  Engine->m_sSettings.AddToMasterServer = 0;

  Engine->RegEdit.LoadNumber("DF3","BuyTime",          &Engine->m_sSettings.BuyTime);
  Engine->RegEdit.LoadNumber("DF3","Port",             &Engine->m_sSettings.Port);
  Engine->RegEdit.LoadNumber("DF3","AddToMasterServer",&Engine->m_sSettings.AddToMasterServer);

  char Temp_Text[12];

  itoa(Engine->m_sSettings.BuyTime,Temp_Text,10);
  SetDlgItemText(hwnd,IDC_BUYTIME,Temp_Text);
  itoa(Engine->m_sSettings.Port,Temp_Text,10);
  SetDlgItemText(hwnd,IDC_PORT,Temp_Text);

  if(Engine->m_sSettings.AddToMasterServer == 0)CheckDlgButton(hwnd,IDC_MASTERSERVER,BST_UNCHECKED);
  if(Engine->m_sSettings.AddToMasterServer == 1)CheckDlgButton(hwnd,IDC_ADDMASTER,BST_CHECKED);

  return true;
  }
  break;

  case WM_CLOSE:

  EndDialog(hwnd,0);

  return false;
  break;

  case WM_COMMAND:
    {
    if(wParam == IDC_LAUNCH)
      {
      char Temp_Text[12];

      GetDlgItemText(hwnd,IDC_BUYTIME,(char *)Temp_Text,3);
      Engine->m_sSettings.BuyTime = atoi(Temp_Text);
      Engine->RegEdit.SaveNumber("DF3","BuyTime",(char *)Engine->m_sSettings.BuyTime);
      GetDlgItemText(hwnd,IDC_PORT,(char *)Temp_Text,7);
      Engine->m_sSettings.Port    = atoi(Temp_Text);
      Engine->RegEdit.SaveNumber("DF3","Port",   (char *)Engine->m_sSettings.Port);

      if(BST_CHECKED == IsDlgButtonChecked(hwnd,IDC_ADDMASTER)){Engine->m_sSettings.AddToMasterServer = 1;}
      else                                                     {Engine->m_sSettings.AddToMasterServer = 0;}
      Engine->RegEdit.SaveNumber("DF3","AddToMasterServer",(char *)Engine->m_sSettings.AddToMasterServer);


      if(Engine->m_sSettings.AddToMasterServer == 1)
        {
        char TempText[128];
        sprintf(TempText,"DF3/server.php?Port=%d&Players=1&Version=1001",Engine->m_sSettings.Port);
        Engine->Internet.InitInternet();
        Engine->Internet.Connect("www.logicwork.net",TempText);

        Engine->Internet.DeInitInternet();
        }

      Engine->Server = true;
      SendMessage(hwnd,WM_CLOSE,NULL,NULL);
      }
    if(wParam == IDC_CANCEL)
      {
      SendMessage(hwnd,WM_CLOSE,NULL,NULL);
      }
    }
  default:
  return false;
  break;

  }
return false;
}

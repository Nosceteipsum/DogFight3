////////////////////////////////////////////////////////////////////
//								  //
//			OpenGl Window			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "COpenGl_Window.h"

//--------------------------------------------------------------------------------
void COpenGl_Window::CreateGLWindow(char* title, int width, int height, int bits, bool fullscreen,HINSTANCE hinstance,HWND *hwnd,char Nils_Proc)
//--------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  int	PixelFormat;				 
  WNDCLASS	wc;							
  DWORD		dwExStyle,dwStyle;						

  RECT WindowRect;							
  WindowRect.left  =(long)0;						
  WindowRect.right =(long)width;						
  WindowRect.top   =(long)0;							
  WindowRect.bottom=(long)height;						

  hinstance		= GetModuleHandle(NULL);			
  wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		
  wc.lpfnWndProc	= (WNDPROC) WndProc;				
  wc.cbClsExtra		= 0;						
  wc.cbWndExtra		= 0;						
  wc.hInstance		= hinstance;					
  wc.hIcon		= LoadIcon(NULL, IDI_WINLOGO);			
  wc.hCursor		= LoadCursor(NULL, IDC_ARROW);			
  wc.hbrBackground	= NULL;						
  wc.lpszMenuName	= NULL;						
  wc.lpszClassName	= "LogicWork";

  if(!RegisterClass(&wc)){Error_Detected = true;memcpy(Error_Message,"Error in Window class(WC)",45);}

  if(fullscreen == true)
    {
    DEVMODE dmScreenSettings;					
    memset(&dmScreenSettings,0,sizeof(dmScreenSettings));

    dmScreenSettings.dmSize 		= sizeof(dmScreenSettings);		
    dmScreenSettings.dmPelsWidth	= width;			
    dmScreenSettings.dmPelsHeight	= height;			
    dmScreenSettings.dmBitsPerPel	= bits;				
    dmScreenSettings.dmFields     	= DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

    ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN);    

    dwExStyle=  WS_EX_APPWINDOW;					
    dwStyle  =  WS_POPUP;						
    ShowCursor(FALSE);						
    }
  if(fullscreen == false)
    {
	if(Nils_Proc != 0)dwExStyle = WS_EX_LAYERED;
	else			  dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;


	  dwStyle   = WS_OVERLAPPEDWINDOW;
    dwStyle  &= !(WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
    }
  AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	


  if(!(*hwnd=CreateWindowEx(dwExStyle,				
  	                   "LogicWork",			
	                   title,		
	                   WS_CLIPSIBLINGS |	
	                   WS_CLIPCHILDREN |	
	                   dwStyle,		
	                   0, 0,				
	                   WindowRect.right-WindowRect.left,	
	                   WindowRect.bottom-WindowRect.top,	
	                   NULL,				
	                   NULL,			
	                   hinstance,				
	                   NULL
    )))		
    {
    Error_Detected = true;
    memcpy(Error_Message,"Could Not create the window",45);
    KillGlWindow(*hwnd,hinstance);
    return;
    }

  if(Nils_Proc != 0 && fullscreen == false)SetLayeredWindowAttributes(*hwnd,RGB(0,0,0),Nils_Proc,LWA_ALPHA);

  static PIXELFORMATDESCRIPTOR pfd=					
    {
    sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,PFD_TYPE_RGBA,bits,0,0,0,0,0,0,0,0,0,0,0,0,0,16,0,0,PFD_MAIN_PLANE,0,0,0,0
    };
  if(!(hDC=GetDC(*hwnd)))							
    {
    KillGlWindow(*hwnd,hinstance);
    Error_Detected = true;
    memcpy(Error_Message,"Crash on GetDC",45);
    return;
    }
  if(!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))
    {
    KillGlWindow(*hwnd,hinstance);
    Error_Detected = true;
    memcpy(Error_Message,"Wrong resolution/window size choosen",45);
    return;
    }
  if(!SetPixelFormat(hDC,PixelFormat,&pfd))
    {
    KillGlWindow(*hwnd,hinstance);
    Error_Detected = true;
    memcpy(Error_Message,"Could not set pixelformat",45);
    return;
    }
  if(!(hRC=wglCreateContext(hDC)))
    {
    KillGlWindow(*hwnd,hinstance);
    Error_Detected = true;
    memcpy(Error_Message,"Could not create hdc_content",45);
    return;						
    }
  if(!wglMakeCurrent(hDC,hRC))	// Direct3D9: (ERROR) :No attached clipper		
    {
    KillGlWindow(*hwnd,hinstance);					
    Error_Detected = true;
    memcpy(Error_Message,"Could not start rendering",45);
    return;							
    }

//  SetBkMode(hDC,TRANSPARENT); // TRANSPARENT / OPAQUE
//  SetBkColor(hDC, RGB(0,0,0));
//  SetLayeredWindowAttributes(*hwnd,RGB(0,0,0),100,LWA_ALPHA);

  ShowWindow(*hwnd,SW_SHOW);						
  SetForegroundWindow(*hwnd);					
  SetFocus(*hwnd);					



  return;
  }

catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in COpenGl_Window::CreateWindow",45);
  }
}

//--------------------------------------------------------------------------------
void COpenGl_Window::SwapBuffers_hdc()
//--------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  { 
  SwapBuffers(hDC); 

//  UpdateLayeredWindow(hwnd,
  }

catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in COpenGl_Window::SwapBuffers",45);
  }
}

//--------------------------------------------------------------------------------
void COpenGl_Window::KillGlWindow(HWND hwnd,HINSTANCE hInstance)
//--------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  ChangeDisplaySettings(NULL,0);					
  ShowCursor(TRUE);						
  if(hRC)								
    {
    wglMakeCurrent(NULL,NULL);					
    wglDeleteContext(hRC);					
    hRC=NULL;							
    }
  if(hDC) ReleaseDC(hwnd,hDC);					
  if(hwnd)DestroyWindow(hwnd);					
  UnregisterClass("OpenGL",hInstance);			
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in COpenGl_Window::KillGlWindow",45);
  }
}

//--------------------------------------------------------------------------------
char *COpenGl_Window::Get_Error_Message(){return Error_Message;}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
bool COpenGl_Window::Error_Check(){return Error_Detected;}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
COpenGl_Window::COpenGl_Window()								
//--------------------------------------------------------------------------------
{
Error_Detected = false;
}

//--------------------------------------------------------------------------------
COpenGl_Window::~COpenGl_Window()								
//--------------------------------------------------------------------------------
{
}

//--------------------------------------------------------------------------------
LPPOINT COpenGl_Window::GetCursorPosition()								
//--------------------------------------------------------------------------------
{
if(Error_Detected == true)return 0;

try
  {
  GetCursorPos(Mouse_Point);
  return Mouse_Point;
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in COpenGl_Window::GetCursorPosition",45);
  }
return 0;
}

//--------------------------------------------------------------------------------
void COpenGl_Window::SetCursorPosition(int x,int y)								
//--------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  SetCursorPos(x,y);
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in COpenGl_Window::SetCursorPosition",45);
  }
}

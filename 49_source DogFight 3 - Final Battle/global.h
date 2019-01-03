////////////////////////////////////////////////////////////////////
//								  //
//	  	  DF 3: Global  			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined Global_H
#define Global_H 

#define WIN32_WINNT 0x9999

//--------------------------------------------------------//
//--			Includes                        --//
//--------------------------------------------------------//

#include <iostream>
#include <vector>

//------ Engine ------//

#include "source/Engine/windows/CWinSock.h"
#include "source/Engine/windows/CInternet.h"

#define _WIN32_WINNT 0x9999

#include <windows.h>
#include <winuser.h>

#include <winuser.h>

#include "source/Engine/windows/CRegEdit.h"

#include "source/Engine/CTimer.h"

#include "source/Engine/Fmod/Fmod.h"

#include "source/Engine/OpenGl/COpenGl_Math.h"
#include "source/Engine/OpenGl/COpenGl_Camera.h"
#include "source/Engine/OpenGl/COpenGl_Font.h"
#include "source/Engine/OpenGl/COpenGl_Texture_TGA.h"
#include "source/Engine/OpenGl/COpenGl_Window.h"

#include "source/Engine/Keyboard/CKey.h"

//------ Game - Headers ------//

#include "resource.h"

#include "source/Winmain/winmain.h"

#include "source/game/CGameHandler.h"

#endif
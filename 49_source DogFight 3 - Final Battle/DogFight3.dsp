# Microsoft Developer Studio Project File - Name="DogFight3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DogFight3 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DogFight3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DogFight3.mak" CFG="DogFight3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DogFight3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DogFight3 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "Perforce Project"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DogFight3 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x406 /d "NDEBUG"
# ADD RSC /l 0x406 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DogFight3 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x406 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DogFight3 - Win32 Release"
# Name "DogFight3 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "WinMain"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\WinMain\WinMain.cpp
# End Source File
# Begin Source File

SOURCE=.\source\WinMain\WinMain.h
# End Source File
# End Group
# Begin Group "Engine"

# PROP Default_Filter ""
# Begin Group "Fmod"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Engine\Fmod\fmod.h
# End Source File
# Begin Source File

SOURCE=.\source\Engine\Fmod\fmodvc.lib
# End Source File
# End Group
# Begin Group "OpenGl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Engine\OpenGl\COpenGl_Camera.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Engine\OpenGl\COpenGl_Camera.h
# End Source File
# Begin Source File

SOURCE=.\source\Engine\OpenGl\COpenGl_Font.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Engine\OpenGl\COpenGl_Font.h
# End Source File
# Begin Source File

SOURCE=.\source\Engine\OpenGl\COpenGl_Math.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Engine\OpenGl\COpenGl_Math.h
# End Source File
# Begin Source File

SOURCE=.\source\Engine\OpenGl\COpenGl_Texture_TGA.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Engine\OpenGl\COpenGl_Texture_TGA.h
# End Source File
# Begin Source File

SOURCE=.\source\Engine\OpenGl\COpenGl_Window.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Engine\OpenGl\COpenGl_Window.h
# End Source File
# End Group
# Begin Group "windows"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Engine\windows\CInternet.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Engine\windows\CInternet.h
# End Source File
# Begin Source File

SOURCE=.\source\Engine\windows\CRegEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Engine\windows\CRegEdit.h
# End Source File
# Begin Source File

SOURCE=.\source\Engine\windows\CWinSock.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Engine\windows\CWinSock.h
# End Source File
# End Group
# Begin Group "Keyboard"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Engine\Keyboard\CKey.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Engine\Keyboard\CKey.h
# End Source File
# End Group
# Begin Group "Memory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Engine\Memory\mmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Engine\Memory\mmgr.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\source\Engine\CTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Engine\CTimer.h
# End Source File
# End Group
# Begin Group "Game"

# PROP Default_Filter ""
# Begin Group "Plane"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Game\Plane\CPlane.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Game\Plane\CPlane.h
# End Source File
# End Group
# Begin Group "Man"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Game\Man\CMan.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Game\Man\CMan.h
# End Source File
# End Group
# Begin Group "Missile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Game\Missile\CMissile.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Game\Missile\CMissile.h
# End Source File
# End Group
# Begin Group "Map"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Game\Map\CMap.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Game\Map\CMap.h
# End Source File
# End Group
# Begin Group "Projectile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Game\Projectile\CFire.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Game\Projectile\CFire.h
# End Source File
# Begin Source File

SOURCE=.\source\Game\Projectile\CSpec.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Game\Projectile\CSpec.h
# End Source File
# End Group
# Begin Group "Loader"

# PROP Default_Filter ""
# End Group
# Begin Group "Player"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Game\Player\CPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Game\Player\CPlayer.h
# End Source File
# End Group
# Begin Group "Network"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Game\Network\CNetwork.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Game\Network\CNetwork.h
# End Source File
# End Group
# Begin Group "Animal"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Game\Animals\CAnimals.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Game\Animals\CAnimals.h
# End Source File
# End Group
# Begin Group "Sky"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Game\Sky\CSky.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Game\Sky\CSky.h
# End Source File
# End Group
# Begin Group "Bot"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Game\Bot\CBot.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Game\Bot\CBot.h
# End Source File
# End Group
# Begin Group "SeaGull"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\Game\Seagull\CSeaGull.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Game\Seagull\CSeaGull.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\source\Game\CGameHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Game\CGameHandler.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\global.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\DF.ico
# End Source File
# Begin Source File

SOURCE=".\Graphics\Forside\Forside,4.bmp"
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Script1.rc
# End Source File
# End Group
# End Target
# End Project

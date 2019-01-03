////////////////////////////////////////////////////////////////////
//								  //
//			RegEdit				  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "CRegEdit.h"

//----------------------------------------------------------------------------------------------
CRegEdit::CRegEdit()
//----------------------------------------------------------------------------------------------
  {
  Error_Detected = false;
  }
//----------------------------------------------------------------------------------------------
CRegEdit::~CRegEdit()
//----------------------------------------------------------------------------------------------
  {
  }
//----------------------------------------------------------------------------------------------
void CRegEdit::SaveText(char *Game_Name,char *Text_Name,char *Text_String,int Size)
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  HKEY Key_Handle;
  DWORD Word_Temp;
  long Temp_Value;
  char Game_Name_Temp[50] = "Software\\LogicWork\\";
  memcpy(Game_Name_Temp+19,Game_Name,20);

  Temp_Value = RegCreateKeyEx(HKEY_LOCAL_MACHINE,Game_Name_Temp,0,0,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,0,&Key_Handle,&Word_Temp);

  if(Temp_Value == ERROR_SUCCESS)
    {
    //------------- Save Text ---------------//
    Temp_Value = RegSetValueEx(Key_Handle,Text_Name,0,REG_SZ,(unsigned char *)Text_String,Size);
    //------------- Reg Close ---------------//
    Temp_Value = RegCloseKey(Key_Handle);
    }
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in CRegEdit::SaveText",45);
  }
}
//----------------------------------------------------------------------------------------------
void CRegEdit::SaveNumber(char *Game_Name, char *Number_Name,char *Number_Value)
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  HKEY Key_Handle;
  DWORD Word_Temp;
  long Temp_Value;
  char Game_Name_Temp[50] = "Software\\LogicWork\\";
  memcpy(Game_Name_Temp+19,Game_Name,20);

  Temp_Value = RegCreateKeyEx(HKEY_LOCAL_MACHINE,Game_Name_Temp,0,0,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,0,&Key_Handle,&Word_Temp);

  if(Temp_Value == ERROR_SUCCESS)
    {
    //------------- Save Number -------------//
    Temp_Value = RegSetValueEx(Key_Handle,Number_Name,0,REG_DWORD,(unsigned char *)&Number_Value,4);
    //------------- Reg Close ---------------//
    Temp_Value = RegCloseKey(Key_Handle);
    }
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in CRegEdit::SaveNumber",45);
  }
}
//----------------------------------------------------------------------------------------------
void CRegEdit::LoadText(char *Game_Name,char *Text_Name,char *Text_String,int Size)
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  HKEY Key_Handle;
  DWORD Word_Temp;
  long Temp_Value,Temp_Valueb = Size;

  char Game_Name_Temp[50] = "Software\\LogicWork\\";
  memcpy(Game_Name_Temp+19,Game_Name,20);

  Temp_Value = RegCreateKeyEx(HKEY_LOCAL_MACHINE,Game_Name_Temp,0,0,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,0,&Key_Handle,&Word_Temp);

  if(Temp_Value == ERROR_SUCCESS)
    {
    //------------- Load Text ---------------//
    Temp_Value = RegQueryValueEx(Key_Handle,Text_Name,0,NULL,(unsigned char *)Text_String,(unsigned long *)&Temp_Valueb);
    //------------- Reg Close ---------------//
    Temp_Value = RegCloseKey(Key_Handle);
    }
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in CRegEdit::LoadText",45);
  }
}
//----------------------------------------------------------------------------------------------
void CRegEdit::LoadNumber(char *Game_Name,char *Number_Name,int *Number_Value)
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  HKEY Key_Handle;
  DWORD Word_Temp;
  long Temp_Value,Temp_Valuea = 4;

  char Game_Name_Temp[50] = "Software\\LogicWork\\";
  memcpy(Game_Name_Temp+19,Game_Name,20);

  Temp_Value = RegCreateKeyEx(HKEY_LOCAL_MACHINE,Game_Name_Temp,0,0,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,0,&Key_Handle,&Word_Temp);

  if(Temp_Value == ERROR_SUCCESS)
    {
    //------------- Load number ---------------//
    Temp_Value = RegQueryValueEx(Key_Handle,Number_Name,0,NULL,(unsigned char *)Number_Value,(unsigned long *)&Temp_Valuea);
    //------------- Reg Close ---------------//
    Temp_Value = RegCloseKey(Key_Handle);
    }
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in CRegEdit::LoadNumber",45);
  }
}

//--------------------------------------------------------------------------------
char *CRegEdit::Get_Error_Message(){return Error_Message;}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
bool CRegEdit::Error_Check(){return Error_Detected;}
//--------------------------------------------------------------------------------

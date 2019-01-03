////////////////////////////////////////////////////////////////////
//								  //
//			   RegEdit ()			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined RegEdit_H
#define RegEdit_H

//----------------------------------//
//--------- Library files ----------//
//----------------------------------//

//----------------------------------//
//------------ Defines -------------//
//----------------------------------//

//----------------------------------//
//--------- Include files ----------//
//----------------------------------//

#include <windows.h>

//----------------------------------//
//------------- Class --------------//
//----------------------------------//

class CRegEdit
{
public:

CRegEdit();
~CRegEdit();

bool  Error_Check         ();
char *Get_Error_Message   ();

void LoadNumber(char *Game_Name,char *Number_Name,int *Number_Value);
void LoadText(char *Game_Name,char *Text_Name,char *Text_String,int Size);

void SaveNumber(char *Game_Name, char *Number_Name,char *Number_Value);
void SaveText(char *Game_Name,char *Text_Name,char *Text_String,int Size);

private:

bool Error_Detected;
char Error_Message[50];

};

#endif
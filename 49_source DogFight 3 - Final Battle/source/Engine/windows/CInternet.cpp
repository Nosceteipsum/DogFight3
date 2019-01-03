///////////////////////////////////////////////////////////////
//                                                           //
//                   CInternet Class                         //
//                                                           //
//        Last Updated: 17-06-03 14-51                       //
//        Made By: Tommy Kobberø Andersen                    //
//                                                           //
//                                                           //
///////////////////////////////////////////////////////////////

#define DEFAULT_PHP_FILESIZE 159310 // 159300 = (( 2 +  50  +  7   ) * 100) *       9         *     3
                                   //            Nr   Name   Point  Places   Difficult/Type     MapTypes

#include "CInternet.h"

//-------------------------------------------------------------
CInternet::CInternet()
//-------------------------------------------------------------
{
	m_hSession        = NULL;
	m_hConnection     = NULL;
	m_hHTTP           = NULL;
	m_cpHtml_Data     = NULL;

	m_bError_Detected = false;
	m_oError_Message.erase();
}

//-------------------------------------------------------------
CInternet::~CInternet()
//-------------------------------------------------------------
{

}

//-------------------------------------------------------------
bool CInternet::Error_Check(){return m_bError_Detected;}
//-------------------------------------------------------------

//-------------------------------------------------------------
const char *CInternet::Error_GetMessage(){return m_oError_Message.data();}
//-------------------------------------------------------------

//-------------------------------------------------------------
std::string *CInternet::GetErrorString(){return &m_oError_Message;}
//-------------------------------------------------------------

//-------------------------------------------------------------
bool CInternet::DeInitInternet()
//-------------------------------------------------------------
{
	m_bError_Detected = false;

	try
	{
		if(m_hSession    != NULL){InternetCloseHandle(m_hSession);   m_hSession    = NULL;}
		if(m_hConnection != NULL){InternetCloseHandle(m_hConnection);m_hConnection = NULL;}
		if(m_hHTTP       != NULL){InternetCloseHandle(m_hHTTP);      m_hHTTP       = NULL;}
		if(m_cpHtml_Data != NULL)
		{
			delete[] m_cpHtml_Data;              
			m_cpHtml_Data = NULL;
		}
	}
	catch(...)
	{
		m_bError_Detected = true;
		m_oError_Message.assign("Error in CInternet::DeInitInternet()");
		return false;
	}
	return true;
}

//-------------------------------------------------------------
bool CInternet::InitInternet()
//-------------------------------------------------------------
{
if(m_bError_Detected == true)return false;

try
  {
  m_hSession    = InternetOpen("CInternetClass", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

  if(m_hSession == NULL)
    {
    m_bError_Detected = true;
    m_oError_Message.assign("Error in CInternet::InitInternet() function: InternetOpen() Code: ");
    itoa(GetLastError(),m_cError_Code,10);
    m_oError_Message += m_cError_Code;
    return false;
    }
  }
catch(...)
  {
  m_bError_Detected = true;
  m_oError_Message.assign("Error in CInternet::InitInternet()");
  return false;
  }
return true;
}

//-------------------------------------------------------------
bool CInternet::Connect(char *Url,char *Web_File)
//-------------------------------------------------------------
{
if(m_bError_Detected == true)return false;

try
  {
  m_hConnection = InternetConnect(m_hSession, Url , INTERNET_INVALID_PORT_NUMBER, "","", INTERNET_SERVICE_HTTP,0,0);

  if(m_hConnection == NULL)
    {
    m_bError_Detected = true;
    m_oError_Message.assign("Error in CInternet::Connect() function: InternetConnect() Code: ");
    itoa(GetLastError(),m_cError_Code,10);
    m_oError_Message += m_cError_Code;
    return false;
    }

  m_hHTTP = HttpOpenRequest(m_hConnection,"GET",Web_File,HTTP_VERSION,NULL,0,INTERNET_FLAG_DONT_CACHE,0);

  if(m_hHTTP == NULL)
    {
    m_bError_Detected = true;
    m_oError_Message.assign("Error in CInternet::Connect() function: HttpOpenRequest() Code: ");
    itoa(GetLastError(),m_cError_Code,10);
    m_oError_Message += m_cError_Code;
    return false;
    }

  BOOL SendRequest = HttpSendRequest(m_hHTTP, NULL, 0, 0, 0);

  if(SendRequest == false)
    {
    m_bError_Detected = true;
    m_oError_Message.assign("Error in CInternet::Connect() function: HttpSendRequest() Code: ");
    itoa(GetLastError(),m_cError_Code,10);
    m_oError_Message += m_cError_Code;
    return false;
    }

  }
catch(...)
  {
  m_bError_Detected = true;
  m_oError_Message.assign("Error in CInternet::Connect()");
  return false;
  }
return true;
}

//-------------------------------------------------------------
char *CInternet::GetData()
//-------------------------------------------------------------
{
if(m_bError_Detected == true)return NULL;

try
  {
  char bufQuery[32] ;
  DWORD dwLengthBufQuery = sizeof(bufQuery);
  DWORD dwIndex    = 0;
  DWORD dwFileSize = 0;

  BOOL Query = HttpQueryInfo(m_hHTTP,
                             HTTP_QUERY_CONTENT_LENGTH, 
                             bufQuery, 
                             &dwLengthBufQuery,
			     &dwIndex);

  if(Query == FALSE)
    {
    int Temp_Error = GetLastError();
    if(Temp_Error != 12150)         // Error Code: 12150 (With .php file) = ERROR_WINHTTP_HEADER_NOT_FOUND (The requested header could not be located)
      {
      m_bError_Detected = true;
      m_oError_Message.assign("Error in CInternet::GetData() function: HttpQueryInfo() Code: ");
      itoa(GetLastError(),m_cError_Code,10);
      m_oError_Message += m_cError_Code;
      return NULL;
      }
    if(Temp_Error == 12150)         // Error Code: 12150 (With .php file) = ERROR_WINHTTP_HEADER_NOT_FOUND (The requested header could not be located)
      {
      //------------- Php File (Unknown/Dynamic Size) --------------//

      m_cpHtml_Data = new char[DEFAULT_PHP_FILESIZE+2];
      dwFileSize    = DEFAULT_PHP_FILESIZE-1;
      }
    }
  if(Query == TRUE)
    {
    dwFileSize    = (DWORD)atol(bufQuery);
    m_cpHtml_Data = new char[dwFileSize+1];
    }

  DWORD dwBytesRead       = 0;
  DWORD dwBytesRead_Total = 0;
  DWORD dwBytesRemain     = dwFileSize;
  BOOL  Read;

  do
    {
    Read = InternetReadFile(m_hHTTP,                                 // When using Modem, It can only
                            m_cpHtml_Data+dwBytesRead_Total,         // download 18538 bytes with one funtion call -TOA
                            dwBytesRemain, 
                            &dwBytesRead);

    dwBytesRemain     -= dwBytesRead;
    dwBytesRead_Total += dwBytesRead;

    }while(dwBytesRead_Total < dwFileSize && dwBytesRead > 0);

  if(Read == FALSE)
    {
    m_bError_Detected = true;
    m_oError_Message.assign("Error in CInternet::GetData() function: InternetReadFile() Code: ");
    itoa(GetLastError(),m_cError_Code,10);
    m_oError_Message += m_cError_Code;
    return NULL;
    }
  }

catch(...)
  {
  m_bError_Detected = true;
  m_oError_Message.assign("Error in CInternet::GetData()");
  return NULL;
  }
return m_cpHtml_Data;
}

//-------------------------------------------------------------
bool CInternet::FreePointer()
//-------------------------------------------------------------
{
	m_bError_Detected = false;

	try
	{
		if(m_cpHtml_Data != NULL)
		{
			delete[] m_cpHtml_Data;
			m_cpHtml_Data = NULL;
		}
	}
	catch(...)
	{
		m_bError_Detected = true;
		m_oError_Message.assign("Error in CInternet::FreePointer()");
		return false;
	}
	return true;
}

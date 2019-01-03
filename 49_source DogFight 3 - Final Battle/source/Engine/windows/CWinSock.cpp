////////////////////////////////////////////////////////////////////
//								  //
//			WinSock				  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#include "CWinSock.h"

//----------------------------------------------------------------------------------------------
CWinSock::CWinSock()
//----------------------------------------------------------------------------------------------
  {
  Error_Detected = false;
  Dectect_Packes = (unsigned long *)malloc(sizeof(long));

  }
//----------------------------------------------------------------------------------------------
CWinSock::~CWinSock()
//----------------------------------------------------------------------------------------------
  {
  free(Dectect_Packes);
  }
//--------------------------------------------------------------------------------
char *CWinSock::Get_Error_Message(){return Error_Message;}
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
bool CWinSock::Error_Check(){return Error_Detected;}
//--------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
void CWinSock::Server_SaveIP(char SpaceNumber)
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  memcpy(&Server_Player[SpaceNumber],&Server_from,sizeof(Server_from));
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Server_SaveIP",45);
  }
}
//----------------------------------------------------------------------------------------------
void CWinSock::Server_LoadIP(char SpaceNumber)
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  memcpy(&Server_from,&Server_Player[SpaceNumber],sizeof(Server_from));
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Server_LoadIP",45);
  }
}
//----------------------------------------------------------------------------------------------
bool CWinSock::Server_CheckObject()
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return false;

try
  {
  if(0 != ioctlsocket(Server_listen_socket,FIONREAD,Dectect_Packes))
    {
    Server_Error = true;
    }
  if(*Dectect_Packes != 0)return true;
  return false;
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Server_CheckObject",45);
  }
}
//----------------------------------------------------------------------------------------------
void CWinSock::Server_SelectMessageObject()
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  int Error_Code = 0x00;
  Server_EventObject = WSACreateEvent(); 

  Error_Code = WSAEventSelect(Server_listen_socket,Server_EventObject, 0x00 | FD_READ);

  WSACloseEvent(Server_EventObject);

  if(0 != Error_Code)
    {
    Server_Error = true;
    Error_Detected = true;
    memcpy(Error_Message,"Error in Server_SelectMessageObject: ",45);
    Error_Code = WSAGetLastError();
    itoa(Error_Code,Error_Message+36,10);
    }
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Server_SelectMessageObject",45);
  }
}
//----------------------------------------------------------------------------------------------
void CWinSock::Server_SendData(char *Data,int Size)
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  Server_fromlen = sizeof(Server_from);
  Server_msgsock = Server_listen_socket;
  Server_retval = sendto(Server_msgsock,Data,Size,0,(struct sockaddr *)&Server_from,Server_fromlen);
  if(Server_retval == SOCKET_ERROR) 
    {
    Server_Error = true;
    }
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Server_SendData",45);
  }
}
//----------------------------------------------------------------------------------------------
void CWinSock::Server_DeInit()
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  closesocket(Server_msgsock);
  WSACleanup();
  Server_Error = false;
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Server_SendData",45);
  }
}
//----------------------------------------------------------------------------------------------
void CWinSock::Server_GetData(char *DataRecv)
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  Server_fromlen = sizeof(Server_from);
  Server_msgsock = Server_listen_socket;
  Server_retval = recvfrom(Server_msgsock,DataRecv,1000,0,(struct sockaddr *)&Server_from,&Server_fromlen); 
  if(Server_retval == SOCKET_ERROR) 
    {
    Error_Detected = true;
    Server_Error   = true;
    memcpy(Error_Message,"Error in Server_GetData: ",45);
    int Error_Code = WSAGetLastError();
    itoa(Error_Code,Error_Message+25,10);
    return;
    }
  if(Server_retval == 0) 
    {
    //--- connection has been gracefully closed ---//
    //Server_Error = true;
    //closesocket(Server_msgsock);
    }
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Server_GetData",45);
  }
}

//----------------------------------------------------------------------------------------------
bool CWinSock::Server_CheckForError()
//----------------------------------------------------------------------------------------------
  {
  return Server_Error | Error_Detected;
  }
//----------------------------------------------------------------------------------------------
void CWinSock::Server_StartServer(unsigned short Port)
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  Server_Error = false;
  Server_Socket_Type = DEFAULT_PROTO;
  char *Interface= NULL;
  if(WSAStartup(0x202,&Server_wsaData) == SOCKET_ERROR) 
    {
    Server_Error = true;
    WSACleanup();
    }
  Server_local.sin_family = AF_INET;
  Server_local.sin_addr.s_addr = (!Interface) ? INADDR_ANY : inet_addr(Interface); 
  Server_local.sin_port = htons(Port);
  Server_listen_socket = socket(AF_INET, Server_Socket_Type,0);
	
  if(Server_listen_socket == INVALID_SOCKET)
    {
    Server_Error = true;
    WSACleanup();
    }
  if(bind(Server_listen_socket,(struct sockaddr*)&Server_local,sizeof(Server_local) ) == SOCKET_ERROR) 
    {
    Server_Error = true;
    WSACleanup();
    }
  Server_SelectMessageObject();
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Server_StartServer",45);
  }
}
//----------------------------------------------------------------------------------------------
void CWinSock::Client_SelectMessageObject()
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  int Error_Code = 0x00;

  Client_EventObject = WSACreateEvent(); 
  Error_Code	     = WSAEventSelect(Client_conn_socket,Client_EventObject, FD_READ);

  WSACloseEvent(Client_EventObject);

  if(0 != Error_Code)
    {
    Client_Error = true;
    Error_Detected = true;
    memcpy(Error_Message,"Error in Client_SelectMessageObject: ",45);
    Error_Code = WSAGetLastError();
    itoa(Error_Code,Error_Message+36,10);
    }

  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Client_SelectMessageObject",45);
  }
}
//----------------------------------------------------------------------------------------------
bool CWinSock::Client_CheckObject()
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return false;

try
  {
  if(0 != ioctlsocket(Client_conn_socket,FIONREAD,Dectect_Packes))
    {
    Client_Error = true;
    }
  if(*Dectect_Packes != 0){return true;}
  return false;
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Client_CheckObject",45);
  }
}
//----------------------------------------------------------------------------------------------
char *CWinSock::Client_RecvData()
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return NULL;

try
  {
  Client_retval = recv(Client_conn_socket,Client_RecvBuffer,sizeof (Client_RecvBuffer),0 );
  if(Client_retval == SOCKET_ERROR) 
    {
    Client_Error = true;
    Error_Detected = true;
    memcpy(Error_Message,"Error in Client_RecvData: ",45);
    int Error_Code = WSAGetLastError();
    itoa(Error_Code,Error_Message+25,10);

    if(Error_Code == 10054) // Connection Reset By Peer (UDP - The port is closed and cannot continue. Check if the server is running) (Can't connect to the selected port)
      {
      memcpy(Error_Message,"Error: Server is not running",45);
      }
    return Client_RecvBuffer;

    }
  return Client_RecvBuffer;
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Client_RecvData",45);
  }
}
//----------------------------------------------------------------------------------------------
void CWinSock::Client_SendData(char *Data,int Size)
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  Client_retval = send(Client_conn_socket,Data,Size,0);
  if(Client_retval == SOCKET_ERROR) 
    {
    Client_Error = true;
    WSACleanup();
    }
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Client_SendData",45);
  }
}
//----------------------------------------------------------------------------------------------
void CWinSock::Client_ShutDown()
//----------------------------------------------------------------------------------------------
{ 
if(Error_Detected == true)return;

try
  {
  closesocket(Client_conn_socket);
  WSACleanup();
  Client_Error = false;
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Client_ShutDown",45);
  }
}
//----------------------------------------------------------------------------------------------
void CWinSock::Client_Connect(char *IpOrName,unsigned short Port)
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  Client_server_name = IpOrName; 
  if (isalpha(Client_server_name[0])) // Checker den første byte om det er et bogstavt eller et tal...
    { 
    Client_hp = gethostbyname(Client_server_name); // den henter host information via host-name
    }
  else  
    { 
    Client_addr = inet_addr(Client_server_name); // Lavet Client_server_name om til et korrket Ipv4 format
    Client_hp = gethostbyaddr((char *)&Client_addr,4,AF_INET); // den henter host information via ip-address
    }
  if (Client_hp == NULL ) 
    {
    Client_Error = true; 
    WSACleanup();
    return;
    }
  memset(&Client_server,0,sizeof(Client_server)); // sletter alt information
//---------- Lægger informationen ind -------------------//
  memcpy(&(Client_server.sin_addr),Client_hp->h_addr,Client_hp->h_length);
  Client_server.sin_family = Client_hp->h_addrtype;
  Client_server.sin_port = htons(Port);
  Client_conn_socket = socket(AF_INET,Client_socket_type,0); 
  if (Client_conn_socket <0 ) 
    {
    Client_Error = true;
    WSACleanup();
    }
  if (connect(Client_conn_socket,(struct sockaddr*)&Client_server,sizeof(Client_server)) == SOCKET_ERROR) 
    {
    Client_Error = true;
    WSACleanup();
    return;
    }

  Client_SelectMessageObject();
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Client_Connect",45);
  }
} 
//----------------------------------------------------------------------------------------------
bool CWinSock::Client_CheckForError()
//----------------------------------------------------------------------------------------------
  {
  return Client_Error | Error_Detected;
  }
//----------------------------------------------------------------------------------------------
void CWinSock::Client_Init()
//----------------------------------------------------------------------------------------------
{
if(Error_Detected == true)return;

try
  {
  Client_Error = false;
  Client_server_name = "localhost"; 
  Client_socket_type = DEFAULT_PROTO;
  if (WSAStartup(0x202,&Client_wsaData) == SOCKET_ERROR) 
    {
    Client_Error = true;
    WSACleanup();
    }
  }
catch(...)
  {
  Error_Detected = true;
  memcpy(Error_Message,"Error in Client_Init",45);
  }
}
//----------------------------------------------------------------------------------------------
int CWinSock::Get_Error_Type()
//----------------------------------------------------------------------------------------------
  {
  return WSAGetLastError(); 
  }

//----------------------------------------------------------------------------------------------
int CWinSock::Get_Waiting_Packet()
//----------------------------------------------------------------------------------------------
  {
  return (int)*Dectect_Packes;
  }
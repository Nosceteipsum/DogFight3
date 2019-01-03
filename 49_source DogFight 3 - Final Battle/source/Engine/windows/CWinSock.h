////////////////////////////////////////////////////////////////////
//								  //
//			   WinSock ()			  	  //
//								  //
//	     Made By: Tommy Kobberø Andersen			  //
//								  //
////////////////////////////////////////////////////////////////////

#if!defined WinSock_H
#define WinSock_H

//----------------------------------//
//--------- Library files ----------//
//----------------------------------//

#pragma comment(linker, "/defaultlib:WS2_32.lib")

//----------------------------------//
//------------ Defines -------------//
//----------------------------------//

#define DEFAULT_PROTO                  SOCK_DGRAM // UDP

//----------------------------------//
//--------- Include files ----------//
//----------------------------------//

#include <winsock2.h>
#include <windows.h>

//----------------------------------//
//------------- Class --------------//
//----------------------------------//

class CWinSock
{
public:

CWinSock();
~CWinSock();

void  Client_Init();
bool  Client_CheckForError();
void  Client_Connect(char *IpOrName,unsigned short Port);
void  Client_ShutDown();
char* Client_RecvData();
void  Client_SendData(char *Data,int Size);
bool  Client_CheckObject();

bool  Server_CheckForError();
void  Server_SendData(char *Data,int Size);
void  Server_GetData(char *DataRecv);
bool  Server_CheckObject();
void  Server_StartServer(unsigned short Port);
void  Server_SaveIP(char SpaceNumber); 
void  Server_LoadIP(char SpaceNumber);
void  Server_DeInit();

int   Get_Error_Type();
int   Get_Waiting_Packet();

bool  Error_Check         ();
char *Get_Error_Message   ();

protected:
private:

void  Client_SelectMessageObject();
void  Server_SelectMessageObject();

u_long FAR*	  Dectect_Packes;

char              Client_RecvBuffer[2048];
bool              Client_Error;
char             *Client_server_name;
int               Client_retval;
unsigned int      Client_addr;
int               Client_socket_type;
struct            sockaddr_in Client_server;
struct            hostent *Client_hp;
WSADATA           Client_wsaData;
SOCKET            Client_conn_socket;
WSAEVENT	  Client_EventObject;

WSAEVENT	  Server_EventObject;
char             *Server_Interface;
int               Server_Socket_Type;
int               Server_fromlen;
WSADATA           Server_wsaData;
SOCKET            Server_listen_socket;
SOCKET            Server_msgsock;
bool              Server_Error;
int               Server_retval;
struct            sockaddr_in Server_local, 
                              Server_from, 
                              Server_Player[128];
unsigned long     Server_ioctl_opt;

bool Error_Detected;
char Error_Message[50];

};

#endif



/*  Error code

   WSAEINTR               10004   Interrupted system call.
   WSAEBADF               10009   Bad file number.
   WSEACCES               10013   Permission denied.
   WSAEFAULT              10014   Bad address.
   WSAEINVAL              10022   Invalid argument.
   WSAEMFILE              10024   Too many open files.
   WSAEWOULDBLOCK         10035   Operation would block.
   WSAEINPROGRESS         10036   Operation now in progress. This error is
                                  returned if any Windows Sockets API
                                  function is called while a blocking
                                  function is in progress.
   WSAEALREADY            10037   Operation already in progress.
   WSAENOTSOCK            10038   Socket operation on nonsocket.
   WSAEDESTADDRREQ        10039   Destination address required.
   WSAEMSGSIZE            10040   Message too long.
   WSAEPROTOTYPE          10041   Protocol wrong type for socket.
   WSAENOPROTOOPT         10042   Protocol not available.
   WSAEPROTONOSUPPORT     10043   Protocol not supported.
   WSAESOCKTNOSUPPORT     10044   Socket type not supported.
   WSAEOPNOTSUPP          10045   Operation not supported on socket.
   WSAEPFNOSUPPORT        10046   Protocol family not supported.
   WSAEAFNOSUPPORT        10047   Address family not supported by protocol
                                  family.
   WSAEADDRINUSE          10048   Address already in use.
   WSAEADDRNOTAVAIL       10049   Cannot assign requested address.
   WSAENETDOWN            10050   Network is down. This error may be
                                  reported at any time if the Windows
                                  Sockets implementation detects an
                                  underlying failure.
   WSAENETUNREACH         10051   Network is unreachable.
   WSAENETRESET           10052   Network dropped connection on reset.
   WSAECONNABORTED        10053   Software caused connection abort.
   WSAECONNRESET          10054   Connection reset by peer.
   WSAENOBUFS             10055   No buffer space available.
   WSAEISCONN             10056   Socket is already connected.
   WSAENOTCONN            10057   Socket is not connected.
   WSAESHUTDOWN           10058   Cannot send after socket shutdown.
   WSAETOOMANYREFS        10059   Too many references: cannot splice.
   WSAETIMEDOUT           10060   Connection timed out.
   WSAECONNREFUSED        10061   Connection refused.
   WSAELOOP               10062   Too many levels of symbolic links.
   WSAENAMETOOLONG        10063   File name too long.
   WSAEHOSTDOWN           10064   Host is down.
   WSAEHOSTUNREACH        10065   No route to host.
   WSASYSNOTREADY         10091   Returned by WSAStartup(), indicating that
                                  the network subsystem is unusable.
   WSAVERNOTSUPPORTED     10092   Returned by WSAStartup(), indicating that
                                  the Windows Sockets DLL cannot support
                                  this application.
   WSANOTINITIALISED      10093   Winsock not initialized. This message is
                                  returned by any function except
                                  WSAStartup(), indicating that a
                                  successful WSAStartup() has not yet been
                                  performed.
   WSAEDISCON             10101   Disconnect.
   WSAHOST_NOT_FOUND      11001   Host not found. This message indicates
                                  that the key (name, address, and so on)
                                  was not found.
   WSATRY_AGAIN           11002   Nonauthoritative host not found. This
                                  error may suggest that the name service
                                  itself is not functioning.
   WSANO_RECOVERY         11003   Nonrecoverable error. This error may
                                  suggest that the name service itself is
                                  not functioning.
   WSANO_DATA             11004   Valid name, no data record of requested
                                  type. This error indicates that the key
                                  (name, address, and so on) was not found.



WSAEINVAL
10022 
    Invalid argument. 
    Some invalid argument was supplied 
    (for example, specifying an invalid level to the setsockopt function). 
    In some instances, it also refers to the current state of the socket—for instance, 
    calling accept on a socket that is not listening.  

WSAECONNRESET
10054
    The virtual circuit was reset by the remote side executing a hard or abortive close. 
    The application should close the socket as it is no longer usable. 
    On a UPD-datagram socket this error would indicate that a previous send operation resulted 
    in an ICMP "Port Unreachable" message.

*/
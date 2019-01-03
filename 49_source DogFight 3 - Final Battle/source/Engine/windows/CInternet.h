///////////////////////////////////////////////////////////////
//                                                           //
//                   CInternet Class                         //
//                                                           //
//        Last Updated: 25-04-03 08-28                       //
//        Made By: Tommy Kobberø Andersen                    //
//                                                           //
//                                                           //
///////////////////////////////////////////////////////////////

#if!defined CINTERNET_H
#define CINTERNET_H

///////////////////////////////////////////////////////////////
//                       Headers                             //
///////////////////////////////////////////////////////////////

#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////
//                       Library's                           //
///////////////////////////////////////////////////////////////

#pragma comment(linker, "/defaultlib:wininet.lib")

///////////////////////////////////////////////////////////////
//                       Prototypes                          //
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
//                      Class/Struct                         //
///////////////////////////////////////////////////////////////

class CInternet
{
public:

CInternet();
~CInternet();

bool  InitInternet();
bool  DeInitInternet();

bool  Connect(char *Url,char* Web_File);
char  *GetData();

bool  FreePointer();

std::string *GetErrorString();

bool         Error_Check();
const char  *Error_GetMessage();

protected:
private:

HINTERNET m_hSession;
HINTERNET m_hConnection;
HINTERNET m_hHTTP;

char     *m_cpHtml_Data;

std::string m_oError_Message;
bool        m_bError_Detected;
char        m_cError_Code[32];
};

#endif




/* Error Type returned by GetLastError():

ERROR_WINHTTP_AUTO_PROXY_SERVICE_ERROR 
12178
Returned by WinHttpGetProxyForUrl when a proxy for the specified URL cannot be located. 
ERROR_WINHTTP_AUTODETECTION_FAILED 
12180
Returned by WinHttpDetectAutoProxyConfigUrl if WinHTTP was unable to discover the URL of the Proxy Auto-Configuration (PAC) file. 
ERROR_WINHTTP_BAD_AUTO_PROXY_SCRIPT 
12166
An error occurred executing the script code in the Proxy Auto-Configuration (PAC) file. 
ERROR_WINHTTP_CANNOT_CALL_AFTER_OPEN 
12103
Returned by the HttpRequest object if a specified option cannot be requested after the Open method has been called. 
ERROR_WINHTTP_CANNOT_CALL_AFTER_SEND 
12102
Returned by the HttpRequest object if a requested operation cannot be performed after calling the Send method. 
ERROR_WINHTTP_CANNOT_CALL_BEFORE_OPEN 
12100
Returned by the HttpRequest object if a requested operation cannot be performed before calling the Open method. 
ERROR_WINHTTP_CANNOT_CALL_BEFORE_SEND 
12101
Returned by the HttpRequest object if a requested operation cannot be performed before calling the Send method. 
ERROR_WINHTTP_CANNOT_CONNECT 
12029
Returned if connection to the server failed. 
ERROR_WINHTTP_CHUNKED_ENCODING_HEADER_SIZE_OVERFLOW 
12183
Returned by WinHttpReceiveResponse when an overflow condition is encountered in the course of parsing chunked encoding. 
ERROR_WINHTTP_CLIENT_AUTH_CERT_NEEDED 
12044
Returned by WinHttpReceiveResponse when the server requests client authentication. 
ERROR_WINHTTP_CONNECTION_ERROR 
12030
The connection with the server has been reset or terminated, or an incompatible SSL protocol was encountered. For example, WinHTTP version 5.1 does not support SSL2 unless the client specifically enables it. 
ERROR_WINHTTP_HEADER_ALREADY_EXISTS 
12155
Obsolete; no longer used. 
ERROR_WINHTTP_HEADER_COUNT_EXCEEDED 
12181
Returned by WinHttpReceiveResponse when a larger number of headers were present in a response than WinHTTP could receive. 
ERROR_WINHTTP_HEADER_NOT_FOUND 
12150
The requested header could not be located. 
ERROR_WINHTTP_HEADER_SIZE_OVERFLOW 
12182
Returned by WinHttpReceiveResponse when the size of headers received exceeds the limit for the request handle. 
ERROR_WINHTTP_INCORRECT_HANDLE_STATE 
12019
The requested operation cannot be carried out because the handle supplied is not in the correct state. 
ERROR_WINHTTP_INCORRECT_HANDLE_TYPE 
12018
The type of handle supplied is incorrect for this operation. 
ERROR_WINHTTP_INTERNAL_ERROR 
12004
An internal error has occurred. 
ERROR_WINHTTP_INVALID_OPTION 
12009
A request to WinHttpQueryOption or WinHttpSetOption specified an invalid option value. 
ERROR_WINHTTP_INVALID_QUERY_REQUEST 
12154
Obsolete; no longer used. 
ERROR_WINHTTP_INVALID_SERVER_RESPONSE 
12152
The server response could not be parsed. 
ERROR_WINHTTP_INVALID_URL 
12005
The URL is invalid. 
ERROR_WINHTTP_LOGIN_FAILURE 
12015
The login attempt failed. When this error is encountered, the request handle should be closed with WinHttpCloseHandle. A new request handle must be created before retrying the function that originally produced this error. 
ERROR_WINHTTP_NAME_NOT_RESOLVED 
12007
The server name could not be resolved. 
ERROR_WINHTTP_NOT_INITIALIZED 
12172
Obsolete; no longer used. 
ERROR_WINHTTP_OPERATION_CANCELLED 
12017
The operation was canceled, usually because the handle on which the request was operating was closed before the operation completed. 
ERROR_WINHTTP_OPTION_NOT_SETTABLE 
12011
The requested option cannot be set, only queried. 
ERROR_WINHTTP_OUT_OF_HANDLES 
12001
Obsolete; no longer used. 
ERROR_WINHTTP_PROXY_AUTH_REQUIRED 
12185
Returned by WinHttpSendRequest on Windows Server 2003 family if an HTTP status code of 407 is returned, which indicates that proxy authentication is required. This error was added to handle the case where the client is trying to establish an SSL connection to a target server via a proxy server, but the proxy server requires authentication. 
This error is not returned on Windows XP SP1 and Windows 2000 SP3, which leaves the client unaware that the SSL connection failed. In this case, a subsequent call to WinHttpWriteData to send some POST data, or to WinHttpReceiveResponse to get the response, fails with an INCORRECT_HANDLE_STATE error.

ERROR_WINHTTP_REDIRECT_FAILED 
12156
The redirection failed because either the scheme changed or all attempts made to redirect failed (default is five attempts). 
ERROR_WINHTTP_RESEND_REQUEST 
12032
The WinHTTP function failed. The desired function can be retried on the same request handle. 
ERROR_WINHTTP_RESPONSE_DRAIN_OVERFLOW 
12184
Returned when an incoming response exceeds an internal WinHTTP size limit. 
ERROR_WINHTTP_SECURE_CERT_CN_INVALID 
12038
Returned when a certificate's CN name does not match the passed value (equivalent to a CERT_E_CN_NO_MATCH error). 
ERROR_WINHTTP_SECURE_CERT_DATE_INVALID 
12037
Indicates that a required certificate is not within its validity period when verifying against the current system clock or the timestamp in the signed file, or that the validity periods of the certification chain do not nest correctly (equivalent to a CERT_E_EXPIRED or a CERT_E_VALIDITYPERIODNESTING error). 
ERROR_WINHTTP_SECURE_CERT_REV_FAILED 
12057
Indicates that revocation could not be checked because the revocation server was offline (equivalent to CRYPT_E_REVOCATION_OFFLINE). 
ERROR_WINHTTP_SECURE_CERT_REVOKED 
12170
Indicates that a certificate has been revoked (equivalent to CRYPT_E_REVOKED). 
ERROR_WINHTTP_SECURE_CERT_WRONG_USAGE 
12179
Indicates that a certificate is not valid for the requested usage (equivalent to CERT_E_WRONG_USAGE). 
ERROR_WINHTTP_SECURE_CHANNEL_ERROR 
12157
Indicates that an error occurred having to do with a secure channel (equivalent to error codes that begin with "SEC_E_" and "SEC_I_" listed in the winerror.h header file ). 
ERROR_WINHTTP_SECURE_FAILURE 
12175
One or more errors were found in the Secure Sockets Layer (SSL) certificate sent by the server. To determine what type of error was encountered, check for a WINHTTP_CALLBACK_STATUS_SECURE_FAILURE notification in a status callback function. For more information, see WINHTTP_STATUS_CALLBACK. 
ERROR_WINHTTP_SECURE_INVALID_CA 
12045
Indicates that a certificate chain was processed but terminated in a root certificate that is not trusted by the trust provider (equivalent to CERT_E_UNTRUSTEDROOT). 
ERROR_WINHTTP_SECURE_INVALID_CERT 
12169
Indicates that a certificate is invalid (equivalent to errors such as CERT_E_ROLE, CERT_E_PATHLENCONST, CERT_E_CRITICAL, CERT_E_PURPOSE, CERT_E_ISSUERCHAINING, CERT_E_MALFORMED and CERT_E_CHAINING). 
ERROR_WINHTTP_SHUTDOWN 
12012
The WinHTTP function support is being shut down or unloaded. 
ERROR_WINHTTP_TIMEOUT 
12002
The request has timed out. 
ERROR_WINHTTP_UNABLE_TO_DOWNLOAD_SCRIPT 
12167
The PAC file could not be downloaded. For example, the server referenced by the PAC URL may not have been reachable, or the server returned a 404 NOT FOUND response. 
ERROR_WINHTTP_UNRECOGNIZED_SCHEME 
12006
The URL specified a scheme other than "http:" or "https:". 
ERROR_NOT_ENOUGH_MEMORY 
Not enough memory was available to complete the requested operation. (Windows error code) 
ERROR_INSUFFICIENT_BUFFER 
The size of the buffer supplied to a function was insufficient to contain the returned data. The number of bytes required is usually returned in the buffer size parameter. See the specific function for details. (Windows error code) 
ERROR_INVALID_HANDLE 
The handle that was passed to the application programming interface (API) has been either invalidated or closed. (Windows error code) 
ERROR_NO_MORE_FILES 
No more files have been found. (Windows error code) 
ERROR_NO_MORE_ITEMS 
No more items have been found. (Windows error code) 
ERROR_NOT_SUPPORTED 
The required protocol stack is not loaded and the application cannot start WinSock. 
*/
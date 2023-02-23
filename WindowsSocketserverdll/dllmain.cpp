// dllmain.cpp : 定义 DLL 应用程序的入口点。
#define _CRT_SECURE_NO_WARNINGS 1
#include "pch.h"
using namespace std;
bool initWinSockC(BYTE bLow, BYTE bHigh)
{
    //初始化
    WORD wVersionRequired = MAKEWORD(bLow, bHigh);//请根据不同的windows系统版本选择套接字1.0，1.1，2.0，2.2
    WSADATA lpWSAData;//接收的指针
    int intEr = WSAStartup(wVersionRequired, &lpWSAData); // 指定winsock版本并初始化
    switch (intEr) {
    case WSASYSNOTREADY:
        //底层网络子系统尚未准备好进行网络通信。
        MessageBoxA(NULL, "The underlying network subsystem is not ready for network communication.", "Error", 0);
    case WSAVERNOTSUPPORTED:
        //此特定 Windows 套接字实现不提供请求的 Windows 套接字支持版本。
        MessageBoxA(NULL, "The version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation.", "Error", 0);
    case WSAEINPROGRESS:
        //正在进行阻塞的 Windows Sockets 1.1 操作。
        MessageBoxA(NULL, "A blocking Windows Sockets 1.1 operation is in progress.", "Error", 0);
    case WSAEPROCLIM:
        //已达到 Windows 套接字实现支持的任务数限制。
        MessageBoxA(NULL, "A limit on the number of tasks supported by the Windows Sockets implementation has been reached.", "Error", 0);
    case WSAEFAULT:
        //lpWSAData 参数不是有效指针。
        MessageBoxA(NULL, "The lpWSAData parameter is not a valid pointer.", "Error", 0);
    case 0:
        //cout << "WinSock初始化成功！" << endl;
        return true;
    default:
        //发生未知错误
        MessageBoxA(NULL, "WSAStartup an unknown error occurred.", "Error", 0);
    }
    return false;
}
char* WindowsSocketServer(IN_ADDR ip, unsigned short port) {
    if (initWinSockC(2, 2) == false) {
        return 0;
    }
    typedef struct addrinfo {
        int             ai_flags;
        int             ai_family;
        int             ai_socktype;
        int             ai_protocol;
        size_t          ai_addrlen;
        char* ai_canonname;
        struct sockaddr* ai_addr;
        struct addrinfo* ai_next;
    } ADDRINFOA, * PADDRINFOA;
    //https://learn.microsoft.com/en-us/windows/win32/api/ws2def/ns-ws2def-addrinfoa
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    ZeroMemory(&hints, sizeof(hints));
    //SecureZeroMemory(&hints, sizeof(addrinfo));此函数为老版函数
    hints.ai_family = AF_INET; //IPv4协议，AF_INET6 IPv6协议
    hints.ai_socktype = SOCK_STREAM; //流式套接字用于TCP协议
    hints.ai_protocol = IPPROTO_TCP;
    //创建套接字
    SOCKET Create_Server_Socket = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
    if (Create_Server_Socket == INVALID_SOCKET) {
        //套接字创建失败
        switch (WSAGetLastError()) {
        case WSANOTINITIALISED:
            //在使用此函数之前必须进行成功的 WSAStartup调用。
            printf("A successful WSAStartup call must occur before using this function.\n");
        case WSAENETDOWN:
            //网络子系统或关联的服务提供商出现故障。
            printf("The network subsystem or the associated service provider has failed.\n");
        case WSAEAFNOSUPPORT:
            //不支持指定的地址族。例如，应用程序试图为AF_IRDA地址系列创建套接字，但本地计算机上未安装红外线适配器和设备驱动程序。
            printf("The specified address family is not supported.For example, an application tried to create a socket for the AF_IRDA address family but an infrared adapterand device driver is not installed on the local computer.\n");
        case WSAEINPROGRESS:
            //正在进行阻塞的 Windows Sockets 1.1 调用，或者服务提供商仍在处理回调函数。
            printf("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.\n");
        case WSAEMFILE:
            //没有更多的套接字描述符可用。
            printf("No more socket descriptors are available.\n");
        case WSAEINVAL:
            //提供了无效参数。
            printf("An invalid argument was supplied.This error is returned if the af parameter is set to AF_UNSPECand the typeand protocol parameter are unspecified.\n");
        case WSAEINVALIDPROVIDER:
            //服务提供商返回了 2.2 以外的版本。
            printf("The service provider returned a version other than 2.2.\n");
        case WSAEINVALIDPROCTABLE:
            //服务提供商向WSPStartup 返回了无效或不完整的过程表 。
            printf("The service provider returned an invalid or incomplete procedure table to the WSPStartup.\n");
        case WSAENOBUFS:
            //没有可用的缓冲区空间。无法创建套接字。
            printf("No buffer space is available.The socket cannot be created.\n");
        case WSAEPROTONOSUPPORT:
            //不支持指定的协议。
            printf("The specified protocol is not supported.\n");
        case WSAEPROTOTYPE:
            //指定的协议是此套接字的错误类型。
            printf("The specified protocol is the wrong type for this socket.\n");
        case WSAEPROVIDERFAILEDINIT:
            //服务提供者初始化失败。
            printf("The service provider failed to initialize.This error is returned if a layered service provider(LSP) or namespace provider was improperly installed or the provider fails to operate correctly.\n");
        case WSAESOCKTNOSUPPORT:
            //此地址系列不支持指定的套接字类型。
            printf("The specified socket type is not supported in this address family.\n");
        default:
            printf("an unknown error occurred.\n");
        }
        MessageBoxA(NULL, "Create_Server_Socket TCP IPv4 failed.", "Error", 0);
        return 0;
    }
    //填充服务器端套接字结构  
    SOCKADDR_IN addrServer;
    //将主机字节顺序转换为TCP/IP网络字节顺序  
    addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrServer.sin_family = AF_INET;
    //in_addr addr = ip;
    //addrServer.sin_addr = addr;
    addrServer.sin_port = htons(port);
    int err = bind(Create_Server_Socket, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
    if (err == SOCKET_ERROR) {
        //套接字绑定失败
        switch (WSAGetLastError()) {
        case WSANOTINITIALISED:
            //注意在使用此函数之前必须进行成功的 WSAStartup调用。
            printf("Note  A successful WSAStartup call must occur before using this function.\n");
        case WSAENETDOWN:
            //网络子系统出现故障。
            printf("The network subsystem has failed.\n");
        case WSAEACCES:
            //试图以访问权限禁止的方式访问套接字。
            printf("An attempt was made to access a socket in a way forbidden by its access permissions.\n");
        case WSAEADDRINUSE:
            //每个套接字地址（协议/网络地址/端口）通常只允许使用一次。
            printf("Only one usage of each socket address (protocol/network address/port) is normally permitted.\n");
        case WSAEADDRNOTAVAIL:
            //请求的地址在其上下文中无效。
            printf("The requested address is not valid in its context.\n");
        case WSAEFAULT:
            //系统在尝试在调用中使用指针参数时检测到无效的指针地址。
            printf("The system detected an invalid pointer address in attempting to use a pointer argument in a call.\n");
        case WSAEINPROGRESS:
            //正在进行阻塞的 Windows Sockets 1.1 调用，或者服务提供商仍在处理回调函数。
            printf("A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.\n");
        case WSAEINVAL:
            //提供了无效参数。
            printf("An invalid argument was supplied.\n");
        case WSAENOBUFS:
            //由于系统缺少足够的缓冲区空间或队列已满，无法对套接字执行操作。
            printf("An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.\n");
        case WSAENOTSOCK:
            //尝试对不是套接字的对象进行操作。
            printf("An operation was attempted on something that is not a socket.\n");
        default:
            //其它未知错误
            printf("an unknown error occurred.\n");
        }
        MessageBoxA(NULL, "addrServer failed.", "Error", 0);
        return 0;
    }
    err = listen(Create_Server_Socket, 5);
    //-------------------------------------------listen(SOCKET s,int backlog)-------------------------------------------
       //挂起连接队列的最大长度。
       //如果设置为SOMAXCONN，负责 socket 的底层服务提供者会将积压设置为最大合理值。
       //如果设置为SOMAXCONN_HINT(N)（其中 N 是一个数字），则积压值将为 N，调整到范围(200, 65535) 内。
       //请注意，SOMAXCONN_HINT可用于将积压设置为比 SOMAXCONN 可能的值更大的值。
       //SOMAXCONN_HINT仅受 Microsoft TCP / IP 服务提供商支持。没有获取实际积压值的标准规定。
       //https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-listen
    if (err == SOCKET_ERROR) {
        //监听失败
        switch (WSAGetLastError()) {
        case WSAENOTSOCK:
            printf("The descriptor is not a socket..\n");
        case WSAEOPNOTSUPP:
            //引用的套接字不是支持侦听操作 的类型 。
            printf("The referenced socket is not of a type that supports the listen operation.\n");
        default:
            //其它未知错误
            printf("an unknown error occurred.\n");
        }
        MessageBoxA(NULL, "listen failed.", "Error", 0);
        return 0;
    }
    SOCKADDR_IN addrClient;
    int len = sizeof(SOCKADDR);
    SOCKET sockConn = accept(Create_Server_Socket, (SOCKADDR*)&addrClient, &len);
    //创建等待连接的套接字，需要清理
    if (sockConn == INVALID_SOCKET) {
        //等待客户端连接失败
        MessageBoxA(NULL, "accept called failed!.", "Error", 0);
        //printf("accept() called failed! The error code is: %d\n", WSAGetLastError());
    }
    char sendBuf[100] = "";
    int senderror = send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);//发送数据
    if (senderror == SOCKET_ERROR) {
        cout << "not send" << endl;
    }
    char* recvBuf = { 0 };
    int recvError = recv(sockConn, recvBuf, 255, 0);//接收数据
    if (recvError == SOCKET_ERROR) {
        cout << "not recv" << endl;
    }
    closesocket(sockConn);
    closesocket(Create_Server_Socket);
    return recvBuf;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


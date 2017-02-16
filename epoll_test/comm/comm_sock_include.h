#pragma once

#include <stdint.h>

#if defined(__linux__)
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <net/if.h>
#include <errno.h>


using socket_fd_t = int;
using last_err_t = int;
#define LAST_ERROR_CODE errno

#define close_socket(s) close(s)

#elif defined(_MSC_VER)
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"WS2_32")

using socket_fd_t = SOCKET;
using last_err_t = DWORD;
#define LAST_ERROR_CODE GetLastError()

#define close_socket(s) closesocket(s)

/**************在 windows 上自己定义一下epoll_event结构, 省得到处需要macro***************/
//参考自Linux上的定义
typedef union epoll_data {
    void    *ptr;
    int      fd;
    uint32_t u32;
    uint64_t u64;
} epoll_data_t;

struct epoll_event {
    uint32_t     events;    /* Epoll events */
    epoll_data_t data;      /* User data variable */
};


#else
#error "TODO: Platform not supported.";   //TODO: 
#endif


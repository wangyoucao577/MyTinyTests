#pragma once

#include "comm_sock_include.h"
#include "comm_include.h"
#include "TcpLister.h"

class EpollServer
{
public:
    explicit EpollServer();
    ~EpollServer();

public:
    void AddTcpLister(TcpLister tcp_listener);
    void AddSocket(socket_fd_t sock, uint32_t events);
    void DelSocket(socket_fd_t sock);

public:
    socket_fd_t Accept(socket_fd_t sock);

public:
    int Wait(int timeout_msec, struct epoll_event* events, int max_events);

public:
    bool IsListener(socket_fd_t sock);

private:

    socket_fd_t epoll_fd_;
    map<socket_fd_t, TcpLister> tcp_listeners_map_;
    
};


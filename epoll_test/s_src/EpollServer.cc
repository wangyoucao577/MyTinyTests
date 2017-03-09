#include "EpollServer.h"
#include "comm_include.h"


EpollServer::EpollServer()
{
    epoll_fd_ = epoll_create(1);
    if (-1 == epoll_fd_) {
        cout << "create epoll failed, errno " << LAST_ERROR_CODE << endl;
        throw LAST_ERROR_CODE;
    }
}


EpollServer::~EpollServer()
{
    close(epoll_fd_);
}

int EpollServer::Wait(int timeout_msec, struct epoll_event* events, int max_events) {

    int ready_count = -1;

    ready_count = epoll_wait(epoll_fd_, events, max_events, timeout_msec);
    if (-1 == ready_count) {
        cout << "epoll_wait on " << epoll_fd_
            << " failed, errno " << LAST_ERROR_CODE << endl;
        throw LAST_ERROR_CODE;
    }

    return ready_count;
}

void EpollServer::AddTcpLister(TcpLister tcp_listener)
{
    socket_fd_t sock = tcp_listener.Socket();

    //NOTE: insert的动作触发了两次移动构造
    //遗留问题: 没太搞明白为什么?
    //tcp_listeners_map_.insert(map<socket_fd_t, TcpLister>::value_type(sock, move(tcp_listener)));
    tcp_listeners_map_.insert(make_pair(sock, move(tcp_listener)));

    uint32_t events = kEpollEventRead | kEpollEventError | kEpollEventET;
    return AddSocket(sock, events);
}
void EpollServer::AddSocket(socket_fd_t sock, uint32_t events)
{

    struct epoll_event ev;
    ev.events = events;
    ev.data.fd = sock;

    int err = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, sock, &ev);
    if (-1 == err) {
        cout << "epoll_ctl add " << sock << " to " << epoll_fd_ 
            << " failed, errno " << LAST_ERROR_CODE << endl;
        throw LAST_ERROR_CODE;
    }

}

void EpollServer::DelSocket(socket_fd_t sock) {

    int err = epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, sock, NULL);
    if (-1 == err) {
        cout << "epoll_ctl delete " << sock << " to " << epoll_fd_
            << " failed, errno " << LAST_ERROR_CODE << endl;
        throw LAST_ERROR_CODE;
    }
}

bool EpollServer::IsListener(socket_fd_t sock) {
    auto it = tcp_listeners_map_.find(sock);
    if (it != tcp_listeners_map_.end()) {
        return true;
    }
    return false;
}

socket_fd_t EpollServer::Accept(socket_fd_t sock) {
    assert(IsListener(sock));

    auto it = tcp_listeners_map_.find(sock);
    return it->second.Accept();
}
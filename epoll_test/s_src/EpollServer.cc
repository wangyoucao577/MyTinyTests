#include "EpollServer.h"
#include "comm_include.h"


EpollServer::EpollServer()
{
#if defined(__linux__)
    epoll_fd_ = epoll_create(1);
    if (-1 == epoll_fd_) {
        cout << "create epoll failed, errno " << LAST_ERROR_CODE << endl;
        throw LAST_ERROR_CODE;
    }
#endif
}


EpollServer::~EpollServer()
{
#if defined(__linux__)
    close(epoll_fd_);
#endif

}

int EpollServer::Wait(int timeout_msec, struct epoll_event* events, int max_events) {

    int ready_count = -1;
#if defined(__linux__)

    ready_count = epoll_wait(epoll_fd_, events, max_events, timeout_msec);
    if (-1 == ready_count) {
        cout << "epoll_wait on " << epoll_fd_
            << " failed, errno " << LAST_ERROR_CODE << endl;
        throw LAST_ERROR_CODE;
    }
#endif

    return ready_count;
}

void EpollServer::AddTcpLister(socket_fd_t sock)
{
    tcp_listener_set_.insert(sock);
    
    uint32_t events = kEpollEventRead | kEpollEventError | kEpollEventET;

    return AddSocket(sock, events);
}
void EpollServer::AddSocket(socket_fd_t sock, uint32_t events)
{
#if defined(__linux__)

    struct epoll_event ev;
    ev.events = events;
    ev.data.fd = sock;

    int err = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, sock, &ev);
    if (-1 == err) {
        cout << "epoll_ctl add " << sock << " to " << epoll_fd_ 
            << " failed, errno " << LAST_ERROR_CODE << endl;
        throw LAST_ERROR_CODE;
    }
#endif
}

void EpollServer::DelSocket(socket_fd_t sock) {

#if defined(__linux__)
    int err = epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, sock, NULL);
    if (-1 == err) {
        cout << "epoll_ctl delete " << sock << " to " << epoll_fd_
            << " failed, errno " << LAST_ERROR_CODE << endl;
        throw LAST_ERROR_CODE;
    }
#endif

}

bool EpollServer::IsListener(socket_fd_t sock) {
    auto it = tcp_listener_set_.find(sock);
    if (it != tcp_listener_set_.end()) {
        return true;
    }
    return false;
}
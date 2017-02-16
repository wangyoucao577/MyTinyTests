#include "TcpLister.h"



TcpLister::TcpLister(unsigned short port, string name) :
    name_(name), port_(port)
{
    tcp_lister_sock_ = socket(AF_INET, SOCK_STREAM, 0);
    assert(static_cast<int>(tcp_lister_sock_) != -1);

    int reuse = 1;
    if (0 != setsockopt(tcp_lister_sock_, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)))
    {
        assert(0);
    }

    struct sockaddr_in tcpListenAddr;
    tcpListenAddr.sin_family = AF_INET;
    tcpListenAddr.sin_port = htons(port_);
    tcpListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (-1 == bind(tcp_lister_sock_, (struct sockaddr*)&tcpListenAddr, sizeof(tcpListenAddr)))
    {
        assert(0);
    }

    if (-1 == listen(tcp_lister_sock_, 100))
    {
        assert(0);
    }

}

TcpLister::TcpLister(TcpLister&& org):
tcp_lister_sock_(org.tcp_lister_sock_),
name_(org.name_),
port_(org.port_)
{
    org.tcp_lister_sock_ = -1;  //clear
}

TcpLister::~TcpLister()
{
    if (-1 != static_cast<int>(tcp_lister_sock_)) {
        close_socket(tcp_lister_sock_);
    }
}

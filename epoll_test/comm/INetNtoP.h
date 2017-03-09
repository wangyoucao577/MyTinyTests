#pragma once

#include "comm_include.h"
#include "comm_sock_include.h"


class INetNtoP
{
public:
    explicit INetNtoP(const struct sockaddr* sa);
    ~INetNtoP();

public:
    string IPStr() { return string(ipstr_); }
    const char* IPCStr() { return ipstr_; }
    unsigned int Port() { return port_; }

private:
    char ipstr_[INET6_ADDRSTRLEN] {0};
    unsigned int port_{0};
};


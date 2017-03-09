#include "INetNtoP.h"


INetNtoP::INetNtoP(const struct sockaddr* sa)
{
    const char * pstr = NULL;
    switch (sa->sa_family) {
    case AF_INET:
        pstr = inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr), ipstr_, sizeof(ipstr_));
        break;
    case AF_INET6:
        pstr = inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr), ipstr_, sizeof(ipstr_));
        break;
    default:
        strncpy(ipstr_, "Unknown AF", sizeof(ipstr_));
        return;
    }

    if (pstr == NULL) {
        //inet_ntop failed, throw the error code as an exception
        throw LAST_ERROR_CODE;
    }

    port_ = ntohs(((struct sockaddr_in*)sa)->sin_port);
}


INetNtoP::~INetNtoP()
{
}

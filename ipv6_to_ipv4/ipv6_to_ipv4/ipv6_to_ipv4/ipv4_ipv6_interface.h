//
//  ipv4_ipv6_interface.h
//  ipv6_to_ipv4
//
//  Created by wangyoucao577 on 8/29/16.
//  Copyright © 2016 wangyoucao577. All rights reserved.
//

#ifndef ipv4_ipv6_interface_h
#define ipv4_ipv6_interface_h

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <net/if.h>

struct sockaddr_ex{
    struct sockaddr_storage sockaddr_info;
    socklen_t sockaddr_len;
    
    char ip_address_str[INET6_ADDRSTRLEN];  //also enough space for ipv4, so compatible for ipv4 and ipv6
    unsigned short port;
    
    int	ai_socktype;	/* SOCK_xxx */
    int	ai_protocol;	/* 0 or IPPROTO_xxx for IPv4 and IPv6 */
};

char * ipv4v6_inet_ntop(const struct sockaddr_ex*);

//return a malloced memory pointer to the indicated device.
//should call free_sockaddr_ex after use.
struct sockaddr_ex* get_local_net(const char* dev_name, int dev_name_len);

//return a malloced memory pointer to the struct.
//should call free_sockaddr_ex after use.
struct sockaddr_ex* get_ipv4_sockaddr_ex(int local_ss_family, int socktype, const char* ipv4);

void free_sockaddr_ex(struct sockaddr_ex*);

int format_port_to_sockaddr_ex(struct sockaddr_ex*, unsigned short port);




int test_tcp_connect_to_ipv4(const struct sockaddr_ex* local_addr, const char* peer_ipv4, unsigned short port);

#endif /* ipv4_ipv6_interface_h */

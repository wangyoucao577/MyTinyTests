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
//if dev_name pass NULL as input, it's behavior will be printf all interfaces with ipv4 or ipv6 address, ignore LINKLOCAL
struct sockaddr_ex* get_local_net(const char* dev_name, int dev_name_len);

//return a malloced memory pointer to the struct.
//should call free_sockaddr_ex after use.
struct sockaddr_ex* get_ipv4_sockaddr_ex(int local_ss_family, int socktype, const char* ipv4);

void free_sockaddr_ex(struct sockaddr_ex*);

int format_port_to_sockaddr_ex(struct sockaddr_ex*, unsigned short port);


char * inet_ntop_ipv4_ipv6_compatible(const struct sockaddr *sa, char *s, unsigned int maxlen);



/**
 @brief a easy way to get addrinfo when you as a client or a server.
 @param ss_family AF_INET or AF_INET6
 @param sock_type SOCK_STREAM or SOCK_DGRAM
 @param ip presentation format ip, could be ipv4 or ipv6. NULL if any ip. could not be a domain name(such as "www.google.com").
 @param port indicated port. 0 if any port.
 @param [out] output the constructed addrinfo, similar as getaddrinfo interface. but only output one res. call freeaddrinfo after use.
 @return 0 if it succeeds, otherwise failed. reference the errorcode of getaddrinfo interface if failed.
 */
int easy_getaddrinfo(int ss_family, int sock_type, const char* ip, unsigned short port, struct addrinfo** res);

//you can reference the easy_client_getaddrinfo interface sample here
void getaddrinfo_behavior_individual_case(const char* case_str, int ss_family, const char* ip, unsigned short port);


//test interfaces
int test_tcp_connect_to_ipv4(const struct sockaddr_ex* local_addr, const char* peer_ipv4, unsigned short port);
int test_tcp_connect_to_ipv4_via_easy_getaddrinfo(const struct sockaddr_ex* local_addr, const char* peer_ipv4, unsigned short port);

void getaddrinfo_behavior_test();
void exported_test();


#endif /* ipv4_ipv6_interface_h */

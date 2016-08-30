//
//  ipv4_ipv6_interface.h
//  ipv6_to_ipv4
//
//  Created by wangyoucao577 on 8/29/16.
//  Copyright © 2016 wangyoucao577. All rights reserved.
//

#ifndef ipv4_ipv6_interface_h
#define ipv4_ipv6_interface_h

#ifdef WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <errno.h>
#endif


#ifndef WIN32
//return a mallocced memory pointer to the indicated device, indicated the ip address as presentation format.
//should call free after use.
//if dev_name pass NULL as input, it's behavior will be printf all interfaces with ipv4 or ipv6 address, ignore LINKLOCAL
char* get_local_net(const char* dev_name, int dev_name_len);
#endif

//Convert a struct sockaddr address to a string, support IPv4 and IPv6
char * inet_ntop_ipv4_ipv6_compatible(const struct sockaddr *sa, char *s, unsigned int maxlen);

//check ss_family for ipstr, return AF_INET or AF_INET6 if succeed, otherwise failed.
int ip_str_family(char* ipstr);

/**
 @brief a easy way to get addrinfo when you as a client or a server.
 @param ss_family AF_INET, AF_INET6 or AF_UNSPEC
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
//if local_ip_str is not NULL, the socket will bind this ip address before connect
int test_tcp_connect_to_ipv4_via_easy_getaddrinfo(int ss_family, char* local_ip_str, const char* peer_ipv4, unsigned short port);

void getaddrinfo_behavior_test();
void exported_test();


#endif /* ipv4_ipv6_interface_h */

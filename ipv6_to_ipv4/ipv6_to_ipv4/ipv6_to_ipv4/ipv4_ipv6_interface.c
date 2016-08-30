//
//  ipv4_ipv6_interface.c
//  ipv6_to_ipv4
//
//  Created by wangyoucao577 on 8/29/16.
//  Copyright © 2016 wangyoucao577. All rights reserved.
//

#include "ipv4_ipv6_interface.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#ifndef __APPLE__
#define IN_LINKLOCALNETNUM	(u_int32_t)0xA9FE0000 /* 169.254.0.0 */
#define IN_LINKLOCAL(i)		(((u_int32_t)(i) & IN_CLASSB_NET) == IN_LINKLOCALNETNUM)
#endif

char * ipv4v6_inet_ntop(const struct sockaddr_ex* s_ex)
{
    assert(NULL != s_ex);
    
    memset((char*)s_ex->ip_address_str, 0, sizeof(s_ex->ip_address_str));
    
    switch(s_ex->sockaddr_info.ss_family) {
        case AF_INET:
            inet_ntop(AF_INET, &(((struct sockaddr_in *)&s_ex->sockaddr_info)->sin_addr), (char*)s_ex->ip_address_str, sizeof(s_ex->ip_address_str));
            break;
            
        case AF_INET6:
            inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)&s_ex->sockaddr_info)->sin6_addr), (char*)s_ex->ip_address_str, sizeof(s_ex->ip_address_str));
            break;
            
        default:
            strncpy((char*)s_ex->ip_address_str, "Unknown AF", sizeof(s_ex->ip_address_str));
            return NULL;
    }
    
    return (char*)s_ex->ip_address_str;
}

struct sockaddr_ex* get_local_net(const char* dev_name, int dev_name_len)
{
    struct sockaddr_ex* sock_ex = NULL;
    
    struct ifaddrs* addrs = 0;
    struct ifaddrs* head = 0;
    getifaddrs(&head);
    addrs = head;
    
    while(addrs) {
        //1, for ipv4, ignore the linklocal ip 169.254.0.0/16
        //2, for ipv6, ignore the linklocal ip fe80::...
        //3, only care about the indicated device, ignore other devices
        if (    (   (addrs->ifa_addr->sa_family == AF_INET && 0 == IN_LINKLOCAL(ntohl(((struct sockaddr_in *)addrs->ifa_addr)->sin_addr.s_addr)))
                 || (addrs->ifa_addr->sa_family == AF_INET6 && 0 == IN6_IS_ADDR_LINKLOCAL(&(((struct sockaddr_in6 *)addrs->ifa_addr)->sin6_addr))))
            &&  (strncmp(dev_name, addrs->ifa_name, dev_name_len) == 0)){
            
            // for ipv6 will get two ipv6 addresses, one of them is temporary ipv6 address
            // but seems we don't have any function to get the whether it's temporary on ios. so we just choose the first one.
            // I have tried that we can use each one of them to connect outside.
            // reference this link
            // http://stackoverflow.com/questions/17833765/detect-temporary-ipv6-address-crossplatform
            if (NULL == sock_ex){
                sock_ex = (struct sockaddr_ex*)malloc(sizeof(struct sockaddr_ex));
                assert(NULL != sock_ex);
                memset(sock_ex, 0, sizeof(struct sockaddr_ex));
                sock_ex->sockaddr_len = addrs->ifa_addr->sa_family == AF_INET6 ? sizeof(struct sockaddr_in6) : sizeof(struct sockaddr_in);
                memcpy(&sock_ex->sockaddr_info, addrs->ifa_addr, sock_ex->sockaddr_len);
                ipv4v6_inet_ntop(sock_ex);
            
                printf("%s first found indicated device-->ifa_name:%s, sa_family:%d, addr->%s.\n", __func__, addrs->ifa_name, sock_ex->sockaddr_info.ss_family, sock_ex->ip_address_str);

            }
            else{
                //others only printf
                struct sockaddr_ex temp;
                memset(&temp, 0, sizeof(struct sockaddr_ex));
                temp.sockaddr_len = addrs->ifa_addr->sa_family == AF_INET6 ? sizeof(struct sockaddr_in6) : sizeof(struct sockaddr_in);
                memcpy(&temp.sockaddr_info, addrs->ifa_addr, temp.sockaddr_len);
                ipv4v6_inet_ntop(&temp);
                
                printf("%s ifa_name:%s, sa_family:%d, addr->%s.\n", __func__, addrs->ifa_name, temp.sockaddr_info.ss_family, temp.ip_address_str);

            }
            
            //printf("%s ifa_name:%s, ifa_family:%d, ifa_flags:%u, addr->%s. \n", __func__, addrs->ifa_name, \
                   addrs->ifa_addr->sa_family, addrs->ifa_flags, \
                   inet_ntop_ipv4_ipv6_compatible(addrs->ifa_addr, p_addr, sizeof(p_addr)));
        }
        addrs = addrs->ifa_next;
    }
    freeifaddrs(head);
    
    return sock_ex;
}
struct sockaddr_ex* get_ipv4_sockaddr_ex(int local_ss_family, int socktype, const char* ipv4)
{
    assert(NULL != ipv4);
    
    if (local_ss_family != AF_INET && local_ss_family != AF_INET6){
        return NULL;
    }
    
    struct sockaddr_ex* sock_ex = (struct sockaddr_ex*)malloc(sizeof(struct sockaddr_ex));
    assert(NULL != sock_ex);
    memset(sock_ex, 0, sizeof(struct sockaddr_ex));

    struct addrinfo hints, *res, *res0;

    if (local_ss_family == AF_INET6){
        sock_ex->sockaddr_len = sizeof(struct sockaddr_in6);
        
        //convert target ipv4 to ipv6
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = PF_UNSPEC;
        hints.ai_socktype = socktype;
        hints.ai_flags = (AI_V4MAPPED_CFG | AI_ADDRCONFIG);

    }else
    {
        sock_ex->sockaddr_len = sizeof(struct sockaddr_in);
        
        //ipv4 parameters
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = PF_INET;
        hints.ai_socktype = socktype;
        //hints.ai_flags = AI_DEFAULT;

    }
    
    int error = getaddrinfo(ipv4, NULL, &hints, &res0);
    if (error){
        printf("getaddrinfo failed, %s.\n", gai_strerror(error));
        /*NOTREACHED*/
        free_sockaddr_ex(sock_ex);
        return NULL;

    }
    assert(NULL == res0->ai_next);

    res = res0;
    sock_ex->ai_socktype = res->ai_socktype;
    sock_ex->ai_protocol = res->ai_protocol;
    memcpy(&sock_ex->sockaddr_info, res->ai_addr, sock_ex->sockaddr_len);
    ipv4v6_inet_ntop(sock_ex);
    
    freeaddrinfo(res0);
    
    return sock_ex;
}

void free_sockaddr_ex(struct sockaddr_ex* sock_ex)
{
    free(sock_ex);
}

int format_port_to_sockaddr_ex(struct sockaddr_ex* sock_ex, unsigned short port)
{
    if (sock_ex->sockaddr_info.ss_family == AF_INET)
    {
        struct sockaddr_in * sockaddr_v4 = (struct sockaddr_in *)&(sock_ex->sockaddr_info);
        sockaddr_v4->sin_port = htons(port);

    }
    else if (sock_ex->sockaddr_info.ss_family == AF_INET6)
    {
        //NOTE!!! getaddrinfo can not specified port(such as "80") as the second parameter service_name, only service_name from /etc/services accept.
        //Envrionment: iOS 9 and Mac OS X 10.11
        //This is a bug impacting iOS 9 and Mac OS X 10.11. It has been fixed in iOS 10 and macOS 10.12 (as of beta 1), here is the reference link:
        //http://stackoverflow.com/questions/37386161/service-port-is-missed-when-using-getaddrinfo-to-convert-ipv4-addr-to-ipv6-addr
        
        struct sockaddr_in6 * sockaddr_v6 = (struct sockaddr_in6 *)&(sock_ex->sockaddr_info);
        // START WORKAROUND
        if (sockaddr_v6->sin6_port == 0)
        {
            sockaddr_v6->sin6_port = htons(port);
        }
        // END WORKAROUND

    }
    else
    {
        //unknown
        return -1;
    }
    sock_ex->port = port;
    return 0;
}

int test_tcp_connect_to_ipv4(const struct sockaddr_ex* local_addr, const char* peer_ipv4, unsigned short port)
{
    int ret = 0;
    
    struct sockaddr_ex* peer_addr = get_ipv4_sockaddr_ex(local_addr->sockaddr_info.ss_family, SOCK_STREAM, peer_ipv4);
    assert(NULL != peer_addr);
    format_port_to_sockaddr_ex(peer_addr, port);

    int s = socket(peer_addr->sockaddr_info.ss_family, peer_addr->ai_socktype, peer_addr->ai_protocol);
    assert (s >= 0);
    
    ret = bind(s, (struct sockaddr*)&(local_addr->sockaddr_info), local_addr->sockaddr_len);
    if (ret != 0){
        printf("bind failed, return %d errno %d.\n", ret, errno);
        close(s);
        free_sockaddr_ex(peer_addr);
        return ret;
    }
    
    char p_addr[INET6_ADDRSTRLEN] = {0};    //could also compatible for ipv4
    printf("%s try to connect family->%d, addr->%s.\n", __func__, \
           peer_addr->sockaddr_info.ss_family, peer_addr->ip_address_str);
    
    if (connect(s, (struct sockaddr*)&(peer_addr->sockaddr_info), peer_addr->sockaddr_len) < 0) {
        printf("connect failed, errno %d.\n", errno);
        close(s);
        free_sockaddr_ex(peer_addr);
        return ret;
    }
    
    close(s);
    free_sockaddr_ex(peer_addr);
    return ret;
}


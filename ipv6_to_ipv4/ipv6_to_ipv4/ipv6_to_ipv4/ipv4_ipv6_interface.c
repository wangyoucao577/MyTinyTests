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

#ifndef __APPLE__
#define IN_LINKLOCALNETNUM	(u_int32_t)0xA9FE0000 /* 169.254.0.0 */
#define IN_LINKLOCAL(i)		(((u_int32_t)(i) & IN_CLASSB_NET) == IN_LINKLOCALNETNUM)
#endif

char * inet_ntop_ipv4_ipv6_compatible(const struct sockaddr *sa, char *s, unsigned int maxlen)
{
    memset(s, 0, maxlen);
    switch(sa->sa_family) {
        case AF_INET:
            inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr), s, maxlen);
            break;
            
        case AF_INET6:
            inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr), s, maxlen);
            break;
            
        default:
            strncpy(s, "Unknown AF", maxlen);
            return NULL;
    }
    
    return s;
}

int ip_str_family(char* ipstr)
{
    struct sockaddr_storage temp_sockaddr;
    memset(&temp_sockaddr, 0, sizeof(struct sockaddr_storage));

    int ret = inet_pton(AF_INET6, ipstr, &temp_sockaddr);
    if (1 == ret) { //succeed
        return AF_INET6;
    }

    ret = inet_pton(AF_INET, ipstr, &temp_sockaddr);
    if (1 == ret) { //succeed
        return AF_INET;
    }
    return -1;
}

#ifndef WIN32

char* get_local_net(const char* dev_name, int dev_name_len)
{
    if (NULL == dev_name){
        printf("\n\nget_local_net printf all ipv4 and ipv6 here, ignore LINKLOCAL\n");
    }
    char* ipstr = NULL;

    struct ifaddrs* addrs = 0;
    struct ifaddrs* head = 0;
    getifaddrs(&head);
    addrs = head;
    
    while(addrs) {
        //1, for ipv4, ignore the linklocal ip 169.254.0.0/16
        //2, for ipv6, ignore the linklocal ip fe80::...
        //3, only care about the indicated device, ignore other devices
        if (NULL == dev_name || (strncmp(dev_name, addrs->ifa_name, dev_name_len) == 0))
        {
            if (    (addrs->ifa_addr->sa_family == AF_INET && 0 == IN_LINKLOCAL(ntohl(((struct sockaddr_in *)addrs->ifa_addr)->sin_addr.s_addr)))
                 || (addrs->ifa_addr->sa_family == AF_INET6 && 0 == IN6_IS_ADDR_LINKLOCAL(&(((struct sockaddr_in6 *)addrs->ifa_addr)->sin6_addr)))){
                
                // for ipv6 will get two ipv6 addresses, one of them is temporary ipv6 address
                // but seems we don't have any function to get the whether it's temporary on ios. so we just choose the first one.
                // I have tried that we can use each one of them to connect outside.
                // reference this link
                // http://stackoverflow.com/questions/17833765/detect-temporary-ipv6-address-crossplatform

                int ipstr_len = addrs->ifa_addr->sa_family == AF_INET6 ? INET6_ADDRSTRLEN : INET_ADDRSTRLEN;
                if (NULL != dev_name && NULL == ipstr){
                    ipstr = (char*)malloc(ipstr_len);
                    assert(NULL != ipstr);
                    char* pstr = inet_ntop_ipv4_ipv6_compatible(addrs->ifa_addr, ipstr, ipstr_len);
                    assert(NULL != pstr);
                
                    printf("%s dev_name:%s, first found indicated device-->ifa_name:%s, sa_family:%d(%s), addr->%s.\n", __func__, dev_name, \
                        addrs->ifa_name, addrs->ifa_addr->sa_family, \
                        addrs->ifa_addr->sa_family == AF_INET6 ? "AF_INET6" : "AF_INET", ipstr);
                }
                else{
                    //others only printf
                    char * temp_ipstr = (char*)malloc(ipstr_len);
                    assert(NULL != temp_ipstr);
                    char* pstr = inet_ntop_ipv4_ipv6_compatible(addrs->ifa_addr, temp_ipstr, ipstr_len);
                    assert(NULL != pstr);

                    printf("%s ifa_name:%s, sa_family:%d(%s), addr->%s.\n", __func__, addrs->ifa_name, addrs->ifa_addr->sa_family, \
                        addrs->ifa_addr->sa_family == AF_INET6 ? "AF_INET6" : "AF_INET", temp_ipstr);
                    free(temp_ipstr);
                }
                
                //printf("%s ifa_name:%s, ifa_family:%d, ifa_flags:%u, addr->%s. \n", __func__, addrs->ifa_name, \
                       addrs->ifa_addr->sa_family, addrs->ifa_flags, \
                       inet_ntop_ipv4_ipv6_compatible(addrs->ifa_addr, p_addr, sizeof(p_addr)));
            }
        }
        addrs = addrs->ifa_next;
    }
    freeifaddrs(head);
    
    if (NULL == dev_name){
        printf("\n\n");
    }
    return ipstr;
}

#endif


int easy_getaddrinfo(int ss_family, int sock_type, const char* ip, unsigned short port, struct addrinfo** output_res)
{
    struct addrinfo hints;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = ss_family;
    hints.ai_socktype = sock_type;
    
    if (ss_family == AF_INET6 || ss_family == AF_UNSPEC){
        //ipv4 mapped to ipv6, or maybe original ipv6
        hints.ai_flags = AI_ADDRCONFIG | AI_V4MAPPED;
    }
    
    static const char* kDefaultServiceName = "80";
    char* service_name = NULL;
    if (NULL == ip){
        hints.ai_flags |= AI_PASSIVE;   //automatically fill in the ip to INADDR_ANY or IN6ADDR_ANY_INIT
        service_name = (char*)kDefaultServiceName;
        assert(0 != port);
    }
    
    //getaddrinfo, at least one of ip and service_name should be set
    int error = getaddrinfo(ip, service_name, &hints, output_res);
    if (0 != error){
        printf("getaddrinfo failed, error code:%d, msg:%s.\n", error, gai_strerror(error));
        return error;
    }
    
    //set port
    if (0 != port){
        if (ss_family == AF_INET6){
            //NOTE!!! getaddrinfo can not specified port(such as "80") as the second parameter service_name, only service_name from /etc/services accept.
            //Envrionment: iOS 9 and Mac OS X 10.11
            //This is a bug impacting iOS 9 and Mac OS X 10.11. It has been fixed in iOS 10 and macOS 10.12 (as of beta 1), here is the reference link:
            //http://stackoverflow.com/questions/37386161/service-port-is-missed-when-using-getaddrinfo-to-convert-ipv4-addr-to-ipv6-addr
            
            struct sockaddr_in6 * sockaddr_v6 = (struct sockaddr_in6 *)((*output_res)->ai_addr);
            sockaddr_v6->sin6_port = htons(port);
        }else{
            struct sockaddr_in * sockaddr_v4 = (struct sockaddr_in *)((*output_res)->ai_addr);
            sockaddr_v4->sin_port = htons(port);
        }
    }
    
    return 0;
}

void getaddrinfo_behavior_individual_case(const char* case_str, int ss_family, const char* ip, unsigned short port)
{
    int err = 0;
    char* p_str = NULL;
    struct addrinfo *res0;
    char ipstr[INET6_ADDRSTRLEN] = {0};

    
    err = easy_getaddrinfo(ss_family, SOCK_STREAM, ip, port, &res0);
    assert(0 == err);
    assert(NULL == res0->ai_next);  //I want only one result.
    memset(ipstr, 0, sizeof(ipstr));
    p_str = inet_ntop_ipv4_ipv6_compatible(res0->ai_addr, ipstr, sizeof(ipstr));
    assert(NULL != p_str);
    printf("{%s} %s %s ip->%s port->%d addr_len->%d.\n", case_str, res0->ai_family == AF_INET6 ? "AF_INET6" : "AF_INET", \
           res0->ai_socktype == SOCK_STREAM ? "SOCK_STREAM" : "SOCK_DGRAM", \
           ipstr, (int)ntohs(((struct sockaddr_in*)res0->ai_addr)->sin_port), res0->ai_addrlen);
           
    assert(res0->ai_family == ss_family || ss_family == AF_UNSPEC);
    assert(ntohs(((struct sockaddr_in*)res0->ai_addr)->sin_port) == port);
    if (res0->ai_family == AF_INET6){
        assert(res0->ai_addrlen == sizeof(struct sockaddr_in6));
    }else{
        assert(res0->ai_addrlen == sizeof(struct sockaddr_in));
    }
           
    freeaddrinfo(res0);
    res0 = NULL;

}

void getaddrinfo_behavior_test()
{
    const char* IPV4 = "114.114.114.114";
    const char* IPV6 = "2001:2::aab1:1c2d:6fd3:a33b:499b";
    
    //only ipv4
    getaddrinfo_behavior_individual_case("case1 client: ipv4 for local bind, ignore port", AF_INET, IPV4, 0);
    getaddrinfo_behavior_individual_case("case2 client: ipv4 for remote connect, local also ipv4", AF_INET, IPV4, 80);
    getaddrinfo_behavior_individual_case("case3 server: ipv4 for local bind and listening, ignore ip address", AF_INET, NULL, 80);

    //decide by system
    getaddrinfo_behavior_individual_case("case4 client: ipv4 for remote connect, local depends on system, may ipv4 or ipv6", AF_UNSPEC, IPV4, 80);

    //use ipv6
    getaddrinfo_behavior_individual_case("case5 client: ipv6 for local bind. ignore port", AF_INET6, IPV6, 0);
    getaddrinfo_behavior_individual_case("case6 client: ipv4 for remote connect, local ipv6", AF_INET6, IPV4, 80);
    getaddrinfo_behavior_individual_case("case7 client: ipv6 for remote connect, local also ipv6", AF_INET6, IPV6, 80);
    getaddrinfo_behavior_individual_case("case8 server: ipv6 for local bind and listening, ignore ip address", AF_INET6, NULL, 80);

}

int test_tcp_connect_to_ipv4_via_easy_getaddrinfo(int local_ss_family, char* local_ip_str, const char* peer_ipv4, unsigned short port)
{
    int err = 0;
    char* p_str = NULL;
    struct addrinfo *resLocal, *resPeer;
    char local_ipstr[INET6_ADDRSTRLEN] = {0};
    char peer_ipstr[INET6_ADDRSTRLEN] = {0};
    
    //get local
    err = easy_getaddrinfo(local_ss_family, SOCK_STREAM, local_ip_str, 0, &resLocal);
    assert(0 == err);
    assert(NULL == resLocal->ai_next);  //I want only one result.
    p_str = inet_ntop_ipv4_ipv6_compatible(resLocal->ai_addr, local_ipstr, sizeof(local_ipstr));
    assert(NULL != p_str);
    printf("{%s} %s %s ip->%s port->%d addr_len->%d.\n", "local", resLocal->ai_family == AF_INET6 ? "AF_INET6" : "AF_INET", \
           resLocal->ai_socktype == SOCK_STREAM ? "SOCK_STREAM" : "SOCK_DGRAM", \
           local_ipstr, (int)ntohs(((struct sockaddr_in*)resLocal->ai_addr)->sin_port), resLocal->ai_addrlen);
    
    //get peer
    err = easy_getaddrinfo(local_ss_family, SOCK_STREAM, peer_ipv4, port, &resPeer);
    assert(0 == err);
    assert(NULL == resPeer->ai_next);  //I want only one result.
    p_str = inet_ntop_ipv4_ipv6_compatible(resPeer->ai_addr, peer_ipstr, sizeof(peer_ipstr));
    assert(NULL != peer_ipstr);
    printf("{%s} %s %s ip->%s port->%d addr_len->%d.\n", "peer", resPeer->ai_family == AF_INET6 ? "AF_INET6" : "AF_INET", \
           resPeer->ai_socktype == SOCK_STREAM ? "SOCK_STREAM" : "SOCK_DGRAM", \
           peer_ipstr, (int)ntohs(((struct sockaddr_in*)resPeer->ai_addr)->sin_port), resPeer->ai_addrlen);

    
    
    int s = socket(resLocal->ai_family, resLocal->ai_socktype, resLocal->ai_protocol);
    assert (s >= 0);
    
    int ret = bind(s, resLocal->ai_addr, resLocal->ai_addrlen);
    if (ret != 0){
        printf("bind failed, return %d errno %d.\n", ret, errno);
        goto End;
    }
    
    if (connect(s, resPeer->ai_addr, resPeer->ai_addrlen) < 0) {
        printf("connect failed, errno %d.\n", errno);
        ret = -1;
        goto End;
    }
    printf("local %s %d try connect peer %s(%s) %d succeed.\n", local_ipstr, (int)ntohs(((struct sockaddr_in*)resLocal->ai_addr)->sin_port), \
           peer_ipv4, peer_ipstr, (int)ntohs(((struct sockaddr_in*)resPeer->ai_addr)->sin_port));
    
End:
    close(s);
    freeaddrinfo(resLocal);
    freeaddrinfo(resPeer);
    return ret;
}

void exported_test()
{

    getaddrinfo_behavior_test();
    
    static const char *PublicIpv4 = "115.239.211.112";  //change to your own Public IP address. here is the ip from baidu.com
    static const unsigned short PublicServicePort = 80; //Your Listening port
    static const char *WifiName = "en0" ;
    static const char *CellularName ="pdp_ip0";

#ifndef WIN32
    //print all ipv4 and ipv6 interface and addressed, ignore LINKLOCAL
    get_local_net(NULL, 0);


    char* ipstr = get_local_net(WifiName, (int)strlen(WifiName));
    if (NULL != ipstr) {
        int ipstr_family = ip_str_family(ipstr);
        assert(ipstr_family == AF_INET || ipstr_family == AF_INET6);
        test_tcp_connect_to_ipv4_via_easy_getaddrinfo(ipstr_family, ipstr, PublicIpv4, PublicServicePort);
        free(ipstr);
    }

    ipstr = get_local_net(CellularName, (int)strlen(CellularName));
    if (NULL != ipstr) {
        int ipstr_family = ip_str_family(ipstr);
        assert(ipstr_family == AF_INET || ipstr_family == AF_INET6);
        test_tcp_connect_to_ipv4_via_easy_getaddrinfo(ipstr_family, ipstr, PublicIpv4, PublicServicePort);
        free(ipstr);
    }
#else
    //TODO: ipv6 connect test on windows
#endif


}


#ifndef __APPLE__
int main()
{
#ifdef WIN32
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
        printf("Error at WSAStartup()\n");
#endif

    exported_test();


#ifdef WIN32
    WSACleanup();

    //wait before return
    printf("Please press any key to continue...");
    char a;
    scanf_s("%c", &a, (int)sizeof(a));
#endif
    return 0;
}

#endif

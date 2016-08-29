//
//  ViewController.m
//  ipv6_to_ipv4
//
//  Created by wangyoucao577 on 8/25/16.
//  Copyright © 2016 wangyoucao577. All rights reserved.
//

#import "ViewController.h"
#include "ipv4_ipv6_interface.h"

static const char *PublicIpv4 = "114.114.114.114";  //change to your own Public IP address
static const unsigned short PublicServicePort = 80; //Your Listening port

static const char *WifiName = "en0" ;
static const char *CellularName ="pdp_ip0";
static struct sockaddr_storage wifi_sockaddr;
static struct sockaddr_storage cellular_sockaddr;
static int cellularOpened = 0;
static int wifiOpened = 0;

//Convert a struct sockaddr address to a string, IPv4 and IPv6:
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

void refresh_local_net()
{
    struct ifaddrs* addrs = 0;
    struct ifaddrs* head = 0;
    getifaddrs(&head);
    addrs = head;
    
    while(addrs) {
        //1, for ipv4, ignore the linklocal ip 169.254.0.0/16
        //2, for ipv6, ignore the linklocal ip fe80::...
        //3, only care about wifi(en0) and 4G(pdp_ip0), ignore other devices
        if (    (   (addrs->ifa_addr->sa_family == AF_INET && 0 == IN_LINKLOCAL(ntohl(((struct sockaddr_in *)addrs->ifa_addr)->sin_addr.s_addr)))
                 || (addrs->ifa_addr->sa_family == AF_INET6 && 0 == IN6_IS_ADDR_LINKLOCAL(&(((struct sockaddr_in6 *)addrs->ifa_addr)->sin6_addr))))
            &&  (strncmp(CellularName, addrs->ifa_name, 7) == 0 || strncmp(WifiName, addrs->ifa_name, 3) == 0)){
            
            char p_addr[INET6_ADDRSTRLEN] = {0};    //could also compatible for ipv4
            printf("%s ifa_name:%s, ifa_family:%d, ifa_flags:%u, addr->%s. \n", __func__, addrs->ifa_name, \
                   addrs->ifa_addr->sa_family, addrs->ifa_flags, \
                   inet_ntop_ipv4_ipv6_compatible(addrs->ifa_addr, p_addr, sizeof(p_addr)));
            
            if (strncmp(CellularName, addrs->ifa_name, 7) == 0) {
                memcpy(&cellular_sockaddr, addrs->ifa_addr, addrs->ifa_addr->sa_family == AF_INET6 ? sizeof(struct sockaddr_in6) : sizeof(struct sockaddr_in));
                cellularOpened = 1;
            } else if(strncmp(WifiName, addrs->ifa_name, 3) == 0) {
                //for ipv6, we could get two addresses, both are usable
                memcpy(&wifi_sockaddr, addrs->ifa_addr, addrs->ifa_addr->sa_family == AF_INET6 ? sizeof(struct sockaddr_in6) : sizeof(struct sockaddr_in));
                wifiOpened = 1;
            }
        }
        addrs = addrs->ifa_next;
    }
    freeifaddrs(head);
}

void tcp_connect_ipv4(struct sockaddr_storage* local_addr, char* target_ipv4, unsigned short target_port)
{
    assert(NULL != local_addr && NULL != target_ipv4);
    int error, s;
    struct addrinfo hints, *res, *res0;
    socklen_t struct_sockaddr_size;


    if (local_addr->ss_family == AF_INET6){
//        struct sockaddr_in6* sock_v6 = (struct sockaddr_in6*) local_addr;
//        sock_v6->sin6_port = htons(INADDR_ANY);
        struct_sockaddr_size = sizeof(struct sockaddr_in6);

        
        //convert target ipv4 to ipv6
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = PF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_DEFAULT;

    }
    else
    {
//        struct sockaddr_in* sock_v4 = (struct sockaddr_in*) local_addr;
//        sock_v4->sin_port = htons(INADDR_ANY);
        struct_sockaddr_size = sizeof(struct sockaddr_in);

        
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = PF_INET;
        hints.ai_socktype = SOCK_STREAM;
        //hints.ai_flags = AI_DEFAULT;

    }
    error = getaddrinfo(target_ipv4, NULL, &hints, &res0);
    if (error) {
        errx(1, "%s", gai_strerror(error));
        /*NOTREACHED*/
    }
    assert(NULL == res0->ai_next);
    res = res0;
    
    if (res->ai_family == AF_INET6)
    {
        //NOTE!!! getaddrinfo can not specified port(such as "80") as the second parameter service_name, only service_name from /etc/services accept.
        //Envrionment: iOS 9 and Mac OS X 10.11
        //This is a bug impacting iOS 9 and Mac OS X 10.11. It has been fixed in iOS 10 and macOS 10.12 (as of beta 1), here is the reference link:
        //http://stackoverflow.com/questions/37386161/service-port-is-missed-when-using-getaddrinfo-to-convert-ipv4-addr-to-ipv6-addr
        
        struct sockaddr_in6 * sockaddr_v6 = (struct sockaddr_in6 *)res->ai_addr;
        // START WORKAROUND
        if (sockaddr_v6->sin6_port == 0)
        {
            sockaddr_v6->sin6_port = htons(target_port);
        }
        // END WORKAROUND
    }else
    {
        struct sockaddr_in * sockaddr_v4 = (struct sockaddr_in *)res->ai_addr;
        sockaddr_v4->sin_port = htons(target_port);

    }

    s = socket(res->ai_family, res->ai_socktype,
               res->ai_protocol);
    assert (s >= 0);
    
    error = bind(s, (const struct sockaddr*)local_addr, struct_sockaddr_size);
    if (error != 0){
        printf("bind failed, return %d errno %d.\n", error, errno);
    }
    
    char p_addr[INET6_ADDRSTRLEN] = {0};    //could also compatible for ipv4
    printf("%s try to connect family->%d, addr->%s.\n", __func__, \
           res->ai_addr->sa_family, \
           inet_ntop_ipv4_ipv6_compatible(res->ai_addr, p_addr, sizeof(p_addr)));
    
    if (connect(s, res->ai_addr, res->ai_addrlen) < 0) {
        printf("connect failed, errno %d.\n", errno);
        
    }
    close(s);

}


@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void) ipv6_to_ipv4_test {
    
    refresh_local_net();
    tcp_connect_ipv4(&wifi_sockaddr, PublicIpv4, PublicServicePort);
    tcp_connect_ipv4(&cellular_sockaddr, PublicIpv4, PublicServicePort);
    return;
    
    //uint8_t ipv4[4] = {192, 168, 1, 1};
    //    char ipv4_str_buf[INET_ADDRSTRLEN] = { 0 };
    //    const char *ipv4_str = inet_ntop(AF_INET, &ipv4, ipv4_str_buf, sizeof(ipv4_str_buf));
    const char *ipv4_str = PublicIpv4;

    struct addrinfo hints, *res, *res0;
    int error, s;
    const char *cause = NULL;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_DEFAULT;
    error = getaddrinfo(ipv4_str, NULL, &hints, &res0);
    if (error) {
        errx(1, "%s", gai_strerror(error));
        /*NOTREACHED*/
    }
    s = -1;
    for (res = res0; res; res = res->ai_next) {
        if (res->ai_family == AF_INET6)
        {
            //NOTE!!! getaddrinfo can not specified port(such as "80") as the second parameter service_name, only service_name from /etc/services accept.
            //Envrionment: iOS 9 and Mac OS X 10.11
            //This is a bug impacting iOS 9 and Mac OS X 10.11. It has been fixed in iOS 10 and macOS 10.12 (as of beta 1), here is the reference link:
            //http://stackoverflow.com/questions/37386161/service-port-is-missed-when-using-getaddrinfo-to-convert-ipv4-addr-to-ipv6-addr
            
            struct sockaddr_in6 * sockaddr_v6 = (struct sockaddr_in6 *)res->ai_addr;
            // START WORKAROUND
            if (sockaddr_v6->sin6_port == 0)
            {
                sockaddr_v6->sin6_port = htons(22002);
            }
            // END WORKAROUND
        }

        
        s = socket(res->ai_family, res->ai_socktype,
                   res->ai_protocol);
        if (s < 0) {
            cause = "socket";
            continue;
        }
        
        char p_addr[INET6_ADDRSTRLEN] = {0};    //could also compatible for ipv4
        printf("%s try to connect family->%d, addr->%s.\n", __func__, \
               res->ai_addr->sa_family, \
               inet_ntop_ipv4_ipv6_compatible(res->ai_addr, p_addr, sizeof(p_addr)));
        
        if (connect(s, res->ai_addr, res->ai_addrlen) < 0) {
            cause = "connect";
            close(s);
            s = -1;
            continue;
        }
        
        break;  /* okay we got one */
    }
    if (s < 0) {
        err(1, "%s", cause);
        /*NOTREACHED*/
    }
    freeaddrinfo(res0);

}
- (void) ipv6_to_ipv4_test_2 {
    struct sockaddr_ex * local_sock_ex = get_local_net(WifiName, strlen(WifiName));
    if (NULL != local_sock_ex){
        test_tcp_connect_to_ipv4(local_sock_ex, PublicIpv4, PublicServicePort);
        free_sockaddr_ex(local_sock_ex);
    }
    
    local_sock_ex = get_local_net(CellularName, strlen(CellularName));
    if (NULL != local_sock_ex){
        test_tcp_connect_to_ipv4(local_sock_ex, PublicIpv4, PublicServicePort);
        free_sockaddr_ex(local_sock_ex);
    }
}

- (IBAction)test_run:(id)sender {
    //[self ipv6_to_ipv4_test];
    [self ipv6_to_ipv4_test_2];
}

@end

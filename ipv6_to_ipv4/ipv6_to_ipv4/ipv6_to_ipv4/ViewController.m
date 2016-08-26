//
//  ViewController.m
//  ipv6_to_ipv4
//
//  Created by zhangj on 8/25/16.
//  Copyright © 2016 wangyoucao577. All rights reserved.
//

#import "ViewController.h"


#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>


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
    
    //uint8_t ipv4[4] = {192, 168, 16, 103};
    //    char ipv4_str_buf[INET_ADDRSTRLEN] = { 0 };
    //    const char *ipv4_str = inet_ntop(AF_INET, &ipv4, ipv4_str_buf, sizeof(ipv4_str_buf));
    const char *ipv4_str = "192.168.16.103";

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
- (IBAction)test_run:(id)sender {
    [self ipv6_to_ipv4_test];
}

@end

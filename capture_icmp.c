
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
//#include <netinet/udp.h>
#include <linux/udp.h>
#include <netdb.h>

typedef int SOCKET;

#define IS_VALID_SOCK(s) ((s) >= 0)

static char* get_type(unsigned int icmptype)
{
    static char* type[] = 
    {
        "Echo Reply",               /* 0 */
        "ICMP Type 1",              /* 1 */
        "ICMP Type 2",              /* 2 */
        "Destination Unreachable",  /* 3 */
        "Source Quench",            /* 4 */
        "Redirect",                 /* 5 */
        "ICMP Type 6",              /* 6 */
        "ICMP Type 7",              /* 7 */
        "Echo Request",             /* 8 */
        "Router Advertisement",     /* 9 */
        "Router Solicitation",      /* 10 */
        "Time Exceeded",            /* 11 */
        "Parameter Problem",        /* 12 */
        "Timestamp Request",        /* 13 */
        "Timestamp Reply",          /* 14 */
        "Information Request",      /* 15 */
        "information Reply",        /* 16 */
        "Address Mask Request",     /* 17 */
        "Address Mask Reply"        /* 18 */
    };
    
    if (icmptype < (sizeof(type) / sizeof(type[0])))
        return type[icmptype];
    return "UNKNOWN";
}

static void print_unreachable(struct icmp* icmp, char* ip_src)
{
    struct ip *ip;
    struct udphdr *udp;
    char laddr[15 + 1];
    static char *unreach[] = 
    {
        "Network unreachable",      /* 0 */
        "Host unreachable",         /* 1 */
        "Protocol unreachable",     /* 2 */
        "Port unreachable",         /* 3 */
        "Fragmentation needed, DF bit set", /* 4 */
        "Source route failed",      /* 5 */
        "Destination network unknown",      /* 6 */
        "Destination host unknown", /* 7 */
        "Source host isolated",     /* 8 */
        "Dest. network admin. prohibited",  /* 9 */
        "Dest. host admin. prohibited",     /* 10 */
        "Network unreachable for TOS",      /* 11 */
        "Host unreachable for TOS",         /* 12 */
        "Communication admin. prohibited",  /* 13 */
        "Host precedence violation",        /* 14 */
        "Precedence cutoff in effect"       /* 15 */
    };
    
    ip = (struct ip*)((char*)icmp + 8);
    udp = (struct udphdr*)((char*)ip + (ip->ip_hl << 2));
    strcpy(laddr, ip_src);
    printf("\t%s\n\tSrc: %s.%d, Dest: %s.%d\n", \
        icmp->icmp_code < (sizeof(unreach) / sizeof(unreach[0])) \
        ? unreach[icmp->icmp_code] : "Illegal code", \
        laddr, ntohs(udp->source), inet_ntoa(ip->ip_dst), ntohs(udp->dest));
}
void print_dg(char* dg, int len)
{
    struct ip *ip;
    struct icmp *icmp;
    struct hostent *hp;
    char *hname;
    int hl;
    char ip_src[16];
    //struct sockaddr_in src_addr;    
    //memset(&src_addr, 0, sizeof(struct sockaddr_in));
    
    static char *redirect_code[] = 
    {
        "netowrk", "host", 
        "type-of-service and network", 
        "type-of-service and host"
    };
    static char *timexceed_code[] =
    {
        "transit", "reassembly"
    };
    static char *param_code[] = 
    {
        "IP header bad", "Required option missing"
    };
    
    ip = (struct ip*)dg;
    if (ip->ip_v != 4){
        printf("IP datagram not version 4.\n");
        return;
    }
    hl = ip->ip_hl << 2; //IP header length in bytes
    
    //printf("ip->ip_src %d\n", ip->ip_src);
    inet_ntop(AF_INET, &ip->ip_src, ip_src, sizeof(ip_src));
    //printf("ip_src %s\n", ip_src);

    if (len < hl + ICMP_MINLEN){
        printf("short datagram (%d bytes) from %s.\n", len, ip_src);
        return;
    }
    // hp = gethostbyaddr((char*)&ip->ip_src, 4, AF_INET);
    // if (hp == NULL){
        // hname = "";
    // }
    // else {
        // hname = hp->h_name;
    // }
    icmp = (struct icmp*)(dg + hl); //ICMP packet
    printf("ICMP %s (icmp_type:%d) from %s\n", get_type(icmp->icmp_type), icmp->icmp_type, ip_src);

    if (icmp->icmp_type == ICMP_UNREACH){
        print_unreachable(icmp, ip_src);
    }
    else if (icmp->icmp_type == ICMP_REDIRECT){
        printf("\tRedirect for %s\n", icmp->icmp_code <= 3 \
            ? redirect_code[icmp->icmp_code] : "Illegal code");
    }
    else if (icmp->icmp_type == ICMP_TIMXCEED){
        printf("\tTTL == 0 during %s\n", icmp->icmp_code <= 1 \
            ? timexceed_code[icmp->icmp_code] : "Illegal code");
    }
    else if (icmp->icmp_type == ICMP_PARAMPROB){
        printf("\t%s\n", icmp->icmp_code <= 1 \
            ? param_code[icmp->icmp_code] : "Illegal code");
    }
}

int main(int argc, char* argv)
{
    SOCKET s;
    struct protoent *pp;
    int rc;
    char icmpdg[1024];
    
    pp = getprotobyname("icmp");
    if (pp == NULL){
        printf("getprotobyname failed, errno %d.\n", errno);
        exit(errno);
    }
    
    s = socket(AF_INET, SOCK_RAW, pp->p_proto);
    if (!IS_VALID_SOCK(s)){
        printf("socket RAW failed, errno %d.\n", errno);
        exit(errno);
    }
    
    for(;;)
    {
        rc = recvfrom(s, icmpdg, sizeof(icmpdg), 0, NULL, NULL);
        if (rc < 0){
            printf("recvfrom failed, errno %d.\n", errno);
            exit(errno);
        }
        //printf("(%d bytes)%s\n", rc, icmpdg);
        print_dg(icmpdg, rc);
    }
    
    return 0;
}
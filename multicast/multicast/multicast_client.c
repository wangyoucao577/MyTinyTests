
#ifdef WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>

#define LAST_ERR WSAGetLastError()
#define mc_close_socket(s) closesocket(s)
#define mc_sleep(ms)    Sleep(ms)

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

typedef int SOCKET;

#define LAST_ERR errno
#define mc_close_socket(s) close(s)
#define mc_sleep(ms)    usleep(ms*1000)

#endif

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
#ifdef WIN32
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
        printf("Error at WSAStartup()\n");
#endif

    //TODO: Your test code

    char peer_ip[46] = "239.100.108.151";
    unsigned short peer_port = 5001;
    int ttl = 255;

    struct sockaddr_in peer_addr;
    memset(&peer_addr, 0, sizeof(struct sockaddr_in));
    peer_addr.sin_family = AF_INET;
	peer_addr.sin_addr.s_addr = inet_addr(peer_ip);
	peer_addr.sin_port = htons(peer_port);

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

    //set ttl for unicast or multicast
    int ttl_optname = IP_TTL;
    if (IN_MULTICAST(ntohl(peer_addr.sin_addr.s_addr))) {
        ttl_optname = IP_MULTICAST_TTL;
    }
    setsockopt(sock, IPPROTO_IP, ttl_optname, &ttl, sizeof(ttl));

    char data[1316] = {0};
    while (1)
    {
        int sent_bytes = sendto(sock, data, sizeof(data), 0, (struct sockaddr *)&peer_addr, sizeof(struct sockaddr_in));
        if (sent_bytes != (int)sizeof(data))
		{
			// error occurs
			int code = LAST_ERR;
			printf("send failed, return %d, error code is %d!\n", sent_bytes, code);
		}
        printf("succeed send to %s:%d %d bytes.\n", peer_ip, peer_port, sent_bytes);
        mc_sleep(50);
    }

    mc_close_socket(sock);
#ifdef WIN32
    WSACleanup();

    //wait before return
    printf("Please press any key to continue...");
    char a;
    scanf_s("%c", &a, (int)sizeof(a));
#endif
    return 0;
}


/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */

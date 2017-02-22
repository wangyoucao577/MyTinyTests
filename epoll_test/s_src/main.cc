
#include "comm_include.h"
#include "EpollServer.h"
#include "TcpLister.h"

int main(){

#ifdef _MSC_VER
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
        cout << "Error at WSAStartup()\n" << endl;
#endif

    const int kMaxEvents = 1024;
    
    try {
        EpollServer test_epoll;
        TcpLister tcpLister(13502, "13502");
        tcpLister.Start();
        test_epoll.AddTcpLister(move(tcpLister));
        
        while (1) {
            struct epoll_event eevents[kMaxEvents]{ 0 };
            int ready_count = test_epoll.Wait(1000, eevents, kMaxEvents);
            if (0 == ready_count) {
                cout << "epoll wait timeout, try again." << endl;
                continue;
            }
            assert(ready_count > 0);

            for (int i = 0; i < ready_count; ++i)
            {
                cout << "epoll_wait waked up, event " << eevents[i].events
                    << ", socket_fd " << eevents[i].data.fd << endl;

                // ´¦Àíevents
                if (test_epoll.IsListener(eevents[i].data.fd)) {
                    
                    cout << "socket_fd " << eevents[i].data.fd << " try accept." << endl;
                    
                    // try accept
                    socket_fd_t cli_sock = test_epoll.Accept(eevents[i].data.fd);

                    //TODO: add to epoll
#if 0
                    int sent_len = send(cli_sock, "12345\n", 6, 0);
                    cout << "fd: " << cli_sock << " sent_len: " << sent_len << endl;
                    close_socket(cli_sock);
#endif

                    continue;
                }
                
                //TODO: may need try read or write
                
            }
        }
        
    }
    catch (const last_err_t& err){
        cout << "new EpollServer failed, errno " << err << endl;
    }


#ifdef _MSC_VER
    WSACleanup();
#endif

	ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}
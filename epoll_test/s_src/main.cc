
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
        TcpLister tcpLister(13502);
        test_epoll.AddTcpLister(tcpLister.Socket());
        
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
                    //TODO: try accept

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
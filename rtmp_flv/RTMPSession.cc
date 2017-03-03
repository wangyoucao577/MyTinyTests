
#include "RTMPSession.h"

RTMPSession::RTMPSession(std::string url) {
    rtmp_ = RTMP_Alloc();
    if (NULL == rtmp_) {
        throw kRTMPSessionErrnoAllocFailed;
    }

    RTMP_Init(rtmp_);
    rtmp_->Link.timeout = 10;

    if (!RTMP_SetupURL(rtmp_, (char*)(url.c_str()))) {
        throw kRTMPSessionErrnoSetupURLFailed;
    }
    rtmp_->Link.lFlags |= RTMP_LF_LIVE;
    RTMP_SetBufferMS(rtmp_, 3600 * 1000);  //1hour

}

RTMPSession::~RTMPSession() {
    if (rtmp_) {
        RTMP_Free(rtmp_);
        rtmp_ = nullptr;
    }
}

void RTMPSession::Connect() {
    if (!RTMP_Connect(rtmp_, NULL)) {
        throw kRTMPSessionErrnoConnectFailed;
    }

    if (!RTMP_ConnectStream(rtmp_, 0)) {
        Close();
        throw kRTMPSessionErrnoConnectFailed;
    }
}

void RTMPSession::Close() {
    return RTMP_Close(rtmp_);
}

int RTMPSession::Read(char* buff, int buff_len) {
    return RTMP_Read(rtmp_, buff, buff_len);
}

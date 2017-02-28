
#include "FlvCommon.h"

#include <sys/time.h>

using namespace std;

ostream & operator << (ostream& out, FlvException& e) {
    return out << "FlvExcepton ErrorCode: " << e.error_code() << ", Msg: " << e.msg();
}

int64_t FlvCommonUtils::GetCurrentTimeMillseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t us = (int64_t)tv.tv_sec * 1000000 + tv.tv_usec;
    return us;
}
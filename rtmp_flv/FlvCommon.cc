
#include "FlvCommon.h"

using namespace std;

ostream & operator << (ostream& out, FlvException& e) {
    return out << "FlvExcepton ErrorCode: " << e.error_code() << ", Msg: " << e.msg();
}
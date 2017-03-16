
#include "comm_include.h"

namespace CC11Comm {
    void CC11Printf(const char* s) {
        while (*s) {
            if (*s == '%' && *++s != '%') {
                //变长参数都用完了, 但还有格式化字符串在
                assert(false);
                throw runtime_error("invalid format string: missing arguments");
            }
            cout << *s++;
        }
    }
}

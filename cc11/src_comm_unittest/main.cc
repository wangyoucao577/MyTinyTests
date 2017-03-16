
#include "comm_include.h"

int main() {

    CC11Comm::CC11Printf("test1\n");
    CC11Comm::CC11Printf("test2 %a %% %a %a\n", 1, 10, string("bkjlfs"));

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}
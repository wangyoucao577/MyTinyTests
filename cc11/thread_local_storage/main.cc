
#include "comm_include.h"

static thread_local int err{ 0 };
struct ThreadErr {
    static thread_local int err;
};
thread_local int ThreadErr::err{ 0 };

void MaySetErr(int val) {

    cout << "Enter " << __func__ << " " << std::this_thread::get_id() << " err: " << err << ", ThreadErr::err_: " << ThreadErr::err << endl;
    if (val == 1) {
        err = 1;
        ThreadErr::err = 3;
    }
    else if (val == 2) {
        err = -1;
        ThreadErr::err = -3;
    }
    else {
        err = 0;
        ThreadErr::err = 5;
    }
    cout << "Exit " << __func__ << " " << std::this_thread::get_id() << " err: " << err << ", ThreadErr::err_: " << ThreadErr::err << endl;

}

int main() {
    // test codes

    cout << "Enter " << __func__ << " " << std::this_thread::get_id() << " err: " << err << ", ThreadErr::err_: " << ThreadErr::err << endl;

    thread t1(MaySetErr, 1);
    thread t2(MaySetErr, 2);
    t1.join();
    t2.join();

    cout << "Exit " << __func__ << " " << std::this_thread::get_id() << " err: " << err << ", ThreadErr::err_: " << ThreadErr::err << endl;

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}
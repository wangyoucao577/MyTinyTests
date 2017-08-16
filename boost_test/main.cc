
#include <string>
#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace std;

void posix_time_test(){

    boost::posix_time::ptime current_ptime = boost::posix_time::second_clock::local_time();
    string ptime_iso_str = boost::posix_time::to_iso_string(current_ptime);
    string ptime_simple_str = boost::posix_time::to_simple_string(current_ptime);

    cout << "iso second clock local time: " << ptime_iso_str << endl;
    cout << "simple second clock local time: " << ptime_simple_str << endl;

    boost::posix_time::ptime microsec_current_ptime = boost::posix_time::microsec_clock::local_time();
    cout << "iso microsec clock local time: " << boost::posix_time::to_iso_string(microsec_current_ptime) << endl;
    cout << "simple microsec clock local time: " << boost::posix_time::to_simple_string(microsec_current_ptime) << endl;

}

int main(){

    posix_time_test();

    return 0;
}



#include <iostream>
#include <chrono>

#include "my_shared_ptr.hpp"
#include "mock_classes.h"


template<typename AcceptT, typename SampleT>
void loop_pass_pointers(){
    my_shared_ptr<SampleT> ptr = MY_NAMESPACE::make_shared<SampleT>(SampleT());

    for (int i = 0; i < 10000000; ++i) {
        auto&& t = AcceptT(ptr);
    }
}

class SampleObject{};

int main() {
 
 
    auto start = std::chrono::system_clock::now();
    loop_pass_pointers<AcceptSharedPtr<SampleObject>, SampleObject>();
    auto time_point_1 = std::chrono::system_clock::now();
    loop_pass_pointers<AcceptConstReferenceSharedPtr<SampleObject>, SampleObject>();
    auto time_point_2 = std::chrono::system_clock::now();
    loop_pass_pointers<AcceptConstReferenceSharedPtrWithConstObject<SampleObject>, SampleObject>();
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds_1 = time_point_1 - start;
    std::chrono::duration<double> elapsed_seconds_2 = time_point_2 - time_point_1;
    std::chrono::duration<double> elapsed_seconds_3 = end - time_point_2;

    std::cout << elapsed_seconds_1.count() << " seconds, " 
    << elapsed_seconds_2.count() << " seconds, " 
    << elapsed_seconds_3.count() << " seconds." << std::endl;

    return 0;
}
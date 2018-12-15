
#include <iostream>
#include <chrono>

#include "my_shared_ptr.hpp"
#include "mock_classes.hpp"
#include "loop_pass_pointers.hpp"
#include "sample_object.h"

void test_case_pass_shared_ptr() {

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

    std::cout << __FUNCTION__ << " ---> " 
        << elapsed_seconds_1.count() << " seconds, " 
        << elapsed_seconds_2.count() << " seconds, " 
        << elapsed_seconds_3.count() << " seconds." << std::endl;

}

int main() {
 
    test_case_pass_shared_ptr();

    return 0;
}
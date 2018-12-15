
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

void test_case_access_value() {

    my_shared_ptr<SampleObject> ptr = MY_NAMESPACE::make_shared<SampleObject>();
    SampleObject* raw_ptr = ptr.get();

    constexpr int64_t kLoopCount = 10000000;

    auto start = std::chrono::system_clock::now();

    //modify value by raw pointer
    for (int64_t i = 0; i < kLoopCount; ++i) {
        raw_ptr->Increase();
        auto&& v = raw_ptr->value();
    }
    
    auto time_point_1 = std::chrono::system_clock::now();

    //modify value by shared-ptr
    for (int64_t i = 0; i < kLoopCount; ++i) {
        ptr->Increase();
        auto&& v = ptr->value();
    }

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds_1 = time_point_1 - start;
    std::chrono::duration<double> elapsed_seconds_2 = end - time_point_1;

    std::cout << __FUNCTION__ << " ---> " 
        << elapsed_seconds_1.count() << " seconds, " 
        << elapsed_seconds_2.count() << " seconds" << std::endl; 


}

int main() {
 
    test_case_pass_shared_ptr();
    test_case_access_value();

    return 0;
}
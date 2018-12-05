
#include <iostream>

#include "tbb/tbb.h"

using foo_func = void (*)(float& a);

void plus(float& a) {
    a += 1.0f;
}

void multiply(float& a) {
    a *= 1.8f;
}

void initialize(float& a) {
    a = 0.5f;
}

void print(float& a) {
    std::cout << " " << a;
}

void foo(float& a) {
    a = 1.0f;
}

void SerialApplyFoo(float a[], size_t n, foo_func foo) {
    for (size_t i = 0; i != n; ++i) {
        foo(a[i]);
    }
}

void ParallelApplyFoo(float a[], size_t n, foo_func foo) {

    tbb::parallel_for(tbb::blocked_range<size_t>(0, n), 
        [a, foo](const tbb::blocked_range<size_t>& r){
        for (size_t i = r.begin(); i != r.end(); ++i) {
            foo(a[i]);
        }
    });

    //NOTE: here's a much simpler way, but only valid for numbers
    // tbb::parallel_for(size_t(0), n, [a, foo](size_t i) {
    //     foo(a[i]);
    // });
}

void test_functional() {

    std::cout << "Enter " << __FUNCTION__ << std::endl;

    const int n = 10;
    float* a = (float*)malloc(n * sizeof(float));
    if (!a){
        std::cerr << "malloc failed, size " << n << std::endl;
        return;
    }

    SerialApplyFoo(a, n, initialize);
    SerialApplyFoo(a, n, plus);
    SerialApplyFoo(a, n, multiply);
    SerialApplyFoo(a, n, print);
    std::cout << std::endl;

    ParallelApplyFoo(a, n, initialize);
    ParallelApplyFoo(a, n, plus);
    ParallelApplyFoo(a, n, multiply);
    ParallelApplyFoo(a, n, print);
    std::cout << std::endl;

    free(a);

    std::cout << "Exit " << __FUNCTION__ << std::endl << std::endl;
}

void test_parallel() {

    std::cout << "Enter " << __FUNCTION__ << std::endl;

    const int n = 1000000000;
    float* a = (float*)malloc(n * sizeof(float));
    if (!a){
        std::cerr << "malloc failed, size " << n << std::endl;
        return;
    }

    std::cout << "parallel initialize..." << std::endl;
    ParallelApplyFoo(a, n, initialize);

    std::cout << "parallel plus..." << std::endl;
    ParallelApplyFoo(a, n, plus);

    std::cout << "parallel multiply..." << std::endl;
    ParallelApplyFoo(a, n, multiply);

    std::cout << "parallel done..." << std::endl;
    
    free(a);

    std::cout << "Exit " << __FUNCTION__ << std::endl << std::endl;
}

int main(int argc, char* argv[]) {

    test_functional();
    test_parallel();

    return 0;
}
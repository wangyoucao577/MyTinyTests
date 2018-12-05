
#include <iostream>

#include "tbb/tbb.h"

using foo_func = void (*)(float& a);

void plus1(float& a) {
    a += 1.0f;
}
void initialize(float& a) {
    a = 0.0f;
}
void print(float& a) {
    std::cout << " " << a << std::endl;
}

void SerialApplyFoo(float a[], size_t n, foo_func foo) {
    for (size_t i = 0; i != n; ++i) {
        foo(a[i]);
    }
}

void ParallelApplyFoo(float a[], size_t n, foo_func foo) {
    // tbb::parallel_for(tbb::blocked_range<size_t>(0, n), 
    //     [a, foo](const tbb::blocked_range<size_t>& r){
    //     for (size_t i = r.begin(); i != r.end(); ++i) {
    //         foo(a[i]);
    //     }
    // });

    tbb::parallel_for(size_t(0), n, [a, foo](size_t i) {
        foo(a[i]);
    });
}

int main(int argc, char* argv[]) {
    std::cout << "hello world!" << std::endl;

    const int n = 10;
    float* a = (float*)malloc(n * sizeof(float));
    if (!a){
        std::cerr << "malloc failed, size " << n << std::endl;
        return -1;
    }

    SerialApplyFoo(a, n, initialize);
    SerialApplyFoo(a, n, plus1);
    SerialApplyFoo(a, n, print);

    ParallelApplyFoo(a, n, initialize);
    ParallelApplyFoo(a, n, plus1);
    ParallelApplyFoo(a, n, print);

    free(a);
    return 0;
}

#include <iostream>

#include "tbb/tbb.h"
#include "tbb/parallel_for.h"

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

class ApplyFoo {
private:
    float * const a_;
    foo_func foo_;

public: 
    void operator() (const tbb::blocked_range<size_t>& r) const {
        float *a = a_;
        for (size_t i = r.begin(); i != r.end(); ++i) {
            foo_(a_[i]);
        }
    }
    ApplyFoo(float a[], foo_func f) : a_(a), foo_(f) {}
};

void ParallelApplyFoo(float a[], size_t n, foo_func foo) {
    tbb::parallel_for(tbb::blocked_range<size_t>(0, n), ApplyFoo(a, foo));
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
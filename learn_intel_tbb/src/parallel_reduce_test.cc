
#include <iostream>
#include <float.h>

#include "tbb/tbb.h"

float foo(float a) {
    return a * 2.5f;
}

float SerialSumFoo(float a[], size_t n) {
    float sum = 0;
    for(size_t i = 0; i < n; ++i) {
        sum += foo(a[i]);
    }
    return sum;
}

class SumFoo {
private:
    float* my_a;
public:
    float my_sum;
    void operator()(const tbb::blocked_range<size_t>& r) {
        float *a = my_a;
        float sum = my_sum;
        size_t end = r.end();
        for (size_t i = r.begin(); i != end; ++i) {
            sum += foo(a[i]);
        }
        my_sum = sum;
    }

    SumFoo(SumFoo& x, tbb::split) : my_a(x.my_a), my_sum(0) {}

    void join(const SumFoo& y) { my_sum += y.my_sum; }

    SumFoo(float a[]) : my_a(a), my_sum(0) {}
};

float ParallelSumFoo(float a[], size_t n) {
    SumFoo sf(a);
    parallel_reduce(tbb::blocked_range<size_t>(0, n), sf);
    return sf.my_sum;
}

class MinFoo {
    const float *const my_a;
public:
    float value_of_min;
    long index_of_min;

    void operator() (const tbb::blocked_range<size_t>& r) {
        const float* a = my_a;
        for (size_t i = r.begin(); i != r.end(); ++i){
            float value = foo(a[i]);
            if (value < value_of_min) {
                value_of_min = value;
                index_of_min = i;
            }
        }
    }

    MinFoo(MinFoo& x, tbb::split) : 
        my_a(x.my_a), value_of_min(FLT_MAX), index_of_min(-1) {}

    void join(const MinFoo& y) {
        if (y.value_of_min < value_of_min) {
            value_of_min = y.value_of_min;
            index_of_min = y.index_of_min;
        }
    }

    MinFoo(const float a[]) : 
        my_a(a), value_of_min(FLT_MAX), index_of_min(-1) {}
};

float ParallelFindMinFoo(float a[], size_t n) {
    MinFoo mf(a);
    parallel_reduce(tbb::blocked_range<size_t>(0, n), mf);
    return mf.value_of_min;
}


void test_functional() {

    std::cout << "Enter " << __FUNCTION__ << std::endl;

    const int n = 10;
    float* a = (float*)malloc(n * sizeof(float));
    if (!a){
        std::cerr << "malloc failed, size " << n << std::endl;
        return;
    }

    // initialize values
    for (size_t i = 0; i < n; ++i) {
        a[i] = 1.0f;
    }

    float s_sum = SerialSumFoo(a, n);
    float p_sum = ParallelSumFoo(a, n);

    std::cout << "sum by serial: " << s_sum << ", sum by parallel: " << p_sum << std::endl;

    free(a);

    std::cout << "Exit " << __FUNCTION__ << std::endl << std::endl;
}

void test_parallel_sum() {

    std::cout << "Enter " << __FUNCTION__ << std::endl;

    const int n = 1000000000;
    float* a = (float*)malloc(n * sizeof(float));
    if (!a){
        std::cerr << "malloc failed, size " << n << std::endl;
        return;
    }

    // initialize values
    std::cout << "parallel initialize..." << std::endl;
    tbb::parallel_for(tbb::blocked_range<size_t>(0, n), [a](const tbb::blocked_range<size_t>& r){
        for (size_t i = r.begin(); i != r.end(); ++i) {
            a[i] = 1.0f;
        }
    });

    std::cout << "parallel reduce..." << std::endl;
    float p_sum = ParallelSumFoo(a, n);

    std::cout << "parallel done..." << std::endl;

    std::cout << "sum by parallel: " << p_sum << std::endl;

    free(a);

    std::cout << "Exit " << __FUNCTION__ << std::endl << std::endl;
}

void test_parallel_find_min() {

    std::cout << "Enter " << __FUNCTION__ << std::endl;

    const int n = 1000000000;
    float* a = (float*)malloc(n * sizeof(float));
    if (!a){
        std::cerr << "malloc failed, size " << n << std::endl;
        return;
    }

    // initialize values
    std::cout << "parallel initialize..." << std::endl;
    tbb::parallel_for(tbb::blocked_range<size_t>(0, n), [a](const tbb::blocked_range<size_t>& r){
        for (size_t i = r.begin(); i != r.end(); ++i) {
            a[i] = 1.0f;
        }
    });

    std::cout << "parallel reduce..." << std::endl;
    float p_sum = ParallelFindMinFoo(a, n);

    std::cout << "parallel done..." << std::endl;

    std::cout << "min by parallel: " << p_sum << std::endl;

    free(a);

    std::cout << "Exit " << __FUNCTION__ << std::endl << std::endl;
}


int main(int argc, char* argv[]) {

    test_functional();
    test_parallel_sum();
    test_parallel_find_min();
    return 0;
}
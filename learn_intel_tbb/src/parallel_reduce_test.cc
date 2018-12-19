
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

float ParallelSumFoo(float a[], size_t n) {

    return parallel_reduce(tbb::blocked_range<size_t>(0, n), 
        float(0.f), 
        [a](const tbb::blocked_range<size_t>& r, const float& x) -> float {
            float sum = x;
            for (size_t i = r.begin(); i != r.end(); ++i) {
                sum += foo(a[i]);
            }
            
            return sum;
        }, 
        [](const float& x, const float& y) -> float{
            return x + y;
        });
}

float ParallelFindMinFoo(float a[], size_t n) {

    return parallel_reduce(tbb::blocked_range<size_t>(0, n), 
        float(FLT_MAX), 
        [a](const tbb::blocked_range<size_t>& r, const float& x) -> float {

            float min = x;
            for (size_t i = r.begin(); i != r.end(); ++i){
                float value = foo(a[i]);
                if (value < min) {
                    min = value;
                }
            }
            return min;
        }, 
        [](const float& x, const float& y) -> float{
            if (x < y) {
                return x;
            }
            return y;
        });
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
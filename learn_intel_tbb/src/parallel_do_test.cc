#include <iostream>
#include <vector>
#include <atomic>

#include "tbb/tbb.h"

float foo(float a) {
    return (a + 0.5f) * 2.5f;
}


int main(){

    std::vector<float> a;   //use random storage to enable parallel
    a.resize(100000000);

    std::atomic_uint32_t count {0}; // atomic is NECESSARY since it's parallel operation.

    tbb::parallel_do(a.begin(), a.end(), 
        [&count](float& item, tbb::parallel_do_feeder<float>& feeder){
            item = foo(item);

            uint32_t curr_count = count.fetch_add(1);
            if (curr_count % 10 == 0) {
                feeder.add(1.0f);
            }
    });
    
    std::cout << "a.size() = " << a.size()  << ", do count " << count.load() << std::endl;

    return 0;
}
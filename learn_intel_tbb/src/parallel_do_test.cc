#include <iostream>
#include <vector>
#include <list>
#include <atomic>
#include <typeinfo>

#include "tbb/tbb.h"

float foo(float a) {
    return (a + 0.5f) * 2.5f;
}

template<typename T>
void parallel_do_test(T a) {

    std::cout << "Enter " << __FUNCTION__ << ", container type: " << typeid(T).name() << std::endl;

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
    std::cout << "Exit " << __FUNCTION__ << ", container type: " << typeid(T).name() << std::endl;

}

int main(int argc, char* argv[]){

    if (argc >= 2 && 0 == strcmp(argv[1], "list")){
        std::list<float> b;     //try with non-random storage to enable parallel
        b.resize(100000000);
        parallel_do_test(b);

        return 0;
    }

    std::vector<float> a;   //use random storage to enable parallel
    a.resize(100000000);
    parallel_do_test(a);


    return 0;
}
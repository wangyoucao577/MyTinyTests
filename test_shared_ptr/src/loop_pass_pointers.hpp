
#ifndef TEST_SHARED_PTR_LOOP_PASS_POINTERS_HPP_
#define TEST_SHARED_PTR_LOOP_PASS_POINTERS_HPP_

template<typename AcceptT, typename SampleT>
void loop_pass_pointers(){
    my_shared_ptr<SampleT> ptr = MY_NAMESPACE::make_shared<SampleT>();

    constexpr int64_t kLoopCount = 10000000;
    for (int i = 0; i < kLoopCount; ++i) {
        auto&& t = AcceptT(ptr);
    }
}


#endif
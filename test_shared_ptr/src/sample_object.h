
#ifndef TEST_SHARED_PTR_SAMPLE_OBJECT_H__
#define TEST_SHARED_PTR_SAMPLE_OBJECT_H__

#include <stdint.h>

class SampleObject{
public:
    void Increase() { ++value_;}
    uint64_t value() const { return value_; }
private:
    uint64_t value_ {0};
};

#endif
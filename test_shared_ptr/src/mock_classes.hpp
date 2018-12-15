

#ifndef TEST_SHARED_PTR_MOCK_CLASSES_HPP_
#define TEST_SHARED_PTR_MOCK_CLASSES_HPP_

#include "my_shared_ptr.hpp"



template<typename T>
class AcceptSharedPtr{
public:
    AcceptSharedPtr(my_shared_ptr<T> sample_object)
    : sample_object_(sample_object){}

private:
    my_shared_ptr<T> sample_object_;
};

template<typename T>
class AcceptConstReferenceSharedPtr{
public:
    AcceptConstReferenceSharedPtr(const my_shared_ptr<T> & sample_object)
    : sample_object_(sample_object){}

private:
    my_shared_ptr<T> sample_object_;
};

template<typename T>
class AcceptConstReferenceSharedPtrWithConstObject{
public:
    AcceptConstReferenceSharedPtrWithConstObject(const my_shared_ptr<const T> & sample_object)
    : sample_object_(sample_object){}

private:
    my_shared_ptr<const T> sample_object_;
};

#endif

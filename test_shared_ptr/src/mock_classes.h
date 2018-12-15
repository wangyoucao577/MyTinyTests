
#include "my_shared_ptr.hpp"

class SampleObject{
};

class AcceptSharedPtr{
public:
    AcceptSharedPtr(my_shared_ptr<SampleObject> sample_object)
    : sample_object_(sample_object){}

private:
    my_shared_ptr<SampleObject> sample_object_;
};

class AcceptConstReferenceSharedPtr{
public:
    AcceptConstReferenceSharedPtr(const my_shared_ptr<SampleObject> & sample_object)
    : sample_object_(sample_object){}

private:
    my_shared_ptr<SampleObject> sample_object_;
};

class AcceptConstReferenceSharedPtrWithConstObject{
public:
    AcceptConstReferenceSharedPtrWithConstObject(const my_shared_ptr<const SampleObject> & sample_object)
    : sample_object_(sample_object){}

private:
    my_shared_ptr<const SampleObject> sample_object_;
};
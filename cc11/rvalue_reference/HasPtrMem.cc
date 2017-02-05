#include "HasPtrMem.h"

#include <iostream>
using namespace std;

int HasPtrMem::default_constructor_called_count_ = 0;
int HasPtrMem::copy_constructor_called_count_ = 0;
int HasPtrMem::move_constructor_called_count_ = 0;
int HasPtrMem::destructor_called_count_ = 0;

void HasPtrMem::ClearSum()
{
    default_constructor_called_count_ = 0;
    copy_constructor_called_count_ = 0;
    move_constructor_called_count_ = 0;
    destructor_called_count_ = 0;
}
HasPtrMem HasPtrMem::GetTemp()
{
    return HasPtrMem();
}

HasPtrMem::HasPtrMem() :
d_(new int(1))
{
    cout << "HasPtrMem Default Constructor Count " << ++default_constructor_called_count_ << endl;
}

HasPtrMem::HasPtrMem(const HasPtrMem& org) :
d_(new int(*org.d_))
{
    cout << "HasPtrMem Copy Constructor Count " << ++copy_constructor_called_count_ << endl;
}

#if defined(HAS_MOVE_CONSTRUCTOR)
HasPtrMem::HasPtrMem(HasPtrMem&& org) :
d_(org.d_)
{
    org.d_ = nullptr;

    cout << "HasPtrMem Move Constructor Count " << ++move_constructor_called_count_ << endl;
}
#endif
HasPtrMem::~HasPtrMem()
{
    delete d_;

    cout << "HasPtrMem Destructor Count " << ++destructor_called_count_ << endl;
}


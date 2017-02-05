#include "HasPtrMem.h"

#include <iostream>
using namespace std;

int HasPtrMem::default_constructor_called_count_ = 0;
int HasPtrMem::copy_constructor_called_count_ = 0;
int HasPtrMem::move_constructor_called_count_ = 0;
int HasPtrMem::destructor_called_count_ = 0;


HasPtrMem::HasPtrMem() :
d_(new int(1))
{
    cout << "Default Constructor Count " << ++default_constructor_called_count_ << endl;
}

HasPtrMem::HasPtrMem(const HasPtrMem& org) :
d_(new int(*org.d_))
{
    cout << "Copy Constructor Count " << ++copy_constructor_called_count_ << endl;
}

HasPtrMem::HasPtrMem(HasPtrMem&& org) :
d_(org.d_)
{
    org.d_ = nullptr;

    cout << "Move Constructor Count " << ++move_constructor_called_count_ << endl;
}

HasPtrMem::~HasPtrMem()
{
    delete d_;

    cout << "Destructor Count " << ++destructor_called_count_ << endl;
}


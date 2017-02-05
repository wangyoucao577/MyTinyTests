#include "HasPtrMem.h"



HasPtrMem::HasPtrMem() :
d_(new int(1))
{
}

HasPtrMem::HasPtrMem(HasPtrMem& org) :
d_(new int(*org.d_))
{

}

HasPtrMem::~HasPtrMem()
{
    delete d_;
}

#include "Moveable.h"
#include "HasPtrMem.h"
#include "comm_include.h"

Moveable::Moveable() : hasPtrMem_(), i_(new int(2))
{
    cout << "Moveable Default Constructor " << endl;
}

Moveable::Moveable(const Moveable& org) : i_(new int(*org.i_)), hasPtrMem_(org.hasPtrMem_)
{
    cout << "Moveable Copy Constructor " << endl;

}

#if defined(HAS_MOVE_CONSTRUCTOR)
Moveable::Moveable(Moveable&& org) : i_(org.i_), hasPtrMem_(move(org.hasPtrMem_))
{
    org.i_ = nullptr;

    cout << "Moveable Move Constructor " << endl;

}
#endif


Moveable::~Moveable()
{
    delete i_;

    cout << "Moveable Destructor " << endl;

}

Moveable Moveable::GetTemp()
{
    Moveable temp;
    cout << hex << "HasPtrMem.d_ address " << temp.hasPtrMem_.GetPtrAddress() << endl;
    return temp;
}
#include "Copyable.h"

#include <iostream>
using namespace std;


Copyable::Copyable()
{
}

Copyable::Copyable(const Copyable&)
{
    cout << "Copied." << endl;
}

#if defined(HAS_MOVE_CONSTRUCTOR)
Copyable::Copyable(Copyable&&)
{
    cout << "Moved." << endl;
}
#endif

Copyable::~Copyable()
{
}

Copyable Copyable::ReturnRValue()
{
    return Copyable();
}

void Copyable::AcceptLValue(Copyable)
{

}
void Copyable::AcceptLValueReference(const Copyable&)
{

}
void Copyable::AcceptRValueReference(Copyable&&)
{

}
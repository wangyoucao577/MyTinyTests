#pragma once

#include "HasPtrMem.h"

class Moveable
{
public:
    friend UnitTest;

public:
    Moveable();
    Moveable(const Moveable&);
#if defined(HAS_MOVE_CONSTRUCTOR)
    Moveable(Moveable&&);
#endif
    ~Moveable();

public:
    static Moveable GetTemp();

private:
    HasPtrMem hasPtrMem_;
    int * i_;
};


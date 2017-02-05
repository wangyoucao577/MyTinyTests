#pragma once

class UnitTest;

class HasPtrMem
{
public:
    friend UnitTest;

public:
    HasPtrMem();
    HasPtrMem(HasPtrMem&);
    ~HasPtrMem();

private:
    int * d_;
};


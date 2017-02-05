#pragma once

class UnitTest;

class HasPtrMem
{
public:
    friend UnitTest;

public:
    HasPtrMem();
    HasPtrMem(HasPtrMem&);
    HasPtrMem(HasPtrMem&&);
    ~HasPtrMem();

private:
    int * d_;

private:
    static int default_constructor_called_count_;
    static int copy_constructor_called_count_;
    static int move_constructor_called_count_;
    static int destructor_called_count_;
};

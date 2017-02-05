#pragma once

//#define HAS_MOVE_CONSTRUCTOR

class UnitTest;

class HasPtrMem
{
public:
    friend UnitTest;
public:
    static HasPtrMem GetTemp();

public:
    HasPtrMem();
    HasPtrMem(const HasPtrMem&);
#if defined(HAS_MOVE_CONSTRUCTOR)
    HasPtrMem(HasPtrMem&&);
#endif
    ~HasPtrMem();

private:
    int * d_;

private:
    static int default_constructor_called_count_;
    static int copy_constructor_called_count_;
    static int move_constructor_called_count_;
    static int destructor_called_count_;
};

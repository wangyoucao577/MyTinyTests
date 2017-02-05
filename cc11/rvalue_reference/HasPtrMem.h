#pragma once

// Try to define it while you call GCC
// g++ -std=c++11 -DHAS_MOVE_CONSTRUCTOR -fno-elide-constructors HasPtrMem.cc UnitTest.cc main.cc
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

public:
    int * GetPtrAddress() { return d_; }
private:
    int * d_;

public:
    static void ClearSum();
private:
    static int default_constructor_called_count_;
    static int copy_constructor_called_count_;
    static int move_constructor_called_count_;
    static int destructor_called_count_;
};

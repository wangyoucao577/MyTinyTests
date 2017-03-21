#pragma once

struct Trivial1 {};
struct Trivial2 {
public:
    int a;
private:
    int b;
};

struct Trivial3 {
    Trivial1 a;
    Trivial2 b;
};

struct Trivial4 {
    Trivial2 a[23];
};

struct Trivial5 {
    int x;
    static int y;
};

struct Trivial6 {
    Trivial6() = default;
    Trivial6(int i) : z(i) {}   //带参数的构造函数, 不影响是否trivial的判断
    int z;
};


struct NonTrivial1 {
    NonTrivial1() : z(42) {}
    int z;
};

struct NonTrivial2 {
    NonTrivial2();
    int w;
};
NonTrivial2::NonTrivial2() = default;

struct NonTrivial3 {
    Trivial5 c;
    virtual void f();
};

// standard layout types
struct SL_A1 { static int a; };
struct SL_C1 : SL_A1 { int d; };
struct SL_A2 { int a; };
struct SL_C2 : SL_A2 { static int d; };
struct SL_C3 : SL_A2, SL_A1 { static int d; };
struct SL_C4 : SL_A2 { int d; };
struct SL_C5 : SL_A2, SL_C1{};

struct SL_B1{};
struct SL_B2{};
struct SL_D1 : SL_B1 {
    SL_B1 b;
    int i;
};

struct SL_D2 : SL_B1 {
    SL_B2 b;
    int i;
};

struct SLayout1{};
struct SLayout2 {
private:
    int x;
    int y;
};
struct SLayout3 : SLayout1 {
    int x;
    int y;
    void f();
};
struct SLayout4 : SLayout1 {
    int x;
    SLayout1 y;
};
struct SLayout5 : SLayout1, SLayout3 {};
struct SLayout6 { static int y;};
struct SLayout7 : SLayout6 { int x; };
struct NonSLayout1 : SLayout1 {
    SLayout1 x;
    int i;
};
struct NonSLayout2 : SLayout2 { int z;};
struct NonSLayout3 : NonSLayout2{};
struct NonSLayout4 {
public:
    int x;
private:
    int y;
};

// test for POD
union U{};
union U1 { U1() {} };
enum E{};
typedef double* DA;
typedef void(*PF)(int, double);
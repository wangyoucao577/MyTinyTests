
#include "comm_include.h"

namespace MyUserDefinedLiteral {
    struct MyRGBA {
        uint8_t r_;
        uint8_t g_;
        uint8_t b_;
        uint8_t a_;

        MyRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0) : r_(r), g_(g), b_(b), a_(a) {}
    };

    //NOTE: GCC要求此处的"" 和 _C 中间要有空格, vs2015则无所谓
    MyRGBA operator "" _C(const char* col, size_t n) {

        const char * p = col;
        const char * end = col + n;
        const char *r, *g, *b, *a;
        r = g = b = a = nullptr;

        for (; p != end; ++p)
        {
            if (*p == 'r') {
                r = p + 1;
            }
            else if (*p == 'g') {
                g = p + 1;
            }
            else if (*p == 'b') {
                b = p + 1;
            }
            else if (*p == 'a') {
                a = p + 1;
            }
        }

        if ((r == nullptr) || (g == nullptr) || (b == nullptr)) {
            throw;
        }
        else if (a == nullptr) {
            return MyRGBA(atoi(r), atoi(g), atoi(b));
        }
        else {
            return MyRGBA(atoi(r), atoi(g), atoi(b), atoi(a));
        }
    }

    MyRGBA operator "" _C(unsigned long long a) {   //形参不同可以重载
        return MyRGBA(0, 0, 0, static_cast<uint8_t>(a));
    }

    double operator "" _C(long double centidegree) {    
        return static_cast<double>(centidegree);
    }

    int operator "" _Watt(unsigned long long w) {
        return static_cast<int>(w);
    }

    void operator "" _CHAR(char a) {
        cout << hex << a << endl;
    }

    std::ostream & operator << (std::ostream & out, const MyRGBA & col) {
        return out << "r: " << (int)col.r_
            << ", g: " << (int)col.g_
            << ", b: " << (int)col.b_
            << ", a: " << (int)col.a_ << endl;
    }

    void blend(MyRGBA && col1, MyRGBA && col2) {
        cout << "blend " << endl << col1 << col2 << endl;
    }
}

using namespace MyUserDefinedLiteral;
int main() {
    //test codes

    blend("r255 g255 b255"_C, "r10 g10 b10 a10"_C);
    cout << 10_C << endl;   //对应调用形参 unsigned long long 的函数
    cout << "centi degree sample " << 100.2_C << endl;  //对应调用形参 long double 的函数
    cout << "Watt sample " << 200_Watt << endl;
    'F'_CHAR;

    ROUTINE_BEFORE_EXIT_MAIN_ON_WINOWS;
}

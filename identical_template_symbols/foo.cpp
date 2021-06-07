
#define ID 0xf00
#include "thing.hpp"

unsigned foo() {
    thing<unsigned> t;
    return t.id();
}

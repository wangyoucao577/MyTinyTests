#ifndef THING_HPP
#define THING_HPP

#ifndef ID
#error ID undefined
#endif

template<typename T>
struct thing
{
    T id() const {
        return T{ID};
    }
};

#endif
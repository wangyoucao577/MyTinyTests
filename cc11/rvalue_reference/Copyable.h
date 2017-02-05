#pragma once
class Copyable
{
public:
    Copyable();
    Copyable(const Copyable&);
#if defined(HAS_MOVE_CONSTRUCTOR)
    Copyable(Copyable&&);
#endif
    ~Copyable();

public:
    static Copyable ReturnRValue();

    static void AcceptLValue(Copyable);
    static void AcceptLValueReference(const Copyable&);
    static void AcceptRValueReference(Copyable&&);
};


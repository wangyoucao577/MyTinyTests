#include<stdio.h>

struct base_t{
    int a;
    int b;
};

struct new_t{
    struct base_t base;
    int c;
    int d;
};

void print_base_t(struct base_t * t)
{
    printf("a = %d, b = %d.\n", t->a, t->b);
}

void print_new_t(struct new_t *t)
{
    printf("a = %d, b = %d, c = %d, d = %d.\n", t->base.a, t->base.b, t->c, t->d);
}

int main()
{
    struct new_t my_t;
    my_t.base.a = 100;
    my_t.base.b = 101;
    my_t.c = 102;
    my_t.d = 103;

    print_base_t((struct base_t *)&my_t);
    print_new_t(&my_t);

    return 0;

}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */


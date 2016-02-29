

struct coodinate_t
{
    union 
    {
        int x;
        int x_1;
    }
}; 

int main()
{
    struct coodinate_t cood;
    cood.x = 10;

    printf("cood.x=%d, cood.x_1=%d.\n", cood.x, cood.x_1);

    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */


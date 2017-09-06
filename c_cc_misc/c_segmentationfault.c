
#include <pthread.h>

void* test_thread(void *param)
{
    int *p = 0;
    *p = 17;

    return NULL;
}

int main()
{
    pthread_t id;
    pthread_create(&id, NULL, test_thread, NULL);
    
    pthread_join(id, NULL);
    return 0;
}

/* vim: set expandtab! tabstop=4 softtabstop=4 shiftwidth=4 number! : */

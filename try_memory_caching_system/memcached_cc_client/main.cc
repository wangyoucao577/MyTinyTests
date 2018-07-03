

#include <stdio.h>
#include <assert.h>

#include <libmemcached/memcached.h>


int main(){
    const char *config_string = "--SERVER=localhost:11211";
    memcached_st *memc = memcached(config_string, strlen(config_string));
    
    const char *key= "foo";
    const char *value= "value";
    memcached_return_t rc= memcached_set(memc, key, strlen(key), value, strlen(value), (time_t)0, (uint32_t)0);
    if (rc != MEMCACHED_SUCCESS) {
        printf("memcached_set failed, error %d\n", rc);
    } else {
        printf("memcached_set %s succeed\n", key);
    }

    size_t value_length = 0;
    uint32_t flags = 0;
    memcached_return_t err;
    char* got_value = memcached_get(memc, key, strlen(key), &value_length, &flags, &err);
    if (err != MEMCACHED_SUCCESS) {
        assert(NULL == got_value);
        printf("memcached_get failed, error %d\n", err);
    } else {
        assert(NULL != got_value);
        printf("VALUE %s %s %u %ld\n", key, got_value, flags, value_length);
        free(got_value);
    }
    
    memcached_free(memc);

    return 0;
}
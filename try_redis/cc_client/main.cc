
#include <stdio.h>

extern "C" {
    #include "hiredis/hiredis.h"
}

void printReply(const redisReply* reply){
    if (!reply) {
        printf("redisCommand unknown error\n");
    }else {
        switch (reply->type){
            case REDIS_REPLY_STATUS:
            case REDIS_REPLY_STRING:
                printf("%s\n", reply->str);
                break;
            case REDIS_REPLY_ERROR:
                printf("ERROR: %s\n", reply->str); 
                break;
            case REDIS_REPLY_INTEGER:
                printf("%lld\n", reply->integer);
                break;
            case REDIS_REPLY_NIL:
                printf("(nil)");
                break;
            case REDIS_REPLY_ARRAY:
                //TODO: 
                break;
            default:
                printf("unknown reply type %d\n", reply->type);
                break;
        }
    }
}

int main() {
    
    //Redis Connect
    redisContext *rc = redisConnect("127.0.0.1", 6379);
    if (rc == NULL || rc->err) {
        if (rc){
            printf("error: %s\n", rc->errstr);
            return -1;
        }else {
            printf("Can't allocate redis context\n");
            return -2;
        }
    }

    //test with execute commands 
    redisReply* reply = NULL;
    reply = (redisReply*)redisCommand(rc, "SET key1 %d", 10);
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "GET key1");
    printReply(reply);
    freeReplyObject(reply);

    //Redis Disconnect
    redisFree(rc);

    return 0;
}

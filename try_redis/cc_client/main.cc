
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

extern "C" {
    #include "hiredis/hiredis.h"
}

void printReply(const redisReply* reply, char sep = '\n'){
    if (!reply) {
        printf("redisCommand unknown error%c", sep);
        return;
    }

    switch (reply->type){
        case REDIS_REPLY_STATUS:
        case REDIS_REPLY_STRING:
            assert(reply->str);
            assert(strlen(reply->str) == reply->len);
            printf("%s%c", reply->str, sep);
            break;
        case REDIS_REPLY_ERROR:
            assert(reply->str);
            assert(strlen(reply->str) == reply->len);
            printf("ERROR: %s%c", reply->str, sep); 
            break;
        case REDIS_REPLY_INTEGER:
            printf("%lld%c", reply->integer, sep);
            break;
        case REDIS_REPLY_NIL:
            printf("(nil)%c", sep);
            break;
        case REDIS_REPLY_ARRAY:
            for (int i = 0; i < reply->elements; ++i){
                printReply(reply->element[i], ' ');
            }
            break;
        default:
            printf("unknown reply type %d%c", reply->type, sep);
            break;
    }

}

void test1_basic_commands(redisContext *rc){
    printf("enter %s\n", __func__);

    assert(rc);

    redisReply* reply = NULL;

    reply = (redisReply*)redisCommand(rc, "GET key1");
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "SET key1 %d", 10);
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "GET key1");
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "SETNX key1 15");
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "GET key1");
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "INCR key1");
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "GET key1");
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "INCRBY key1 11");
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "GET key1");
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "EXPIRE key1 10");
    printReply(reply);
    freeReplyObject(reply);

    sleep(3);

    reply = (redisReply*)redisCommand(rc, "TTL key1");
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "GET key1");
    printReply(reply);
    freeReplyObject(reply);

    sleep(10);
    
    reply = (redisReply*)redisCommand(rc, "GET key1");
    printReply(reply);
    freeReplyObject(reply);

    printf("exit %s\n\n", __func__);
}

void test2_rejson(redisContext *rc) {
    printf("enter %s\n", __func__);

    const char* json_str = "{\"key1\":\"value\", \"array\":[{\"key2\":\"value2\"}, {\"key2\":\"value3\"}, {\"key2\":\"value4\"}]}";

    redisReply* reply = NULL;

    reply = (redisReply*)redisCommand(rc, "JSON.SET json1 . %s", json_str);
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "JSON.GET json1 . ");
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "JSON.GET json1 .key1");
    printReply(reply);
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(rc, "JSON.GET json1 .array");
    printReply(reply);
    freeReplyObject(reply);


    printf("exit %s\n\n", __func__);
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
    test1_basic_commands(rc);
    test2_rejson(rc);

    //Redis Disconnect
    redisFree(rc);

    return 0;
}

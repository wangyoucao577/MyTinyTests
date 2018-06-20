# TryRedis 
熟悉 [Redis - REmote DIctionary Server](https://redis.io/) 的使用.    

# 实验平台    
- Linux: `Ubuntu 16.04.4 LTS`    
    - Kernel Version: `Linux ubuntu 4.13.0-36-generic #40~16.04.1-Ubuntu SMP Fri Feb 16 23:25:58 UTC 2018 x86_64 x86_64 x86_64 GNU/Linux`    

# 我的实验   
## Install Redis  
Find latest version on [Download Page](https://redis.io/download) if needed.    
```sh
$ mkdir redis
$ cd redis/
$ wget http://download.redis.io/releases/redis-4.0.10.tar.gz
$ tar -zxf redis-4.0.10.tar.gz
$ cd redis-4.0.10/
$ make
```

## Run Redis Server
- Simplest run, default port 6379    
`./src/redis-server`    
- Or run with conf file    
`./src/redis-server ./redis.conf`

## Try with Redis Cli
Check this [interactive tutorial](https://try.redis.io/) that will walk you through the most important features of Redis.   
```sh
$ ./src/redis-cli
127.0.0.1:6379> SET test1 testvalue1
OK
127.0.0.1:6379> GET test1
"testvalue1"
127.0.0.1:6379> SET test2 10
OK
127.0.0.1:6379> GET test2
"10"
127.0.0.1:6379> INCR test2
(integer) 11
127.0.0.1:6379> INCRBY test2 5
(integer) 16
127.0.0.1:6379> EXPIRE test2 5
(integer) 1
127.0.0.1:6379> TTL test2
(integer) 3
127.0.0.1:6379> GET test2
(nil)
127.0.0.1:6379> SET test2 10
OK
127.0.0.1:6379> SETNX test2 15
(integer) 0
127.0.0.1:6379> GET test2
"10"
```

## Try with Python Redis Client    
## Try with C/C++ Redis Client    

## Commands    
Refer to [Commands](https://redis.io/commands) for full commands list.    
- General Commands
    - SET    
    - SETNX: set if not exist    
    - GET    
    - INCR/INCRBY: atomically increment a number stored at a given key    
    - EXPIRE    
    - TTL    
- Commands for List    
    - RPUSH
    - LPUSH
    - LLEN
    - LRANGE
    - LPOP
    - RPOP
- Commands for Set
    - SADD
    - SREM
    - SISMEMBER
    - SMEMBERS
    - SUNION
- Commands for Sorted Set
    - ZADD
    - ZRANGE
    - ZREM
- Commands for Hashes
    - HSET
    - HGETALL
    - HMSET
    - HGET
    - HINCRBY
    - HDEL

## links 
- [Redis](https://redis.io/)
- [Download Page](https://redis.io/download)
- [interactive tutorial](https://try.redis.io/)
- [Commands](https://redis.io/commands)
- https://redis.io/clients
- https://redis.io/documentation
- http://www.runoob.com/redis/redis-tutorial.html

## Contacts 
- Author's Email: wangyoucao577@gmail.com.    
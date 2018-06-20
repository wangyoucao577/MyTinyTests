# TryRedis 
熟悉 [Redis - REmote DIctionary Server](https://redis.io/) 的使用.    

# 实验平台    
- Linux: `Ubuntu 16.04.4 LTS`    
    - Kernel: `Linux ubuntu 4.13.0-36-generic #40~16.04.1-Ubuntu SMP Fri Feb 16 23:25:58 UTC 2018 x86_64 x86_64 x86_64 GNU/Linux`    
    - `gcc (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609`    
    - `cmake version 3.10.2`
    - `go version go1.9.4 linux/amd64`
    - `Python 2.7.12`

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
Official C client [hiredis](https://github.com/redis/hiredis). Support for the whole command set, pipelining, event driven programming.	
- Build `hiredis`    
```sh
$ cd redis
$ git clone https://github.com/redis/hiredis.git
$ cd hiredis
$ make
$ ll | grep libhiredis.so
-rwxrwxr-x 1 user user 289304 Jun 19 23:22 libhiredis.so
$ sudo make install 
mkdir -p /usr/local/include/hiredis /usr/local/include/hiredis/adapters /usr/local/lib
cp -pPR hiredis.h async.h read.h sds.h /usr/local/include/hiredis
cp -pPR adapters/*.h /usr/local/include/hiredis/adapters
cp -pPR libhiredis.so /usr/local/lib/libhiredis.so.0.13
cd /usr/local/lib && ln -sf libhiredis.so.0.13 libhiredis.so
cp -pPR libhiredis.a /usr/local/lib
mkdir -p /usr/local/lib/pkgconfig
cp -pPR hiredis.pc /usr/local/lib/pkgconfig
```

- Build and Run `main.cc`
```sh
$ cd try_redis/cc_client
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ ./tryredis
```


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
- [Redis Download Page](https://redis.io/download)
- [Redis Interactive Tutorial](https://try.redis.io/)
- [Redis Commands](https://redis.io/commands)
- [Redis Clients](https://redis.io/clients)   
- [Redis Documentation](https://redis.io/documentation)
- [hiredis](https://github.com/redis/hiredis)   
- http://www.runoob.com/redis/redis-tutorial.html

## Author 
wangyoucao577@gmail.com    
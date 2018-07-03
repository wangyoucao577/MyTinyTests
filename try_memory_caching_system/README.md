# Try Memory Caching System - Redis vs. Memcached 
熟悉常用的 Memory Caching System [Redis - REmote DIctionary Server](https://redis.io/) 和 [Memcached](https://memcached.org) 的使用, 以及一些明显的区别.    

## 我的对比 Redis vs. Memcached 
- 对比点
    - `Redis`和`Memcached`两者都是应用非常广泛的基于内存的`key-value`缓存方案, 区别于数据库的持久存储;    
    - `Redis`支持更多类型的数据结构(`String/List/Set/Sorted-Set/Hashes`), 也已经通过扩展支持了的`JSON`类型, 而`memcached`仅支持`bytes`; 
    - `Redis`和`Memcached`都支持多种语言的`Client`接口, 命令行模式`Redis`有`redis-cli`, 而`Memcached`可以直接使用`telnet`, 故而貌似没太多区别. 而`Client`接口的易用性上, `Redis`更好一些;       
    - `Redis`原生支持持久化, 从而进程`crash`后重启数据不会丢失, 更易于恢复, 而`memcached`不支持;   
- 小结
    - 总体看来, 更倾向于在项目中使用 `Redis`.    
- 遗留`topic`
    - `High Available`: 两者的应用都非常广泛, 相信必然都有对应的高可用性的解决方案, 有空时再深入研究.    


## 实验平台    
- Linux: `Ubuntu 16.04.4 LTS`    
    - Kernel: `Linux ubuntu 4.13.0-36-generic #40~16.04.1-Ubuntu SMP Fri Feb 16 23:25:58 UTC 2018 x86_64 x86_64 x86_64 GNU/Linux`    
    - `gcc (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609`    
    - `cmake version 3.10.2`
    - `Python 2.7.12`

## 我的实验 - Redis   
### Install Redis  
Find latest version on [Download Page](https://redis.io/download) if needed.    
```sh
$ mkdir redis
$ cd redis/
$ wget http://download.redis.io/releases/redis-4.0.10.tar.gz
$ tar -zxf redis-4.0.10.tar.gz
$ cd redis-4.0.10/
$ make
```

#### Install ReJSON - Redis as a JSON store (optional)
Refer to the perfect introduction [Tech Blog - Redis as a JSON store](https://redislabs.com/blog/redis-as-a-json-store/).
```sh
$ cd redis
$ git clone https://github.com/RedisLabsModules/rejson.git
$ cd rejson
$ make
$ ll -lh src/ | grep rejson
-rw-rw-r--  1 user user 955K Jun 20 02:39 librejson.a
-rw-rw-r--  1 user user  70K Jun 20 02:38 rejson.c
-rw-rw-r--  1 user user 2.5K Jun 20 02:38 rejson.h
-rw-rw-r--  1 user user 218K Jun 20 02:39 rejson.o
-rwxrwxr-x  1 user user 447K Jun 20 02:39 rejson.so*
```

### Run Redis Server
- Simplest run, default port 6379    
`./src/redis-server`    
- Or run with conf file    
`./src/redis-server ./redis.conf`

#### Run Redis Server with ReJSON (optional)
```sh
$ cd redis
$ ll
drwxrwxr-x  5 user user     4096 Jun 20 02:19 hiredis/
drwxrwxr-x  6 user user     4096 Jun 20 02:38 redis-4.0.10/
-rw-rw-r--  1 user user  1738465 Jun 13 09:51 redis-4.0.10.tar.gz
drwxrwxr-x 10 user user     4096 Jun 20 02:38 rejson/
$
$ ./redis-4.0.10/src/redis-server --loadmodule ./rejson/src/rejson.so
```

### Try with Redis Client
We can try Redis with Redis CLI client. Also, [Redis Clients](https://redis.io/clients) lists lots of Redis clients for various languages. I'll pick up several of them in my test.    

#### Try with Redis Cli
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

#### Try with Python Redis Client    
Offical recommended client for python [redis-py](https://github.com/andymccurdy/redis-py), both for Python2 and Python3.    
- Install `redis-py`
```sh
$ sudo pip install redis
...
Successfully installed redis-2.10.6
$
```

- Run `test.py`
```sh
$ cd redis_python_client
$ python ./test.py
```

#### Try with C/C++ Redis Client 
Official C client [hiredis](https://github.com/redis/hiredis). Support for the whole command set, pipelining, event driven programming.	
- Build and install `hiredis`    
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
$ cd try_redis/redis_cc_client
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ ./tryredis
```

### Redis Persistence 持久化
Refer to [Redis Persistence](https://redis.io/topics/persistence) and [Redis 持久化](https://segmentfault.com/a/1190000002906345) for more details, e.g. advantages vs. disadvantages, how to use, etc.    
- 支持两种方式:     
    - RDB: 即snapshot的方式, 默认启用. 也可以使用命令如`SAVE`手动保存snapshot.    
    - AOF: 持续增量记录每条修改命令, 默认关闭    
- 注意事项:     
    - 若要从RDB文件恢复, 则需要先disable AOF; 否则默认会是从AOF文件进行恢复.    
    - RDB和AOF可以同时使用, 也建议同时使用.    

实验步骤:    
- 修改`redis.conf`, 启用`AOF`: `appendonly yes`    
- 启动`Redis`: `./src/redis-server ./redis.conf`    
- 写入一些 `key/value`    
- 查看是否生成`.aof`和`.rdb`文件
```sh
$ ll
-rw-r--r--  1 user user       93 Jun 22 08:52 try_redis_appendonly.aof
-rw-rw-r--  1 user user      122 Jun 22 08:39 try_redis_dump.rdb
```
- `kill`掉`redis-server`进程 
- 再启动`redis-server`进程, 可以查询刚刚设置的`key/value`依然存在, 此时是通过`.aof`恢复
- `kill`掉`redis-server`进程 
- 修改`redis.conf`, 禁用`AOF`
- 再启动`redis-server`进程, 可以查询刚刚设置的`key/value`依然存在, 此时是通过`.rdb`恢复

### Redis High Availability 高可用性
主要参考官方文档 [Redis Sentinel Documentation](https://redis.io/topics/sentinel).    
TODO: 

### Redis Common Commands    
Refer to [Commands](https://redis.io/commands) for full commands list.    
- General Commands
    - SET    
    - SETNX: set if not exist    
    - GET    
    - INCR/INCRBY: atomically increment a number stored at a given key    
    - EXPIRE    
    - TTL    
    - KEYS
    - TYPE
    - SCAN
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

## 我的实验 - Memcached
NOTE: The [Memcached Official Wiki](https://github.com/memcached/memcached/wiki) is slowly being ported over from the [Memcached old google code wiki](https://github.com/memcached/old-wiki/), please check there if you can't find something here. 

### Install Memcached  
Find latest version on [Memcached Download Page](https://memcached.org/downloads) if needed.    
Refer to [Memcached Install](https://github.com/memcached/memcached/wiki/Install) for further information.     
```sh
$ sudo apt install libevent-dev
$ 
$ wget https://memcached.org/files/memcached-1.5.8.tar.gz
$ tar -zxf memcached-1.5.8.tar.gz
$ cd memcached-1.5.8/
$ ./configure
$ make
```

### Run Memcached Server 
```sh
cd memcached-1.5.8/
./memcached
```

### Try with Memcached Client
We can try Memcached with telnet(as client). Also, [Memcached Clients](https://github.com/memcached/old-wiki/blob/master/Clients.wiki) lists lots of Memcached clients for various languages. I'll pick up several of them in my test.    

#### Try with Telnet as Memcached Client
Memcached can use Telnet as simplest client for the test. Refer to [Memcached Commands Standard Protocol](https://github.com/memcached/memcached/wiki/Commands#standard-protocol) for the command format.      
```sh
$ telnet localhost 11211
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
version
VERSION 1.5.8
get key1
END
set key1 1 0 5
12345
STORED
get key1
VALUE key1 1 5
12345
END
add key2 2 0 10
1234567890
STORED
get key2
VALUE key2 2 10
1234567890
END
add key2 2 0 1
a
NOT_STORED
replace key2 2 0 10
abcedfghij
STORED
get key2
VALUE key2 2 10
abcedfghij
END
delete key2
DELETED
get key2
END
flush_all
OK
get key1
END
```

#### Try with C/C++ Memcached Client
[libmemcached](http://libmemcached.org) is an open source C/C++ client library and tools for the [memcached server](http://memcached.org/), refer to [libmemcached Documentation](http://docs.libmemcached.org/) for API details.     
- Build and Install `libmemcached`
```sh
$ cd memcached
$ wget https://launchpad.net/libmemcached/1.0/1.0.18/+download/libmemcached-1.0.18.tar.gz
$ tar -zxf libmemcached-1.0.18.tar.gz
$ cd libmemcached-1.0.18
$ ./configure
$ make
$ sudo make install
$ ll /usr/local/include/ | grep memcached
drwxr-xr-x  2 root root 4096 Jul  3 00:24 libmemcached/
drwxr-xr-x  4 root root 4096 Jul  3 00:24 libmemcached-1.0/
drwxr-xr-x  2 root root 4096 Jul  3 00:24 libmemcachedutil-1.0/
$ ll /usr/local/lib/ | grep memcached
-rw-r--r--  1 root   root   3101616 Jul  3 00:24 libmemcached.a
-rwxr-xr-x  1 root   root       961 Jul  3 00:24 libmemcached.la*
lrwxrwxrwx  1 root   root        22 Jul  3 00:24 libmemcached.so -> libmemcached.so.11.0.0*
lrwxrwxrwx  1 root   root        22 Jul  3 00:24 libmemcached.so.11 -> libmemcached.so.11.0.0*
-rwxr-xr-x  1 root   root   1342080 Jul  3 00:24 libmemcached.so.11.0.0*
-rw-r--r--  1 root   root    212528 Jul  3 00:24 libmemcachedutil.a
-rwxr-xr-x  1 root   root      1025 Jul  3 00:24 libmemcachedutil.la*
lrwxrwxrwx  1 root   root        25 Jul  3 00:24 libmemcachedutil.so -> libmemcachedutil.so.2.0.0*
lrwxrwxrwx  1 root   root        25 Jul  3 00:24 libmemcachedutil.so.2 -> libmemcachedutil.so.2.0.0*
-rwxr-xr-x  1 root   root    106192 Jul  3 00:24 libmemcachedutil.so.2.0.0*
```

- Build and Run `main.cc`
```sh
$ cd try_redis/memcached_cc_client
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ ./trymemcached
```

### Memcached Common Commands    
Refer to [Memcached Commands](https://github.com/memcached/memcached/wiki/Commands) for more details. 
- Storage Commands  
    - set
    - add
    - replace
    - append
    - prepend
    - cas  
- Retrieval Commands
    - get
    - gets
- Statistcs Commands
    - stats
    - stats items
    - stats slabs
    - stats sizes
- Others
    - delete
    - incr/decr
    - flush_all


## Reference links 
- [Redis](https://redis.io/)
- [Redis Download Page](https://redis.io/download)
- [Redis Interactive Tutorial](https://try.redis.io/)
- [Redis Commands](https://redis.io/commands)
- [Redis Clients](https://redis.io/clients)   
- [Redis Documentation](https://redis.io/documentation)
- [An introduction to Redis data types and abstractions](https://redis.io/topics/data-types-intro)
- [Redis Persistence](https://redis.io/topics/persistence)
- [Redis 持久化](https://segmentfault.com/a/1190000002906345)
- [Redis Sentinel Documentation](https://redis.io/topics/sentinel)
- [Offical C Client - hiredis](https://github.com/redis/hiredis)   
- http://www.runoob.com/redis/redis-tutorial.html
- [Tech Blog - Redis as a JSON store](https://redislabs.com/blog/redis-as-a-json-store/)
- [ReJSON](https://github.com/redislabsmodules/rejson)
- [ReJSON documentation](https://oss.redislabs.com/rejson/)
- https://oss.redislabs.com/rejson/#building-and-loading-the-module
- [redis-py](https://github.com/andymccurdy/redis-py)
- [redis-py documentation](https://redis-py.readthedocs.io/en/latest/)
- [Memcached](https://memcached.org)
- [Memcached on Github](https://github.com/memcached/memcached)
- [Memcached Official Wiki](https://github.com/memcached/memcached/wiki)
- [Memcached Install](https://github.com/memcached/memcached/wiki/Install)
- [Memcached old google code wiki](https://github.com/memcached/old-wiki/)
- [Memcached Clients](https://github.com/memcached/old-wiki/blob/master/Clients.wiki)
- [Memcached Commands](https://github.com/memcached/memcached/wiki/Commands)
- [libmemcached](http://libmemcached.org)
- [libmemcached download page](https://launchpad.net/libmemcached/+download)
- [libmemcached Documentation](http://docs.libmemcached.org/)

## Author 
wangyoucao577@gmail.com    
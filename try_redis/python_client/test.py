

import redis    # redis-py
import time

def test_basic_commands(r):
    print "enter " + test_basic_commands.__name__ 

    reply = r.get("key1")
    print reply

    reply = r.set("key1", 10)
    print reply

    reply = r.get("key1")
    print reply

    reply = r.setnx("key1", 15)
    print reply

    reply = r.get("key1")
    print reply

    reply = r.incr("key1")
    print reply

    reply = r.get("key1")
    print reply

    reply = r.incrby("key1", 11)
    print reply

    reply = r.get("key1")
    print reply

    reply = r.expire("key1", 5)
    print reply

    time.sleep(2)

    reply = r.ttl("key1")
    print reply

    reply = r.get("key1")
    print reply

    time.sleep(5)

    reply = r.get("key1")
    print reply

    print "exit " + test_basic_commands.__name__ 

def test_hashes(r):
    print "enter " + test_hashes.__name__ 

    reply = r.hset('hashkey1', 'name', 'Bob')
    print reply
    reply = r.hset('hashkey1', 'email', 'bob@example.com')
    print reply

    reply = r.hget('hashkey1', 'name')
    print reply

    reply = r.hgetall('hashkey1')
    print reply

    print "exit  " + test_hashes.__name__ 

def test_rejson(r):
    print "enter " + test_rejson.__name__ 

    json_str = "{\"key1\":\"value\", \"array\":[{\"key2\":\"value2\"}, {\"key2\":\"value3\"}, {\"key2\":\"value4\"}]}";

    reply = r.execute_command('JSON.SET', 'json2', '.', json_str)
    print reply

    reply = r.execute_command('JSON.GET', 'json2', '.')
    print reply

    reply = r.execute_command('JSON.GET', 'json2', '.key1')
    print reply

    reply = r.execute_command('JSON.GET', 'json2', '.array')
    print reply

    print "exit  " + test_rejson.__name__ 

def main():
    r = redis.StrictRedis(host='127.0.0.1', port=6379, db=0)
    test_basic_commands(r)
    test_rejson(r)
    test_hashes(r)

    # query all keys in Redis 
    reply = r.keys()
    print reply 
    for item in reply:
        print r.type(item)

    # better way to scan all keys in Redis
    cursor = 0
    while(True):
        reply = r.scan(cursor)
        print reply
        for item in reply[1]:
            print r.type(item)
        if reply[0] == 0:
            break
        cursor = reply[0]
            

main()
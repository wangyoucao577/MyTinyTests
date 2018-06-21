

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
    
def main():
    r = redis.StrictRedis(host='127.0.0.1', port=6379, db=0)
    test_basic_commands(r)



main()
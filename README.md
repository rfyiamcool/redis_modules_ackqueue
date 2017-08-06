# redis_modules_ackqueue
*only support redis4.0, because redis4.x support load custom module*

### TO DO:
* when pop, do something

## why

使用list + zset 实现相对可靠的队列.

`注: Redis持久化机制采用异步写入, 故而无法保证数据安全. 又因RedisModule_Call多命令下无法保证原子性，也无法保证安全.`

## install

1. make
2. /path/to/redis-server --loadmodule ./module.so


## example

run `redis-cli` and try the commands:

```
redis 127.0.0.1:6379> ack.rpush  ack_queue timestamp nima3 queue_mq1
(integer) 1
redis 127.0.0.1:6379> keys *
1) "ack_queue"
2) "queue_mq1"
redis 127.0.0.1:6379> ZRANGE ack_queue 0 -1
1) "nima3"
redis 127.0.0.1:6379> LRANGE queue_mq1 0 -1
1) "nima3"
redis 127.0.0.1:6379>
```

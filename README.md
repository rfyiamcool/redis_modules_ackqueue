## Quick Start Guide

1. make
2. /path/to/redis-server --loadmodule ./module.so

then run `redis-cli` and try the commands:


## example

```
redis 127.0.0.1:6379> ack.rpush  zset_name 1 nima3 queue_mq1
(integer) 1
redis 127.0.0.1:6379> keys *
1) "queue_mq1"
2) "zset_name"
redis 127.0.0.1:6379> ZRANGE zset_name 0 -1
1) "nima3"
redis 127.0.0.1:6379> LRANGE queue_mq1 0 -1
1) "nima3"
redis 127.0.0.1:6379>
```

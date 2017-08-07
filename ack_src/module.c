#include "../redismodule.h"
#include "../rmutil/util.h"
#include "../rmutil/strings.h"
#include "../rmutil/test_util.h"

int AckSureCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
}

int AckLpopCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
}
/*
* example.AckPush <key> <score> <value> <ack queue name>
*/
int AckRpushCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {

  // we need EXACTLY 5 arguments
  if (argc != 5) {
    return RedisModule_WrongArity(ctx);
  }
  RedisModule_AutoMemory(ctx);

  // open the key and make sure it's indeed a HASH and not empty
  RedisModuleKey *key =
	  RedisModule_OpenKey(ctx, argv[1], REDISMODULE_READ | REDISMODULE_WRITE);
  if (RedisModule_KeyType(key) != REDISMODULE_KEYTYPE_ZSET &&
	  RedisModule_KeyType(key) != REDISMODULE_KEYTYPE_EMPTY) {
	return RedisModule_ReplyWithError(ctx, REDISMODULE_ERRORMSG_WRONGTYPE);
  }

  /*RedisModuleCallReply *rep =*/
	  /*RedisModule_Call(ctx, "llen", "ss", argv[1], argv[2]);*/
  /*RMUTIL_ASSERT_NOERROR(ctx, rep);*/

  RedisModuleCallReply *rep =
	  RedisModule_Call(ctx, "ZADD", "sss", argv[1], argv[2], argv[3]);
  RMUTIL_ASSERT_NOERROR(ctx, rep);

  RedisModule_Call(ctx, "RPUSH", "ss", argv[4], argv[3]);

  if (RedisModule_CallReplyType(rep) == REDISMODULE_REPLY_NULL) {
    RedisModule_ReplyWithNull(ctx);
    return REDISMODULE_OK;
  }

  RedisModule_ReplyWithCallReply(ctx, rep);
  return REDISMODULE_OK;
}


int RedisModule_OnLoad(RedisModuleCtx *ctx) {

  // Register the module itself
  if (RedisModule_Init(ctx, "ack", 1, REDISMODULE_APIVER_1) ==
      REDISMODULE_ERR) {
    return REDISMODULE_ERR;
  }

  // register example.hgetset - using the shortened utility registration macro
  RMUtil_RegisterWriteCmd(ctx, "ack.rpush", AckRpushCommand);
  RMUtil_RegisterWriteCmd(ctx, "ack.lpop", AckLpopCommand);
  RMUtil_RegisterWriteCmd(ctx, "ack.sure", AckSureCommand);

  return REDISMODULE_OK;
}

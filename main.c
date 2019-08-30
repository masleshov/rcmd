#include "stdio.h"
#include "reply.h"
#include "util.h"
#include "lib/hiredis.h"
#include "stdbool.h"

const int MAX_CMD_LEN = 256;

void listen(redisContext* ctx, char* cmd)
{
    enum types type = cmd2type(cmd);
    redisReply *reply = redisCommand(ctx, cmd);
    switch (reply->type)
    {
        case REDIS_REPLY_STRING:
            printf("Reply: %s\n", reply->str);
            break;
        case REDIS_REPLY_ERROR:
            printf("Error: %s\n", reply->str);
            break;
        case REDIS_REPLY_STATUS:
            printf("Status: %s\n", reply->str);
            break;
        case REDIS_REPLY_ARRAY:
            {
                handle(type, reply);
                break;
            }
        default:
            printf("Not knowed type of reply.\n");
    }

    freeReplyObject(reply);
}

int main(int argc, char *argv[])
{
    char *ip = "";
    int port = 0;
    
    if(argc <= 1)
    {
        printf("Need specify a host for rcmd tool. As example, \"rcmd 8.8.8.8:8888\".\n");
        return 0;
    }

    int hlen = strlen(argv[1]); //length of host string
    char host[hlen];
    int idx = 0;
    while(idx != hlen)
    {
        host[idx] = argv[1][idx];
        idx++;
    }

    ip = strtok(host, ":");
    port = atoi(strtok(NULL, ":"));

    redisContext *ctx = redisConnect(ip, port);
    if(ctx != NULL && ctx->err)
    {
        printf("Error: %s\n", ctx->errstr);
        return 0;
    }
    else
    {
        printf("Connected! Start typing a command. For help type \"help\", for finish press CTRL+C.\n");
    }

    char input[MAX_CMD_LEN];
    memset(input, 0, MAX_CMD_LEN);

    while(true)
    {
        printf("> ");
        fgets(input, MAX_CMD_LEN, stdin);
        
        int len = strlen(input) - 1;
        char *cmd = clrstr(input, len); // gets length of string without last \n character
        listen(ctx, cmd);
        free(cmd);
    }

    redisFree(ctx);
    return 0;
}

#include "types.h"
#include "stdlib.h"
#include "stdbool.h"

const char* const STR_CMD[] = { "APPEND", "BITCOUNT", "BITFIELD", "BITOP", "BITPOS", "DECR", "DECRBY",
    "GET", "GETBIT", "GETRANGE", "GETSET", "INCR", "INCRBY", "INCRBYFLOAT", "MGET", "MSET", "MSETNX", "PSETEX",
    "SET", "SETBIT", "SETEX", "SETNX", "SETRANGE", "STRLEN", 0 };

const char* const LIST_CMD[] = { "BLPOP", "BRPOP", "BRPOPLPUSH", "LINDEX", "LINSERT", "LLEN", "LPOP", "LPUSH", "LPUSHX",
    "LRANGE", "LREM", "LSET", "LTRIM", "RPOP", "RPOPLPUSH", "RPUSH", "RPUSHX", 0 };

bool contains(const char* const* arr, const char* str);

types cmd2type(char* cmd)
{
    enum types res;
    if(cmd[0] == 'H') res = HASH;
    else if(contains(STR_CMD, cmd)) res = STRING;
    else if(contains(LIST_CMD, cmd)) res = LIST;

    return res;
}

/*
 * cnt - count of objects if hash set
 */
int get_hsize(size_t cnt)
{
    return cnt * sizeof(struct hentry) + sizeof(int);
}

struct hset* chset(int cnt)
{
    return (struct hset*)malloc(get_hsize(cnt));
}

void fhset(struct hset* set)
{
    for (size_t i = 0; i < set->len-1; i++)
    {
        free(set->entries[i]);
    }    

    free(set->entries);
    free(set);
}

/*
 * Prints a hash set to standart output device
 * @set - hash set for printing
 * @lcnt - count of lines which should be printed
 */
void print_hset(struct hset* set, int lcnt)
{
    for (size_t i = 0; i < set->len && i < lcnt; i++)
    {
        printf("Key: %s, Value: %s\n", set->entries[i]->key, set->entries[i]->val);
    }
}

bool contains(const char* const* arr, const char* str)
{
    int idx = 0;
    while(arr[idx] != 0)
    {
        if(strcmp(arr[idx++], str) == 0)
            return true;
    }

    return false;
}
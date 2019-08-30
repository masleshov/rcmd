#include "stddef.h"
#include "stdio.h"
#include "string.h"

typedef enum types
{
    STRING,
    LIST,
    HASH,
    SET,
    SSET,
    BIT
} types;

struct hentry
{
    char* key;
    char* val;
};

struct hset
{
    struct hentry** entries;
    unsigned int len;
};

types cmd2type(char* cmd);

/*
 * cnt - count of objects if hash set
 */
int get_hsize(size_t cnt);
struct hset* chset(int cnt);
void fhset(struct hset* set);
void print_hset(struct hset* set, int lcnt);
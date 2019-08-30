#include "reply.h"
#include "errors.h"
#include "stdlib.h"

int to_hset(redisReply** elements, size_t cnt, struct hset* result);

void handle(types type, redisReply* reply)
{
    switch (type)
    {
        case HASH:
            {
                struct hset *set = chset(reply->elements/2);
                to_hset(reply->element, reply->elements, set);
                print_hset(set, 5);                
                fhset(set);
                break;
            }    
        default:
            break;
    }
}

int to_hset(redisReply** elements, size_t cnt, struct hset* result)
{
    result->entries = malloc((cnt/2) * sizeof(struct hentry));

    struct hentry *entry;
    for (size_t i = 0; i < cnt; i++)
    {
        if(elements[i]->type != REDIS_REPLY_STRING)
        return NOT_A_STRING;        
        
        if(i%2 == 0) // if this element is key of hset
        {
            entry = malloc(sizeof(struct hentry));
            entry->key = elements[i]->str;

            result->entries[i/2] = entry;
            result->len++;
        }
        else
        {
            entry->val = elements[i]->str;
        }
    }

    return 0;
}
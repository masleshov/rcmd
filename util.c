#include "util.h"

char* clrstr(char* str, int len)
{
    int idx = 0;

    char *res = (char*)malloc(len * sizeof(char));
    while(idx < len)
    {
        res[idx] = str[idx];
        idx++;
    }

    res[len] = '\0';
    return res;
}
#include <stdio.h>

#define bool int
#define true 0
#define false -1

bool validIPV6Address(char * IP)
{
    if(NULL == IP)
    {
        return false;
    }

    int interval = 7;
    int max_intevel_num = 4;
    int index = 0;

    if(IP[index] == ':')
    {
        return false;
    }

    for(; index <= interval; index ++)
    {
        if(IP[index] == ':')

        if( IP[index] <= '9' && IP[index] >= '0')
        {
            continue;
        }

        if( IP[index] <= 'z' && IP[index] >= 'a')
        {
            continue;
        }

        if( IP[index] <= 'Z' && IP[index] >= 'A')
        {
            continue;
        }
    }


    return true;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

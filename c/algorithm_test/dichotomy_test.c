/**
 * @file dichotomy_test.c
 * @author your name (you@domain.com)
 * @brief 二分法测试
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>

int dichotomy_fun(int *data, int len, int target)
{
    int start = 0;
    int end = len - 1;
    int mid = 0;
    int index = 0;

    if(target > data[end] ||  target < data[start])
    {
        return -1;
    }

    while(start < end)
    {
        mid = (end + start) / 2;
        index ++;
        printf("cacu time [%d]: %d %d %d\n", index, start, mid, end);
        if(data[mid] < target)
        {
            start = mid + 1;
        }
        else if(data[mid] > target)
        {
            end = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}


int main(int argc, char const *argv[])
{
    int data[] = {1,3,5,8,12,14,15,17,
                    20,21,25,26,36,40,51};
    int len = sizeof(data) / sizeof(data[0]);
    int target = 24;
    int location =dichotomy_fun(data, len, target);
    if(-1 == location)
    {
        printf("could not find target %d\n", target);
        return -1;
    }
    printf("find target location %d\n", location);
    return 0;
}

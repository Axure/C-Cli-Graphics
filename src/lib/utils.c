//
// Created by 郑虎 on 15 年 July. 30..
//

#include "utils.h"

int string_to_number(char *string)
{
    char *p = string;
    int number = 0;
    while (*p != '\0') {
        number = number * 10 + *p - '0';
        ++p;
    }
    return number;
}
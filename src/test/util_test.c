#include <stdio.h>
#include "../lib/utils.h"


int main()
{
    char test_string[] = "3213125";
    printf("The test string is %s. The output integer is %d\n", test_string, string_to_number(test_string));
    return 0;
}
#include <stdio.h>
#include "../include/border.h"
/*border column 1 & 5*/
void border_1_5(const char *str, int i)
{
    int j = i;
    while (j-- > 0)
        printf("%s", j ? "#" : "#\n");
}
/*border column 2 & 4*/
void border_2_4(const char *str, int i)
{
    int j = i;
    while (j-- > 0)
        printf("%s", j == i - 1 || j == 0 ? "#" : " ");
    printf("\n");
}
/*border column 3*/
void border_3(const char *str, int i)
{
    int j = i;
    printf("%s  %s", "#", str);
    j -= strlen(str) + 4;
    while (j-- > 0)
        printf(" ");
    printf("#\n");
}
void border_print(const char *str, int i)
{
    border_1_5(str, i);
    border_2_4(str, i);
    border_3(str, i);
    border_2_4(str, i);
    border_1_5(str, i);
}
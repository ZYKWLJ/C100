#include <stdio.h>
#define READ_TIME 3
int count = 0;
int main(void)
{
    while (count < READ_TIME)
    {
        printf("turn %d\t", count);
        /*fistly, judge whether the count is the first or not*/
        printf("%s\n", "fistly, judge whether the count is the first or not");
        printf("%s\n\n", !(count++) ? "system first read,create the index file structrue from the log file first" : "read the index info to find the position in the disk directly");
        /*test1 start read data by the data's key*/
        printf("%s\n", "==test1 start read data by the data's key==");
        /*then read the exactly position of the data in the disk*/
        printf("%s\n", "then read the exactly position of the data in the disk");
        printf("%s\n", "read the position and value len in the disk of the data according the data's key");
        /*test2 start read data by the data's key*/
        printf("\n\n%s\n", "==test2 start insert data by the data's key==");
        
    }
    return 0;
}
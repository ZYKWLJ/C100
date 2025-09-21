#include <stdio.h>
#include <string.h>

#define READ_TIME 3
int count = 0;
void border_print(const char *str, int i)
{
    int j = i;
    while (j-- > 0)
        printf("#");
    j = i;
    while (j-- > 0)
        printf
        printf("%s", !j || j == i ? "#" :(j-i==strlen(str)?(j)) " ");
    j = i;
    while (j-- > 0)
        printf("#");
}
void search()
{
    /*test1 start read data by the data's key*/
    printf("%s\n", "==test1 start read data by the data's key==");
    /*then read the exactly position of the data in the disk*/
    printf("%s\n", "then read the exactly position of the data in the disk");
    printf("%s\n", "read the position and value len in the disk of the data according the data's key");
}

void insert()
{
    /*test2 start read data by the data's key*/
    printf("\n\n%s\n", "==test2 start insert data by the data's key==");
    /*find whether have the data in the disk, if have, then insert in the end and update the info in index structrue*/
    /*if not, then insert in the end and insert the info in index structrue*/
    printf("%s", "find whether have the data in the disk, if have, then insert in the end and update the info in index structrue");
    printf("%s", "if not, then insert in the end and insert the info in index structrue");
}

void update()
{
    printf("\n\n%s\n", "==test2 start insert data by the data's key==");
    /*first find whether exist the data has the same key, if exists,append the data in the end of disk,and update the index with the new position and len but the same key*/
    /*if not, append the data in the end of disk,and update the index with the new position and len and the new key*/
    printf("%s", "first find whether exist the data has the same key");
    printf("%s", "if exists, append the data in the end of disk,and update the index with the new position and len but the same key");
    printf("%s", "if not, append the data in the end of disk,and update the index with the new position and len and the new key");
}

void delete()
{
}
int main(void)
{
    while (count < READ_TIME)
    {
        printf("turn %d\t", count);
        /*fistly, judge whether the count is the first or not*/
        printf("%s\n", "fistly, judge whether the count is the first or not");
        printf("%s\n\n", !(count++) ? "system first read,create the index file structrue from the log file first" : "read the index info to find the position in the disk directly");
        /*test1 start read data by the data's key*/
        search();
        /*test2 start insert data with key-value*/
        insert();
        /*test3 start update data with key-value*/
        update();
        /*test4 start delete data with key*/
        delete();
    }
    return 0;
}
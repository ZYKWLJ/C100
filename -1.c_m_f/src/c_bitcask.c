#include <stdio.h>
#include <string.h>

#define READ_TIME 3
int count = 0;
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
#if 0
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
#endif
    border_print("hello", 100);

    return 0;
}
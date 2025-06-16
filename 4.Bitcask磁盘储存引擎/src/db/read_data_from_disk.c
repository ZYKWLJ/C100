#include "../../include/include.h"
#define MAX_LINE_LENGTH 1024
// extern INSERT_ON_ODD_SHOW insert_on_or_show;
extern bitcask_t* bitcask;

void read_data_from_disk(char *file_path, disk_engine_type_t disk_engine_type)
{
    if (!file_path || !bitcask)
    {
        printf("Invalid parameters\n");
        return;
    }

    FILE *fp = fopen(file_path, "r");
    char line[MAX_LINE_LENGTH];
    int count = 0;
    rewind(fp);
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // 移除换行符
        line[strcspn(line, "\n")] = '\0';
        // LOG_PRINT("FIND first `:` position");
        //  查找第一个冒号位置
        char *colon = strchr(line, ':');
        if (!colon)
        {
            continue; // 跳过格式错误的行
        }

        // 分割key和value
        *colon = '\0';
        char *key = line;
        char *value = colon + 1;
        // LOG_PRINT("key:%s\tvalue:%s\n", key, value);

        if (strlen(key) > 0 && strlen(value) > 0)
        {
            // 需要复制字符串，因为strtok返回的是指向原缓冲区的指针
            char *key_copy = strdup(key);
            char *value_copy = strdup(value);

            if (key_copy && value_copy)
            {
                db_insert(disk_engine_type, key_copy, value_copy);
                count++;
            }
            else
            {
                free(key_copy);
                free(value_copy);
            }
        }
    }
    fclose(fp);
}
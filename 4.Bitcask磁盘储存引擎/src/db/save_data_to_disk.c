#include "../../include/include.h"
#define MAX_LINE_LENGTH 1024
extern bitcask_t *bitcask;

void save_data_to_disk(char *file_path, disk_engine_type_t disk_engine_type)
{
    if (!file_path || !bitcask)
    {
        printf("Invalid parameters\n");
        return;
    }
}

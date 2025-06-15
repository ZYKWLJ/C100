#include "../include/include.h"

/**
 * data descp: 磁盘偏移和数据大小
 */
typedef struct bitcask_index_offset_size_
{
    int offset; /*4b*/
    int size;   /*4b*/
} bitcask_index_offset_size;

/**
 * data descp: 索引系统
 */
typedef struct bitcask_index_
{
    string key; /*4b*/
    bitcask_index_offset_size *offset_size;
} bitcask_index;

/**
 * data descp: 日志文件系统
 */

typedef struct bitcask_log_
{

} bitcask_log;

/**
 * data descp: bitcask系统
 */
typedef struct bitcask_
{
    bitcask_index *index;
    bitcask_log *log;
} bitcask;

int main(void)
{

    return 0;
}
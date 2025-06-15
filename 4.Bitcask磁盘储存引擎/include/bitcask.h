#ifndef BITCASK_H_
#define BITCASK_H_



#include <stdio.h>
typedef char *string;

/**
 * data descp: 磁盘偏移和数据大小
 */
typedef struct bitcask_index_offset_size_
{
    int offset; /*4b*/
    int size;   /*4b*/
} bitcask_index_offset_size_t;

/**
 * data descp: 索引系统
 */
typedef struct bitcask_index_
{
    string key; /*4b*/
    bitcask_index_offset_size_t *offset_size;
} bitcask_index_t;

/**
 * data descp: 日志文件系统
 */

typedef struct bitcask_log_
{

} bitcask_log_t;

/**
 * data descp: bitcask系统
 */
typedef struct bitcask_
{
    bitcask_index_t *index;
    bitcask_log_t *log;
} bitcask_t;

int main(void)
{

    return 0;
}

#endif /* BITCASK_H_ */

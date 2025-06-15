#ifndef BITCASK_H_
#define BITCASK_H_

#include <stdio.h>
#define MAX_DATA_SIZE 10000

/**
 * data descp: 真实存储的数据
 */
typedef struct data_
{
    string key;
    string value;
    int size;
} data_t;

data_t *data_t_init(string key, string value);

void *data_t_print(data_t *data);
/**
 * data descp: 数据在磁盘上的偏移和数据大小
 */
typedef struct bitcask_index_offset_size_
{
    int offset; /*4b,全局变量*/
    int size;   /*4b，单独计算数据*/
} bitcask_single_index_offset_size_t;

bitcask_single_index_offset_size_t *bitcask_single_index_offset_size_t_init(data_t *data);
bitcask_single_index_offset_size_t *bitcask_single_index_offset_size_t_print(bitcask_single_index_offset_size_t *);

/**
 * data descp: 单个索引
 */
typedef struct bitcask_single_index_
{
    string key; /*4b*/
    bitcask_single_index_offset_size_t *offset_size;
} bitcask_single_index_t;

bitcask_single_index_t *bitcask_single_index_t_init(string key, bitcask_single_index_offset_size_t *offset_size);
bitcask_single_index_t *bitcask_single_index_t_print(bitcask_single_index_t *bitcask_index);

/**
 * data descp: 索引系统——即索引K-V，这里使用hash套壳
 */
typedef struct bitcask_index_
{
    /**
     * data descp: 10000个槽的哈希表
     */
    list_t *map[MAX_DATA_SIZE];
} bitcask_index_t;

bitcask_index_t *bitcask_index_t_init();
void bitcask_index_print(bitcask_index_t *bitcask_index);
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
    bitcask_single_index_t *index;
    bitcask_log_t *log;
} bitcask_t;

#endif /* BITCASK_H_ */

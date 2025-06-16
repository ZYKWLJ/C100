#ifndef LOG_H_
#define LOG_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char *string;
/**
 * data descp: 真实存储的数据k-v
 */
typedef struct data_
{
    string key;
    string value;
    int size;
} data_t;
/**
 * data descp: 索引系统——即索引K-V，这里的哈希索引仅仅存储的是key-(offset,size)
 */
typedef struct bitcask_index_
{
    /**
     * data descp: 10000个槽的哈希表,索引系统本质是一个哈希表
     */
    list_t *map[MAX_DATA_SIZE];
} bitcask_index_t;

data_t *data_t_init(string key, string value);

void *data_t_print(data_t *data);
/**
 * data descp: 日志文件系统条目
 */
typedef struct bitcask_log_entry_
{
    int key_size;
    int value_size;
    string key;   /*变长*/
    string value; /*变长*/
} bitcask_log_entry_t;

/**
 * func descp: 初始化日志条目
 */
bitcask_log_entry_t *bitcask_log_entry_t_init(data_t *date);

/**
 * data descp: 日志文件系统
 */
typedef struct bitcask_log_
{
    string log_file_path; /*日志文件*/
    long offset;          /*不用每次遍历文件，没加入一次，就更新这个offset*/
} bitcask_log_t;

/**
 * func descp: 初始化日志系统
 */
bitcask_log_t *bitcask_log_t_init(string log_file_path);
/**
 * data descp: 追加日志
 */
void bitcask_log_entry_t_write_to_log(bitcask_log_t *bitcask_log, data_t *data, bitcask_index_t *bitcask_index);

/**
 * data descp: 从头读到尾日志
 */
void bitcask_log_read_from_begin_to_end(bitcask_log_t *bitcask_log);
#endif /* LOG_H_ */
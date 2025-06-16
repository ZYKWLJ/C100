#ifndef INDEX_H_
#define INDEX_H_

/**
 * data descp: 单个索引，这是map中存放的数据
 */
typedef struct bitcask_single_index_
{
    string key;            /*4b*/
    long log_entry_offset; /*每一个条目的索引不一样，所以必须保留次字段*/
    int log_entry_size;
} bitcask_single_index_t;

bitcask_single_index_t *bitcask_single_index_t_init(data_t *data, long offset);
bitcask_single_index_t *bitcask_single_index_t_print(bitcask_single_index_t *bitcask_index);
/**
 * func descp: 索引系统初始化，需要完全遍历一次日志系统
 */
bitcask_index_t *bitcask_index_t_init(bitcask_log_t *bitcask_log);

/**
 * func descp: 打印索引系统
 */
void bitcask_index_print(bitcask_index_t *bitcask_index);

/**
 * func descp: 极速访问，通过key获取得到offset+size
 */

#endif /* INDEX_H_ */
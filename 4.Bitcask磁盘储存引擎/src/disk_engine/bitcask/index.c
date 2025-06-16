#include "../../../include/include.h"
// #include "index.h"
int data_num = 0;
int offset = 0;

/**
 * func descp: 本质上还是加入data数据形成的索引条目
 */
bitcask_single_index_t *bitcask_single_index_t_init(data_t *data, long offset)
{
    bitcask_single_index_t *bitcask_single_index = (bitcask_single_index_t *)malloc(sizeof(bitcask_single_index_t));
    bitcask_single_index->key = data->key;
    bitcask_single_index->log_entry_size = data->size;
    bitcask_single_index->log_entry_offset = offset;
    // bitcask_single_index_t_print(bitcask_single_index);
    return bitcask_single_index;
}

bitcask_single_index_t *bitcask_single_index_t_print(bitcask_single_index_t *bitcask_single_index)

{
    printf("%s:", bitcask_single_index->key);

    /**
     * data descp: 闭区间表示数据更直观
     */
    printf("%s[%d,%d]\n", bitcask_single_index->key, bitcask_single_index->log_entry_offset, bitcask_single_index->log_entry_offset + bitcask_single_index->log_entry_size);
}
bitcask_index_t *bitcask_index_t_init(bitcask_log_t *bitcask_log)
{
    printf("first init bitcask_index,create it from log file\n");
    bitcask_index_t *bitcask_index = (bitcask_index_t *)malloc(sizeof(struct bitcask_index_));
    /**
     * data descp: 先统一为NULL，再从log中加载
     */
    for (int i = 0; i < MAX_DATA_SIZE; i++)
    {
        /**
         * data descp: 每一个槽位都是一个链表
         */
        bitcask_index->map[i] = NULL;
    }
    /**
     * data descp: 从log中加载
     */
    /*拿到4字节key和value长度*/

    FILE *file = fopen(bitcask_log->log_file_path, "r+b"); /*打开日志文件，使用"r+b"模式以二进制读/写方式打开，不会截断文件
                                                            */
    int key_size = 0;
    int value_size = 0;
    long offset = 0;

    // 循环读取日志文件中的所有记录
    while (1)
    {
        // 记录当前文件偏移量(即KV对起始位置)
        offset = ftell(file);

        // 读取key大小和value大小
        if (fread(&key_size, sizeof(int), 1, file) != 1)
        {
            break; // 读取失败或文件结束
        }

        if (fread(&value_size, sizeof(int), 1, file) != 1)
        {
            break; // 读取失败或文件结束
        }

        // 读取key
        char *key = (char *)malloc(key_size);
        if (key == NULL || fread(key, 1, key_size, file) != key_size)
        {
            if (key)
                free(key);
            break; // 内存分配失败或读取失败
        }

        bitcask_single_index_t *new_bitcask_single_index = (bitcask_single_index_t *)malloc(sizeof(struct bitcask_single_index_));
        new_bitcask_single_index->key = key;
        new_bitcask_single_index->log_entry_size = value_size;
        new_bitcask_single_index->log_entry_offset = offset;
        bitcask_single_index_t_print(new_bitcask_single_index);
        map_insert(bitcask_index->map, new_bitcask_single_index, BITCAST_INDEX_OFFSET_SIZE_T);
        // 跳过value数据，移动到下一个KV对
        fseek(file, value_size, SEEK_CUR);
    }
    fclose(file);
    printf("first init bitcask_index over!\n");

    return bitcask_index;
}
void bitcask_index_print(bitcask_index_t *bitcask_index)
{
    int map_data_count = 0;
    for (int i = 0; i < MAX_DATA_SIZE; i++)
    {
        if (bitcask_index->map[i])
        {
            printf("index:\n");
            list_print((list_t *)bitcask_index->map[i], BITCAST_INDEX_OFFSET_SIZE_T);
            map_data_count++;
        }
    }
    printf("data_map_count=%d\n", map_data_count);
    printf("data_total_count=%d\n", data_num);
}
// #define MAIN
#ifdef MAIN
int main(void)
{
    bitcask_index_t *bitcask_index = bitcask_index_t_init();
    // for (int i = 0; i < 100 ; i++)
    // {
    //     char key[10];
    //     sprintf(key, "k-%d", i);
    //     char value[10];
    //     sprintf(value, "v-%d", i);
    //     data_t *data1 = data_t_init(key, value);
    //     bitcask_single_index_offset_size_t *os1 = bitcask_single_index_offset_size_t_init(data1);
    //     map_insert(bitcask_index->map, bitcask_single_index_t_init(data1->key, os1), BITCAST_INDEX_OFFSET_SIZE_T);
    // }

    for (int i = 0; i < 100; i++)
    {
        char key[10];
        sprintf(key, "k-%d", i % 2 == 0 ? 100 : 200);
        char value[10];
        sprintf(key, "k-%d", i % 2 == 0 ? 100 : 200);
        data_t *data1 = data_t_init(key, value);
        map_insert(bitcask_index->map, bitcask_single_index_t_init(data1), BITCAST_INDEX_OFFSET_SIZE_T);
    }
    bitcask_index_print(bitcask_index);
    map_find(bitcask_index->map, "k-200", BITCAST_INDEX_OFFSET_SIZE_T);
    map_find(bitcask_index->map, "k-300", BITCAST_INDEX_OFFSET_SIZE_T);

    return 0;
}

#endif /* BITCASK_H_ */

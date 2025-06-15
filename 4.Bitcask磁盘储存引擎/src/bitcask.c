#include "../include/include.h"

#include <stdio.h>
// #include "bitcask.h"
typedef char *string;

data_t *data_t_init(string key, string value)
{
    data_t *data = (data_t *)malloc(sizeof(data_t));
    data->key =strdup(key);
    data->value = strdup(value);
    data->size = strlen(value);
    return data;
}

void *data_t_print(data_t *data)
{
    printf("[%s[%s],%d]\n", data->key, data->value, data->size);
}

int offset = 0;

bitcask_single_index_offset_size_t *bitcask_single_index_offset_size_t_init(data_t *data)
{
    bitcask_single_index_offset_size_t *bitcask_index_offset_size = (bitcask_single_index_offset_size_t *)malloc(sizeof(struct bitcask_index_offset_size_));
    bitcask_index_offset_size->offset = offset;
    bitcask_index_offset_size->size = data->size;
    return bitcask_index_offset_size;
}

bitcask_single_index_offset_size_t *bitcask_single_index_offset_size_t_print(bitcask_single_index_offset_size_t *bitcask_index_offset_size)
{
    /**
     * data descp: 闭区间表示数据更直观
     */
    printf("[%d,%d]", bitcask_index_offset_size->offset, bitcask_index_offset_size->offset + bitcask_index_offset_size->size);
}

bitcask_single_index_t *bitcask_single_index_t_init(string key, bitcask_single_index_offset_size_t *offset_size)
{
    bitcask_single_index_t *bitcask_index = (bitcask_single_index_t *)malloc(sizeof(bitcask_single_index_t));
    bitcask_index->key = key;
    bitcask_index->offset_size = offset_size;
    return bitcask_index;
}

bitcask_single_index_t *bitcask_single_index_t_print(bitcask_single_index_t *bitcask_index)
{
    printf("%s\n", bitcask_index->key);
    bitcask_single_index_offset_size_t_print(bitcask_index->offset_size);
    printf("\n");
}

// #define MAIN
#ifdef MAIN
int main(void)
{
    data_t *data1 = data_t_init("hello", "world");
    bitcask_index_offset_size_t *os1 = bitcask_index_offset_size_t_init(data1);
    data_t_print(data1);
    bitcask_index_offset_size_t_print(os1);
    return 0;
}

#endif /* BITCASK_H_ */

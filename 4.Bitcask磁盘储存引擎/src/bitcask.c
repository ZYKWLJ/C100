#include "../include/include.h"

#include <stdio.h>
typedef char *string;

data_t *data_t_init(string key, string value)
{
    data_t *data = (data_t *)malloc(sizeof(data_t));
    data->key = key;
    data->value = value;
    data->size = strlen(value);
    return data;
}

void *data_t_print(data_t *data)
{
    printf("[%s[%s],%d]\n", data->key, data->value, data->size);
}

int offset = 0;

bitcask_index_offset_size_t *bitcask_index_offset_size_t_init(data_t *data)
{
    bitcask_index_offset_size_t *bitcask_index_offset_size = (bitcask_index_offset_size_t *)malloc(sizeof(struct bitcask_index_offset_size_));
    bitcask_index_offset_size->offset = offset;
    bitcask_index_offset_size->size = data->size;
    return bitcask_index_offset_size;
}

bitcask_index_offset_size_t *bitcask_index_offset_size_t_print(bitcask_index_offset_size_t *bitcask_index_offset_size)
{
    /**
     * data descp: 闭区间表示数据更直观
     */
    printf("[%d,%d]", bitcask_index_offset_size->offset, bitcask_index_offset_size->offset + bitcask_index_offset_size->size);
}


// #define MAIN
#ifdef MAIN
int main(void)
{
    data_t *data1 = data_t_init("hello", "world");
    bitcask_index_offset_size_t *os1 = bitcask_index_offset_size_t_init( data1);
    data_t_print(data1);
    bitcask_index_offset_size_t_print(os1);
    return 0;
}

#endif /* BITCASK_H_ */

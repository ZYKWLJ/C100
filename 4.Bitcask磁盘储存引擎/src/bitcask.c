#include "../include/include.h"

#include <stdio.h>
// #include "bitcask.h"
// #include "bitcask.h"
typedef char *string;
int total_data = 0;
data_t *data_t_init(string key, string value)
{
    data_t *data = (data_t *)malloc(sizeof(data_t));
    /**
     * data descp: 注意这里依然是易错点，一定要使用strdup
     */
    data->key = strdup(key);
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
bitcask_index_t *bitcask_index_t_init()
{
    bitcask_index_t *bitcask_index = (bitcask_index_t *)malloc(sizeof(struct bitcask_index_));

    for (int i = 0; i < MAX_DATA_SIZE; i++)
    {
        /**
         * data descp: 每一个槽位都是一个链表
         */
        bitcask_index->map[i] = NULL;
    }
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
    printf("data_total_count=%d\n", total_data);
}
#define MAIN
#ifdef MAIN
int main(void)
{
    bitcask_index_t *bitcask_index = bitcask_index_t_init();
    for (int i = 0; i < 100; i++)
    {
        char key[10];
        sprintf(key, "k-%d", i);
        char value[10];
        sprintf(value, "v-%d", i);
        data_t *data1 = data_t_init(key, value);
        bitcask_single_index_offset_size_t *os1 = bitcask_single_index_offset_size_t_init(data1);
        map_insert(bitcask_index->map, bitcask_single_index_t_init(data1->key, os1), BITCAST_INDEX_OFFSET_SIZE_T);
    }
    bitcask_index_print(bitcask_index);
    return 0;
}

#endif /* BITCASK_H_ */

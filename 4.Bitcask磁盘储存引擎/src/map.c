#include "../include/include.h"
// #include "map.h"
// extern list_t *map[];
/**
 * data descp: 轻量级K-V搜索引擎
 */

/*固定链表数组+链表扩容(key为数字，value为指针)*/
// #define MAX_SIZE_MAP 10000
// void *map[MAX_SIZE_MAP] = {NULL};
/**
 * func descp: 每个字符的码值余下容量即可作为哈希函数
 */
int hash_func(string key)
{
    int index = 0;
    for (int i = 0; key[i]; i++)
    {
        index += (key[i] - '0') > 0 ? (key[i] - '0') : -(key[i] - '0');
        index %= MAX_DATA_SIZE;
    }
    // printf("%s hashfunc:%d\n", key, index);
    return index;
}
// void map_insert(list_t *map[], list_node_type_t list_node_type)
// {

// }
// map_type_data_t *map_type_data_t_init(list_node_type_t list_node_type)
// {
//     map_type_data_t *map_type_data = (map_type_data_t *)malloc(sizeof(map_type_data_t));

//     switch (list_node_type)
//     {
//     case BITCAST_INDEX_OFFSET_SIZE_T:
//         map_type_data->map_data.bitcask_single_index = (bitcask_single_index_t *)malloc(sizeof(bitcask_single_index_t));
//         map_type_data->map_data.bitcask_single_index->offset_size = (bitcask_single_index_offset_size_t *)malloc(sizeof(bitcask_single_index_offset_size_t));
//         break;
//     default:
//         break;
//     }
//     return map_type_data;
// }
void print_map_key(list_t *map[], string key, list_node_type_t list_node_type)
{
    switch (list_node_type)
    {
    case BITCAST_INDEX_OFFSET_SIZE_T:
    {
        list_t *list = (list_t *)map[hash_func(key)];
        // list_node_t *node = list;
        printf("key:%s\n", key);
        printf("value:");
        list_print(list, BITCAST_INDEX_OFFSET_SIZE_T);
        break;
    }

    default:
        break;
    }
}
void map_conflict_list_method(list_t *map[], string key, bitcask_single_index_offset_size_t *offset_size, list_node_type_t list_node_type)
{
    switch (list_node_type)
    {
    case BITCAST_INDEX_OFFSET_SIZE_T:
    {
        /* code */
        list_t *list = map[hash_func(key)];
        // printf("conflicted key:%s\n", key);
        list_append(list, offset_size, BITCAST_INDEX_OFFSET_SIZE_T);
        // printf("conflicted key over:%s\n", key);
        break;
    }

    default:
        break;
    }

    // printf("conflicted insert...\n");
    // printf("origin value have:\n");
    // print_map_key(key, list_node_type);
    // printf("after insert:\n");

    // print_map_key(key, list_node_type);
}

void map_insert(list_t *map[], void *map_data, list_node_type_t list_node_type)
{
    // printf("end1");
    switch (list_node_type)
    {
    case BITCAST_INDEX_OFFSET_SIZE_T:
    {
        int index = hash_func(((bitcask_single_index_t *)map_data)->key);
        // printf("end1.1");
        if (map[index])
        {
            // printf("end1.2");
            map_conflict_list_method(map, ((bitcask_single_index_t *)map_data)->key, ((bitcask_single_index_t *)map_data)->offset_size, list_node_type);
            // printf("end2");
            return;
        }
#if 0
        printf("first insert:\n");
        printf("key:%s\n", map_data->key);
#endif
        list_t *list = list_init();
        list->head = list_node_init(((bitcask_single_index_t *)map_data)->offset_size, BITCAST_INDEX_OFFSET_SIZE_T);
        map[index] = list;
        // printf("end3");
        break;
    }
    default:
        break;
    }
}

// #define MAIN
#ifdef MAIN
int main(void)
{
    data_t *data1 = data_t_init("hello11", "world12");
    data_t *data2 = data_t_init("hello11", "world21");
    bitcask_single_index_offset_size_t *os1 = bitcask_single_index_offset_size_t_init(data1);
    bitcask_single_index_offset_size_t *os2 = bitcask_single_index_offset_size_t_init(data2);
    map_insert(bitcask_single_index_t_init(data1->key, os1), BITCAST_INDEX_OFFSET_SIZE_T);
    map_insert(bitcask_single_index_t_init(data2->key, os2), BITCAST_INDEX_OFFSET_SIZE_T);
    map_insert(bitcask_single_index_t_init(data2->key, os2), BITCAST_INDEX_OFFSET_SIZE_T);
    map_insert(bitcask_single_index_t_init(data2->key, os2), BITCAST_INDEX_OFFSET_SIZE_T);
    map_insert(bitcask_single_index_t_init(data2->key, os2), BITCAST_INDEX_OFFSET_SIZE_T);
    return 0;
}
#endif
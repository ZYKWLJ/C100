#include "../include/include.h"

/**
 * data descp: 轻量级K-V搜索引擎
 */

/*固定链表数组+链表扩容(key为数字，value为指针)*/
#define MAX_SIZE_MAP 10000
void *map[MAX_SIZE_MAP] = {NULL};
/**
 * func descp: 每个字符的码值余下容量即可作为哈希函数
 */
int hash_func(string key)
{
    int index = 0;
    for (int i = 0; key[i]; i++)
    {
        index += (key[i] - '0') > 0 ? (key[i] - '0') : -(key[i] - '0');
        index %= MAX_SIZE_MAP;
    }
    // printf("%s hashfunc:%d\n", key, index);
    return index;
}

void print_map_key(string key)
{
    list_t *list = (list_t *)map[hash_func(key)];
    list_node_t *node = list;
    printf("key:%s\n", key);
    printf("value:");

    list_print(node, BITCAST_INDEX_OFFSET_SIZE_T);
}
void map_conflict_list_method(string key, bitcask_single_index_offset_size_t *offset_size)
{
    printf("conflicted insert...\n");
    printf("origin value have:\n");
    print_map_key(key);
    printf("after insert:\n");
    list_t *list = (list_t *)map[hash_func(key)];
    list_append(list, offset_size, BITCAST_INDEX_OFFSET_SIZE_T);
    print_map_key(key);
}

void map_insert(bitcask_single_index_t *bitcask_index)
{
    int index = hash_func(bitcask_index->key);
    if (map[index])
    {
        map_conflict_list_method(bitcask_index->key, bitcask_index->offset_size);
        return;
    }
    printf("first insert:\n");
    printf("key:%s\n", bitcask_index->key);
    list_t *list = list_init();
    list->head = list_node_init(bitcask_index->offset_size, BITCAST_INDEX_OFFSET_SIZE_T);
    map[index] = list;
}

#define MAIN
#ifdef MAIN
int main(void)
{
    data_t *data1 = data_t_init("hello11", "world12");
    data_t *data2 = data_t_init("hello11", "world21");
    bitcask_single_index_offset_size_t *os1 = bitcask_single_index_offset_size_t_init(data1);
    bitcask_single_index_offset_size_t *os2 = bitcask_single_index_offset_size_t_init(data2);
    map_insert(bitcask_single_index_t_init(data1->key, os1));
    map_insert(bitcask_single_index_t_init(data2->key, os2));
    map_insert(bitcask_single_index_t_init(data2->key, os2));
    map_insert(bitcask_single_index_t_init(data2->key, os2));
    map_insert(bitcask_single_index_t_init(data2->key, os2));
    return 0;
}

#endif
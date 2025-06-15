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
int key_func(string key)
{
    int index = 0;
    for (int i = 0; key[i]; i++)
    {
        index += key[i] - '0';
        index %= MAX_SIZE_MAP;
    }
    return index;
}

void print_map_key(string key){
    list_node_t* node=(list_node_t* )map[key_func(key)];
    printf("%s\n",key);
    while(node){
        printf("%p",node->pointer);
    }
}
void map_conflict_list_method(string key, bitcask_index_offset_size_t *offset_size)
{
    printf("conflicted insert...");
    printf("origin value have:\n");

}

void map_insert(bitcask_index_t *bitcask_index)
{
    if (map[key_func(bitcask_index->key)])
    {
        map_conflict_list_method(bitcask_index->key, bitcask_index->offset_size);
        return;
    }
    map[key_func(bitcask_index->key)] = bitcask_index->offset_size;
}

// #define MAIN
#ifdef MAIN
int main(void)
{

    return 0;
}

#endif
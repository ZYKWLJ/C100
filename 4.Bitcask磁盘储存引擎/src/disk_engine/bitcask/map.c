#include "../../../include/include.h"

/**
 * data descp: 轻量级K-V搜索引擎
 */

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

// #define SHOW_CONFLICT
void map_conflict_list_method(list_t *map[], string key, bitcask_single_index_t *bitcask_single_index, list_node_type_t list_node_type)
{
    switch (list_node_type)
    {
    case BITCAST_INDEX_OFFSET_SIZE_T:
    {
        /* code */
        list_t *list = map[hash_func(key)];

#ifdef SHOW_CONFLICT
        printf("conflicted insert...\n");
        printf("origin value have:\n");
        print_map_key(map, key, list_node_type);

#endif
        list_append(list, key, bitcask_single_index, BITCAST_INDEX_OFFSET_SIZE_T);
        break;
#ifdef SHOW_CONFLICT

        printf("after insert:\n");
        print_map_key(map, key, list_node_type);
#endif
    }

    default:
        break;
    }
}

void map_insert(list_t *map[], void *map_data, list_node_type_t list_node_type)
{
    switch (list_node_type)
    {
    case BITCAST_INDEX_OFFSET_SIZE_T:
    {
        int index = hash_func(((bitcask_single_index_t *)map_data)->key);
        if (map[index])
        {
            /*冲突后，检查key是否一致，一致则覆盖*/
            map_conflict_list_method(map, ((bitcask_single_index_t *)map_data)->key, ((bitcask_single_index_t *)map_data), list_node_type);
            return;
        }
#if 0
#endif
        list_t *list = list_init();
        list->head = list_node_init(((bitcask_single_index_t *)map_data), BITCAST_INDEX_OFFSET_SIZE_T);
        map[index] = list;
        break;
    }
    default:
        break;
    }
}

void map_find(list_t *map[], string key, list_node_type_t list_node_type)
{
    switch (list_node_type)
    {
    case BITCAST_INDEX_OFFSET_SIZE_T:
    {
        int index = hash_func(key);
        if (map[index])
        {
            list_node_t *curr = map[index]->head;
            while (curr)
            {
                if (strcmp(((bitcask_single_index_t *)(curr->pointer))->key, key) == 0)
                {
                    printf("find key data:");
                    list_node_print(curr, BITCAST_INDEX_OFFSET_SIZE_T);
                    // return;
                }
                curr=curr->next;
            }
        }
        else
        {
            printf("Not find key:%s\n", key);
            // return;  
        }
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
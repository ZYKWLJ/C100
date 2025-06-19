#include <stdio.h>
#include "khashmap.h"
#define HASH_COUNT 100
list_t *map[HASH_COUNT];
// 可不可以用随机值作为哈希函数？不可以！

/**
 * func descp: 每个字符的码值余下容量即可作为哈希函数
 */

void map_init(list_t *map[])
{
    for (int i = 0; i < HASH_COUNT; i++)
    {
        map[i] = list_init();
    }
    printf("init over!\n");
}
int hash_func(string key)
{
    int index = 0;
    for (int i = 0; key[i]; i++)
    {
        index += (key[i] - '0') > 0 ? (key[i] - '0') : -(key[i] - '0');
        index %= HASH_COUNT;
    }
    printf("key %s 's hashValue:%d\n", key, index);
    return index;
}

void print_map_key(list_t *map[], string key, Key_type key_type)
{
    int index = hash_func(key);

    list_t *list = map[index];
    if (key_type != list->head->data->key_type)
    {
        return;
    }
    list_print(list);
}

// #define SHOW_CONFLICT
void map_conflict_list_method(list_t *map[], string key, Key_type key_type, list_node_t *list_node)
{
    int index = hash_func(key);
    list_t *list = map[index];
    if (key_type != list->head->data->key_type)
    {
        return;
    }
    list_append(list, list_node);
}

void map_insert(list_t *map[], string key, Key_type key_type, list_node_t *list_node)
{
    int index = hash_func(key);
    list_t *list = map[index];

    if (list->head == NULL)
    {
        list->head = list_node;
    }
    else
    {
        if (key_type != list->head->data->key_type)
        {
            return;
        }
        map_conflict_list_method(map, key, key_type, list_node);
    }
    printf("insert over!\n");
}

void map_find(list_t *map[], string key, Key_type key_type)
{
    int index = hash_func(key);
    list_t *list = map[index];
    if (key_type != list->head->data->key_type)
    {
        return;
    }
    list_search(list, key, key_type);
}

void map_find_show_info(list_t *map[], string key, Key_type key_type)
{
    int index = hash_func(key);
    list_t *list = map[index];
    if (key_type != list->head->data->key_type)
    {
        return;
    }
    list_search_show_info(list, key, key_type);
}

void map_print(list_t *map[])
{
    printf("start to print all data in map\n");
    for (int i = 0; i < HASH_COUNT; i++)
    {
        if (map[i]->head == NULL)
        {
            continue;
        }
        printf("hashIndex:%d\n", i);
        int count = list_print(map[i]);
        printf("\nTotal count:%d\n", count);
        printf("============================================\n\n");
    }
}
#define TEST_MAP
#ifdef TEST_MAP
int main(void)
{
    map_init(map);

#define TEST_MAP_basic
#ifdef TEST_MAP_basic
    map_insert(map, "123", KEY_STRING, list_node_init(data_t_init("123", "one two three", KEY_STRING, VALUE_STRING)));
    map_find_show_info(map, "123", KEY_STRING);
    map_print(map);

#endif

#define TEST_MAP_1000
#ifdef TEST_MAP_1000
    for (int i = 0; i < 1000; i++)
    {
        char key[10];
        char value[10];
        sprintf(key, "key_%d", i);
        sprintf(value, "value_%d", i);
        map_insert(map, key, KEY_STRING, list_node_init(data_t_init(key, value, KEY_STRING, VALUE_STRING)));
    }
    map_print(map);

#endif

    return 0;
}
#endif

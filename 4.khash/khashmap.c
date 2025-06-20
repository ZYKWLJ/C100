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
    // printf("init over!\n");
}
int hash_func(string key)
{
    int index = 0;
    for (int i = 0; key[i]; i++)
    {
        index += (key[i] - '0') > 0 ? (key[i] - '0') : -(key[i] - '0');
        index %= HASH_COUNT;
    }
    // printf("key %s 's hashValue:%d\n", key, index);
    return index;
}

void print_map_key(list_t *map[], string key, Key_type key_type)
{
    int index = hash_func(key);
    list_t *list = map[index];
    list_print(list);
}

// #define SHOW_CONFLICT
void map_conflict_list_method(list_t *map[], string same_hash_key, string conflict_value, Key_type key_type, Value_type value_type)
{
    int index = hash_func(same_hash_key);
    list_t *list = map[index];
    list_append(list, same_hash_key, conflict_value, key_type, value_type);
}

void map_insert(list_t *map[], string key, string value, Key_type key_type, Value_type value_type)
{
    int index = hash_func(key);
    list_t *list = map[index];

    if (list->dummy_head->next == NULL)
    {
        list->dummy_head->next = list_node_init(data_t_init(key, value, key_type, value_type));
        data_t_print(list->dummy_head->next->data);
        printf(",append succeed!\n");
        return;
    }
    else
    {
        map_conflict_list_method(map, key, value, key_type, value_type);
    }
    // printf("insert over!\n");
}

void map_find(list_t *map[], string key, Key_type key_type)
{
    int index = hash_func(key);
    list_t *list = map[index];
    operate_result_t *operate_result = list_search(list, key, key_type);
    if (operate_result->existed == false)
    {
        printf("find failed, ");
        data_t_no_data_key(key, key_type);
        printf("\n");
        return;
    }
    printf("find data:");
    data_t_print(operate_result->list_node->data);
    printf(" succeed!\n");
}

void map_find_show_info(list_t *map[], string key, Key_type key_type)
{
    int index = hash_func(key);
    list_t *list = map[index];
    list_search_show_info(list, key, key_type);
}

void map_delete(list_t *map[], string key, Key_type key_type)
{
    // printf("map delete\n");
    int index = hash_func(key);

    list_t *list = map[index];
    printf("index=%d\n", index);
    operate_result_t *operate_result = list_delete(list, key, key_type);
    // printf("map delete step 2\n");

    if (operate_result->existed == false)
    {
        printf("map delete failed!");
        data_t_no_data_key(key, key_type);
        printf("\n");
    }
    printf("map delete ");
    data_t_print(operate_result->list_node->data);
    printf(" succeed!\n");
}

void map_print(list_t *map[])
{
    int count = 0;
    printf("\n\n============================================\n");
    printf("start to print all data in map\n");
    for (int i = 0; i < HASH_COUNT; i++)
    {
        if (map[i]->dummy_head->next == NULL)
        {
            continue;
        }
        printf("--------------------------------------------");

        printf("khashIndex:%d\n", i);
        count += list_print(map[i]);
    }
    printf("\nTotal khashmap count:%d\n", count);
    printf("============================================\n\n");
}

#define TEST_MAP
#ifdef TEST_MAP
int main(void)
{
    map_init(map);

// #define TEST_MAP_basic
#ifdef TEST_MAP_basic
    map_insert(map, "123", KEY_STRING, list_node_init(data_t_init("123", "one two three", KEY_STRING, VALUE_STRING)));
    map_find_show_info(map, "123", KEY_STRING);
    map_print(map);

#endif

// #define TEST_MAP_1000
#ifdef TEST_MAP_1000
    for (int i = 0; i < 1000; i++)
    {
        char key[10];
        char value[10];
        sprintf(key, "key_%d", i);
        sprintf(value, "value_%d", i);
        map_insert(map, key, value, KEY_STRING, VALUE_STRING);
    }
    map_print(map);

#endif

#define TEST_MAP_DELETE
#ifdef TEST_MAP_DELETE
    for (int i = 0; i < 110; i++)
    {
        char key[10];
        char value[10];
        char value1[10];
        sprintf(key, "key_%d", i);
        sprintf(value, "value_%d", i);
        sprintf(value1, "value_%d", i + 1);

        map_insert(map, key, value, KEY_STRING, VALUE_STRING);
        // map_print(map);
        // map_insert(map, key, value1, KEY_STRING, VALUE_STRING);
        // map_print(map);

        // map_find(map, key, KEY_STRING);
        // map_delete(map, key, KEY_STRING);

        // map_print(map);
        // map_find(map, key, KEY_STRING);
    }
    map_print(map);
#endif

// #define TEST_HASH_TABLE_10
#ifdef TEST_HASH_TABLE_10
    printf("TEST_HASH_TABLE_10\n\n");
    for (int i = 0; i < 10; i++)
    {
        char key[10];
        char value[10];
        sprintf(key, "key_%d", 0);
        sprintf(value, "value_%d", i);
        map_insert(map, key, value, KEY_STRING, VALUE_STRING);
    }
    map_print(map);

#endif
    return 0;
}
#endif

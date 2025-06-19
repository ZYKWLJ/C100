#include "klist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * func descp: 打印节点数据
 */
void list_node_print(list_node_t *list_node)
{
   
    data_t_print(list_node->data);
     printf(",next=%p\n", list_node->next);
}

/**
 * func descp: 节点数据初始化
 */
list_node_t *list_node_init(data_t *data)
{
    list_node_t *list_node = (list_node_t *)malloc(sizeof(struct list_node_));
    list_node->next = NULL;
    list_node->data = data;
    return list_node;
}

/**
 * func descp: 释放节点和节点数据
 */
void list_node_free(list_node_t *list_node)
{
    data_t_free(list_node->data);
    free(list_node);
}

/**
 * func descp:节点判等
 */
bool list_node_equal(list_node_t *list_node, string key_target, Key_type key_type)
{
    /**
     * func descp: 先判断是不是相等的数据类型
     */
    if (list_node->data->key_type != key_type)
    {
        return false;
    }
    /**
     * data descp: 数据类型相等了，再一次判断是哪一种数据类型
     */
    switch (key_type)
    {
    case KEY_STRING:
        return strcmp(list_node->data->key.str_key, key_target) == 0;
        break;
    case KEY_INT:
    {
        int key = atoi(key_target);
        return (list_node->data->key.int_key - key) == 0;
    }
    break;
    default:
        break;
    }
}
/**
 * func descp: 链表初始化
 */
list_t *list_init()
{
    list_t *list = (list_t *)malloc(sizeof(struct list_));
    list->dummy_head = list_node_init(NULL);
    // list->dummy_head->data = NULL;
    return list;
}

/**
 * func descp: 打印链表
 */
int list_print(list_t *list)
{
    int count = 0;
    list_node_t *curr = list->dummy_head->next;
    while (curr)
    {
        list_node_print(curr);
        curr = curr->next;
        count++;
    }
    printf("list_node count :%d\n", count);
    printf("============================================\n\n");
    return count;
}

operate_result_t *operate_result_init()
{
    operate_result_t *operate_result = (operate_result_t *)malloc(sizeof(struct search_result_));
    operate_result->list_node = NULL;
    operate_result->existed = false;
    return operate_result;
}

/**
 * func descp: 查找链表中的数据
 */
operate_result_t *list_search(list_t *list, string key_target, Key_type key_type)
{
    operate_result_t *search_result = operate_result_init();
    // printf("1");
    if (list->dummy_head->next == NULL)
    {
        return search_result;
    }
    // printf("2");
    list_node_t *curr = list->dummy_head->next;
    switch (key_type)
    {
    case KEY_STRING:
    {
        while (curr)
        {
            if (list_node_equal(curr, key_target, key_type))
            {
                // printf("find data:\n");
                // data_t_print(curr->data);
                search_result->list_node = curr;
                search_result->existed = true;
                return search_result;
            }
            curr = curr->next;
        }
    }
    /* code */
    break;
    case KEY_INT:
    {
        while (curr)
        {
            if (list_node_equal(curr, key_target, key_type))
            {
                // printf("find data:\n");
                // data_t_print(curr->data);
                search_result->list_node = curr;
                search_result->existed = true;
                return search_result;
            }
            curr = curr->next;
        }
    }
    /* code */
    break;
    default:
        break;
    }
    return search_result;
}

/**
 * func descp: 查找链表中的数据，并打印结果
 */
void list_search_show_info(list_t *list, string key_target, Key_type key_type)
{
    operate_result_t *search_result = list_search(list, key_target, key_type);
    if (search_result->existed)
    {
        printf("find data of key %s\n", key_target);
        data_t_print(search_result->list_node->data);
    }
    else
    {
        printf("not find data of key %s\n\n", key_target);
    }
}

/**
 * func descp: 更新函数，节点的值跟新（值的数据类型可以变化）,这里值也要做参数，因为类型变了也是变了@！
 */
void list_node_update(list_node_t *list_node, string key_target, string new_value, Key_type key_type, Value_type value_type)
{
    switch (list_node->data->value_type)
    {
    case VALUE_STRING:
    {
        list_node->data->value.str_value = new_value;
        return;
    }
    case VALUE_INT:
    {
        list_node->data->value.int_value = atoi(new_value);
        return;
    }
    case VALUE_NONE:
    {
        list_node->data->value.int_value = atoi(new_value);
        return;
    }
    default:
        break;
    }
}

/**
 * func descp: 判存函数=查找函数。追加前应该判断相同的key是否存在，即是不是需要更新，而不是追加。如果存在，就返回这个节点。
 */

/*这里追加是无脑追加，注意防止相同的key出现，否则这就是相等了！就需要覆盖数据，所以一定会遍历一次判存*/
/**
 * func descp: 追加链表节点(不区分value类型，只区分key类型)
 */

void list_append(list_t *list, string key_target, string new_value, Key_type key_type, Value_type value_type)
{
    // printf(" append start!\n");

    operate_result_t *search_result = list_search(list, key_target, key_type);
    // printf(" 1\n");

    /**
     * func descp: 存在数据，那么就是跟新，不是追加
     */
    if (search_result->existed)
    {
        data_t_print_key(key_target, key_type);
        printf("existed, now update.\n");
        list_node_update(search_result->list_node, key_target, new_value, key_type, value_type);
        return;
    }
    // printf(" 2\n");

    /**
     * func descp: 不存在数据，就是追加
     */
    // printf("No data which key is %s\n", key_target);
    list_node_t *curr = list->dummy_head->next;
    list_node_t *list_node = list_node_init(data_t_init(key_target, new_value, key_type, value_type));
    list->dummy_head->next = list_node;
    list_node->next = curr;
    data_t_print(list_node->data);
    printf(",append succeed!\n");
}

/**
 * func descp: 删除链表节点
 */

operate_result_t *list_delete(list_t *list, string key_target, Key_type key_type)
{
    operate_result_t *search_result = list_search(list, key_target, key_type);
    if (search_result->existed == false)
    {
        printf("Data of the key is %s is not existed.\n", key_target);
    }
    list_node_t *curr = list->dummy_head->next;
    list_node_t *pre = list->dummy_head;
    switch (key_type)
    {

    case KEY_STRING:
    {
        while (curr)
        {
            if (strcmp(curr->data->key.str_key, key_target) == 0)
            {
                pre->next = curr->next;
                search_result->existed = true;
                search_result->list_node = curr;
                list_node_free(curr);
                return search_result;
            }
            pre = curr;
            curr = curr->next;
        }
    }
    /* code */
    break;
    case KEY_INT:
    {
        int key_target_ = atoi(key_target);
        while (curr)
        {
            if (curr->data->key.int_key == key_target_)
            {
                pre->next = curr->next;
                search_result->existed = true;
                search_result->list_node = curr;
                list_node_free(curr);
                return search_result;
            }
            pre = curr;
            curr = curr->next;
        }
    }
    /* code */
    break;
    default:
        break;
    }
    printf("No data which key is %s\n", key_target);
}

/**
 * func descp: 查找链表中的数据，并打印结果
 */
void list_delete_show_info(list_t *list, string key_target, Key_type key_type)
{
    operate_result_t *delete_result = list_delete(list, key_target, key_type);
    if (delete_result->existed)
    {
        printf("delete data of key %s succeed!\n ", key_target);
        data_t_print(delete_result->list_node->data);
    }
    else
    {
        printf("delete failed,not find data of key %s\n\n", key_target);
    }
}

#define TEST_LIST
#ifdef TEST_LIST
int main(void)
{

    list_t *list = list_init();
// #define TEST_APPEND
#ifdef TEST_APPEND

    list_search(list, "1", KEY_INT) ? printf("find data 1\n") : printf("not find data 1\n");
    list_append(list, list_node_init(data_t_init("1", "3", KEY_INT, VALUE_STRING)));
    list_append(list, list_node_init(data_t_init("2", "3", KEY_INT, VALUE_STRING)));
    printf("start to print all list data:\n");
    list_print(list);
    list_search_show_info(list, "1", KEY_STRING);
    list_search_show_info(list, "2", KEY_INT);
#endif
// #define TEST_APPEND_10000
#ifdef TEST_APPEND_10000
    for (int i = 9950; i < 10000; i++)
    {
        char key[20];
        char value[20];
        sprintf(key, "%d", i);
        sprintf(value, "value_%d", i);
        list_append(list, list_node_init(data_t_init(key, value, KEY_INT, VALUE_STRING)));
    }
    list_print(list);

#endif

// #define TEST_DELETE
#ifdef TEST_DELETE

    list_append(list, "hello", "world", KEY_STRING, VALUE_STRING);
    list_append(list, "hello1", "world1", KEY_STRING, VALUE_STRING);

    list_print(list);
    list_delete(list, "hello1", KEY_STRING);
    list_print(list);
    list_delete(list, "hello", KEY_STRING);
    list_print(list);

#endif


#define TEST_DELETE_DIFFENT_KIND
#ifdef TEST_DELETE_DIFFENT_KIND

    list_append(list, "1", "world1", KEY_STRING, VALUE_STRING);
    list_append(list, "1", "world1", KEY_INT, VALUE_STRING);
    list_print(list);

    list_append(list, "1", "world122", KEY_INT, VALUE_STRING);
    list_print(list);

#endif
    return 0;
}

#endif

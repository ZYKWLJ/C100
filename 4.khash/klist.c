#include "klist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * func descp: 打印节点数据
 */
void list_node_print(list_node_t *list_node)
{
    printf("next=%p\n", list_node->next);
    data_t_print(list_node->data);
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
 * func descp: 链表初始化
 */
list_t *list_init()
{
    list_t *list = (list_t *)malloc(sizeof(struct list_));
    list->head = NULL;
    return list;
}

/**
 * func descp: 打印链表
 */
void list_print(list_t *list)
{
    list_node_t *curr = list->head;
    while (curr)
    {
        list_node_print(curr);
        curr = curr->next;
    }
}

/**
 * func descp: 查找链表中的数据
 */
search_result_t *list_search(list_t *list, string key_target, Key_type key_type)
{
    search_result_t *search_result = (search_result_t *)malloc(sizeof(struct search_result_));
    search_result->data = NULL;
    search_result->existed = false;
    // printf("1");
    if (list->head == NULL)
    {
        return search_result;
    }
    // printf("2");

    list_node_t *curr = list->head;
    if (curr->data->key_type != key_type)
    {
        // printf("Key type is not matched!\n");
        return search_result;
    }
    switch (key_type)
    {
    case KEY_STRING:
    {
        while (curr)
        {
            if (strcmp(curr->data->key.str_key, key_target) == 0)
            {
                // printf("find data:\n");
                // data_t_print(curr->data);
                search_result->data = curr->data;
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
        int key_target_ = atoi(key_target);
        while (curr)
        {
            if (curr->data->key.int_key == key_target_)
            {
                // printf("find data:\n");
                // data_t_print(curr->data);
                search_result->data = curr->data;
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
}

/**
 * func descp: 追加链表节点
 */
void list_append(list_t *list, list_node_t *list_node)
{
    /**
     * data descp: 注意隐含条件是一定有一个head节点的！list初始化的时候就解决了！
     */
    list_node_t *curr = list->head;
    list->head = list_node;
    list_node->next = curr;
}
void list_search_show_info(list_t *list, string key_target, Key_type key_type)
{
    search_result_t *search_result = list_search(list, key_target, key_type);
    if (search_result->existed)
    {
        printf("find data of key %s\n", key_target);
        data_t_print(search_result->data);
    }
    else
    {
        printf("not find data of key %s\n\n", key_target);
    }
}
// #define TEST_LIST
#ifdef TEST_LIST
int main(void)
{

    list_t *list = list_init();
    list_search(list, "1", KEY_INT) ? printf("find data 1\n") : printf("not find data 1\n");
    list_append(list, list_node_init(data_t_init("1", "3", KEY_INT, VALUE_STRING)));
    list_append(list, list_node_init(data_t_init("2", "3", KEY_INT, VALUE_STRING)));
    printf("start to print all list data:\n");
    list_print(list);
    list_search_show_info(list, "1", KEY_STRING);
    list_search_show_info(list, "2", KEY_INT);
    return 0;
}

#endif

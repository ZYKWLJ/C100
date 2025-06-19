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
    operate_result->data = NULL;
    operate_result->existed = false;
    return operate_result;
}

/**
 * func descp: 查找链表中的数据
 */
operate_result_t *list_delete(list_t *list, string key_target, Key_type key_type)
{
    operate_result_t *search_result = operate_result_init();
    // printf("1");
    if (list->dummy_head->next == NULL)
    {
        return search_result;
    }
    // printf("2");

    list_node_t *curr = list->dummy_head->next;
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
 * func descp: 查找链表中的数据，并打印结果
 */
void list_search_show_info(list_t *list, string key_target, Key_type key_type)
{
    operate_result_t *search_result = list_delete(list, key_target, key_type);
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

/*注意，这里有个易错点，int和string的key值会可能映射到统一的index下，这时，就要比较type和key了！*/
/**
 * func descp: 追加链表节点(不区分value类型，只区分key类型)
 */
void list_append(list_t *list, list_node_t *list_node)
{
    operate_result_t *search_result = (operate_result_t *)malloc(sizeof(struct search_result_));
    search_result->data = NULL;
    search_result->existed = false;
    list_node_t *curr = list->dummy_head->next;
    if (curr == NULL || curr->data->key_type != list_node->data->key_type)
    {
        printf("append %s\n");
        return;
    }
    list_node_t *pre = list->dummy_head; /*虚拟头结点*/
    switch (key_type)
    {

    case KEY_STRING:
    {
        while (curr)
        {
            if (strcmp(curr->data->key.str_key, key_target) == 0)
            {
                pre->next = curr->next;
                printf("data");
                list_node_print(curr->data);
                printf("succeed!");
                list_node_free(curr);
                return;
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
                list_node_free(curr);
                return;
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

    /**
     * data descp: 注意隐含条件是一定有一个head节点的！list初始化的时候就解决了！
     */
    list_node_t *curr = list->dummy_head->next;
    list->dummy_head->next = list_node;
    list_node->next = curr;
}

/**
 * func descp: 删除链表节点
 */

operate_result_t *list_delete(list_t *list, string key_target, Key_type key_type)
{
    operate_result_t *search_result = (operate_result_t *)malloc(sizeof(struct search_result_));
    search_result->data = NULL;
    search_result->existed = false;
    list_node_t *curr = list->dummy_head->next;
    if (curr == NULL || curr->data->key_type != key_type)
    {
        printf("No data which key is %s\n", key_target);
        return;
    }
    list_node_t *pre = list->dummy_head; /*虚拟头结点*/
    switch (key_type)
    {

    case KEY_STRING:
    {
        while (curr)
        {
            if (strcmp(curr->data->key.str_key, key_target) == 0)
            {
                pre->next = curr->next;
                printf("data");
                list_node_print(curr->data);
                printf("succeed!");
                list_node_free(curr);
                return;
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
                list_node_free(curr);
                return;
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
        printf("find data of key %s\n", key_target);
        data_t_print(delete_result->data);
    }
    else
    {
        printf("not find data of key %s\n\n", key_target);
    }
}

/**
 * func descp: 更新链表节点数据
 */
void list_update(list_t *list, string key_target, string new_value, Key_type key_type)
{
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

#define TEST_DELETE
#ifdef TEST_DELETE

    list_append(list, list_node_init(data_t_init("hello", "world", KEY_STRING, VALUE_STRING)));
    list_append(list, list_node_init(data_t_init("hello1", "world1", KEY_STRING, VALUE_STRING)));

    // list_print(list);
    list_delete(list, "hello2", KEY_STRING);
    // list_print(list);
    list_delete(list, "hello1", KEY_STRING);
    // list_print(list);
#endif
    return 0;
}

#endif

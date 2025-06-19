#ifndef LIST_H_
#define LIST_H_
#include "kdata.h"
#include <stdbool.h>

typedef char *string;

/**
 * data descp: 这里还要考虑链表的数据结构是key还是K-V(解决方案：都使用k-v，如果v为null则默认为集合结构,负责为表结构)，其次，考虑是string还是int
 */

/**
/*哈希槽，即key的个数*/
#define MAX_DATA_SIZE 100

/**
 * data descp: 链表节点——存放void指针
 */
typedef struct list_node_
{
    struct list_node_ *next;
    data_t *data;
} list_node_t;

/**
 * func descp: 打印节点数据
 */
void list_node_print(list_node_t *list_node);

/**
 * func descp: 节点数据初始化
 */
list_node_t *list_node_init(data_t *data);

/**
 * func descp: 释放节点和节点数据
 */
void list_node_free(list_node_t *node);

/**
 * data descp: 链表的定义——仅仅头结点就好了！
 */
typedef struct list_
{
    list_node_t *dummy_head;
} list_t;

/**
 * func descp: 打印链表并返回该哈希值下的数据的个数
 */
int list_print(list_t *list);

/**
 * func descp: 链表初始化
 */
list_t *list_init();

/**
 * func descp: 查找并返回链表中的数据的结构体
 */
typedef struct search_result_
{
    bool existed;
    data_t *data;
} operate_result_t;
/**
 * func descp:操作结果初始化
 */
operate_result_t *operate_result_init();
/**
 * func descp: 查找链表中的数据，不打印
 */
operate_result_t *list_delete(list_t *list, string key, Key_type key_type);

/**
 * func descp: 查找链表中的数据，并打印结果
 */
void list_search_show_info(list_t *list, string key_target, Key_type key_type);

/**
 * func descp: 追加链表节点
 */
void list_append(list_t *list, list_node_t *list_node);

/**
 * func descp: 删除链表节点
 */

void list_delete(list_t *list, string key_target, Key_type key_type);

/**
 * func descp: 更新链表节点数据
 */
void list_update(list_t *list, string key_target, string new_value, Key_type key_type);

#endif /* LIST_H_ */

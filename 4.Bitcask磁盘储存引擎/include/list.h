#ifndef LIST_H_
#define LIST_H_

#include "include.h"
#include <stdbool.h>
typedef enum list_node_type_
{
    BITCAST_INDEX_OFFSET_SIZE_T,
} list_node_type_t;
/**
 * data descp: 存放任何指针的链表节点
 */
typedef struct list_node_
{
    struct list_node_ *next;
    void *pointer; /*存放任何数据的指针*/
} list_node_t;

void list_node_print(list_node_t *node, list_node_type_t list_node_type);


void list_node_free(list_node_t *node);
/**
 * data descp: 链表的定义就是头结点就好了！
 */
typedef struct list_
{
    list_node_t *head;
    // struct list_node_ *tail;
} list_t;

 void list_print(list_t *list, list_node_type_t list_node_type);

list_t *list_init();

// bool list_search(list_t *head, int target);

// void list_prepend(list_t *head, int prepend_pointer);

#if 0
int main(void)
{

    list *head = list_init();
    list_node *pre = list_node_init(0);
    head->head = pre;
    for (int i = 1; i < 10; i++)
    {
        list_node *curr = list_node_init(i + 1);
        pre->next = curr;
        pre = curr;
    }
    list_print(head);
    list_search(head, 101)
        ? printf("find %d", 101)
        : printf("not find %d", 101);
    list_prepend(head, 20);
    list_print(head);
    return 0;
}

#endif

#endif /* LIST_H_ */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct list_node_
{
    struct list_node_ *next;
    int val;
} list_node_t;

void list_node_print(list_node_t *node)
{
    /*
    printf("node addr:%p\n", node);
    printf("node next addr:%p\n", node->next);
    printf("node val:%d\n", node->val);
    printf("\n");
    */
    printf("%d[%p]-[%p]", node->val, node, node->next);
}
list_node_t *list_node_init(int val)
{
    list_node_t *node = (list_node_t *)malloc(sizeof(struct list_node_));
    node->next = NULL;
    node->val = val;
    // printf("init node val:%d\n", node->val);
    return node;
}

void list_node_free(list_node_t *node)
{
    free(node->next);
    free(node);
    printf("free node\n");
}

/**
 * data descp: 链表的定义就是头结点就好了！
 */
typedef struct list_
{
    struct list_node_ *head;

} list_t;

void list_print(list_t *node)
{
    int count = 0;
    while (node->head)
    {
        list_node_print(node->head);
        if (node->head->next)
        {
            printf("->");
        }
        if ((count + 1) % 4 == 0)
        {
            printf("\n");
        }
        count++;
        node->head = node->head->next;
    }
}
list_t *list_init()
{
    list_t *node = (list_t *)malloc(sizeof(struct list_));
    node->head = NULL;
    return node;
}

bool list_search(list_t *head, int target)
{
    while (head->head)
    {
        if (head->head->val == target)
        {
            return true;
        }
        head->head = head->head->next;
    }
    return false;
}

void list_prepend(list_t *head, int prepend_val)
{
    list_node_t *node = list_node_init(prepend_val);
    list_node_t *next = head->head->next;
    node->next = next;
    head->head->next = node;
}

int main(void)
{

    list_t *head = list_init();
    list_node_t *pre = list_node_init(0);
    head->head = pre;
    for (int i = 1; i < 10; i++)
    {
        list_node_t *curr = list_node_init(i + 1);
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
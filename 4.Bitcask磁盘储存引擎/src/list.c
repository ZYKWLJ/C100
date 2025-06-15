#include "../include/include.h"


/**
 * data descp: 存放指针的链表节点
 */
typedef struct list_node_
{
    struct list_node_ *next;
    void *pointer; /*存放任何数据的指针*/
} list_node_t;

void list_node_print(list_node_t *node)
{
    /*
    printf("node addr:%p\n", node);
    printf("node next addr:%p\n", node->next);
    printf("node pointer:%d\n", node->pointer);
    printf("\n");
    */
    printf("%p[%p]-[%p]", node->pointer, node, node->next);
}
list_node_t *list_node_init(int pointer)
{
    list_node_t *node = (list_node_t *)malloc(sizeof(struct list_node_));
    node->next = NULL;
    node->pointer = pointer;
    // printf("init node pointer:%d\n", node->pointer);
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

} list;

void list_print(list *node)
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
list *list_init()
{
    list *node = (list *)malloc(sizeof(struct list_));
    node->head = NULL;
    return node;
}

bool list_search(list *head, int target)
{
    while (head->head)
    {
        if (head->head->pointer == target)
        {
            return true;
        }
        head->head = head->head->next;
    }
    return false;
}

void list_prepend(list *head, int prepend_pointer)
{
    list_node_t *node = list_node_init(prepend_pointer);
    list_node_t *next = head->head->next;
    node->next = next;
    head->head->next = node;
}

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
#include "../include/include.h"
extern int offset;

void list_node_print(list_node_t *list_node, list_node_type_t list_node_type)
{
    switch (list_node_type)
    {
    case BITCAST_INDEX_OFFSET_SIZE_T:
        bitcask_index_offset_size_t_print((bitcask_index_offset_size_t *)list_node->pointer);
        break;
    default:
        break;
    }
}
list_node_t *list_node_init(void *pointer, list_node_type_t list_node_type)
{
    list_node_t *node = (list_node_t *)malloc(sizeof(struct list_node_));
    switch (list_node_type)
    {
    case BITCAST_INDEX_OFFSET_SIZE_T:
    {
        node->next = NULL;
        node->pointer = (bitcask_index_offset_size_t *)pointer;
        // printf("init bitcask_index_offset_size_t node :\n"); /* code */
        // bitcask_index_offset_size_t_print((bitcask_index_offset_size_t *)node->pointer);
        break;
    }
    default:
        break;
    }

    return node;
}

void list_node_free(list_node_t *node)
{
    free(node->next);
    free(node);
    printf("free node\n");
}

void list_print(list_t *list, list_node_type_t list_node_type)
{
    if (list->head == NULL)
    {
        printf("list is empty\n");
        return;
    }
    int count = 0;
    list_node_t *node = list->head;
    switch (list_node_type)
    {
    case BITCAST_INDEX_OFFSET_SIZE_T:
    {
        printf("list_node_type_t:BITCAST_INDEX_OFFSET_SIZE_T:\n");
        while (node)
        {

            list_node_print(node, list_node_type);
            if (node->next)
            {
                printf("->");
            }
            if ((count + 1) % 4 == 0)
            {
                printf("\n");
            }
            count++;
            node = node->next;
        }
        printf("\n");
    }
    /* code */
    break;

    default:
        break;
    }
}

list_t *list_init()
{

    list_t *node = (list_t *)malloc(sizeof(struct list_));
    node->head = NULL;
    // node->tail = node->head;
    return node;
}

// bool list_search(list_t *head, int target)
// {
//     while (head->head)
//     {
//         if (head->head->pointer == target)
//         {
//             return true;
//         }
//         head->head = head->head->next;
//     }
//     return false;
// }

void list_append(list_t *list, void *prepend_pointer, list_node_type_t list_node_type)
{
    switch (list_node_type)
    {
    case BITCAST_INDEX_OFFSET_SIZE_T:
    {
        list_node_t *node = (list_node_t *)list_node_init(prepend_pointer, list_node_type);
        list_node_t *curr = list->head;
        while (curr->next)
        {
            curr = curr->next;
        }
        curr->next = node;
        break;
    }
    default:
        break;
    }

    // node->next = NULL;/*有没有无所谓，初始化中有了*/
}
#define MAIN
#ifdef MAIN
int main(void)
{
    data_t *data1 = data_t_init("hello11111", "world1");
    data_t *data2 = data_t_init("hello2", "world2");
    bitcask_index_offset_size_t *os1 = bitcask_index_offset_size_t_init(data1);
    bitcask_index_offset_size_t *os2 = bitcask_index_offset_size_t_init(data2);
    data_t_print(data1);
    bitcask_index_offset_size_t_print(os1);
    list_t *list = list_init();
    list->head = list_node_init(os1, BITCAST_INDEX_OFFSET_SIZE_T);
    // list->head = list_node_init(os2, BITCAST_INDEX_OFFSET_SIZE_T);
    list_print(list, BITCAST_INDEX_OFFSET_SIZE_T);
    list_append(list, os2, BITCAST_INDEX_OFFSET_SIZE_T);
    list_append(list, os2, BITCAST_INDEX_OFFSET_SIZE_T);
    list_append(list, os2, BITCAST_INDEX_OFFSET_SIZE_T);
    list_append(list, os2, BITCAST_INDEX_OFFSET_SIZE_T);
    list_append(list, os2, BITCAST_INDEX_OFFSET_SIZE_T);
    list_append(list, os2, BITCAST_INDEX_OFFSET_SIZE_T);
    list_append(list, os2, BITCAST_INDEX_OFFSET_SIZE_T);
    list_append(list, os2, BITCAST_INDEX_OFFSET_SIZE_T);
    list_print(list, BITCAST_INDEX_OFFSET_SIZE_T);

    return 0;
}
#endif

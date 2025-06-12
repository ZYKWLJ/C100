#include "../../include/include.h"
#define MAX_LINE_LENGTH 1024

void save_data_to_disk(char *file_path, skiplist *skiplist)
{
    if (!file_path || !skiplist || !skiplist->head)
    {
        printf("Invalid parameters\n");
        return;
    }

    FILE *fp = fopen(file_path, "w");
    if (fp == NULL)
    {
        printf("Failed to open file for writing: %s\n", file_path);
        return;
    }
    skiplist_node *curr = skiplist->head->forward[0];
    /*仅仅只存最后一层就好了！*/
    for (; curr;)
    {
        fprintf(fp, "%s:%s\n", curr->key, curr->val);
        curr = curr->forward[0];
    }
}

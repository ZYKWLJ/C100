#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX_LEVEL 32
#define P_FACTOR RAND_MAX >> 2
#define HEAD -1
// 结构体命名改为下划线风格
typedef struct skiplist_node
{
    int val;
    int max_level;
    struct skiplist_node **forward; // 前向数组
} skiplist_node;

typedef struct
{
    skiplist_node *head;
    int level;
} skiplist;

void print_skip_list(skiplist *obj)
{
    if (obj == NULL)
    {
        printf("NULL\n");
        return;
    }
    skiplist_node *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--)
    {
        printf("Level %d:    ", i);
        curr = obj->head;
        while (curr)
        {
            printf("%d", curr->val);
            if (curr->forward[i])
            {
                printf(" -> ");
            }
            curr = curr->forward[i];
        }
        printf("\n");
    }
    printf("\n");
}

// 函数命名改为下划线风格
skiplist_node *skiplist_node_create(int val, int max_level)
{
    skiplist_node *obj = (skiplist_node *)malloc(sizeof(skiplist_node));
    obj->val = val;
    obj->max_level = max_level;
    obj->forward = (skiplist_node **)malloc(sizeof(skiplist_node *) * max_level);
    for (int i = 0; i < max_level; i++)
    {
        obj->forward[i] = NULL;
    }
    return obj;
}

void skiplist_node_free(skiplist_node *obj)
{
    if (obj->forward)
    {
        free(obj->forward);
        obj->forward = NULL;
        obj->max_level = 0;
    }
    free(obj);
}

skiplist *skiplist_create()
{
    skiplist *obj = (skiplist *)malloc(sizeof(skiplist));
    obj->head = skiplist_node_create(HEAD, MAX_LEVEL);
    obj->level = 0;
    srand(time(NULL));
    return obj;
}

static inline int random_level()
{
    int lv = 1;
    /* 随机生成 lv */
    while (rand() % 2 && lv < MAX_LEVEL)
    {
        lv++;
    }
    return lv;
}

bool skiplist_search(skiplist *obj, int target)
{
    print_skip_list(obj); // 打印跳表结构
    skiplist_node *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--)
    {
        /* 找到第 i 层小于且最接近 target 的元素*/
        while (curr->forward[i] && curr->forward[i]->val < target)
        {
            curr = curr->forward[i];
        }
    }
    curr = curr->forward[0];
    /* 检测当前元素的值是否等于 target */
    if (curr && curr->val == target)
    {
        printf("value %d existed!\n", target);
        return true;
    }
    printf("value %d not existed!\n", target);
    return false;
}

void skiplist_insert(skiplist *obj, int num)
{
    skiplist_node *update[MAX_LEVEL] = {NULL};
    skiplist_node *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--)
    {
        /* 找到第 i 层小于且最接近 num 的元素*/
        while (curr->forward[i] && curr->forward[i]->val < num)
        {
            curr = curr->forward[i];
        }
        update[i] = curr;
    }
    int lv = random_level();
    if (lv > obj->level)
    {
        for (int i = obj->level; i < lv; i++)
        {
            update[i] = obj->head;
        }
        obj->level = lv;
    }
    skiplist_node *new_node = skiplist_node_create(num, lv);
    for (int i = 0; i < lv; i++)
    {
        /* 对第 i 层的状态进行更新，将当前元素的 forward 指向新的节点 */
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }
    printf("Insert value %d successd!\n", num);
    // print_skip_list(obj); // 打印跳表结构
}

bool skiplist_erase(skiplist *obj, int num)
{
    skiplist_node *update[MAX_LEVEL] = {NULL};
    skiplist_node *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--)
    {
        /* 找到第 i 层小于且最接近 num 的元素*/
        while (curr->forward[i] && curr->forward[i]->val < num)
        {
            curr = curr->forward[i];
        }
        update[i] = curr;
    }
    /*跳到最后一层来开始更新!*/
    curr = curr->forward[0];
    /* 如果值不存在则返回 false */
    if (!curr || curr->val != num)
    {
        printf("delete faided! value %d not existed!\n", num);
        return false;
    }
    /*从底层开始更新*/
    for (int i = 0; i < obj->level; i++)
    {
        /*遇到第一个更新数组不是cur，那么说明该元素在该层及以上都不会出现了，直接break即可!*/
        if (update[i]->forward[i] != curr)
        {
            break;
        }
        /* 对第 i 层的状态进行更新，将 forward 指向被删除节点的下一跳 */
        update[i]->forward[i] = curr->forward[i];
    }
    skiplist_node_free(curr); /*回收删除了的节点*/
    /* 更新当前的 level,很简单，直到head节点后面的next节点不为NULL即可 */
    while (obj->level > 1 && obj->head->forward[obj->level - 1] == NULL)
    {
        obj->level--;
    }
    print_skip_list(obj);
    return true;
}

void skiplist_free(skiplist *obj)
{
    for (skiplist_node *curr = obj->head; curr;)
    {
        skiplist_node *prev = curr;
        curr = curr->forward[0];
        skiplist_node_free(prev);
    }
    free(obj);
}

// 主函数保持逻辑不变，仅函数调用名对应修改
int main(void)
{
    skiplist *obj = skiplist_create();
    printf("Created skip list\n");
#if 0
    printf("Searching for 100 in empty list: %s\n",
           skiplist_search(obj, 100) ? "PASS" : "FAIL");

    skiplist_insert(obj, 50);
    skiplist_insert(obj, 30);
    skiplist_insert(obj, 70);
    skiplist_insert(obj, 20);
    skiplist_insert(obj, 40);
    skiplist_insert(obj, 60);
    skiplist_insert(obj, 80);
    printf("Added elements: 20, 30, 40, 50, 60, 70, 80\n");

    printf("Searching for 30: %s\n",
           skiplist_search(obj, 30) ? "PASS" : "FAIL");
    printf("Searching for 50: %s\n",
           skiplist_search(obj, 50) ? "PASS" : "FAIL");
    printf("Searching for 80: %s\n",
           skiplist_search(obj, 80) ? "PASS" : "FAIL");

    printf("Searching for 10: %s\n",
           skiplist_search(obj, 10) ? "FAIL" : "PASS");
    printf("Searching for 90: %s\n",
           skiplist_search(obj, 90) ? "FAIL" : "PASS");

    printf("Erasing 30: %s\n",
           skiplist_erase(obj, 30) ? "PASS" : "FAIL");
    printf("Searching for 30 after erase: %s\n",
           skiplist_search(obj, 30) ? "FAIL" : "PASS");

    printf("Erasing 80: %s\n",
           skiplist_erase(obj, 80) ? "PASS" : "FAIL");
    printf("Searching for 80 after erase: %s\n",
           skiplist_search(obj, 80) ? "FAIL" : "PASS");

    printf("Erasing 100: %s\n",
           skiplist_erase(obj, 100) ? "FAIL" : "PASS");

    skiplist_insert(obj, 50);
    printf("Added duplicate 50. Searching: %s\n",
           skiplist_search(obj, 50) ? "PASS" : "FAIL");

    printf("Erasing 20: %s\n",
           skiplist_erase(obj, 20) ? "PASS" : "FAIL");
    printf("Erasing 40: %s\n",
           skiplist_erase(obj, 40) ? "PASS" : "FAIL");
    printf("Erasing 50: %s\n",
           skiplist_erase(obj, 50) ? "PASS" : "FAIL");
    printf("Erasing 60: %s\n",
           skiplist_erase(obj, 60) ? "PASS" : "FAIL");
    printf("Erasing 70: %s\n",
           skiplist_erase(obj, 70) ? "PASS" : "FAIL");

    printf("Searching for 50 in empty list: %s\n",
           skiplist_search(obj, 50) ? "FAIL" : "PASS");

    skiplist_free(obj);
    printf("Freed skip list\n");

    printf("All test cases completed.\n");

#endif

#if 1

    for (int i = 0; i < 10000; i++)
    {
        skiplist_insert(obj, i);
    }
#endif
    print_skip_list(obj);
    return 0;
}

/*最重要的一定就是，实际上针对某一个节点时，可以忽略下面的所有节点，如下：*/


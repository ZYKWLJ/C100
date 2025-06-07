#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int MAX_LEVEL = 32;
const int P_FACTOR = RAND_MAX >> 2;

// 结构体命名改为下划线风格
typedef struct skiplist_node {
    int val;
    int max_level;
    struct skiplist_node **forward; // 前向数组
} skiplist_node;

typedef struct {
    skiplist_node *head;
    int level;
} skiplist;

void print_skip_list() {}

// 函数命名改为下划线风格
skiplist_node *skiplist_node_create(int val, int max_level) {
    skiplist_node *obj = (skiplist_node *)malloc(sizeof(skiplist_node));
    obj->val = val;
    obj->max_level = max_level;
    obj->forward = (skiplist_node **)malloc(sizeof(skiplist_node *) * max_level);
    for (int i = 0; i < max_level; i++) {
        obj->forward[i] = NULL;
    }
    return obj;
}

void skiplist_node_free(skiplist_node *obj) {
    if (obj->forward) {
        free(obj->forward);
        obj->forward = NULL;
        obj->max_level = 0;
    }
    free(obj);
}

skiplist *skiplist_create() {
    skiplist *obj = (skiplist *)malloc(sizeof(skiplist));
    obj->head = skiplist_node_create(-1, MAX_LEVEL);
    obj->level = 0;
    srand(time(NULL));
    return obj;
}

static inline int random_level() {
    int lv = 1;
    /* 随机生成 lv */
    while (rand() < P_FACTOR && lv < MAX_LEVEL) {
        lv++;
    }
    return lv;
}

bool skiplist_search(skiplist *obj, int target) {
    skiplist_node *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--) {
        /* 找到第 i 层小于且最接近 target 的元素*/
        while (curr->forward[i] && curr->forward[i]->val < target) {
            curr = curr->forward[i];
        }
    }
    curr = curr->forward[0];
    /* 检测当前元素的值是否等于 target */
    if (curr && curr->val == target) {
        return true;
    }
    return false;
}

void skiplist_add(skiplist *obj, int num) {
    skiplist_node *update[MAX_LEVEL] = {NULL};
    skiplist_node *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--) {
        /* 找到第 i 层小于且最接近 num 的元素*/
        while (curr->forward[i] && curr->forward[i]->val < num) {
            curr = curr->forward[i];
        }
        update[i] = curr;
    }
    int lv = random_level();
    if (lv > obj->level) {
        for (int i = obj->level; i < lv; i++) {
            update[i] = obj->head;
        }
        obj->level = lv;
    }
    skiplist_node *new_node = skiplist_node_create(num, lv);
    for (int i = 0; i < lv; i++) {
        /* 对第 i 层的状态进行更新，将当前元素的 forward 指向新的节点 */
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }
}

bool skiplist_erase(skiplist *obj, int num) {
    skiplist_node *update[MAX_LEVEL] = {NULL};
    skiplist_node *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--) {
        /* 找到第 i 层小于且最接近 num 的元素*/
        while (curr->forward[i] && curr->forward[i]->val < num) {
            curr = curr->forward[i];
        }
        update[i] = curr;
    }
    curr = curr->forward[0];
    /* 如果值不存在则返回 false */
    if (!curr || curr->val != num) {
        return false;
    }
    for (int i = 0; i < obj->level; i++) {
        if (update[i]->forward[i] != curr) {
            break;
        }
        /* 对第 i 层的状态进行更新，将 forward 指向被删除节点的下一跳 */
        update[i]->forward[i] = curr->forward[i];
    }
    skiplist_node_free(curr);
    /* 更新当前的 level */
    while (obj->level > 1 && obj->head->forward[obj->level - 1] == NULL) {
        obj->level--;
    }
    return true;
}

void skiplist_free(skiplist *obj) {
    for (skiplist_node *curr = obj->head; curr;) {
        skiplist_node *prev = curr;
        curr = curr->forward[0];
        skiplist_node_free(prev);
    }
    free(obj);
}

// 主函数保持逻辑不变，仅函数调用名对应修改
int main(void) {
    skiplist *skiplist = skiplist_create();
    printf("Created skip list\n");

    printf("Searching for 100 in empty list: %s\n",
           skiplist_search(skiplist, 100) ? "PASS" : "FAIL");

    skiplist_add(skiplist, 50);
    skiplist_add(skiplist, 30);
    skiplist_add(skiplist, 70);
    skiplist_add(skiplist, 20);
    skiplist_add(skiplist, 40);
    skiplist_add(skiplist, 60);
    skiplist_add(skiplist, 80);
    printf("Added elements: 20, 30, 40, 50, 60, 70, 80\n");

    printf("Searching for 30: %s\n",
           skiplist_search(skiplist, 30) ? "PASS" : "FAIL");
    printf("Searching for 50: %s\n",
           skiplist_search(skiplist, 50) ? "PASS" : "FAIL");
    printf("Searching for 80: %s\n",
           skiplist_search(skiplist, 80) ? "PASS" : "FAIL");

    printf("Searching for 10: %s\n",
           skiplist_search(skiplist, 10) ? "FAIL" : "PASS");
    printf("Searching for 90: %s\n",
           skiplist_search(skiplist, 90) ? "FAIL" : "PASS");

    printf("Erasing 30: %s\n",
           skiplist_erase(skiplist, 30) ? "PASS" : "FAIL");
    printf("Searching for 30 after erase: %s\n",
           skiplist_search(skiplist, 30) ? "FAIL" : "PASS");

    printf("Erasing 80: %s\n",
           skiplist_erase(skiplist, 80) ? "PASS" : "FAIL");
    printf("Searching for 80 after erase: %s\n",
           skiplist_search(skiplist, 80) ? "FAIL" : "PASS");

    printf("Erasing 100: %s\n",
           skiplist_erase(skiplist, 100) ? "FAIL" : "PASS");

    skiplist_add(skiplist, 50);
    printf("Added duplicate 50. Searching: %s\n",
           skiplist_search(skiplist, 50) ? "PASS" : "FAIL");

    printf("Erasing 20: %s\n",
           skiplist_erase(skiplist, 20) ? "PASS" : "FAIL");
    printf("Erasing 40: %s\n",
           skiplist_erase(skiplist, 40) ? "PASS" : "FAIL");
    printf("Erasing 50: %s\n",
           skiplist_erase(skiplist, 50) ? "PASS" : "FAIL");
    printf("Erasing 60: %s\n",
           skiplist_erase(skiplist, 60) ? "PASS" : "FAIL");
    printf("Erasing 70: %s\n",
           skiplist_erase(skiplist, 70) ? "PASS" : "FAIL");

    printf("Searching for 50 in empty list: %s\n",
           skiplist_search(skiplist, 50) ? "FAIL" : "PASS");

    skiplist_free(skiplist);
    printf("Freed skip list\n");

    printf("All test cases completed.\n");
    return 0;
}
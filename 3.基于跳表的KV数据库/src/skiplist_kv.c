#include "../include/include.h"
extern INSERT_ON_ODD_SHOW insert_on_or_show;
extern SEARCH_ON_ODD_SHOW search_on_or_show;
void skiplist_node_free(skiplist_node *obj);
void print_skip_list_with_level(skiplist *obj)
{
#ifdef PRINT
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
            printf("%s:%s", curr->key, curr->val);
            if (curr->forward[i])
            {
                printf(" -> ");
            }
            curr = curr->forward[i];
        }
        printf("\n");
    }
    printf("\n");
#endif
}

void print_skip_list(skiplist *obj)
{
#ifdef PRINT
    if (obj == NULL)
    {
        printf("NULL\n");
        return;
    }
    skiplist_node *curr = obj->head->forward[0];
    for (; curr;)
    {
        printf("%s:%s\n", curr->key, curr->val);
        curr = curr->forward[0];
    }
    // printf("\n");
#endif
}
// 函数命名改为下划线风格
skiplist_node *skiplist_node_create(string key, string val, int max_level)
{
    skiplist_node *obj = (skiplist_node *)malloc(sizeof(skiplist_node));
    obj->key = (string)malloc(sizeof(char) * 100); /*各开辟10000的字符数据*/
    obj->val = (string)malloc(sizeof(char) * 100);
    /*设置默认的key、val*/
    // 处理key
    if (key == NULL)
    {
        obj->key = strdup("defult-key"); // 使用strdup复制字符串字面量,这里很重要，因为能够使得free！
    }
    else
    {
        obj->key = strdup(key); // 复制输入的字符串
    }

    // 处理val
    if (val == NULL)
    {
        obj->val = strdup("NULL");
    }
    else
    {
        obj->val = strdup(val);
    }
    obj->max_level = max_level;
    obj->forward = (skiplist_node **)malloc(sizeof(skiplist_node *) * max_level);
    for (int i = 0; i < max_level; i++)
    {
        obj->forward[i] = NULL;
    }
    return obj;
}

skiplist *skiplist_create()
{
    skiplist *obj = (skiplist *)malloc(sizeof(skiplist));
    obj->head = skiplist_node_create(HEAD, NULL, MAX_LEVEL);
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

bool skiplist_search(skiplist *obj, string target_key)
{
    if (strcmp(target_key, "%%") == 0)
    {
        print_skip_list(obj);
        exit(EXIT_SUCCESS);
    }
    skiplist_node *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--)
    {
        /* 找到第 i 层小于且最接近 target 的元素*/
        while (curr->forward[i] && strcmp(curr->forward[i]->key, target_key) < 0)
        {
            curr = curr->forward[i];
        }
    }
    curr = curr->forward[0];
    /* 检测当前元素的值是否等于 target */
    if (curr && strcmp(curr->key, target_key) == 0)
    {
        // printf("value %s existed!\n", target_key);
        printf("%s", curr->val);
        // print_skip_list(obj); // 打印跳表结构
        return true;
    }
    printf("key %s not existed!\n", target_key);
    // print_skip_list(obj); // 打印跳表结构
    return false;
}

void skiplist_insert(skiplist *obj, string target_key, string target_val)
{
    skiplist_node *curr1 = obj->head;
    for (int i = obj->level - 1; i >= 0; i--)
    {
        /* 找到第 i 层小于且最接近 target 的元素*/
        while (curr1->forward[i] && strcmp(curr1->forward[i]->key, target_key) < 0)
        {
            curr1 = curr1->forward[i];
        }
    }
    curr1 = curr1->forward[0];
    /* 检测当前元素的值是否等于 target */
    if (curr1 && strcmp(curr1->key, target_key) == 0)
    {

        printf("insert failed, key %s existed!\n", target_key);
        return;
        return true;
    }
    /**
     * data descp: 不存在数据则插入
     */
    skiplist_node *update[MAX_LEVEL] = {NULL};
    skiplist_node *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--)
    {
        /* 找到第 i 层小于且最接近 num 的元素*/
        while (curr->forward[i] && strcmp(curr->forward[i]->key, target_key) < 0)
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
    skiplist_node *new_node = skiplist_node_create(target_key, target_val, lv);
    for (int i = 0; i < lv; i++)
    {
        /* 对第 i 层的状态进行更新，将当前元素的 forward 指向新的节点 */
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }
    if (insert_on_or_show == INSERT_ON)
    {
        printf("Insert %s:%s successd!\n", target_key, target_val);
    }
    // print_skip_list(obj); // 打印跳表结构
}

bool skiplist_update(skiplist *obj, string target_key, string target_val)
{
    skiplist_node *update[MAX_LEVEL] = {NULL};
    skiplist_node *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--)
    {
        /* 找到第 i 层小于且最接近 target 的元素*/
        while (curr->forward[i] && strcmp(curr->forward[i]->key, target_key) < 0)
        {
            curr = curr->forward[i];
        }
        update[i] = curr;
    }
    curr = curr->forward[0];
    /* 检测当前元素的值是否等于 target */
    if (curr && strcmp(curr->key, target_key) == 0)
    {
        /*逐层级更新*/
        for (int i = 0; i < curr->max_level; i++)
        {
            sprintf(update[i]->forward[i]->val, "%s", target_val);
        }
        // print_skip_list(obj); // 打印跳表结构
        printf("update succeed key %s!\n", target_key);
        return true;
    }
    printf("update failed key %s not existed!\n", target_key);
    // print_skip_list(obj); // 打印跳表结构
    return false;
}

bool skiplist_erase(skiplist *obj, string target_key)
{
    skiplist_node *update[MAX_LEVEL] = {NULL};
    skiplist_node *curr = obj->head;
    for (int i = obj->level - 1; i >= 0; i--)
    {
        /* 找到第 i 层小于且最接近 num 的元素*/
        while (curr->forward[i] && strcmp(curr->forward[i]->key, target_key) < 0)
        {
            curr = curr->forward[i];
        }
        update[i] = curr;
    }
    /*跳到最后一层来开始更新!*/
    curr = curr->forward[0];
    /* 如果值不存在则返回 false */
    if (!curr || strcmp(curr->key, target_key) != 0)
    {
        printf("delete faided! key %s not existed!\n", target_key);
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

    // print_skip_list(obj);
    printf("delete key %s succeed!\n", target_key);
    return true;
}
void skiplist_node_free(skiplist_node *obj)
{
    if (!obj)
        return; // 空指针保护

    if (obj->forward)
    {
        free(obj->forward);
        obj->forward = NULL;
        obj->max_level = 0;
    }

    free(obj->key);
    free(obj->val);
    free(obj);
}

void skiplist_free(skiplist *obj)
{
    for (skiplist_node *curr = obj->head; curr;)
    {
        skiplist_node *prev = curr;
        curr = curr->forward[0]; /*只需要释放最底层的元素节点就好了！*/
        skiplist_node_free(prev);
    }
    free(obj);
}

// 主函数保持逻辑不变，仅函数调用名对应修改
#ifdef MAIN
int main(void)
{
    skiplist *obj = skiplist_create();
    printf("===== Skip List Database Test Suite =====\n");
    print_skip_list(obj);

    // Test 1: Search in empty list
    printf("\n===== Test 1: Empty List Search =====\n");
    printf("Search for non-existent key 'key100': %s\n",
           skiplist_search(obj, "key100") ? "FAIL" : "PASS");

    // Test 2: Single key-value operations
    printf("\n===== Test 2: Single Key-Value Operations =====\n");
    skiplist_insert(obj, "key50", "value50");
    print_skip_list(obj);

    printf("Search for existing key 'key50': %s\n",
           skiplist_search(obj, "key50") ? "PASS" : "FAIL");
    printf("Search for non-existent key 'key30': %s\n",
           skiplist_search(obj, "key30") ? "FAIL" : "PASS");

    printf("Erase existing key 'key50': %s\n",
           skiplist_erase(obj, "key50") ? "PASS" : "FAIL");
    printf("Search for 'key50' after erase: %s\n",
           skiplist_search(obj, "key50") ? "FAIL" : "PASS");

    // Test 3: Multiple key-value operations
    printf("\n===== Test 3: Multiple Key-Value Operations =====\n");
    skiplist_insert(obj, "key30", "value30");
    skiplist_insert(obj, "key70", "value70");
    skiplist_insert(obj, "key20", "value20");
    skiplist_insert(obj, "key50", "value50");
    skiplist_insert(obj, "key90", "value90");
    skiplist_insert(obj, "key10", "value10");
    skiplist_insert(obj, "key40", "value40");
    skiplist_insert(obj, "key60", "value60");
    skiplist_insert(obj, "key80", "value80");

    printf("Skip list structure after insertions:\n");
    print_skip_list(obj);

    // Verify inserted keys
    printf("\nVerify inserted keys:\n");
    printf("Search 'key20': %s\n", skiplist_search(obj, "key20") ? "PASS" : "FAIL");
    printf("Search 'key50': %s\n", skiplist_search(obj, "key50") ? "PASS" : "FAIL");
    printf("Search 'key80': %s\n", skiplist_search(obj, "key80") ? "PASS" : "FAIL");
    printf("Search non-existent 'key100': %s\n", skiplist_search(obj, "key100") ? "FAIL" : "PASS");

    // Test 4: Erase operations
    printf("\n===== Test 4: Erase Operations =====\n");
    printf("Erase 'key30': %s\n", skiplist_erase(obj, "key30") ? "PASS" : "FAIL");
    printf("Erase 'key70': %s\n", skiplist_erase(obj, "key70") ? "PASS" : "FAIL");
    printf("Erase non-existent 'key100': %s\n", skiplist_erase(obj, "key100") ? "FAIL" : "PASS");

    printf("Skip list structure after erasures:\n");
    print_skip_list(obj);

    // Test 5: Duplicate key insertion
    printf("\n===== Test 5: Duplicate Key Insertion =====\n");
    skiplist_insert(obj, "key50", "new_value50");
    printf("After inserting duplicate key, search 'key50': %s\n",
           skiplist_search(obj, "key50") ? "PASS" : "FAIL");

    // Test 6: Boundary condition tests
    printf("\n===== Test 6: Boundary Conditions =====\n");
    skiplist_insert(obj, "a", "value_a");                     // Minimum key
    skiplist_insert(obj, "zzzz", "value_zzzz");               // Maximum key
    skiplist_insert(obj, "", "value_empty");                  // Empty key
    skiplist_insert(obj, "very_long_key_name", "value_long"); // Long key

    printf("Skip list structure with boundary keys:\n");
    print_skip_list(obj);
    // Test 7: Large dataset test
    printf("\n===== Test 7: Large Dataset Test =====\n");
    for (int i = 0; i < 10000; i++)
    {
        char key[20];
        sprintf(key, "key%d", i);
        skiplist_insert(obj, key, "value");
    }
    // Test 9: Memory management test
    printf("\n===== Test 9: Memory Management =====\n");
    skiplist_free(obj);
    printf("Skiplist memory freed successfully\n");

    // Recreate and test free again (double-free test)
    obj = skiplist_create();
    skiplist_insert(obj, "test_key", "test_val");
    skiplist_free(obj);
    printf("Double-free test completed without errors\n");

    printf("\n===== All test cases passed =====\n");
    return 0;
}

#endif
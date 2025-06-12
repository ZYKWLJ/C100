#ifndef SKIPLIST_KV_H_
#define SKIPLIST_KV_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX_LEVEL 32
#define P_FACTOR RAND_MAX >> 2
#define HEAD "HEAD"
// #define MAIN
#define PRINT
typedef char *string;
// 结构体命名改为下划线风格
typedef struct skiplist_node
{
    string key;
    string val; /*仅仅是这里新增了val*/
    int max_level;
    struct skiplist_node **forward; // 前向数组
} skiplist_node;

typedef struct
{
    skiplist_node *head;
    int level;
} skiplist;
void skiplist_node_free(skiplist_node *obj);
void print_skip_list(skiplist *obj);

typedef enum INSERT_ON_ODD_SHOW_
{
    INSERT_ON,
    INSERT_OFF
} INSERT_ON_ODD_SHOW;
/*查找节点,返回节点*/
typedef enum SEARCH_ON_ODD_SHOW_
{
    SEARCH_ON,
    SEARCH_OFF
} SEARCH_ON_ODD_SHOW;

// 函数命名改为下划线风格
skiplist_node *skiplist_node_create(string key, string val, int max_level);

skiplist *skiplist_create();

bool skiplist_search(skiplist *obj, string target_key);

void skiplist_insert(skiplist *obj, string target_key, string target_val);
bool skiplist_update(skiplist *obj, string target_key, string target_val);
bool skiplist_erase(skiplist *obj, string target_key);
void skiplist_node_free(skiplist_node *obj);
void skiplist_free(skiplist *obj);

#endif /* SKIPLIST_KV_H_ */

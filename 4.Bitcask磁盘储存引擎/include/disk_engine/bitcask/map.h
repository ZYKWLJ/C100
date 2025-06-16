#ifndef MAP_H_
#define MAP_H_
// #include"include.h"
/**
 * data descp: 轻量级K-V搜索引擎
 */

/*固定链表数组+链表扩容(key为数字，value为指针)*/
// #define MAX_SIZE_MAP 10000
// void *map[MAX_SIZE_MAP];
/**
 * func descp: 每个字符的码值余下容量即可作为哈希函数
 */
int hash_func(string key);
void map_insert(list_t *map[],void *map_data, list_node_type_t list_node_type );
void map_find(list_t *map[], string key, list_node_type_t list_node_type);
#endif /* MAP_H_ */

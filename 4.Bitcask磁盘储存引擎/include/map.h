#ifndef MAP_H_
#define MAP_H_
// #include"include.h"
/**
 * data descp: 轻量级K-V搜索引擎
 */

/*固定链表数组+链表扩容(key为数字，value为指针)*/
#define MAX_SIZE_MAP 10000
void *map[MAX_SIZE_MAP];
/**
* func descp: 每个字符的码值余下容量即可作为哈希函数
*/
int hash_func(string key);
void map_conflict_list_method();

#endif /* MAP_H_ */

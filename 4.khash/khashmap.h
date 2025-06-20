#ifndef KHASHMAP_H_
#define KHASHMAP_H_
#include "klist.h"
/**
 * func descp: 哈希表初始化
 */
void map_init(list_t *map[]);
/**
 * func descp: 哈希函数
 */
int hash_func(string key);
/**
 * func descp: 打印某一哈希值下所有的数据
 */
void print_map_key(list_t *map[], string key, Key_type key_type);
/**
 * func descp: 解决哈希冲突的函数
 */
void map_conflict_list_method(list_t *map[], string same_hash_key, string conflict_value, Key_type key_type, Value_type value_type);
/**
 * func descp: 插入数据到哈希表
 */
void map_insert(list_t *map[], string key, string value, Key_type key_type, Value_type value_type);
/**
 * func descp: 到哈希表中查找数据
 */
void map_find(list_t *map[], string key, Key_type key_type);
/**
 * func descp: 到哈希表中查找数据，并显示详细信息
 */
void map_find_show_info(list_t *map[], string key, Key_type key_type);
/**
 * func descp: 删除哈希表中的数据
 */
void map_delete(list_t *map[], string key, Key_type key_type);
/**
 * func descp: 打印整个哈希表
 */
void map_print(list_t *map[]);

#endif /* KHASHMAP_H_ */
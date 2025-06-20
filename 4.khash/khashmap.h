#ifndef KHASHMAP_H_
#define KHASHMAP_H_
#include "klist.h"

void print_map_key(list_t *map[], string key, Key_type key_type);
void map_conflict_list_method(list_t *map[], string same_hash_key, string conflict_value, Key_type key_type, Value_type value_type);
void map_insert(list_t *map[], string key, string value, Key_type key_type, Value_type value_type);
void map_find(list_t *map[], string key, Key_type key_type);
void map_find_show_info(list_t *map[], string key, Key_type key_type);
#endif /* KHASHMAP_H_ */
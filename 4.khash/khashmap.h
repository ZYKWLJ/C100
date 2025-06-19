#ifndef KHASHMAP_H_
#define KHASHMAP_H_
#include "klist.h"

void print_map_key(list_t *map[], string key, Key_type key_type);
void map_conflict_list_method(list_t *map[], string key, Key_type key_type, list_node_t *list_node);
void map_insert(list_t *map[], string key, Key_type key_type, list_node_t *list_node);
void map_find(list_t *map[], string key, Key_type key_type);
void map_find_show_info(list_t *map[], string key, Key_type key_type);
#endif /* KHASHMAP_H_ */
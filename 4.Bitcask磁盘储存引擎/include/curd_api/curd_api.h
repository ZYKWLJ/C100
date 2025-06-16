#ifndef CURD_API_H_
#define CURD_API_H_
#include "../include.h"
void db_erase(disk_engine_type_t disk_engine_type, string key);
void db_search(disk_engine_type_t disk_engine_type, string key);

void db_insert(disk_engine_type_t disk_engine_type, string key, string value);
void db_update(disk_engine_type_t disk_engine_type, string key, string value);

#endif /* CURD_API_H_ */
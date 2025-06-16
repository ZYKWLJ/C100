#include "../include/include.h"
#include <windows.h>

#define MAIN
#ifdef MAIN
bitcask_t *bitcask;
string db_file_path;
int main(int argc, char const *argv[])
{
    menu();
    /*日志文件目录*/
    db_file_path = get_appdata_path(DATE_FILE);
    /*存储引擎选型*/
    disk_engine_type_t disk_engine_type = BITCASK;
    switch (disk_engine_type)
    { /*选用bitcask*/
    case BITCASK:
    {
        /*日志文件系统初始化*/
        bitcask_log_t *bitcask_log = bitcask_log_t_init(db_file_path);
        /*首次读取，根据log建立index*/
        bitcask_index_t *bitcask_index = bitcask_index_t_init(bitcask_log);
        while (1)
        {
            for (int i = 100; i > 0; i--)
            {
                char result_key[100];   // 分配足够大的缓冲区
                char result_value[100]; // 分配足够大的缓冲区
                sprintf(result_key, "key-%d", i);
                sprintf(result_value, "value-%d", i);
                bitcask_log_entry_t_write_to_log(bitcask_log, data_t_init(result_key, result_value), bitcask_index);
            }
            bitcask_index_print(bitcask_index);

            // bitcask_log_read_from_begin_to_end(bitcask_log);
            break;
        }
    }
    break;
    /*选型为原生的遍历裸存储引擎*/
    case RAW:
    {
    }
    break;
    default:
        break;
    }
    return 0;
}

#endif
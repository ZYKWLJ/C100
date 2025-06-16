#include "../../../include/include.h"

data_t *data_t_init(string key, string value)
{
    data_t *data = (data_t *)malloc(sizeof(data_t));
    /**
     * data descp: 注意这里依然是易错点，一定要使用strdup
     */
    data->key = strdup(key);
    data->value = strdup(value);
    data->size = strlen(value);
    return data;
}

void *data_t_print(data_t *data)
{
    printf("[%s[%s],%d]\n", data->key, data->value, data->size);
}
/**
 * func descp: 初始化日志条目
 */
bitcask_log_entry_t *bitcask_log_entry_t_init(data_t *date)
{
    bitcask_log_entry_t *bitcask_log_entry = (bitcask_log_entry_t *)malloc(sizeof(bitcask_log_entry_t));
    bitcask_log_entry->key_size = strlen(date->key);
    bitcask_log_entry->value_size = strlen(date->value);
    bitcask_log_entry->key = date->key;
    bitcask_log_entry->value = date->value;
    return bitcask_log_entry;
}

/**
 * func descp: 打印日志条目
 */
void bitcask_log_print(bitcask_log_entry_t *bitcask_log_entry)
{
    printf("[%d,%d,%s,%s]\n", bitcask_log_entry->key_size, bitcask_log_entry->value_size, bitcask_log_entry->key, bitcask_log_entry->value);
}

/**
 * func descp: 初始化日志系统
 */
bitcask_log_t *bitcask_log_t_init(string log_file_path)
{
    bitcask_log_t *bitcask_log = (bitcask_log_t *)malloc(sizeof(struct bitcask_log_));
    bitcask_log->offset = 0;
    bitcask_log->log_file_path = log_file_path;
    // 打开文件以确定当前offset
    FILE *file = fopen(log_file_path, "a+b"); // 以读写模式打开，不截断文件
    // 获取文件大小（即下一个写入位置的offset）
    if (fseek(file, 0, SEEK_END /*这是直接的文件末尾*/) != 0)
    {
        fclose(file);
        free(bitcask_log->log_file_path);
        free(bitcask_log);
        return NULL;
    }
    /*读取到了当前文件的长度*/
    bitcask_log->offset = ftell(file);
    fclose(file);
    return bitcask_log;
}

/**
 * func descp: 追加日志
 */

void bitcask_log_entry_t_write_to_log(bitcask_log_t *bitcask_log, data_t *data, bitcask_index_t *bitcask_index)
{
    if (bitcask_log == NULL || data == NULL || bitcask_index == NULL)
    {
        return;
    }

    bitcask_log_entry_t *entry = bitcask_log_entry_t_init(data);
    if (entry == NULL)
    {
        return;
    }

    // 打开文件（使用"ab"模式确保追加且为二进制）
    FILE *file = fopen(bitcask_log->log_file_path, "ab");
    if (file == NULL)
    {
        free(entry);
        return;
    }

    // 写入前记录当前偏移量
    long offset = ftell(file);

    // 写入完整结构体（修正大小参数）
    size_t written = fwrite(entry, sizeof(bitcask_log_entry_t), 1, file);

    if (written != 1)
    {
        // 写入失败处理
        perror("Failed to write entry");
    }
    else
    {
        // 更新索引（使用实际写入的偏移量）
        map_insert(bitcask_index->map,
                   bitcask_single_index_t_init(data, offset),
                   BITCAST_INDEX_OFFSET_SIZE_T);

        // 更新日志文件偏移量（使用实际结构体大小）
        bitcask_log->offset += sizeof(bitcask_log_entry_t);
    }

    // 关闭文件
    fclose(file);

    // 释放临时分配的内存
    free(entry);
}
/**
 * func descp: 按照顺序读取数据
 */

/*注意这里有一个结构体对齐问题！*/
void bitcask_log_read_from_begin_to_end(bitcask_log_t *bitcask_log)
{
    printf("begin read log entty\n");

    /**
     * data descp: 从log中加载
     */
    /*拿到4字节key和value长度*/

    FILE *file = fopen(bitcask_log->log_file_path, "r+b"); /*打开日志文件，使用"r+b"模式以二进制读/写方式打开，不会截断文件
                                                            */
    int key_size = 0;
    int value_size = 0;
    long offset = 0;

    // 循环读取日志文件中的所有记录
    while (1)
    {
        // 记录当前文件偏移量(即KV对起始位置)
        offset = ftell(file);
        printf("offset: %ld\n", offset);
        // 读取key大小和value大小
        if (fread(&key_size, sizeof(int), 1, file) != 1)
        {
            break; // 读取失败或文件结束
        }
        printf("key_size: %d\n", key_size);
        if (fread(&value_size, sizeof(int), 1, file) != 1)
        {
            break; // 读取失败或文件结束
        }
        printf("value_size: %d\n", value_size);

        // 读取key
        char *key = (char *)malloc(key_size);
        if (key == NULL || fread(key, 1, key_size, file) != key_size)
        {
            if (key)
                free(key);
            break; // 内存分配失败或读取失败
        } // 读取key
        printf("key: %s\n", key);
        char *value = (char *)malloc(value_size);
        if (value == NULL || fread(value, 1, value_size, file) != value_size)
        {
            if (value)
                free(value);
            break; // 内存分配失败或读取失败
        }
        printf("value: %s\n", value);

        printf("[%d,%d,%s,%s]\n", key_size, value_size, key, value);
    }
    fclose(file);
}
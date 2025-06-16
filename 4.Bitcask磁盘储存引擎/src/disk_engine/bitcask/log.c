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
 * @brief 追加日志条目到日志文件
 * @param bitcask_log 日志对象
 * @param data 数据（key-value）
 * @param bitcask_index 索引对象
 */
void bitcask_log_entry_t_write_to_log(bitcask_log_t *bitcask_log, data_t *data, bitcask_index_t *bitcask_index)
{
    if (bitcask_log == NULL || data == NULL || bitcask_index == NULL)
    {
        fprintf(stderr, "Error: Invalid arguments in bitcask_log_entry_t_write_to_log\n");
        return;
    }

    // 打开文件（追加二进制模式）
    FILE *file = fopen(bitcask_log->log_file_path, "ab");
    if (file == NULL)
    {
        perror("Failed to open log file for writing");
        return;
    }

    // 写入前记录当前偏移量
    long offset = ftell(file);

    // 写入 key_size 和 value_size（使用 int）
    int key_size = strlen(data->key);
    int value_size = strlen(data->value);

    if (fwrite(&key_size, sizeof(int), 1, file) != 1)
    {
        perror("Failed to write key_size");
        fclose(file);
        return;
    }
    if (fwrite(&value_size, sizeof(int), 1, file) != 1)
    {
        perror("Failed to write value_size");
        fclose(file);
        return;
    }

    // 写入 key 和 value
    if (fwrite(data->key, 1, key_size, file) != key_size)
    {
        perror("Failed to write key");
        fclose(file);
        return;
    }
    if (fwrite(data->value, 1, value_size, file) != value_size)
    {
        perror("Failed to write value");
        fclose(file);
        return;
    }

    // 更新索引
    map_insert(bitcask_index->map,
               bitcask_single_index_t_init(data, offset),
               BITCAST_INDEX_OFFSET_SIZE_T);

    // 更新日志文件偏移量
    bitcask_log->offset += sizeof(int) * 2 + key_size + value_size;
    // printf("%s[%d]-%s[%d]\n",data->key,key_size,data->value,value_size);
    fclose(file);
}

/**
 * @brief 从头到尾读取日志文件，并打印内容
 * @param bitcask_log 日志对象
 */
void bitcask_log_read_from_begin_to_end(bitcask_log_t *bitcask_log)
{
    if (bitcask_log == NULL)
    {
        fprintf(stderr, "Error: bitcask_log is NULL\n");
        return;
    }

    printf("=== Begin reading log entries ===\n");

    FILE *file = fopen(bitcask_log->log_file_path, "rb"); // 只读二进制模式
    if (file == NULL)
    {
        perror("Failed to open log file for reading");
        return;
    }

    int key_size = 0;
    int value_size = 0;
    long offset = 0;

    while (1)
    {
        offset = ftell(file);
        printf("\noffset: %ld\n", offset);

        // 读取 key_size 和 value_size（使用 int）
        if (fread(&key_size, sizeof(int), 1, file) != 1)
        {
            if (feof(file))
                printf("Reached end of file.\n");
            else
                perror("Failed to read key_size");
            break;
        }
        printf("key_size: %zu\n", key_size);

        if (fread(&value_size, sizeof(int), 1, file) != 1)
        {
            perror("Failed to read value_size");
            break;
        }
        printf("value_size: %zu\n", value_size);

        // 读取 key
        char *key = (char *)malloc(key_size + 1); // +1 for '\0'
        if (key == NULL)
        {
            perror("Failed to allocate memory for key");
            break;
        }
        if (fread(key, 1, key_size, file) != key_size)
        {
            perror("Failed to read key");
            free(key);
            break;
        }
        key[key_size] = '\0'; // 确保字符串以 '\0' 结尾
        printf("key: %s\n", key);

        // 读取 value
        char *value = (char *)malloc(value_size + 1); // +1 for '\0'
        if (value == NULL)
        {
            perror("Failed to allocate memory for value");
            free(key);
            break;
        }
        if (fread(value, 1, value_size, file) != value_size)
        {
            perror("Failed to read value");
            free(key);
            free(value);
            break;
        }
        value[value_size] = '\0'; // 确保字符串以 '\0' 结尾
        printf("value: %s\n", value);

        printf("[key_size=%zu, value_size=%zu, key='%s', value='%s']\n",
               key_size, value_size, key, value);

        free(key);
        free(value);
    }

    fclose(file);
    printf("=== Finished reading log entries ===\n");
}
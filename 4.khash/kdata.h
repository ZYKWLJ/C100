#ifndef KDATA_H_
#define KDATA_H_
typedef char *string;
typedef enum
{
    KEY_STRING,
    KEY_INT
} Key_type;
typedef enum
{
    VALUE_STRING,
    VALUE_INT,
    VALUE_NONE
} Value_type;

/**
 * data descp: 真实存储的数据k-v
 */
typedef struct data_
{
    Key_type key_type;
    Value_type value_type;
    /**
     * data descp: key和value都有任意的类型实现，要拓展直接加就好！
     */
    union
    {
        string str_key;
        int int_key;
    } key;
    union
    {
        string str_value;
        int int_value;
    } value;

} data_t;

void data_t_print(data_t *data);
data_t *data_t_init(string key, string value, Key_type key_type, Value_type value_type);
void data_t_free(data_t *data);
void data_t_print_key(string key, Key_type key_type);
void data_t_no_data_key(string key, Key_type key_type);
void data_t_print_value(string value, Value_type value_type);
#endif /* KDATA_H_ */
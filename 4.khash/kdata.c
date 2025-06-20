#include "kdata.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

data_t *data_t_init(string key, string value, Key_type key_type, Value_type value_type)
{
    data_t *data = (data_t *)malloc(sizeof(struct data_));

    switch (key_type)
    {
    case KEY_STRING:
        data->key_type = KEY_STRING;
        data->key.str_key = strdup(key);
        break;
    case KEY_INT:
        data->key_type = KEY_INT;
        data->key.int_key = atoi(key) == 0 ? -1 : atoi(key);
        break;
    default:
        break;
    }

    switch (value_type)
    {
    case VALUE_STRING:
        data->value_type = VALUE_STRING;
        data->value.str_value = strdup(value);
        break;
    case VALUE_INT:
        data->value_type = VALUE_INT;
        data->value.int_value = atoi(key) == 0 ? -1 : atoi(key);
        break;
    case VALUE_NONE:
        data->value_type = VALUE_NONE;
        data->value.int_value = atoi(key) == 0 ? -1 : atoi(key);
        break;
    default:
        break;
    }
    return data;
}

void data_t_print_key_value(string k_or_v, string key, Key_type key_type)
{
    printf("%s:", k_or_v);
    switch (key_type)
    {
    case KEY_STRING:
        printf("[string]%s", key);
        break;
    case KEY_INT:
        printf("[int]%d", atoi(key));
        break;
    default:
        break;
    }
}
void data_t_print_key(string key, Key_type key_type)
{
    data_t_print_key_value("key", key, key_type);
}

void data_t_no_data_key(string key, Key_type key_type)
{
    printf("No data which key is ");
    data_t_print_key(key, key_type);
}

void data_t_print_value(string value, Value_type value_type)
{
    data_t_print_key_value(",value", value, value_type);
}
void data_t_print(data_t *data)
{
    printf("[");
    switch (data->key_type)
    {
    case KEY_STRING:
    {

        data_t_print_key(data->key.str_key, data->key_type);
    }
    break;
    case KEY_INT:
    {
        char key[100];
        sprintf(key, "%d", data->key.int_key);
        data_t_print_key(key, data->key_type);
    }
    break;
    default:
        break;
    }
    switch (data->value_type)
    {
    case VALUE_STRING:
        data_t_print_value(data->value.str_value, data->value_type);
        break;
    case VALUE_INT:
    {
        char value[100];
        sprintf(value, "%d", data->value.int_value);
        data_t_print_value(value, data->value_type);
    }

    break;
    case VALUE_NONE:
        break;
    default:
        break;
    }
    printf("]");
    // printf("\n");
}

void data_t_free(data_t *data)
{
    switch (data->key_type)
    {
    case KEY_STRING:
        free(data->key.str_key);
        break;
    default:
        break;
    }
    switch (data->value_type)
    {
    case VALUE_STRING:
        free(data->value.str_value);
        break;
    default:
        break;
    }
    free(data);
}

// #define TEST_KDATA
#ifdef TEST_KDATA

int main(void)
{
    string key1 = "Ethan";
    string value1 = "xxx";
#define BASIC1
#ifdef BASIC1
    /*这里会会发生一个很有趣的现象，编译器优化共用内存，导致malloc但是会相互影响*/
    data_t *data1 = data_t_init(key1, value1, KEY_STRING, VALUE_STRING);
    data_t *data2 = data_t_init(key1, value1, KEY_STRING, VALUE_INT);
    data_t *data3 = data_t_init(key1, value1, KEY_INT, VALUE_STRING);
    data_t *data4 = data_t_init(key1, value1, KEY_INT, VALUE_INT);

    data_t_print(data1);
    free(data1);
    data_t_print(data2);
    free(data2);
    data_t_print(data3);
    free(data3);
    data_t_print(data4);
    free(data4);
#endif
#ifdef BASIC2

    /*这里就不会发生共用内存，因为已经free了！*/
    data_t *data1 = data_t_init(key1, value1, KEY_STRING, VALUE_STRING);
    data_t_print(data1);
    free(data1);
    data_t *data2 = data_t_init(key1, value1, KEY_STRING, VALUE_INT);
    data_t_print(data2);
    free(data2);
    data_t *data3 = data_t_init(key1, value1, KEY_INT, VALUE_STRING);
    data_t_print(data3);
    free(data3);
    data_t *data4 = data_t_init(key1, value1, KEY_INT, VALUE_INT);
    data_t_print(data4);
    free(data4);
#endif

#define PRINT_DATA
#ifdef PRINT_DATA

#endif

    return 0;
}
#endif
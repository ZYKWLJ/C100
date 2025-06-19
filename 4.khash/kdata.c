#include "kdata.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void data_t_print(data_t *data)
{
    switch (data->key_type)
    {
    case KEY_STRING:
        printf("key type : string\n");
        printf("\"%s\"\n", data->key.str_key);
        break;
    case KEY_INT:
        printf("key type : int\n");
        printf("%d\n", data->key.int_key);
        break;
    default:
        break;
    }
    switch (data->value_type)
    {
    case VALUE_STRING:
        printf("value type : string\n");

        printf("\"%s\"\n", data->value.str_value);
        break;
    case VALUE_INT:
        printf("value type : int\n");
        printf("%d\n", data->value.int_value);
        break;
    case VALUE_NONE:
        break;
    default:
        break;
    }
    printf("\n");
}
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
#if 1
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

#else
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
    return 0;
}
#endif
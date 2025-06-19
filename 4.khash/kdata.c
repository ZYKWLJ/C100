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
        int *key1 = (int *)malloc(sizeof(int));
        *key1 = atoi(key);
        data->key.int_key = *key1;
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
        int *value1 = (int *)malloc(sizeof(int));
        *value1 = atoi(value);
        data->value.int_value = *value1;
        break;
    default:
        break;
    }
    return data;
}

#define TEST_KDATA
#ifdef TEST_KDATA

int main(void)
{
    string key1 = "Ethan";
    string value1 = "666";
    data_t *data1 = data_t_init(key1, value1, KEY_STRING, VALUE_STRING);
    data_t *data2 = data_t_init(key1, value1, KEY_STRING, VALUE_INT);
    data_t *data3 = data_t_init(key1, value1, KEY_INT, VALUE_STRING);
    data_t *data4 = data_t_init(key1, value1, KEY_INT, VALUE_INT);
    data_t_print(data1);
    data_t_print(data2);
    data_t_print(data3);
    data_t_print(data4);
    return 0;
}

#endif
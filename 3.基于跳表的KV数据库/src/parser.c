#include "../include/include.h"
/*
只提供crud功能

*/
extern skiplist *sklist;
void print_help_curd()
{

    char *name[] = {"Operations", "Add data:", "Delete data:", "Query data:", "Modify data:", NULL};
    char *instructions[] = {"Commands", "hd add key value", "hd delete key", "hd find key", "hd update key value", NULL};
    char **columns[] = {name, instructions};
    text_print_head1_blank0(columns, sizeof(columns) / sizeof(columns[0]));
}

#define AUTHOR "Author: EthanYankang"
#define WECHAT "Wechat: 2126483838"
// #define GITHUB "Github: https://github.com/ZYKWLJ/C_skip_list"
// #define LINK "HelpRefence: https://blog.csdn.net/m0_68657832/article/details/147869804"
/*
  ____
 /    \
/      \
\      /
 \____/
 /    \
/      \
\      /
 \____/

*/
/*
  ___
 /   \
 \___/
 /   \
 \___/
 /   \
 \___/
*/
void author()
{
    printf("\n");
    printf("%s\n", AUTHOR);
    printf("%s\n", WECHAT);
    // printf("%s\n", GITHUB);
    // printf("%s\n", LINK);
}

void logo()
{
#if 0
#endif
    {
        // 硬编码方式打印蜂窝图案
        printf("    __________    __________    __________    \n");
        printf("   /          \\  /          \\  /          \\   \n");
        printf("  /            \\/            \\/            \\  \n");
        printf("  \\            /\\            /\\            /  \n");
        printf("   \\__________/  \\__________/  \\__________/   \n");
        // printf("    __________    __________    __________    \n");
        printf("   /          \\  /          \\  /          \\   \n");
        printf("  /            \\/            \\/            \\  \n");
        printf("  \\            /\\            /\\            /  \n");
        printf("   \\__________/  \\__________/  \\__________/   \n");
        // printf("    __________    __________    __________    \n");
        printf("   /          \\  /          \\  /          \\   \n");
        printf("  /            \\/            \\/            \\  \n");
        printf("  \\            /\\            /\\            /  \n");
        printf("   \\__________/  \\__________/  \\__________/   \n");
    }
}

void honeydb()
{
    {
        printf("                                               _    _                        _____  ____  \n");
        printf("                                              | |  | |                      |  __ \\|  _ \\ \n");
        printf("                                              | |__| | ___  _ __   ___ _   _| |  | | |_) |\n");
        printf("                                              |  __  |/ _ \\| '_ \\ / _ \\ | | | |  | |  _ < \n");
        printf("                                              | |  | | (_) | | | |  __/ |_| | |__| | |_) |\n");
        printf("                                              |_|  |_|\\___/|_| |_|\\___|\\__, |_____/|____/ \n");
        printf("                                                                        __/ |             \n");
        printf("                                                                       |___/              \n");
    }
}

void menu()
{
    logo();
    printf("");
    // printf("%40s\n", "HoneyDB");
    honeydb();
    // printf("MUNE\n\n");
    // honeydb是一个轻量级键值数据库，使用跳表作为默认内核，可以实现log2(n)的时间复杂度查询。
    // 内置如下命令，如下：
    // 帮助手册：hd ?
    printf("HoneyDB is a lightweight key-value database that uses a skip list as its default kernel, enabling query time complexity of log(n).\n");
    printf("The built-in commands are as follows:\n");
    print_help_curd(); /*只提供CURD，精简数据库！*/
    author();
}

void argc1()
{
    menu();
    // return OK;
    exit(EXIT_SUCCESS);
}

// hd delete/find key
void argc3(char *argv[])
{
    if (strcmp(argv[1], "delete") == 0)
    {
        skiplist_erase(sklist, argv[2]);
    }
    else if (strcmp(argv[1], "find") == 0)
    {
        skiplist_search(sklist, argv[2]);
    }
    else
    {
        printf("Error command\n\n");
        menu();
    }
}
// hd add/update key value
void argc4(char *argv[])
{
    if (strcmp(argv[1], "add") == 0)
    {
        skiplist_insert(sklist, argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "update") == 0)
    {
        skiplist_update(sklist, argv[2], argv[3]);
    }
    else
    {
        printf("Error command\n\n");
        menu();
    }
}

// int main(int argc, char const *argv[])
// {
//     menu();
//     return 0;
// }

void parser(int argc, char *argv[])
{
    if (argc == 1)
    {
        argc1();
    }
    else if (argc == 3)
    {
        argc3(argv);
    }
    else if (argc == 4)
    {
        argc4(argv);
    }
    else
    {
        printf("Error command\n\n");
        menu();
    }
}
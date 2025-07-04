
#ifndef TEXT_PRINT_HELP_H_
#define TEXT_PRINT_HELP_H_
#include "../../include/include.h"

#ifdef _WIN32
/**
 * filename:text_print_help.c
 * description: 这是win下专属的格式，不会出错！
 * author:EthanYankang
 * create time:2025/05/08 13:41:22
 */
// #include "../../include/include.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// 定义表格边框宏
// #define BORDER_PLUS "+"
// #define BORDER_MINUS "-"
// #define BORDER_VERTICAL_LINE "|"
// #define BORDER_PLUS ""
// #define BORDER_MINUS ""
// #define BORDER_VERTICAL_LINE ""
// 打印表格内容的函数（指令help版本）

// 这是不管这一列有没有数据，都打印该列的带有表头的打印函数

char BORDER_PLUS[2] = {0};
char BORDER_MINUS[2] = {0};
char BORDER_VERTICAL_LINE[2] = {0};

void text_print_head1_blank1(const char **str[], int columns_num)
{
    // 判断边框打印否

    {
        BORDER_PLUS[0] = '+';
        BORDER_MINUS[0] = '-';
        BORDER_VERTICAL_LINE[0] = '|';
    }

    setlocale(LC_ALL, ""); // 设置本地化，支持宽字符
    // 1. 计算每列的最大宽度
    int col_max_widths[columns_num];
    for (int i = 0; i < columns_num; i++)
    {
        col_max_widths[i] = 0;
        for (int row = 0; str[i][row] != NULL; row++)
        {
            int width = text_display_width(str[i][row]);
            if (width > col_max_widths[i])
            {
                col_max_widths[i] = width;
            }
        }
    }

    // 2. 计算最大行数（以最长的列为准）
    int max_rows = 0;
    for (int i = 0; i < columns_num; i++)
    {
        int rows = 0;
        while (str[i][rows] != NULL)
        {
            rows++;
        }
        if (rows > max_rows)
        {
            max_rows = rows;
        }
    }

    // 3. 打印上边框
    for (int i = 0; i < columns_num; i++)
    {
        printf("%s", BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf("%s", BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);

    // 4. 打印表头（第一行）
    printf("%s", BORDER_VERTICAL_LINE);
    for (int i = 0; i < columns_num; i++)
    {
        printf(" ");
        text_print_padded(str[i][0], col_max_widths[i]);
        printf(" %s", BORDER_VERTICAL_LINE);
    }
    printf("\n");

    // 5. 打印表头和内容之间的分隔线
    for (int i = 0; i < columns_num; i++)
    {
        printf("%s", BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf("%s", BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);

    // 6. 打印表格内容（从第2行开始）
    for (int row = 1; row < max_rows; row++)
    {
        printf("%s", BORDER_VERTICAL_LINE);
        for (int i = 0; i < columns_num; i++)
        {
            printf(" ");
            if (str[i][row] != NULL)
            {
                text_print_padded(str[i][row], col_max_widths[i]);
            }
            else
            {
                text_print_padded("", col_max_widths[i]);
            }
            printf(" %s", BORDER_VERTICAL_LINE);
        }
        printf("\n");
    }

    // 7. 打印下边框
    for (int i = 0; i < columns_num; i++)
    {
        printf("%s", BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf("%s", BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);
}
// 这是自动跳过空白列的带有表头的打印函数
// 颜色开启下沉到这里
void text_print_head1_blank0(const char **str[], int columns_num)
{
    // 判断边框打印否
    {
        BORDER_PLUS[0] = ' ';
        BORDER_MINUS[0] = ' ';
        BORDER_VERTICAL_LINE[0] = ' ';
    }
    setlocale(LC_ALL, ""); // 设置本地化，支持宽字符

    // 1. 计算每列的最大宽度并确定哪些列需要打印
    int col_max_widths[columns_num];
    bool print_column[columns_num]; // 标记哪些列需要打印
    int visible_columns = 0;        // 实际可见的列数

    for (int i = 0; i < columns_num; i++)
    {
        col_max_widths[i] = 0;
        print_column[i] = false;

        // 先计算表头宽度（假设第一行是表头）
        if (str[i][0] != NULL)
        {
            int header_width = text_display_width(str[i][0]);
            if (header_width > col_max_widths[i])
            {
                col_max_widths[i] = header_width;
            }
        }

        // 检查列内容是否全为空/空格
        bool has_content = false;
        for (int row = 1; str[i][row] != NULL; row++) // 从第2行开始检查内容
        {
            if (str[i][row] != NULL && str[i][row][0] != '\0')
            {
                // 检查是否全为空格
                bool all_spaces = true;
                for (const char *p = str[i][row]; *p != '\0'; p++)
                {
                    if (!isspace((unsigned char)*p))
                    {
                        all_spaces = false;
                        break;
                    }
                }

                if (!all_spaces)
                {
                    has_content = true;
                    int width = text_display_width(str[i][row]);
                    if (width > col_max_widths[i])
                    {
                        col_max_widths[i] = width;
                    }
                }
            }
        }

        // 如果该列有内容（非全空/空格），则标记为需要打印
        if (has_content)
        {
            print_column[i] = true;
            visible_columns++;
        }
    }

    // 如果没有可见列，直接返回
    if (visible_columns == 0)
    {
        return;
    }

    // 2. 计算最大行数（以最长的列为准）
    int max_rows = 0;
    for (int i = 0; i < columns_num; i++)
    {
        if (!print_column[i])
            continue;

        int rows = 0;
        while (str[i][rows] != NULL)
        {
            rows++;
        }
        if (rows > max_rows)
        {
            max_rows = rows;
        }
    }

    // 3. 打印上边框（只打印可见列）
    for (int i = 0; i < columns_num; i++)
    {
        if (!print_column[i])
            continue;

        printf("%s", BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf("%s", BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);

    // 4. 打印表头（第一行，只打印可见列）
    printf("%s", BORDER_VERTICAL_LINE);
    for (int i = 0; i < columns_num; i++)
    {
        if (!print_column[i])
            continue;

        printf(" ");
        text_print_padded(str[i][0], col_max_widths[i]);
        printf(" %s", BORDER_VERTICAL_LINE);
    }
    printf("\n");

    // 5. 打印表头和内容之间的分隔线（只打印可见列）
    for (int i = 0; i < columns_num; i++)
    {
        if (!print_column[i])
            continue;

        printf("%s", BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf("%s", BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);

    // 6. 打印表格内容（从第2行开始，只打印可见列）
    for (int row = 1; row < max_rows; row++)
    {
        printf("%s", BORDER_VERTICAL_LINE);
        for (int i = 0; i < columns_num; i++)
        {
            if (!print_column[i])
                continue;

            printf(" ");
            if (str[i][row] != NULL)
            {
                text_print_padded(str[i][row], col_max_widths[i]);
            }
            else
            {
                text_print_padded("", col_max_widths[i]);
            }
            printf(" %s", BORDER_VERTICAL_LINE);
        }
        printf("\n");
    }

    // 7. 打印下边框（只打印可见列）
    for (int i = 0; i < columns_num; i++)
    {
        if (!print_column[i])
            continue;

        printf("%s", BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf("%s", BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);
}

// 打印表格内容的函数（通用版本，不含表头），全部打印，不管有没有数据
void text_print_head0_blank1(const char **str[], int columns_num)
{
    // 判断边框打印否
    {
        BORDER_PLUS[0] = '+';
        BORDER_MINUS[0] = '-';
        BORDER_VERTICAL_LINE[0] = '|';
    }
    setlocale(LC_ALL, ""); // 设置本地化，支持宽字符

    // 1. 计算每列的最大宽度
    int col_max_widths[columns_num];
    for (int i = 0; i < columns_num; i++)
    {
        col_max_widths[i] = 0;
        for (int row = 0; str[i][row] != NULL; row++)
        {
            int width = text_display_width(str[i][row]);
            if (width > col_max_widths[i])
            {
                col_max_widths[i] = width;
            }
        }
    }

    // 2. 计算最大行数（以最长的列为准）
    int max_rows = 0;
    for (int i = 0; i < columns_num; i++)
    {
        int rows = 0;
        while (str[i][rows] != NULL)
        {
            rows++;
        }
        if (rows > max_rows)
        {
            max_rows = rows;
        }
    }

    // 3. 打印上边框
    for (int i = 0; i < columns_num; i++)
    {
        printf("%s", BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf("%s", BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);

    // 4. 打印表格内容（从第2行开始）
    for (int row = 0; row < max_rows; row++)
    {
        printf("%s", BORDER_VERTICAL_LINE);
        for (int i = 0; i < columns_num; i++)
        {
            printf(" ");
            if (str[i][row] != NULL)
            {
                text_print_padded(str[i][row], col_max_widths[i]);
            }
            else
            {
                text_print_padded("", col_max_widths[i]);
            }
            printf(" %s", BORDER_VERTICAL_LINE);
        }
        printf("\n");
    }

    // 5. 打印下边框
    for (int i = 0; i < columns_num; i++)
    {
        printf("%s", BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf("%s", BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);
}

void text_print_head0_blank0(const char **str[], int columns_num)
{
    {
        BORDER_PLUS[0] = ' ';
        BORDER_MINUS[0] = ' ';
        BORDER_VERTICAL_LINE[0] = ' ';
    }
    setlocale(LC_ALL, ""); // 设置本地化，支持宽字符
    // LOG_PRINT("text_print_help_all 1 passed!");

    // 1. 计算每列的最大宽度并确定哪些列需要打印
    int col_max_widths[columns_num];
    bool print_column[columns_num]; // 标记哪些列需要打印
    int visible_columns = 0;        // 实际可见的列数

    for (int i = 0; i < columns_num; i++)
    {
        col_max_widths[i] = 0;
        print_column[i] = false;

        // 先计算表头宽度（假设第一行是表头）
        if (str[i][0] != NULL)
        {
            int header_width = text_display_width(str[i][0]);
            if (header_width > col_max_widths[i])
            {
                col_max_widths[i] = header_width;
            }
        }

        // 检查列内容是否全为空/空格
        bool has_content = false;
        for (int row = 1; str[i][row] != NULL; row++) // 从第2行开始检查内容
        {
            if (str[i][row] != NULL && str[i][row][0] != '\0')
            {
                // 检查是否全为空格
                bool all_spaces = true;
                for (const char *p = str[i][row]; *p != '\0'; p++)
                {
                    if (!isspace((unsigned char)*p))
                    {
                        all_spaces = false;
                        break;
                    }
                }

                if (!all_spaces)
                {
                    has_content = true;
                    int width = text_display_width(str[i][row]);
                    if (width > col_max_widths[i])
                    {
                        col_max_widths[i] = width;
                    }
                }
            }
        }

        // 如果该列有内容（非全空/空格），则标记为需要打印
        if (has_content)
        {
            print_column[i] = true;
            visible_columns++;
        }
    }

    // 如果没有可见列，直接返回
    if (visible_columns == 0)
    {
        return;
    }

    // 2. 计算最大行数（以最长的列为准）
    int max_rows = 0;
    for (int i = 0; i < columns_num; i++)
    {
        if (!print_column[i])
            continue;

        int rows = 0;
        while (str[i][rows] != NULL)
        {
            rows++;
        }
        if (rows > max_rows)
        {
            max_rows = rows;
        }
    }
    // LOG_PRINT("text_print_help_all 2 passed!");

#if 0
    // 3. 打印上边框（只打印可见列）
    for (int i = 0; i < columns_num; i++)
    {
        if (!print_column[i])
            continue;

        printf("%s", BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf("%s", BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);

    // 4. 打印表头（第一行，只打印可见列）
    printf("%s", BORDER_VERTICAL_LINE);
    for (int i = 0; i < columns_num; i++)
    {
        if (!print_column[i])
            continue;

        printf(" ");
        text_print_padded(str[i][0], col_max_widths[i]);
        printf(" %s", BORDER_VERTICAL_LINE);
    }
    printf("\n");
#endif
    // 5. 打印表头和内容之间的分隔线（只打印可见列）
    for (int i = 0; i < columns_num; i++)
    {
        if (!print_column[i])
            continue;

        printf("%s", BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf("%s", BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);

    // 6. 打印表格内容（从第2行开始，只打印可见列）
    for (int row = 1; row < max_rows; row++)
    {
        printf("%s", BORDER_VERTICAL_LINE);
        for (int i = 0; i < columns_num; i++)
        {
            if (!print_column[i])
                continue;

            printf(" ");
            if (str[i][row] != NULL)
            {
                text_print_padded(str[i][row], col_max_widths[i]);
            }
            else
            {
                text_print_padded("", col_max_widths[i]);
            }
            printf(" %s", BORDER_VERTICAL_LINE);
        }
        printf("\n");
    }

    // 7. 打印下边框（只打印可见列）
    for (int i = 0; i < columns_num; i++)
    {
        if (!print_column[i])
            continue;

        printf("%s", BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf("%s", BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);
    // LOG_PRINT("text_print_help_all 3 passed!");
}
// 不打印表头

#else
// #define BORDER_PLUS "+"
// #define BORDER_MINUS "-"
// #define BORDER_VERTICAL_LINE "|"

#define BORDER_PLUS " "
#define BORDER_MINUS " "
#define BORDER_VERTICAL_LINE " "
// 打印表格内容的函数（指令help版本）
void text_print_help(const char **str[], int columns_num)
{
    setlocale(LC_ALL, ""); // 设置本地化，支持宽字符

    // 1. 计算每列的最大宽度
    int col_max_widths[columns_num];
    for (int i = 0; i < columns_num; i++)
    {
        col_max_widths[i] = 0;
        for (int row = 0; str[i][row] != NULL; row++)
        {
            int width = text_display_width(str[i][row]);
            if (width > col_max_widths[i])
            {
                col_max_widths[i] = width;
            }
        }
    }

    // 2. 计算最大行数（以最长的列为准）
    int max_rows = 0;
    for (int i = 0; i < columns_num; i++)
    {
        int rows = 0;
        while (str[i][rows] != NULL)
        {
            rows++;
        }
        if (rows > max_rows)
        {
            max_rows = rows;
        }
    }

    // 3. 打印上边框
    for (int i = 0; i < columns_num; i++)
    {
        printf(BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf(BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);

    // 4. 打印表头（第一行）
    // printf(BORDER_VERTICAL_LINE);
    printf(BORDER_VERTICAL_LINE);
    for (int i = 0; i < columns_num; i++)
    {
        printf(" ");
        // printf(BORDER_PLUS);
        text_print_padded(str[i][0], col_max_widths[i]);
        // printf(" %s",BORDER_VERTICAL_LINE);
        printf(" %s", BORDER_VERTICAL_LINE);
    }
    printf("\n");

    // 5. 打印表头和内容之间的分隔线
    for (int i = 0; i < columns_num; i++)
    {
        // printf(BORDER_PLUS);
        printf(BORDER_PLUS);

        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            // printf(BORDER_MINUS);
            printf(BORDER_MINUS);
        }
    }
    // printf("%s\n",BORDER_PLUS);
    printf("%s\n", BORDER_PLUS);

    // 6. 打印表格内容（从第2行开始）
    for (int row = 1; row < max_rows; row++)
    {
        // printf(BORDER_VERTICAL_LINE);
        printf(BORDER_VERTICAL_LINE);
        for (int i = 0; i < columns_num; i++)
        {
            printf(" ");
            if (str[i][row] != NULL)
            {
                text_print_padded(str[i][row], col_max_widths[i]);
            }
            else
            {
                text_print_padded("", col_max_widths[i]);
            }
            printf(" %s", BORDER_VERTICAL_LINE);
            // printf(BORDER_VERTICAL_LINE);
        }
        printf("\n");
    }

    // 7. 打印下边框
    for (int i = 0; i < columns_num; i++)
    {
        // printf(BORDER_PLUS);
        printf(BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            // printf(BORDER_MINUS);
            printf(BORDER_MINUS);
        }
    }
    // printf("%s\n",BORDER_PLUS);
    printf("%s\n", BORDER_PLUS);
}

// 打印表格内容的函数（通用版本）
void text_print(const char **str[], int columns_num)
{
    setlocale(LC_ALL, ""); // 设置本地化，支持宽字符

    // 1. 计算每列的最大宽度
    int col_max_widths[columns_num];
    for (int i = 0; i < columns_num; i++)
    {
        col_max_widths[i] = 0;
        for (int row = 0; str[i][row] != NULL; row++)
        {
            int width = text_display_width(str[i][row]);
            if (width > col_max_widths[i])
            {
                col_max_widths[i] = width;
            }
        }
    }

    // 2. 计算最大行数（以最长的列为准）
    int max_rows = 0;
    for (int i = 0; i < columns_num; i++)
    {
        int rows = 0;
        while (str[i][rows] != NULL)
        {
            rows++;
        }
        if (rows > max_rows)
        {
            max_rows = rows;
        }
    }

    // 3. 打印上边框
    for (int i = 0; i < columns_num; i++)
    {
        printf(BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf(BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);

    // 4. 打印表格内容（从第2行开始）
    for (int row = 0; row < max_rows; row++)
    {
        printf(BORDER_VERTICAL_LINE);
        for (int i = 0; i < columns_num; i++)
        {
            printf(" ");
            if (str[i][row] != NULL)
            {
                text_print_padded(str[i][row], col_max_widths[i]);
            }
            else
            {
                text_print_padded("", col_max_widths[i]);
            }
            printf(" %s", BORDER_VERTICAL_LINE);
        }
        printf("\n");
    }

    // 5. 打印下边框
    for (int i = 0; i < columns_num; i++)
    {
        printf(BORDER_PLUS);
        for (int j = 0; j < col_max_widths[i] + 2; j++)
        {
            printf(BORDER_MINUS);
        }
    }
    printf("%s\n", BORDER_PLUS);
}
#endif
#endif /* TEXT_PRINT_HELP_H_ */
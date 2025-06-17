#include <stdio.h>
#include <windows.h>
#include <time.h>
void show_time(char *str)
{
    time_t current_time;
    struct tm *local_time;
    time(&current_time);                   // 获取当前时间
    local_time = localtime(&current_time); // 转换为本地时间

    // 使用strftime格式化输出时间
    char time_str[100];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
    printf("[%s]%s\n", time_str, str);
}
int main(void)
{
    const char *file_path = "C:\\Users\\29001\\Desktop\\file.txt";
    FILE *file = fopen(file_path, "w+");
    setvbuf(file, NULL, _IOFBF, BUFSIZ); // 设置全缓冲
    if (file == NULL)
    {
        perror("Failed to open file");
        return 1;
    }
    char str[] = "hello world";
    fwrite(str, sizeof(char), sizeof(str), file);
    show_time("start to write to file:\n");
    for (size_t i = 0; i < 5; i++)
    {
        printf("write count:%d\n", i);
        Sleep(100);
    }
    show_time("print the file before fflush:\n");
    // （使用另一个文件指针,防止移动同一文件指针导致刷新内容到磁盘）
    FILE *read_file = fopen(file_path, "r");
    if (read_file)
    {
        char buffer[100] = {0};
        size_t read_size = fread(buffer, 1, sizeof(buffer), read_file);
        printf("file data size: %zu\n", read_size); // 输出应为0
        printf("file data: %s\n", buffer);
        fclose(read_file);
    }

    Sleep(200);
    fflush(file);
    printf("\n\n");
    show_time("after fflush the file:\n");
    read_file = fopen(file_path, "r");
    if (read_file)
    {
        char buffer[100] = {0};
        size_t read_size = fread(buffer, 1, sizeof(buffer), read_file);
        printf("file data size: %zu\n", read_size); // 输出应为12
        printf("file data: %s\n", buffer);
        fclose(read_file);
    }
    fflush(file);
    return 0;
}
#include <stdio.h>
#include <time.h>

#define LOG_
#ifdef LOG_
// #define LOG(msg) printf("[LOG %s %s %s:%d] %s\n" __DATE__, __TIME__, __FILE__, __LINE__, msg)
#define LOG(...)                                                         \
    printf("[LOG ][%s %s %s:%d] ", __DATE__, __TIME__, __FILE__, __LINE__); \
    printf(__VA_ARGS__);                                                 \
    printf("\n");
#else
#define LOG(...) \
    do           \
    {            \
    } while (0);
#endif

#define TODO_
#ifdef TODO_
#define TODO(...)                                                         \
    printf("[TODO][%s %s %s:%d] ", __DATE__, __TIME__, __FILE__, __LINE__); \
    printf(__VA_ARGS__);                                                  \
    printf("\n");
#else
#define TODO(...) \
    do            \
    {             \
    } while (0);
#endif
void show_time(char *str)
{
    time_t current_time;
    struct tm *local_time;
    time(&current_time);                   // 获取当前时间
    local_time = localtime(&current_time); // 转换为本地时间
    // 使用strftime格式化输出时间
    char time_str[100];
    strftime(time_str, sizeof(time_str), "[log]%Y-%m-%d %H:%M:%S", local_time);
    printf("[%s]%s\n", time_str, str);
}
int main(void)
{
    LOG("hello world")
    TODO("Func1")
    return 0;
}
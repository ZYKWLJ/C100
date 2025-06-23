#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct queue_
{
    int arr[100];
    int L;
    int R;
} queue_t;

// 初始化队列
queue_t* queue_init(){
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    q->L = 0;     // 队首索引初始化为0
    q->R = 0;     // 队尾索引初始化为0
    return q;
}
void queue_basic_border_err(queue_t *queue)
{
    if (queue->L < 0 || queue->L >= 100||queue->R < 0 || queue->R >= 100)
    {
        fprintf(stderr, "queue border error\n");
        return;
    }
}
int queue_size(queue_t *queue)
{
    queue_basic_border_err(queue);
    return queue->R- queue->L;
}

void queue_overflow_err(queue_t *queue)
{
    queue_basic_border_err(queue);
    if (queue_size(queue) > 100)
    {
        fprintf(stderr, "queue overflow error\n");
        return;
    }
}
void queue_underflow_err(queue_t *queue)
{
    queue_basic_border_err(queue);
    if (queue_size(queue) < 0)
    {
        fprintf(stderr, "queue underflow error\n");
        return;
    }
}
// 判断队列是否为空
bool queue_empty(queue_t* q){
    return q->L == q->L;
}

// 入队列（从队尾添加）
void queue_push(queue_t* q, int node){
    q->arr[q->R++] = node;
}

// 出队列（从队首取出）
int queue_pop(queue_t* q){
    return q->arr[q->L++];
}

// 获取队列首元素
int queue_front(queue_t* q){
    return q->arr[q->L];
}
void queue_print(queue_t *queue)
{
    queue_underflow_err(queue);
    queue_overflow_err(queue);
    for (int i = queue->L ; i < queue->R; i++)
    {
        printf("%d ", queue->arr[i]);
    }
    printf("\n");
}

int main(void)
{

    queue_t *st = queue_init();
    queue_print(st);

    for (int i = 0; i < 50; i++)
    {
        queue_push(st, i);
    }
    queue_print(st);
    printf("size:%d\n", queue_size(st));
    queue_pop(st);
    queue_print(st);
    printf("size:%d\n", queue_size(st));
    return 0;
}
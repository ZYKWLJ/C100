#include <stdio.h>
#include <stdlib.h>
typedef struct queue_
{
    int arr[100];
    int in;
    int out;
} queue_t;

queue_t *queue_init()
{
    queue_t *queue = (queue_t *)malloc(sizeof(struct queue_));
    /**
     * data descp: 起点都在最中间的100，然后往两边扩张.左右指针刚好交替的。
     */
    queue->out = 99;
    queue->in = 99;
    for (int i = 0; i < 100; i++)
    {
        queue->arr[i] = INT_MIN;
    }
    return queue;
}
void queue_basic_border_err(queue_t *queue)
{
    if (queue->in < 0 || queue->out >= 200)
    {
        fprintf(stderr, "queue border error\n");
        return;
    }
}
int queue_size(queue_t *queue)
{
    queue_basic_border_err(queue);
    return queue->out - queue->in + 1;
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
void queue_push(queue_t *queue, int val)
{
    queue_overflow_err(queue);
    queue->arr[queue->in--] = val;
}

int queue_pop(queue_t *queue)
{
    queue_underflow_err(queue);
    return queue->arr[--queue->out];
}
int queue_peek(queue_t *queue)
{
    queue_underflow_err(queue);
    return queue->arr[queue->out - 1];
}
void queue_print(queue_t *queue)
{
    queue_underflow_err(queue);
    queue_overflow_err(queue);
    for (int i = queue->in + 1; i <= queue->out; i++)
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
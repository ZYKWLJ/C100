#include <stdio.h>
#include <stdlib.h>
typedef struct stack_
{
    int arr[100];
    int top;
} stack_t;

stack_t *stack_init()
{
    stack_t *stack = (stack_t *)malloc(sizeof(struct stack_));
    stack->top = 0;
    for (int i = 0; i < 100; i++)
    {
        stack->arr[i] = 0;
    }
    return stack;
}

void stack_overflow_err(stack_t *stack)
{
    if (stack->top >= 100)
    {
        fprintf(stderr, "stack overflow error\n");
        return;
    }
}
void stack_underflow_err(stack_t *stack)
{
    if (stack->top <= 0)
    {
        fprintf(stderr, "stack underflow error\n");
        return;
    }
}
void stack_push(stack_t *stack, int val)
{
    stack_overflow_err(stack);
    stack->arr[stack->top++] = val;
}

int stack_pop(stack_t *stack)
{
    stack_underflow_err(stack);
    return stack->arr[--stack->top];
}
int stack_peek(stack_t *stack)
{
    stack_underflow_err(stack);
    return stack->arr[stack->top - 1];
}
void stack_print(stack_t *stack)
{
    stack_underflow_err(stack);
    for (int i = 0; i < stack->top; i++)
    {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}
int stack_size(stack_t *stack)
{
    return stack->top;
}
int main(void)
{
    stack_t *st = stack_init();
    for (int i = 0; i < 5; i++)
    {
        stack_push(st, i);
    }
    stack_print(st);
    printf("size:%d\n", stack_size(st));
    stack_pop(st);
    stack_print(st);
    printf("size:%d\n", stack_size(st));
    return 0;
}
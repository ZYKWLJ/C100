#ifndef BITCASK_H_
#define BITCASK_H_

#include <stdio.h>

/**
 * data descp: bitcask系统
 */
typedef struct bitcask_
{
    bitcask_single_index_t *index;
    bitcask_log_t *log;
} bitcask_t;
/**
 * func descp: 初始化bitcask，最开始时，是没有index的，后面在创建的
 */
bitcask_t *bitcask_t_init(bitcask_log_t *log);

/**
 * func descp: 第一次访问，根据log建立index，并且构建完成bitcask
 */
bitcask_t *first_visit_create_index(bitcask_t *bitcask, bitcask_log_t *log);

#endif /* BITCASK_H_ */

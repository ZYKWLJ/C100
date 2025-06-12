#ifndef PARSER_H_
#define PARSER_H_

#include <stdlib.h>
#include <stdio.h>

void print_help_curd();

#define AUTHOR "Author: EthanYankang"
#define WECHAT "Wechat: 2126483838"
#define GITHUB "Github: https://github.com/ZYKWLJ/C_skip_list"
#define LINK "HelpRefence: https://blog.csdn.net/m0_68657832/article/details/147869804"

void author();
void logo();

void honeydb();

void menu();

void argc1();
void argc3(char *argv[]);
void argc4(char *argv[]);

void parser(int argc, char *argv[]);
#endif /* PARSER_H_ */

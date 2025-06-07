#include <stdio.h>

int main() {
    printf("Level 4:    1 -------------------------------------------------> 100\n");
    printf("            |                                                     |\n");
    printf("            v                                                     v\n");
    printf("Level 3:    1 -----------> 10 -----------------------> 70 -----> 100\n");
    printf("            |              |                           |          |\n");
    printf("            v              v                           v          v\n");
    printf("Level 2:    1 -----------> 10 -----> 30 -------------> 70 -----> 100\n");
    printf("            |              |         |                 |          |\n");
    printf("            v              v         v                 v          v\n");
    printf("Level 1:    1 -> 4 ------> 10 -----> 30 -------------> 70 -----> 100\n");
    printf("            |              |         |                 |          |\n");
    printf("            v              v         v                 v          v\n");
    printf("Level 0:    1 -> 4 -> 9 -> 10 -----> 30 -> 40 -> 60 -> 70 -----> 100\n");
    
    return 0;
}
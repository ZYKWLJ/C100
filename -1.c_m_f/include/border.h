#ifndef BORDER_H_
#define BORDER_H_
#include <string.h>

/*border column 1 & 5*/
void border_1_5(const char *str, int i);
/*border column 2 & 4*/
void border_2_4(const char *str, int i);
/*border column 3*/
void border_3(const char *str, int i);
void border_print(const char *str, int i);

#endif /* BORDER_H_ */
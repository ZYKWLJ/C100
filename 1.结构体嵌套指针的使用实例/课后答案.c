#include <stdio.h>
#include <stdlib.h>
struct person_
{
    char name[20];
    char *subject[20];
} *person;
void print_person(struct person_ *person)
{
    printf("name: %s\n", person->name);
    for (int i = 0; i < 3; i++)
    {
        printf("subject[%d]: %s\n", i, person->subject[i]);
    }
    puts("");
}
int main(void)
{
    person = (struct person_ *)malloc(sizeof(struct person_) * 1);
    sprintf(person->name, "%s", "Ethan");
    for (int i = 0; i < 3; i++)
    {
        person->subject[i] = (char *)malloc(sizeof(char) * 10);
        sprintf(person->subject[i], "%s-%d", "subject", i);
    }
    print_person(person);
    return 0;
}
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* я добавила очередь, будем реализовывать через очередь, мне кажется это самым рациональным решением
очередь почти правильно работает, только почему-то сжирает первый спецификатор, зато остальные номрмально выводит*/

#define QMAX 100
int token_format(const char* format);
struct queue {
    char qu[QMAX];
    char rear, frnt;
};

void init(struct queue* q) {
    q->frnt = 1;
    q->rear = 0;
    return;
}

int isempty(struct queue* q) {
    if (q->rear < q->frnt)    return 1;
    else  return 0;
}

void insert(struct queue* q, char *x) {
    if (q->rear < QMAX - 1) {
        q->rear++;
        q->qu[q->rear] = *x;
    }
    return;
}
char removex(struct queue* q) {
    char x;
     int h;
    if (isempty(q) == 1) {
        return 0;
    }
    x = q->qu[q->frnt];
    for (h = q->frnt; h < q->rear; h++) {
        q->qu[h] = q->qu[h + 1];
    }
    q->rear--;
    return x;
}
void print(struct queue* q) {
    int h;
    if (isempty(q) == 1) {
        printf("pizdec pusto!\n");
        return;
    }
    for (h = q->frnt; h <= q->rear; h++)
        printf("%c ", q->qu[h]);
    return;
}
/*Я пока использовала сишные функции, потом думала заменить. У нас есть свой strtok, но он 
один не может обрабатывать несколько строк сразу, потому что в нем лежит указатель на строку. 
Пока что заменила на strtok_r, он может работать с несколькими строками. Потом либо свой напишем,
либо не будем одновременно обрабатывать строки.
*/
/*int s21_sscanf(const char* str, const char* format, ...) {


  char *saveptr1, *saveptr2;
  char *format_str = malloc((strlen(format) + 1)*sizeof(const char*));
  char *string = malloc((strlen(str) + 1) * sizeof(const char*));
  strcpy(format_str, format);
  strcpy(string, str);

  char *format_token = strtok_s(format_str, "%", &saveptr1);
  char *string_token = strtok_s(string, " \n\t\r", &saveptr2);
  while (format_token)
  {
    printf("specifier: %s\n", format_token);
    printf("str: %s\n", string_token);
    format_token = strtok_s(NULL, "%", &saveptr1);
    string_token = strtok_s(NULL, " \n\t\r", &saveptr2);
  }
  return 0;
}*/

int main(int argc, char **argv) {
  int d;
  char s[30];
  // sscanf("str\n1 2 str", "%s%d",s, &d);
  // printf("d: %d\n", d);
  // printf("str: %s\n", s);
  //s21_sscanf("Some string", "%d%s", &d, s);
  token_format("%s%d%l%n%s%d");
}


int token_format(const char *format) {
    struct queue* format_string;
    format_string = (struct queue*)malloc(sizeof(struct queue));
    init(format_string);
    char* temp = malloc(sizeof(char));
    char* temp_format = malloc(strlen(format) * sizeof(char));
    strcpy(temp_format, format);
    strtok_s(temp_format, "%", &temp);
    insert(format_string, temp);
    while (strtok_s(NULL, "%", &temp) != NULL) {
        insert(format_string, temp);
    }
    print(format_string);

    return 0;
}

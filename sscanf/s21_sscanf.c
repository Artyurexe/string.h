#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*Я пока использовала сишные функции, потом думала заменить. У нас есть свой strtok, но он 
один не может обрабатывать несколько строк сразу, потому что в нем лежит указатель на строку. 
Пока что заменила на strtok_r, он может работать с несколькими строками. Потом либо свой напишем,
либо не будем одновременно обрабатывать строки.
*/
int s21_sscanf(const char *str, const char *format, ...) {
  char *saveptr1, *saveptr2;
  char *format_str = malloc(strlen(format) + 1);
  char *string = malloc(strlen(str) + 1);
  strcpy(format_str, format);
  strcpy(string, str);

  char *format_token = strtok_r(format_str, "%", &saveptr1);
  char *string_token = strtok_r(string, " \n\t\r", &saveptr2);
  while (format_token)
  {
    printf("specifier: %s\n", format_token);
    printf("str: %s\n", string_token);
    format_token = strtok_r(NULL, "%", &saveptr1);
    string_token = strtok_r(NULL, " \n\t\r", &saveptr2);
  }
  return 0;
}

int main(int argc, char **argv) {
  int d;
  char s[30];
  // sscanf("str\n1 2 str", "%s%d",s, &d);
  // printf("d: %d\n", d);
  // printf("str: %s\n", s);
  s21_sscanf("Some string", "%d%s", &d, s);
}

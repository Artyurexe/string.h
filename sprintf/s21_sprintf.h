#ifndef SRC_SPRINTF_S21_SPRINTF_H_
#define SRC_SPRINTF_S21_SPRINTF_H_

#include "../standard_functions/s21_string.h"
#include <stdarg.h>

struct specifier {
  char flag[4];
  char width[310];
  char precision[310];
  char length;
  char type[3];
};

int s21_sprintf(char *str, const char *format, ...);
int specifier_parsing(char* str, va_list* ap);
void vararg_init(char type, va_list *ap);
void specifier_init(struct specifier* spec);
int star_check(int length, char* str);

#endif  // SRC_SPRINTF_S21_SPRINTF_H_
#ifndef SRC_SPRINTF_S21_SPRINTF_H_
#define SRC_SPRINTF_S21_SPRINTF_H_

#include "../standard_functions/s21_string.h"
#include <stdarg.h>

struct specifier {
  char flag[4];
  char width[310];
  char precision[310];
  char length[3];
  char type;
};

int s21_sprintf(char *str, const char *format, ...);
int specifier_parsing(char *str, struct specifier* spec);
void vararg_init(char type, va_list *ap);
void specifier_init(struct specifier* spec);
int star_check(char* str);

#endif  // SRC_SPRINTF_S21_SPRINTF_H_
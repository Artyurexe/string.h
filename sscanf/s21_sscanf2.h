#ifndef SRC_SPRINTF_S21_SSCANF_H_
#define SRC_SPRINTF_S21_SSCANF_H_

// #include "s21_string.h"
#include <stdarg.h>

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct specifier {
  char flag[4];
  char width[310];
  char precision[310];
  char length[3];
  char type;
};

void s21_sprintf(char *str, const char *format, ...);
void specifier_parsing(char *str, struct specifier* spec);
void numbers_parsing(char* str, char* buff);
void pointer_shift(size_t* length, char* buff, char* buff1, const char* str);
void vararg_init(char type, va_list *ap);
void specifier_init(struct specifier* spec);
void match_str_and_format(char *str, struct specifier spec);

#endif  // SRC_SPRINTF_S21_SPRINTF_H_

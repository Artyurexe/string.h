#ifndef SRC_sscanf_S21_SSCANF_H_
#define SRC_sscanf_S21_SSCANF_H_

// #include "s21_string.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define flags_char "CcsS"
#define flags_int "diouxn"
#define flags_float "EeFfGgAa"
#define width_float "L"
#define width_int_char "h"
#define width_shared "l"
#define width_num "0123456789"

struct specifier {
  char flag[4];
  char width[310];
  char precision[310];
  char length[3];
  char type;

};


enum type_flag {
  SHARED,
  CHAR_INT,
  CHAR_FLAG,
  INT_FLAG,
  FLOAT_FLAG,
};

void s21_sprintf(char *str, const char *format, ...);
void specifier_parsing(char *str, struct specifier* spec);
void numbers_parsing(char* str, char* buff);
void pointer_shift(size_t* length, char* buff, char* buff1, const char* str);
void vararg_init(char type, va_list* ap);
void specifier_init(struct specifier* spec);
void match_str_and_format(char* str, struct specifier *spec, va_list* ap, int read_buf_size);
int check_falid_format(const char* format, char* string);
#endif  // SRC_sscanf_s21_sscanf_H_

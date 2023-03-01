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

int s21_sscanf(const char *str, const char *format, ...);
void specifier_parsing(char *str, struct specifier* spec);
void numbers_parsing(char* str, char* buff);
void pointer_shift(char** buff, char* buff1, const char* str);
void vararg_init(char type, va_list* ap);
void specifier_init(struct specifier* spec);
int match_str_and_format(char* str, struct specifier *spec, va_list* ap, int *j, char c);
int check_falid_format(const char *format);
int s21_isspace(char c);
int read_d(char *str, va_list *ap, struct specifier *spec, int *j, char c);
int read_s(char *str, va_list *ap, struct specifier *spec, int *j);
int read_c(char *str, va_list *ap, struct specifier *spec, int *j);
int read_u(char *str, va_list *ap, struct specifier *spec, int *j, char c);
int read_o(char *str, va_list *ap, struct specifier *spec, int *j, char c);
int read_xX(char *str, va_list *ap, struct specifier *spec, int *j, char c);
int read_f(char *str, va_list *ap, struct specifier *spec, int *j, char c);
int read_i(char *str, va_list *ap, struct specifier *spec, int *j, char c);
int s21_isdigit(char c);
int s21_empty_str(char *str);
// int s21_isunsigned(char c);
int s21_ishex(char c);
int s21_isoctal(char c);
#endif  // SRC_sscanf_s21_sscanf_H_

#ifndef SRC_SPRINTF_S21_SPRINTF_H_
#define SRC_SPRINTF_S21_SPRINTF_H_

#include <stdarg.h>
#include <wchar.h>
#include "../standard_functions/s21_string.h"

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
void pointer_shift(s21_size_t* length, char** buff, char* buff1, const char* str);
void specifier_init(struct specifier* spec);
void record(char *str, struct specifier spec, va_list *ap);
void record_int(char *str, struct specifier spec, va_list *ap);
void record_u_int(char *str, struct specifier spec, va_list *ap);
void numcat(char* str, char* buff, long long token, struct specifier spec, va_list *ap);
void u_numcat(char* str, char* buff, unsigned long long token, struct specifier spec, va_list *ap);
void cat_str(char* str, char* str2, int length_diff, char* filler);
void int_to_string(char* str, long long num);
void u_int_to_string(char* str, unsigned long long num);
void num_conversion(unsigned long long n, int base, char sign, char *outbuf, struct specifier spec);
int record_char(char *str, struct specifier spec, va_list *ap);
int record_str(char *str, struct specifier spec, va_list *ap);

#endif  // SRC_SPRINTF_S21_SPRINTF_H_
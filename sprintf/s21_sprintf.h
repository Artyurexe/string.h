#ifndef SRC_SPRINTF_S21_SPRINTF_H_
#define SRC_SPRINTF_S21_SPRINTF_H_

#include <stdarg.h>
#include <math.h>
#include <wchar.h>
#include "../standard_functions/s21_string.h"

struct specifier {
  char flag[4];
  char width[310];
  char precision[310];
  char length[3];
  char type;
};
char* dec_to_hex(long long dec);
void pointer_shift(char** buff, char* buff1, const char* str);
void record_f(char *temp, long double num, s21_size_t precision, char type, long long exp, char* flag);
void record_e(char *temp, long double num, s21_size_t precision, char type, char other_type, long long exp, char* flag);
long long count_exp(long double num);
void record(char *str, struct specifier spec, va_list *ap);
int record_double(char *str, struct specifier *spec, va_list *ap);
void s21_sprintf(char *str, const char *format, ...);
void specifier_parsing(char *str, struct specifier* spec);
void numbers_parsing(char* str, char* buff);
void pointer_shift(char** buff, char* buff1, const char* str);
void specifier_init(struct specifier* spec);
void record(char *str, struct specifier spec, va_list *ap);
void record_int(char *str, struct specifier spec, va_list *ap);
void record_u_int(char *str, struct specifier spec, va_list *ap);
void numcat(char* str, long long token, struct specifier spec, va_list *ap);
void u_numcat(char* str, unsigned long token, struct specifier spec, va_list *ap);
void length_init(char* str, int* num, va_list* ap);
void fill_str(char* str, char* str1, s21_size_t length_diff, char* filler);
void int_to_string(char* str, long long num);
void u_int_to_string(char* str, unsigned long num);
void num_conversion(unsigned long n, int base, char *outbuf, struct specifier spec);
int record_char(char *str, struct specifier spec, va_list *ap);
int record_str(char *str, struct specifier spec, va_list *ap);
void record(char *str, struct specifier spec, va_list *ap);
void record_pointer(char *str, struct specifier spec, va_list *ap);

#endif  // SRC_SPRINTF_S21_SPRINTF_H_
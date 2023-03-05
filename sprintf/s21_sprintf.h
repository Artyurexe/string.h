#ifndef SRC_SPRINTF_S21_SPRINTF_H_
#define SRC_SPRINTF_S21_SPRINTF_H_

#include <stdarg.h>
#include <math.h>
#include <wchar.h>
#include "../standard_functions/s21_string.h"
#include <float.h>
#define S21_isnan(x) ((x) != x)
#define S21_isinf(x) (!S21_isnan(x) && S21_isnan(x - x))
struct specifier {
  char flag[4];
  char* width;
  char precision[310];
  char length[3];
  char type;
};

long long s21_atoi(char *str);
char* dec_to_hex(long long dec);
void pointer_shift(char** buff, char* buff1, const char* str);
void record_f(char *temp, long double num, s21_size_t precision, char type, long long exp, char* flag);
void record_e(char *temp, long double num, s21_size_t precision, char type, char other_type, long long exp, char* flag);
long long count_exp(long double num);
void record(char *str, struct specifier spec, va_list *ap);
int record_double(char *str, struct specifier *spec, va_list *ap);
void specifier_parsing(char *str, struct specifier* spec, va_list *ap);
void numbers_parsing(char* str, char* buff, struct specifier* spec, va_list *ap);
void pointer_shift(char** buff, char* buff1, const char* str);
void specifier_init(struct specifier* spec);
void record(char *str, struct specifier spec, va_list *ap);
void record_int(char *str, struct specifier spec, va_list *ap);
void record_u_int(char *str, struct specifier spec, va_list *ap);
void numcat(char* str, long long token, struct specifier spec);
void u_numcat(char* str, unsigned long token, struct specifier spec);
void sign_input(char* str, char* str1, int precision, int* length, char* fill, struct specifier spec);
void fill_str(char* str, char* str1, s21_size_t length_diff, char* filler);
void int_to_string(char* str, long long num);
void u_int_to_string(char* str, unsigned long num);
void num_conversion(unsigned long n, int base, char *outbuf, struct specifier spec);
int record_char(char *str, struct specifier spec, va_list *ap);
int record_str(char *str, struct specifier spec, va_list *ap);
void record(char *str, struct specifier spec, va_list *ap);
void record_pointer(char *str, struct specifier spec, va_list *ap);
void record_nan_inf(char* str, long double num, struct specifier *spec, s21_size_t width);

#endif  // SRC_SPRINTF_S21_SPRINTF_H_
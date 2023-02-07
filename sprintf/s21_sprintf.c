#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  int err_num = 0;
  va_list ap;
  va_start(ap, format);
  s21_size_t spec_num = 0;
  struct specifier* spec = S21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(format) && err_num == 0; i++) {
    specifier_init(&spec);
    if (format[i] == '%') {
      err_num = specifier_parsing(&format[i + 1], &spec);
      i += strcspn(&format[i + 1], types) + 1;
    }
  }
}

int specifier_parsing(char *str, struct specifier* spec) {
  int err_num = 0;
  char buff[1024] = S21_NULL;
  const char* flags = "-+ #0";
  const char* numbers = "1234567890*";
  const char* length = "hlL";
  const char* types = "cdieEfgGosuxXpn%%";
  spec_length = strcspn(&format[i + 1], types) + 1
  s21_memcpy(buff, str, spec_length);
  spec->type = str[spec_length - 1];
  s21_size_t spec_length = s21_strspn((const char*) buff, flags);
  s21_memcpy(spec->flag, buff, spec_length);
  buff += spec_length;
  spec_length = s21_strspn((const char*) buff, numbers);
  s21_memcpy(spec->width, buff, spec_length);
  err_num = star_check(spec->width);
  buff += spec_length;
  if (*(buff + 1) == '.') {
    spec_length = s21_strspn((const char*) buff, numbers);
    err_num = star_check(spec->precision);
    buff += (spec_length + 1);
  }
  s21_memcpy(spec->length, buff, s21_strspn((const char*) buff, length));
  return err_num;
}

int star_check(char* str) {
  return (s21_strlen(str) != 1 && s21_strchr(str, '*') != S21_NULL);
}

void vararg_init(char type, va_list *ap) {
  if (type == 'c') {
    va_arg(*ap, char);
  } else if (type == 'd' || type == 'i') {
    va_arg(*ap, int);
  } else if (type == 'e' || type == 'E' || type == 'f' || type == 'g' || type == 'G' ) {
    va_arg(*ap, double);
  } else if (type == 'o' || type == 'u' || type == 'x' || type == 'X') {
    va_arg(*ap, unsigned int);
  } else if (type == 's') {
    va_arg(*ap, char *);
  } else if (type == 'p') {
    va_arg(*ap, void *);
  } else if (type == 'n') {
    va_arg(*ap, int *);
  } 
}

void specifier_init(struct specifier* spec) {
  spec->flag = S21_NULL;
  spec->width = S21_NULL;
  spec->precision = S21_NULL;
  spec->length = S21_NULL;
  spec->type = 0;
}

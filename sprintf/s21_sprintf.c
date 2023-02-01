#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  char* types = "cdieEfgGosuxXpn%%";
  va_list ap;
  va_start(ap, format);
  s21_size_t spec_num = 0;
  struct specifier* spec = S21_NULL;
  specifier_init(&spec);
  for (s21_size_t i = 0; i < s21_strlen(format); i++) {
    if (format[i] == 37) {
      
      specifier_parsing(&format[i + 1]), strcspn(&format[i + 1]) + 1, &spec);
    }
  }
}

void specifier_parsing(char *str, s21_size_t length, struct specifier* spec) {
  char type = str[length];
  vararg_init(type, ap);
}

void vararg_init(char type, va_list *ap) {
  if (type == 'c') {
    va_arg(*ap, char);
  } else if (type == 'd' || type == 'i') {
    va_arg(*ap, int);
  } else if (type == 'e' || type == 'E' || type == 'f' || type == 'g' || type == 'G' ) {
    va_arg(*ap, double);
  } else if (type == 'o' || type == 'u' || type == 'x' || type == 'X') {
    va_arg(*ap, unsinged int);
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

int main() {
  va_list ap;
  printf("%p", ap);
  return 1;
}
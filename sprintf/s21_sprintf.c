#include "s21_sprintf.h"

void s21_sprintf(char *str, const char *format, ...) {
  const char* types = "cdieEfgGosuxXpn%%";
  va_list ap;
  char test[100];
  test[0] = '\0';
  va_start(ap, format);
  struct specifier spec;
  for (s21_size_t i = 0; i < s21_strlen(format); i++) {
    specifier_init(&spec);
    if (format[i] == '%') {
      specifier_parsing((char*) &format[i + 1], &spec);
      i += s21_strcspn(&format[i + 1], types) + 1;
      printf("%s %s %s %s %c\n", spec.flag, spec.length, spec.precision, spec.width, spec.type);
    }
  }
}

void specifier_parsing(char *str, struct specifier* spec) {
  char *buff = malloc(1024);
  char *buff1 = malloc(1024);
  int k = 0;
  const char* flags = "-+ #0";
  const char* numbers = "1234567890*";
  const char* length = "hLl";
  const char* types = "cdieEfgGosuxXpn%%";
  s21_size_t spec_length = s21_strcspn(str, types) + 1;
  s21_memcpy(buff, str, spec_length);
  spec->type = str[spec_length - 1];
  spec_length = s21_strspn((const char*) buff, flags);
  s21_memcpy(buff1, buff, spec_length);
  for (int i = 0; i < 5; i++) {
    if (s21_strchr(buff1, flags[i]) != S21_NULL)
      spec->flag[k++] = flags[i];
  }
  spec->flag[k] = '\0';
  k = 0;
  buff += spec_length;
  spec_length = s21_strspn((const char*) buff, numbers);
  s21_memcpy(spec->width, buff, spec_length);
  buff += spec_length;
  if (*(buff + 1) == '.') {
    spec_length = s21_strspn((const char*) buff, numbers);
    buff += (spec_length + 1);
  }
  s21_memcpy(buff1, buff, s21_strspn((const char*) buff, length));
  for (int i = 0; i < 3; i++) {
    char* c = s21_strchr(buff1, length[i]);
    if (c != S21_NULL) {
      if (length[i] == 'L' || (length[i] == 'h' && c < s21_strchr(buff1, 'l')) || (length[i] == 'l' && s21_strchr(c, length[i]) == S21_NULL && spec.length[0] != 'h')) {
        spec->length[k++] = length[i];
      } else {
        spec->length[k++] = length[i];
        spec->length[k++] = length[i];
      } 
    }
  }
  spec->length[k] = '\0';
  free(buff);
  free(buff1);
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
  spec->flag[0] = '\0';
  spec->width[0] = '\0';
  spec->precision[0] = '\0';
  spec->length[0] = '\0';
  spec->type = 0;
}

void record(char *str, struct specifier spec, va_list *ap) {
  if (spec.type == 'c') {


  } else if (spec.type == 'd' || spec.type == 'i') {
    
  } else if (spec.type == 'e' || spec.type == 'E' || spec.type == 'f' || spec.type == 'g' || spec.type == 'G' ) {
    double num = va_arg(*ap, double);
  } else if (spec.type == 'o' || spec.type == 'u' || spec.type == 'x' || spec.type == 'X') {
    unsigned int num = va_arg(*ap, unsigned int);
  } else if (spec.type == 's') {
    char *str = va_arg(*ap, char *);
  } else if (spec.type == 'p') {
    void *pointer = va_arg(*ap, void *);
  } else if (spec.type == 'n') {
    int *arr = va_arg(*ap, int *);
  }

}

void record_char(char *str, struct specifier spec, va_list *ap) {
  if (s21_strchr(spec.flag, "l"))
    char c = va_arg(*ap, char);
  if (s21_strspn(spec.flag, "Ll") != 0)
}

int main() {
  char test[] = "%+0ls";
  char str[100];
  s21_sprintf(str, test, "hey");
}
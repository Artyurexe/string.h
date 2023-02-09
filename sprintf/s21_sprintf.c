#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  int err_num = 0;
  const char* types = "cdieEfgGosuxXpn%%";
  va_list ap;
  char test[100];
  test[0] = '\0';
  va_start(ap, format);
  s21_size_t spec_num = 0;
  struct specifier spec;
  for (s21_size_t i = 0; i < s21_strlen(format) && err_num == 0; i++) {
    specifier_init(&spec);
    if (format[i] == '%') {
      err_num = specifier_parsing((char*) &format[i + 1], &spec);
      i += s21_strcspn(&format[i + 1], types) + 1;
      printf("%s %s %s %s %c\n", spec.flag, spec.length, spec.precision, spec.width, spec.type);
    }
  }
  return err_num;
}

int specifier_parsing(char *str, struct specifier* spec) {
  int err_num = 0;
  char *buff = malloc(1024);
  const char* flags = "-+ #0";
  const char* numbers = "1234567890*";
  const char* length = "hlL";
  const char* types = "cdieEfgGosuxXpn%%";
  s21_size_t spec_length = s21_strcspn(str, types) + 1;
  s21_memcpy(buff, str, spec_length);
  spec->type = str[spec_length - 1];
  spec_length = s21_strspn((const char*) buff, flags);
  s21_memcpy(spec->flag, buff, spec_length);
  buff += spec_length;
  spec_length = s21_strspn((const char*) buff, numbers);
  s21_memcpy(spec->width, buff, spec_length);
  err_num = star_check(spec->width);
  buff += spec_length;
  if (*(buff + 1) == '.' && err_num == 0) {
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
  spec->flag[0] = '\0';
  spec->width[0] = '\0';
  spec->precision[0] = '\0';
  spec->length[0] = '\0';
  spec->type = 0;
}

void record(char *str, struct specifier spec, va_list *ap) {
  if (spec.type == 'c') {


  } else if (spec.type == 'd' || spec.type == 'i') {
    int num = va_arg(*ap, int);
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

int record_char(char *str, struct specifier spec, va_list *ap) {
  s21_size_t width = 0;
  if (s21_strlen(spec.width) != 0) {
    width = atoi(spec.width);
    if (!width)
      return 1;
    if (s21_strchr(spec.flag, '-') == S21_NULL)
      for(int i = 0; i < width - 1; i++)
        s21_strcat(str, " ");
  }
  if (s21_strchr(spec.length, 'l')) {
    wchar_t wc = va_arg(*ap, wchar_t);
    if (wcstombs(str + s21_strlen(str), &wc, 1) == 0)
      return 1;
  }
  else {
    char c = va_arg(*ap, char);
    s21_size_t len = s21_strlen(str);
    str[len] = c;
    str[len + 1] = '\0';
  }
  if (width && s21_strchr(spec.flag, '-'))
    for(int i = 0; i < width - 1; i++)
        s21_strcat(str, " ");
  return 0;
}

int record_str(char *str, struct specifier spec, va_list *ap) {
  s21_size_t width = 0;
  if (s21_strlen(spec.width) != 0) {
    width = atoi(spec.width);
    if (!width)
      return 1;
  }
  if (s21_strchr(spec.length, 'l')) {
    wchar_t *ws = va_arg(*ap, wchar_t*);
    width -= wcslen(ws);
    if (width) {
      for(int i = 0; i < width; i++)
        s21_strcat(str, " ");
    }
    if (wcstombs(str + s21_strlen(str), ws, wcslen(ws) * sizeof(wchar_t)) == 0)
      return 1;
  }
  else {
    char* s = va_arg(*ap, char*);
    s21_size_t len = s21_strlen(str);
    width -= s21_strlen(s);
    if (width) {
      for(int i = 0; i < width; i++)
        s21_strcat(str, " ");
    }
    strcat(str, s);
  }
  if (width && s21_strchr(spec.flag, '-'))
    for(int i = 0; i < width; i++)
        s21_strcat(str, " ");
  return 0;
}

int main() {
  char test[] = "%+0ls";
  char str[100];
  s21_sprintf(str, test, "hey");
}
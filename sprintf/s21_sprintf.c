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

void specifier_parsing(char *str, struct specifier* spec) {
  char* buff = str;
  char* buff1 = malloc(1024);
  int k = 0;
  const char* flags = "-+ #0";
  const char* numbers = "1234567890*";
  const char* length = "hlL";
  const char* types = "cdieEfgGosuxXpn%%";
  s21_size_t spec_length = s21_strcspn(str, types);
  spec->type = str[spec_length];
  pointer_shift(&spec_length, buff, buff1, flags);
  for (int i = 0; i < 5; i++) {
    if (s21_strchr(buff1, flags[i]) != S21_NULL && ((flags[i] == ' ' && s21_strchr(buff1, '+') == S21_NULL) || (flags[i] == '0' && s21_strchr(buff1, '-') == S21_NULL)))
      spec->flag[k++] = flags[i];
  }
  spec->flag[k] = '\0';
  k = 0;
  pointer_shift(&spec_length, buff, buff1, numbers);
  numbers_parsing(spec->width, buff1);
  if (*(buff++) == '.') {
    pointer_shift(&spec_length, buff, buff1, numbers);
    numbers_parsing(spec->precision, buff1);
  }
  s21_memcpy(buff1, buff, s21_strspn((const char*) buff, length));
  for (int i = 0; i < 3; i++) {
    char* c = s21_strchr(buff1, length[i]);
    if (c != S21_NULL) {
      if (length[i] == 'L' || (length[i] == 'h' && c < s21_strchr(buff1, 'l')) || (length[i] == 'l' && s21_strchr(c, length[i]) == S21_NULL && spec.length[0] != 'h')) {
        spec->length[k++] = length[i];
      } else if (length[i] == 'l' && s21_strchr(c, length[i]) != S21_NULL && spec.length[0] != 'h') {
        spec->length[k++] = length[i];
        spec->length[k++] = length[i];
      } 
    }
  }
  spec->length[k] = '\0';
  free(buff1);
}

void numbers_parsing(char* str, char* buff) {
  s21_size_t length = s21_strspn((const char*) buff, (const char*) "1234567890");
  if (*buff == '*' && length == 0)
    length = 1;
  s21_memcpy(str, buff, length);
}

void pointer_shift(s21_size_t* length, char* buff, char* buff1, const char* str) {
  *length = s21_strspn((const char*) buff, str);
  s21_memcpy(buff1, buff, *length);
  buff += *length;
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

void record_int(char* str, struct specifier spec, va_list *ap) {
  if (s21_strchr(spec.flag, "l"))
    char c = va_arg(*ap, char);
  if (s21_strspn(spec.flag, "ll") != 0)
    int num = va_arg(*ap, int);
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

int record_double(char *str, struct specifier spec, va_list *ap) {
  s21_size_t width = 0;
  s21_size_t precision = 0;
  s21_size_t exp = 0;
  long double num;
  width = atoi(spec.width);
  precision = atoi(spec.precision);
  if (precision == 0 && s21_strlen(spec.precision) == 0)
    precision = 6;
  if (precision == 0 && s21_strlen(spec.precision) != 0)
    precision = 1;
  
  if (strchr(spec.length, 'l'))
    num = va_arg(*ap, double);
  else if (strchr(spec.length, 'L'))
    num = va_arg(*ap, long double);
  else
    num = va_arg(*ap, float);
  exp = count_exp(num);

}

s21_size_t count_exp(long double num) {
  long double cpy = num;
  cpy = fabs(cpy);
  s21_size_t exp = 0;
  if (cpy >= 10) {
    while ((long long) cpy >=10) {
      exp++;
      cpy /= 10;
    }
  }
  else if (cpy < 1) {
    while ((long long) cpy < 1) {
      exp--;
      cpy *= 10;
    }
  }
  return exp;
}

int main() {
  char test[] = "%+0ls";
  char str[100];
  s21_sprintf(str, test, "hey");
}
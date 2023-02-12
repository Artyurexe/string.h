#include "s21_sprintf.h"

void s21_sprintf(char *str, const char *format, ...) {
  const char* types = "cdieEfgGosuxXpn%%";
  va_list ap;
  va_start(ap, format);
  struct specifier spec;
  for (s21_size_t i = 0; i < s21_strlen(format); i++) {
    specifier_init(&spec);
    if (format[i] == '%') {
      specifier_parsing((char*) &format[i + 1], &spec);
      printf("%s %s %s %s %c\n", spec.flag, spec.length, spec.precision, spec.width, spec.type);
      record(str, spec, &ap);
      i += s21_strcspn(&format[i + 1], types) + 1;
    }
  }
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
      if (length[i] == 'L' || (length[i] == 'h' && c < s21_strchr(buff1, 'l')) || (length[i] == 'l' && s21_strchr(c, length[i]) == S21_NULL && spec->length[0] != 'h')) {
        spec->length[k++] = length[i];
      } else if (length[i] == 'l' && s21_strchr(c, length[i]) != S21_NULL && spec->length[0] != 'h') {
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
    record_int(str, spec, ap);
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

void record_int(char *str, struct specifier spec, va_list *ap) {
  char* buff = malloc(1024);
  if (s21_strchr(spec.length, 'h')) {
    int short_token = va_arg(*ap, int);
    short token = short_token;
    numcat(str, buff, (long long) token, spec, ap);
  } else if (s21_strstr(spec.length, "ll")) {
    long long token = va_arg(*ap, long long);
    numcat(str, buff, token, spec, ap);
  } else if (s21_strchr(spec.length, 'l')) {
    long token = va_arg(*ap, long);
    numcat(str, buff, (long long) token, spec, ap);
  } else {
    int token = va_arg(*ap, int);
    numcat(str, buff, (long long) token, spec, ap);
  }
  free(buff);
}

void numcat(char* str, char* buff, long long token, struct specifier spec, va_list *ap) {
  s21_size_t length = 0;
  int_to_string(buff, token, spec);
  if (spec.width[0] == '*')
    length = va_arg(*ap, int);
  else 
    length = atoi(spec.width);
  s21_size_t buff_length = s21_strlen(buff);
  if (length > buff_length) {
    if (s21_strchr(spec.flag, '-')) {
      s21_strcat(str, buff);
      for (int i = 0; i < length - buff_length; i++, s21_strcat(str, " ")) {}
    } else if (s21_strchr(spec.flag, '0')) {
      cat_str(str, buff, length - buff_length, "0");
    } else
      cat_str(str, buff, length - buff_length, " ");
  } else
    s21_strcat(str, buff);
}

void cat_str(char* str, char* str2, int length_diff, char* filler) {
  for (int i = 0; i < length_diff; i++, s21_strcat(str, filler)) {}
  s21_strcat(str, str2);
}

void int_to_string(char* str, long long num, struct specifier spec) {
  char* buff = str;
  int len = 0;
  if (num > 0) {
    if (s21_strchr(spec.flag, '+') != S21_NULL)
      *(buff++) = '+';
    else if (s21_strchr(spec.flag, ' ') != S21_NULL)
      *(buff++) = ' ';
  }
  if (num < 0) {
    num *= -1;
    *(buff++) = '-';
  }
  long long n = num;
  for (; n != 0; len++, n /= 10) {}
  for (int i = 0; i < len; i++, num /= 10)
    buff[len - (i + 1)] = num % 10 + '0';
  buff[len] = '\0';
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
    char c = va_arg(*ap, int);
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
    s21_strcat(str, s);
  }
  if (width && s21_strchr(spec.flag, '-'))
    for(int i = 0; i < width; i++)
        s21_strcat(str, " ");
  return 0;
}

int main() {
  char str[100] = "\0";
  s21_sprintf(str, "%- 10d", -13423);
  puts(str);
  return 0;
}
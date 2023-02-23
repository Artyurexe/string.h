#include "s21_sprintf.h"

void s21_sprintf(char *str, const char *format, ...) {
  str[0] = '\0';
  const char* types = "cdieEfgGosuxXpn%%";
  va_list ap;
  va_start(ap, format);
  struct specifier spec;
  for (s21_size_t i = 0; i < s21_strlen(format); i++) {
    specifier_init(&spec);
    if (format[i] == '%') {
      specifier_parsing((char*) &format[i + 1], &spec);
      record(str, spec, &ap);
      i += s21_strcspn(&format[i + 1], types) + 1;
    }
  }
}

void specifier_parsing(char *str, struct specifier* spec) {
  char* buff = str;
  char* buff1 = malloc(1024);
  char* buff2 = buff1;
  int k = 0;
  const char* flags = "-+ #0";
  const char* numbers = "1234567890*";
  const char* length = "hlL";
  const char* types = "cdieEfgGosuxXpn%%";
  spec->type = str[s21_strcspn(str, types)];
  pointer_shift(&buff, buff1, flags);
  for (int i = 0; i < 5; i++) {
    if (s21_strchr(buff1, flags[i]) != S21_NULL && ((flags[i] == ' ' && s21_strchr(buff1, '+') == S21_NULL) || (flags[i] == '0' && s21_strchr(buff1, '-') == S21_NULL) || flags[i] == '-' || flags[i] == '+' || flags[i] == '#'))
      spec->flag[k++] = flags[i];
  }
  spec->flag[k] = '\0';
  k = 0;
  pointer_shift(&buff, buff1, numbers);
  numbers_parsing(spec->width, buff1);
  if (*buff == '.') {
    buff++;
    pointer_shift(&buff, buff1, numbers);
    numbers_parsing(spec->precision, buff1);
  }
  s21_memcpy(buff1, buff, s21_strspn((const char*) buff, length));
  for (int i = 0; i < 3; i++) {
    char* c = s21_strchr(buff1, length[i]);
    if (c != S21_NULL) {
      if (length[i] == 'L' || (length[i] == 'h' && c < s21_strchr(buff1, 'l')) || (length[i] == 'l' && s21_strchr(c, length[i + 1]) == S21_NULL && spec->length[0] != 'h')) {
        spec->length[k++] = length[i];
      } else if (length[i] == 'l' && s21_strchr(c, length[i + 1]) != S21_NULL && spec->length[0] != 'h') {
        spec->length[k++] = length[i];
        spec->length[k++] = length[i];
      } 
    }
  }
  spec->length[k] = '\0';
  free(buff2);
}

void numbers_parsing(char* str, char* buff) {
  s21_size_t length = s21_strspn((const char*) buff, "1234567890");
  if (*buff == '*' && length == 0)
    length = 1;
  s21_strncpy(str, buff, length);
  buff[length + 1] = '\0';
}

void pointer_shift(char** buff, char* buff1, const char* str) {
  s21_size_t length = s21_strspn((const char*) *buff, str);
  s21_strncpy(buff1, *buff, length);
  buff1[length] = '\0';
  *buff += length;
}


// void vararg_init(char type, va_list *ap) {
//   if (type == 'c') {
//     va_arg(*ap, char);
//   } else if (type == 'd' || type == 'i') {
//     va_arg(*ap, int);
//   } else if (type == 'e' || type == 'E' || type == 'f' || type == 'g' || type == 'G' ) {
//     va_arg(*ap, double);
//   } else if (type == 'o' || type == 'u' || type == 'x' || type == 'X') {
//     va_arg(*ap, unsigned int);
//   } else if (type == 's') {
//     va_arg(*ap, char *);
//   } else if (type == 'p') {
//     va_arg(*ap, void *);
//   } else if (type == 'n') {
//     va_arg(*ap, int *);
//   } 
// }

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
    record_double(str, &spec, ap);
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

// void record_int(char* str, struct specifier spec, va_list *ap) {
//   if (s21_strchr(spec.flag, "l"))
//     char c = va_arg(*ap, char);
//   if (s21_strspn(spec.flag, "ll") != 0)
//     int num = va_arg(*ap, int);
// }

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

int record_double(char *str, struct specifier *spec, va_list *ap) {
  s21_size_t width = 0;
  s21_size_t precision = 0;
  long long exp = 0;
  long double num;
  width = atoi(spec->width);
  precision = atoi(spec->precision);
  if (precision == 0 && s21_strlen(spec->precision) == 0)
    precision = 6;
  if (precision == 0 && s21_strlen(spec->precision) != 0 && s21_strchr("Gg", spec->type))
    precision = 1;
  else if (precision == 0 && s21_strlen(spec->precision) != 0)
    precision = 0;

  
  if (s21_strchr(spec->length, 'l'))
    num = va_arg(*ap, double);
  else if (s21_strchr(spec->length, 'L'))
    num = va_arg(*ap, long double);
  else {
    float num_temp = va_arg(*ap, double);
    num = num_temp;

  }
  exp = count_exp(num);
  char type = spec->type;
  if (spec->type == 'g' || spec->type == 'G') {
    if (precision > exp && exp >= -4) {
      type = 'f';
      precision = precision - exp - 1;
    }
    else {
      type = spec->type == 'G' ? 'E' : 'e';
      precision--;
    }
  }
  
  char temp[100];
  temp[0] = '\0';
  if (type == 'f') {
    record_f(temp, num, precision, spec->type, exp, spec->flag);
  }
  else {
    record_e(temp, num, precision, spec->type, type, exp, spec->flag);
  }
  if (s21_strchr(spec->flag, '#') && !s21_strchr(temp, '.'))
    s21_strcat(temp, ".");
  if (s21_strlen(temp) < width) {
    s21_size_t cnt = width - s21_strlen(temp);
    char filler[2] = "";
    if (s21_strchr(spec->flag, '0'))
      s21_strcat(filler, "0");
    else
      s21_strcat(filler, " ");
    if (!s21_strchr(spec->flag, '-')) {
      char spaces[100] = "";
      for (int i = 0; i < cnt; i++)
        s21_strcat(spaces, filler);
      s21_strcat(spaces, temp);
      s21_strcpy(temp, spaces);
    }
    else {
      for (int i = 0; i < cnt; i++)
        s21_strcat(temp, " ");
    }
  }
  s21_strcat(str, temp);
  return 0;
}

void record_f(char *temp, long double num, s21_size_t precision, char type, long long exp, char* flag) {
  if (num < 0) {
    s21_strcat(temp, "-");
    num = fabsl(num);
  }
  if (num >=0 && s21_strchr(flag, '+'))
    s21_strcat(temp, "+");
  num = roundl(num * pow(10, precision))/pow(10, precision);
  long long num_int = fabsl(num);
  for (int i = 0; i <= exp; i++) {
    int ind = s21_strlen(temp);
    temp[ind] = (num_int / (long long)(pow(10, exp - i))) % 10 + '0';
    temp[ind + 1] = '\0';
  }
  if (exp < 0)
    s21_strcat(temp, "0");
  if (precision)
    s21_strcat(temp, ".");

  for (int i = 0; i < precision; i++) {
    num *= 10;
    int digit = fmod(num, 10);
    int ind = s21_strlen(temp);
    temp[ind] = digit + '0';
    temp[ind + 1] = '\0';
  }
  // exclude zeros
  if (type == 'g' || type == 'G')
    while(temp[s21_strlen(temp) - 1] == '0')
      temp[s21_strlen(temp) - 1] = '\0';
}

void record_e(char *temp, long double num, s21_size_t precision, char type, char other_type, long long exp, char* flag) {
  num = num / pow(10, exp);
    if (num < 0) {
      s21_strcat(temp, "-");
      num = fabsl(num);
    }
    if (num >=0 && s21_strchr(flag, '+'))
      s21_strcat(temp, "+");
    num = roundl(num * pow(10, precision))/pow(10, precision);
    int num_int = num;
    int ind = s21_strlen(temp);
    temp[ind] = num_int + '0';
    temp[ind + 1] = '\0';
    if (precision)
      s21_strcat(temp, ".");
    
    for (int i = 0; i < precision; i++) {
      num *= 10;
      int digit = fmod(num, 10);
      int ind = s21_strlen(temp);
      temp[ind] = digit + '0';
      temp[ind + 1] = '\0';
    }
    // exclude zeros
    if (type == 'g' || type == 'G')
      while(temp[s21_strlen(temp) - 1] == '0')
        temp[s21_strlen(temp) - 1] = '\0';
    
    if (type == 'G' || other_type == 'E')
      s21_strcat(temp, "E");
    else
      s21_strcat(temp, "e");
    
    if (exp >= 0)
      s21_strcat(temp, "+");
    else
      s21_strcat(temp, "-");
    if (llabs(exp) < 10)
      s21_strcat(temp, "0");
    else {
      int ind = s21_strlen(temp);
      temp[ind] = llabs(exp)/10 + '0';
      temp[ind + 1] = '\0';
    }
    ind = s21_strlen(temp);
    temp[ind] = llabs(exp)%10 + '0';
    temp[ind + 1] = '\0';
}

long long count_exp(long double num) {
  long double cpy = num;
  cpy = fabsl(cpy);
  long long exp = 0;
  if (cpy >= 10) {
    while (cpy >=10) {
      exp++;
      cpy /= 10;
    }
  }
  else if (cpy < 1) {
    while (cpy < 1) {
      exp--;
      cpy *= 10;
    }
  }

  return exp;
}

int main() {
  char test[] = "%.0f";
  char str[100];
  float num = 123.123;
  s21_sprintf(str, test, num);
  puts(str);
}
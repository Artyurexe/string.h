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
    record_double(str, &spec, ap);
  } else if (spec.type == 'o' || spec.type == 'u' || spec.type == 'x' || spec.type == 'X') {
    record_u_int(str, spec, ap);
  } else if (spec.type == 's') {
  } else if (spec.type == 'p') {
  } else if (spec.type == 'n') {
  }

}

void record_int(char *str, struct specifier spec, va_list *ap) {
  if (s21_strchr(spec.length, 'h')) {
    int short_token = va_arg(*ap, int);
    short token = short_token;
    numcat(str, (long long) token, spec, ap);
  } else if (s21_strstr(spec.length, "ll")) {
    long long token = va_arg(*ap, long long);
    numcat(str, token, spec, ap);
  } else if (s21_strchr(spec.length, 'l')) {
    long token = va_arg(*ap, long);
    numcat(str, (long long) token, spec, ap);
  } else {
    int token = va_arg(*ap, int);
    numcat(str, (long long) token, spec, ap);
  }
}

void record_u_int(char *str, struct specifier spec, va_list *ap) {
  if (s21_strchr(spec.length, 'h')) {
    unsigned int short_token = va_arg(*ap, unsigned int);
    unsigned short token = short_token;
    u_numcat(str, (unsigned long) token, spec, ap);
  } else if (s21_strchr(spec.length, 'l')) {
    unsigned long token = va_arg(*ap, unsigned long);
    u_numcat(str, (unsigned long) token, spec, ap);
  } else {
    unsigned int token = va_arg(*ap,unsigned  int);
    u_numcat(str, (unsigned long) token, spec, ap);
  }
}

void numcat(char* str, long long token, struct specifier spec, va_list *ap) {
  char* str1 = malloc(1024);
  char* buff = malloc(1024);
  *buff = 0;
  *str1 = 0;
  s21_size_t length = 0, precision = 0;
  if (token >= 0) {
    if (s21_strchr(spec.flag, '+') != S21_NULL)
      s21_strcat(str1, "+");
    else if (s21_strchr(spec.flag, ' ') != S21_NULL)
      s21_strcat(str1, " ");
  } else {
    token *= -1;
    s21_strcat(str1, "-");
  }
  int_to_string(buff, token);
  length_init(spec.width, &length, ap);
  length_init(spec.precision, &precision, ap);
  s21_size_t buff_length = s21_strlen(buff);
  if (precision > buff_length)
    fill_str(str1, buff, precision - buff_length, "0");
  else
    s21_strcat(str1, buff);
  buff_length = s21_strlen(str1);
  if (length > buff_length) {
    if (s21_strchr(spec.flag, '-')) {
      s21_strcat(str, str1);
      for (s21_size_t i = 0; i < length - buff_length; i++, s21_strcat(str, " ")) {}
    } else if (s21_strchr(spec.flag, '0') && !precision) {
      fill_str(str, str1, length - buff_length, "0");
    } else
      fill_str(str, str1, length - buff_length, " ");
  } else
    s21_strcat(str, str1);
  free(str1);
  free(buff);
}

void u_numcat(char* str, unsigned long token, struct specifier spec, va_list *ap) {
  char* str1 = malloc(1024);
  char* buff = malloc(1024);
  *buff = 0;
  *str1 = 0;
  s21_size_t length = 0, precision = 0;
  if (spec.type == 'o')
    num_conversion(token, 8, buff, spec);
  else if (spec.type == 'x' || spec.type == 'X')
    num_conversion(token, 16, buff, spec);
  else
    u_int_to_string(buff, token);
  length_init(spec.width, &length, ap);
  length_init(spec.precision, &precision, ap);
  s21_size_t buff_length = s21_strlen(buff);
  if (s21_strchr(spec.flag, '#') != S21_NULL) {
    if (spec.type == 'x')
      s21_strcat(str1, "0x");
    else if (spec.type == 'X')
      s21_strcat(str1, "0X");
  }
  if (precision > buff_length)
    fill_str(str1, buff, precision - buff_length, "0");
  else {
    if (spec.type == 'o' && s21_strchr(spec.flag, '#') != S21_NULL)
      s21_strcat(str1, "0");
    s21_strcat(str1, buff);
  }
  buff_length = s21_strlen(str1);
  if (length > buff_length) {
    if (s21_strchr(spec.flag, '-')) {
      s21_strcat(str, str1);
      for (s21_size_t i = 0; i < length - buff_length; i++, s21_strcat(str, " ")) {}
    } else if (s21_strchr(spec.flag, '0') && !precision) {
      fill_str(str, str1, length - buff_length, "0");
    } else
      fill_str(str, str1, length - buff_length, " ");
  } else
    s21_strcat(str, str1);
  free(str1);
  free(buff);
}

void length_init(char* str, s21_size_t* num, va_list* ap) {
if (*str == '*')
    *num = va_arg(*ap, unsigned int);
  else {
    s21_strtok(str, "*");
    *num = atoi(str);
  }
}

void fill_str(char* str, char* str1, s21_size_t length_diff, char* filler) {
  for (s21_size_t i = 0; i < length_diff; i++, s21_strcat(str, filler)) {}
  s21_strcat(str, str1);
}

void int_to_string(char* str, long long num) {
  char* buff = str;
  s21_size_t len = 0;
  long long n = num;
  for (; n != 0; len++, n /= 10) {}
  for (s21_size_t i = 0; i < len; i++, num /= 10)
    buff[len - (i + 1)] = num % 10 + '0';
  buff[len] = '\0';
}

void u_int_to_string(char* str, unsigned long num) {
  char* buff = str;
  s21_size_t len = 0;
  unsigned long n = num;
  for (; n != 0; len++, n /= 10) {}
  for (s21_size_t i = 0; i < len; i++, num /= 10)
    buff[len - (i + 1)] = num % 10 + '0';
  buff[len] = '\0';
}

void num_conversion(unsigned long n, int base, char *outbuf, struct specifier spec) {
  int i = 0, j, k = 0;
  char buff[30];
  int temp;
  if (n == 0)
    outbuf[0] = spec.precision[0] == '0' ? '\0' : '0';
  while (n != 0) {
    temp = n % base;
    temp += (temp < 10) ? 48 : spec.type == 'X' ? 55 : 87;
    buff[i++] = temp;
    n /= base;
  }
  for (j = i - 1; j >  -1; j--)
  outbuf[k++] = buff[j];
}

int record_char(char *str, struct specifier spec, va_list *ap) {
  s21_size_t width = 0;
  if (s21_strlen(spec.width) != 0) {
    width = atoi(spec.width);
    if (!width)
      return 1;
    if (s21_strchr(spec.flag, '-') == S21_NULL)
      for(s21_size_t i = 0; i < width - 1; i++)
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
    for(s21_size_t i = 0; i < width - 1; i++)
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
      for(s21_size_t i = 0; i < width; i++)
        s21_strcat(str, " ");
    }
    if (wcstombs(str + s21_strlen(str), ws, wcslen(ws) * sizeof(wchar_t)) == 0)
      return 1;
  }
  else {
    char* s = va_arg(*ap, char*);
    width -= s21_strlen(s);
    if (width) {
      for(s21_size_t i = 0; i < width; i++)
        s21_strcat(str, " ");
    }
    s21_strcat(str, s);
  }
  if (width && s21_strchr(spec.flag, '-'))
    for(s21_size_t i = 0; i < width; i++)
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
  return 0;
}

#include "s21_sprintf.h"

s21_size_t s21_sprintf(char *str, const char *format, ...) {
  str[0] = '\0';
  const char* types = "cdieEfgGosuxXpn%%";
  va_list ap;
  va_start(ap, format);
  struct specifier spec;
  for (s21_size_t i = 0; i < s21_strlen(format); i++) {
    specifier_init(&spec);
    if (format[i] == '%') {
      if(format[i+1] == '%'){
        str[s21_strlen(str)] = format[i];
        i++;
      }
      else{
      specifier_parsing((char *) &(format[i + 1]), &spec, &ap);
      record(str, spec, &ap);
      i += s21_strcspn(&format[i + 1], types) + 1;
      }
    }
    else {
      s21_size_t index = s21_strlen(str);
      str[index] = format[i];
      str[index + 1] = '\0';
    }
  }
  return s21_strlen(str);
}

void specifier_parsing(char *str, struct specifier* spec, va_list *ap) {
  char* buff = str;
  char temp[1024];
  char* buff1 = temp;
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
  numbers_parsing(spec->width, buff1, spec, ap);
  char* c = s21_strchr(spec->flag, '*');
  if (c != S21_NULL && s21_strchr(spec->flag, '-') == S21_NULL)
    *c = '-';
  if (*buff == '.') {
    buff++;
    pointer_shift(&buff, buff1, numbers);
    if (*buff1 == '\0')
      s21_strcpy(spec->precision, "0");
    else
      numbers_parsing(spec->precision, buff1, spec, ap);
  }
  s21_memcpy(buff1, buff, s21_strspn((const char*) buff, length));
  for (int i = 0; i < 3; i++) {
    char* c = s21_strchr(buff1, length[i]);
    if (c != S21_NULL) {
      if (length[i] == 'L' || (length[i] == 'h' && (c < s21_strchr(buff1, 'l') || s21_strchr(buff1, 'l') == S21_NULL)) || (length[i] == 'l' && s21_strchr(c + 1, length[i]) == S21_NULL && spec->length[0] != 'h')) {
        spec->length[k++] = length[i];
      } else if (length[i] == 'l' && s21_strchr(c + 1, length[i]) != S21_NULL && spec->length[0] != 'h') {
        spec->length[k++] = length[i];
        spec->length[k++] = length[i];
      } 
    }
  }
  spec->length[k] = '\0';
}

void numbers_parsing(char* str, char* buff, struct specifier* spec, va_list *ap) {
  if (*buff == '*') {
    int star = va_arg(*ap, int);
    if (star < 0)
      s21_strcat(spec->flag, "*");
    int_to_string(str, (long long) star);
  } else
    s21_strcpy(str, buff);
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
void dec_to_hex(char* buf,long long dec){
    for (int i = 0; i < 16; i++) {
        buf[i] = (dec >> (4 * (15 - i))) & 0xF;
        if (buf[i] < 10) {
            buf[i] += '0';
        } else {
            buf[i] += 'a' - 10;
        }
    }
    buf[16] = '\0';
    int l_move = s21_strspn(buf, "0");
    for(int i = 0; i <  16 - l_move; i++){
      buf[i] = buf[i+l_move];
    }
    buf[16 - l_move] = '\0';
}

void record_pointer(char *str, struct specifier spec, va_list *ap) {
  long long pointer = va_arg(*ap, long long);
  char str1[100] = "\0";
  char hex[17];
  dec_to_hex(hex, pointer);
  s21_size_t width = 0;
  width = s21_atoi(spec.width);
  char temp[100];
  int dif = width - s21_strlen(hex) - 2;
  if(width > s21_strlen(hex) + 2){
    for (int i = 0; i < dif; i++){
      if(s21_strchr(spec.flag, '0'))
        temp[i] = '0';
      else
        temp[i] = ' ';
    }
    temp[dif]='\0';
  }
  if(width > s21_strlen(hex) + 2 && !s21_strchr(spec.flag, '0') && !s21_strchr(spec.flag, '-'))
    s21_strcat(str1, temp);
  s21_strcat(str1, "0x");
  if(width > s21_strlen(hex) + 2 && s21_strchr(spec.flag, '0'))
    s21_strcat(str1, temp);
  s21_strcat(str1, hex);
  if(width > s21_strlen(hex) + 2 && !s21_strchr(spec.flag, '0') && s21_strchr(spec.flag, '-'))
    s21_strcat(str1, temp);
  s21_strcat(str, str1);
}

void record(char *str, struct specifier spec, va_list *ap) {
  if (spec.type == 'c') {
    record_char(str, spec, ap);
  } else if (spec.type == 'd' || spec.type == 'i') {
    record_int(str, spec, ap);
  } else if (spec.type == 'e' || spec.type == 'E' || spec.type == 'f' || spec.type == 'g' || spec.type == 'G' ) {
    record_double(str, &spec, ap);
  } else if (spec.type == 'o' || spec.type == 'u' || spec.type == 'x' || spec.type == 'X') {
    record_u_int(str, spec, ap);
  } else if (spec.type == 's') {
    record_str(str, spec, ap);
  } else if (spec.type == 'p') {
    record_pointer(str, spec, ap);
  } else if (spec.type == 'n') {
    int *counter_of_symbols =  va_arg(*ap, int *);
    *counter_of_symbols = s21_strlen(str);
  }
  specifier_init(&spec);
}

void record_int(char *str, struct specifier spec, va_list *ap) {
  if (s21_strchr(spec.length, 'h')) {
    int short_token = va_arg(*ap, int);
    short token = short_token;
    numcat(str, (long long) token, spec);
  } else if (s21_strstr(spec.length, "ll")) {
    long long token = va_arg(*ap, long long);
    numcat(str, token, spec);
  } else if (s21_strchr(spec.length, 'l')) {
    long token = va_arg(*ap, long);
    numcat(str, (long long) token, spec);
  } else {
    int token = va_arg(*ap, int);
    numcat(str, (long long) token, spec);
  }
}

void record_u_int(char *str, struct specifier spec, va_list *ap) {
  if (s21_strchr(spec.length, 'h')) {
    unsigned int short_token = va_arg(*ap, unsigned int);
    unsigned short token = short_token;
    u_numcat(str, (unsigned long) token, spec);
  } else if (s21_strchr(spec.length, 'l')) {
    unsigned long token = va_arg(*ap, unsigned long);
    u_numcat(str, (unsigned long) token, spec);
  } else {
    unsigned int token = va_arg(*ap,unsigned  int);
    u_numcat(str, (unsigned long) token, spec);
  }
}

void numcat(char* str, long long token, struct specifier spec) {
  char temp1[1024], temp2[1024];
  char* str1 = temp1;
  char* buff = temp2;
  *buff = 0;
  *str1 = 0;
  int length = -1, precision = -1;
  if (*spec.width != '\0')
    length = s21_atoi(spec.width);
  if (*spec.precision != '\0' && s21_strchr(spec.flag, '*') == S21_NULL)
    precision = s21_atoi(spec.precision);
  if (token >= 0) {
    if (s21_strchr(spec.flag, '+') != S21_NULL)
      sign_input(str, str1, precision, &length, "+", spec);
    else if (s21_strchr(spec.flag, ' ') != S21_NULL)
      sign_input(str, str1, precision, &length, " ", spec);
  } else
    sign_input(str, str1, precision, &length, "-", spec);
  int_to_string(buff, token);
  int buff_length = s21_strlen(buff);
  if (precision == 0 && token == 0)
    s21_strcat(str1, "");
  else if (precision > buff_length)
    fill_str(str1, buff, precision - buff_length, "0");
  else
    s21_strcat(str1, buff);
  buff_length = s21_strlen(str1);
  if (length > buff_length) {
    if (s21_strchr(spec.flag, '-')) {
      s21_strcat(str, str1);
      for (int i = 0; i < length - buff_length; i++, s21_strcat(str, " ")) {}
    } else if (s21_strchr(spec.flag, '0') && precision < 0) {
      fill_str(str, str1, length - buff_length, "0");
    } else
      fill_str(str, str1, length - buff_length, " ");
  } else
    s21_strcat(str, str1);
}

void u_numcat(char* str, unsigned long token, struct specifier spec) {
  char temp1[1024], temp2[1024];
  char* str1 = temp1;
  char* buff = temp2;
  *buff = 0;
  *str1 = 0;
  int length = -1, precision = -1;
  if (*spec.width != '\0')
    length = s21_atoi(spec.width);
  if (*spec.precision != '\0'  && s21_strchr(spec.flag, '*') == S21_NULL) {
    precision = s21_atoi(spec.precision);
  }
  if (spec.type == 'o')
    num_conversion(token, 8, buff, spec);
  else if (spec.type == 'x' || spec.type == 'X')
    num_conversion(token, 16, buff, spec);
  else
    u_int_to_string(buff, token);
  int buff_length = s21_strlen(buff);
  if (s21_strchr(spec.flag, '#') != S21_NULL) {
    if (spec.type == 'x' && token != 0)
      s21_strcat(str1, "0x");
    else if (spec.type == 'X' && token != 0)
      s21_strcat(str1, "0X");
    else if (spec.type == 'o' && (token != 0 || (precision == 0 && token == 0)) && precision <= buff_length)
      s21_strcat(str1, "0");
  }
  if (precision == 0 && token == 0)
    s21_strcat(str1, "");
  else if (precision > buff_length)
    fill_str(str1, buff, precision - buff_length, "0");
  else
    s21_strcat(str1, buff);
  buff_length = s21_strlen(str1);
  if (length > buff_length) {
    if (s21_strchr(spec.flag, '-') != S21_NULL || (s21_strchr(spec.flag, '*') != S21_NULL && s21_strchr(spec.flag, '-') == S21_NULL)) {
      s21_strcat(str, str1);
      for (int i = 0; i < length - buff_length; i++, s21_strcat(str, " ")) {}
    } else if (s21_strchr(spec.flag, '0') && precision < 0) {
      fill_str(str, str1, length - buff_length, "0");
    } else
      fill_str(str, str1, length - buff_length, " ");
  } else
    s21_strcat(str, str1);
  
}

void sign_input(char* str, char* str1, int precision, int* length, char* fill, struct specifier spec) {
  if (precision < 0 && s21_strchr(spec.flag, '0') != S21_NULL) {
    s21_strcat(str, fill);
    *length -= 1;
  } else
    s21_strcpy(str1, fill);
}

void fill_str(char* str, char* str1, s21_size_t length_diff, char* filler) {
  for (s21_size_t i = 0; i < length_diff; i++, s21_strcat(str, filler)) {}
  s21_strcat(str, str1);
}

void int_to_string(char* str, long long num) {
  char* buff = str;
  s21_size_t len = 0;
  long long n = num;
  if (n == 0)
    s21_strcpy(buff, "0");
  else {
    for (; n != 0; len++, n /= 10) {}
    buff[len - 1] = llabs(num % 10) + '0';
    num /= 10;
    num = llabs(num);
    for (s21_size_t i = 1; i < len; i++, num /= 10)
      buff[len - (i + 1)] = num % 10 + '0';
    buff[len] = '\0';
  }
}
void invert_str(char *origin, char *inverted) {
  if (origin && inverted) {
    int length = 0;
    length = s21_strlen(origin);
    for (int i = 0; i < length; i++) {
      inverted[i] = origin[length - 1 - i];
    }
    inverted[length] = '\0';
  }
}
void int_to_string_precision(char* str, long long num, s21_size_t precision) {
  char wrong[precision+1];
  s21_size_t i =0;
  while (i < precision) {
    wrong[i++] = num%10 + '0';
    num /= 10;
  }
  wrong[i] = '\0';
  invert_str(wrong, str);
}

void u_int_to_string(char* str, unsigned long num) {
  char* buff = str;
  s21_size_t len = 0;
  unsigned long n = num;
  if (n == 0)
    s21_strcpy(buff, "0");
  else {
    for (; n != 0; len++, n /= 10) {}
    for (s21_size_t i = 0; i < len; i++, num /= 10)
      buff[len - (i + 1)] = num % 10 + '0';
    buff[len] = '\0';
  }
}

void num_conversion(unsigned long n, int base, char *outbuf, struct specifier spec) {
  int i = 0, j, k = 0;
  char buff[30];
  int temp;
  if (n == 0)
    s21_strcpy(outbuf, "0");
  else {
    while (n != 0) {
      temp = n % base;
      temp += (temp < 10) ? 48 : spec.type == 'X' ? 55 : 87;
      buff[i++] = temp;
      n /= base;
    }
    for (j = i - 1; j >  -1; j--)
    outbuf[k++] = buff[j];
    outbuf[k] = '\0';
  }
}

int record_char(char *str, struct specifier spec, va_list *ap) {
  long long width = 0;
  if (s21_strlen(spec.width) != 0) {
    width = s21_atoi(spec.width);
    if (s21_strchr(spec.flag, '-') == S21_NULL)
      for(s21_size_t i = 0; i < width - 1; i++)
        s21_strcat(str, " ");
  }
  if (s21_strchr(spec.length, 'l')) {
    wchar_t wchar = va_arg(*ap, wchar_t);
    wchar_t wstr[2] = {0};
    wstr[0] = wchar;
    s21_WchInStr(str, wstr, 1);
  } else {
    char sym = (char)va_arg(*ap, int);
    str[s21_strlen(str) + 1] = '\0';
    str[s21_strlen(str)] = sym;
  }
  if (width && s21_strchr(spec.flag, '-'))
    for(long long i = 0; i < width - 1; i++)
        s21_strcat(str, " ");
  return 0;
}

int record_str(char *str, struct specifier spec, va_list *ap) {
  long long width = 0;
  if (s21_strlen(spec.width) != 0) {
    width = s21_atoi(spec.width);
  }
  if (s21_strchr(spec.length, 'l')) {
    wchar_t *ws = va_arg(*ap, wchar_t*);
    width -= wcslen(ws);
    if (width>=0 && !s21_strchr(spec.flag, '-')) {
      for(long long i = 0; i < width; i++)
        s21_strcat(str, " ");
    }
    if (wcstombs(str + s21_strlen(str), ws, (wcslen(ws)) * sizeof(wchar_t)) == 0)
      return 1;
  }
  else {
    char* s = va_arg(*ap, char*);
    width -= s21_strlen(s);
    if (width>=0 && !s21_strchr(spec.flag, '-')) {
      for(long long i = 0; i < width; i++) {
        s21_strcat(str, " ");
      }
      
    }
    s21_strcat(str, s);
  }
  if (width >= 0 && s21_strchr(spec.flag, '-'))
    for(s21_size_t i = 0; i < width; i++)
      s21_strcat(str, " ");
  return 0;
}

int record_double(char *str, struct specifier *spec, va_list *ap) {
  s21_size_t width = 0;
  s21_size_t precision = 0;
  long long exp = 0;
  long double num;
  width = s21_atoi(spec->width);
  precision = s21_atoi(spec->precision);
  if (s21_strlen(spec->precision) == 0 || s21_strchr(spec->flag, '*'))
    precision = 6;
  if (precision == 0 && s21_strlen(spec->precision) != 0 && s21_strchr("gG", spec->type))
    precision = 1;
  
  if (s21_strchr(spec->length, 'L'))
    num = va_arg(*ap, long double);
  else 
    num = va_arg(*ap, double);
  
  if (S21_isnan(num) || S21_isinf(num)) {
    record_nan_inf(str, num, spec, width);
    return 1;
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
  int flag = 1;
  if (type == 'f') {
    record_f(temp, num, precision, spec->type, exp, spec->flag);
  }
  else {
    record_e(temp, num, precision, spec->type, type, exp, spec->flag);
  }
  if (s21_strchr(spec->flag, '#') && !s21_strchr(temp, '.'))
    s21_strcat(temp, ".");
  if (s21_strlen(temp) < width) {
    flag = 0;
    s21_size_t cnt = width - s21_strlen(temp);
    char filler[2] = "";
    if (s21_strchr(spec->flag, '0'))
      s21_strcat(filler, "0");
    else
      s21_strcat(filler, " ");
    if (!s21_strchr(spec->flag, '-')) {
      char spaces[100] = "";
      for (s21_size_t i = 0; i < cnt; i++)
        s21_strcat(spaces, filler);
      s21_strcat(spaces, temp);
      s21_strcpy(temp, spaces);
    }
    else {
      if (s21_strchr(spec->flag, ' ') && s21_strchr("eE", type)) {
        flag = 1;
        cnt--;
      }
      for (s21_size_t i = 0; i < cnt; i++)
        s21_strcat(temp, " ");
    }
  }
  if (s21_strchr(spec->flag, ' ') && flag) {
    s21_strcat(str, " ");
  }
  
  s21_strcat(str, temp);
  return 0;
}

void record_nan_inf(char* str, long double num, struct specifier *spec, s21_size_t width) {
  char temp[100] = "";
  if (S21_isnan(num)) {
    if (s21_strchr("GE", spec->type))
      s21_strcat(temp, "NAN");
    else
      s21_strcat(temp, "nan");
  }
  if (S21_isinf(num)) {
    if (num < 0)
      s21_strcat(temp, "-");
    else if (s21_strchr(spec->flag, '+'))
      s21_strcat(temp, "+");
    if (s21_strchr("GE", spec->type))
      s21_strcat(temp, "INF");
    else
      s21_strcat(temp, "inf");
  }

  if (s21_strlen(temp) < width) {
    s21_size_t cnt = width - s21_strlen(temp);
    char filler[2] = "";
    s21_strcat(filler, " ");
    if (!s21_strchr(spec->flag, '-')) {
      char spaces[100] = "";
      for (s21_size_t i = 0; i < cnt; i++)
        s21_strcat(spaces, filler);
      s21_strcat(spaces, temp);
      s21_strcpy(temp, spaces);
    }
    else {
      for (s21_size_t i = 0; i < cnt; i++)
        s21_strcat(temp, " ");
    }
  }
  else if (s21_strchr(spec->flag, ' ')) {
      char spaces[100] = " ";
      s21_strcat(spaces, temp);
      s21_strcpy(temp, spaces);
  }
  s21_strcat(str, temp);
}

void record_f(char *temp, long double num, s21_size_t precision, char type, long long exp, char* flag) {
  if (num < 0) {
    s21_strcat(temp, "-");
    num = fabsl(num);
  }
  else if (num >=0 && s21_strchr(flag, '+'))
    s21_strcat(temp, "+");
  num = roundl(num * powl(10.L, precision))/powl(10.L, precision);
  exp = count_exp(num);
  long long num_int = num;
  for (int i = 0; i <= exp; i++) {
    int ind = s21_strlen(temp);
    temp[ind] = (num_int / (long long)(powl(10.L, exp - i))) % 10 + '0';
    temp[ind + 1] = '\0';
  }
  if (exp < 0)
    s21_strcat(temp, "0");
  if (precision)
    s21_strcat(temp, ".");
  num = num - (long long) num;
  num *= powl(10.L, precision);
  num_int = num;
  char buff[precision + 1];
  int_to_string_precision(buff, num_int, precision);
  s21_strcat(temp, buff);
  // for (s21_size_t i = 0; i < precision; i++) {
  //   num *= 10.L;
  //   int digit = fmodl(num, 10.L);
  //   int ind = s21_strlen(temp);
  //   temp[ind] = digit + '0';
  //   temp[ind + 1] = '\0';
  // }
  // exclude zeros
  if ((type == 'g' || type == 'G') && s21_strchr(temp, '.'))
    while(temp[s21_strlen(temp) - 1] == '0' || temp[s21_strlen(temp) - 1] == '.') {
      if (temp[s21_strlen(temp) - 1] == '.') {
        temp[s21_strlen(temp) - 1] = '\0';
        break;
      }
      temp[s21_strlen(temp) - 1] = '\0';
    }
}

void record_e(char *temp, long double num, s21_size_t precision, char type, char other_type, long long exp, char* flag) {
    num = num / powl(10.L, exp);
    if (num < 0) {
      s21_strcat(temp, "-");
      num = fabsl(num);
    }
    if (num >=0 && s21_strchr(flag, '+'))
      s21_strcat(temp, "+");
    num = roundl(num * powl(10.L, precision))/powl(10.L, precision);
    long long num_int = num;
    int ind = s21_strlen(temp);
    temp[ind] = num_int + '0';
    temp[ind + 1] = '\0';
    if (precision || s21_strchr(flag, '#'))
      s21_strcat(temp, ".");
    num = num - (long long) num;
    num_int = roundl(num * powl(10, precision));
    num = (long double)num_int / powl(10, precision);
    char buff[precision + 1];
    int_to_string_precision(buff, num_int, precision);
    s21_strcat(temp, buff);
    // exclude zeros
    if ((type == 'g' || type == 'G') && s21_strchr(temp, '.'))
      while(temp[s21_strlen(temp) - 1] == '0' || temp[s21_strlen(temp) - 1] == '.') {
        if (temp[s21_strlen(temp) - 1] == '.') {
          temp[s21_strlen(temp) - 1] = '\0';
          break;
        }
        temp[s21_strlen(temp) - 1] = '\0';
      }
      
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
      exp = llabs(exp);
      s21_size_t exp_of_exp = count_exp(exp);
      for (s21_size_t i = 0; i < exp_of_exp; i++) {
        int ind = s21_strlen(temp);
        char digit =  (exp/((long long)pow(10, exp_of_exp - i))) + '0';
        exp = exp % (long long)pow(10, exp_of_exp - i);
        temp[ind] = digit;
        temp[ind+1] = '\0';
      }
    }
    ind = s21_strlen(temp);
    temp[ind] = llabs(exp)%10 + '0';
    temp[ind + 1] = '\0';
}

long long count_exp(long double num) {
  long double cpy = num;
  cpy = fabsl(cpy);
  long long exp = 0;
  while (cpy >=10.L && cpy <= LDBL_MAX) {
    exp++;
    cpy /= 10;
  }
  while (cpy < 1L && cpy >= LDBL_TRUE_MIN) {
    exp--;
    cpy *= 10;
  }
  
  return exp;
}
void s21_WchInStr(char *str, wchar_t *wstr, int len) {
  int buflen = 0;
  char *p = S21_NULL;
  buflen = s21_strlen(str);
  p = str + buflen;
  for (int i = 0; i < len; i++) {
    *(p++) = (char)*(wstr++);
  }
  *p = '\0';
}
// int main() {
//   char str1[1000];
//   char str2[1000];
//   char format[] = "This is a simple b%*sba";
//   char str[] = "ooooooo";
//   s21_sprintf(str1, format, 5, str);
//   sprintf(str2, format, 5, str);
//   puts(str1);
//   puts(str2);
// }
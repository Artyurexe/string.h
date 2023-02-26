#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  const char *types = "cdieEfgGosuxXpn%%";
  va_list ap;
  va_start(ap, format);
  struct specifier spec;
  char *string = malloc((strlen(str) + 1) * sizeof(char));
  strcpy(string, str);
  int count_successes = 0;
  if (string[0] == '\0' && format[0] != '\0')
    count_successes = -1;
  int j = 0;
  char c = '\0';

  if (string[0] != '\0') {
    for (size_t i = 0; i < strlen(format) && j < strlen(string); i++) {
      specifier_init(&spec);
      if (format[i] != '%' && (format[i] == string[j])) {
      }
      else if (format[i] != '%' && (format[i] != string[j]) && !s21_isspace(string[j])) {
        break;
      }
      else if (format[i] == '%' && string[j]) {
        while (s21_isspace(string[j])) {
          j++;
        }
        specifier_parsing((char *)&format[i + 1], &spec);
        i += strcspn(&format[i + 1], types) + 1;
        if (format[i]) {
          c = format[i + 1];
        }
        count_successes += match_str_and_format(string, &spec, &ap, &j, c);
        j--;
      }
      j++;
    }
  }
  if (string)
    free(string);
  return count_successes;
}


void specifier_parsing(char *str, struct specifier *spec) {
  char *buff = str;
  char *buff1 = malloc(1024);
  int k = 0;
  const char *flags = "-+ #0";
  const char *numbers = "1234567890*";
  const char *length = "hlL";
  const char *types = "cdieEfgGosuxXpn%%";
  size_t spec_length = strcspn(str, types);
  spec->type = str[spec_length];
  pointer_shift(&spec_length, buff, buff1, flags);
  for (int i = 0; i < 5; i++) {
    if (strchr(buff1, flags[i]) != NULL &&
        ((flags[i] == ' ' && strchr(buff1, '+') == NULL) ||
         (flags[i] == '0' && strchr(buff1, '-') == NULL)))
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
  memcpy(buff1, buff, strspn((const char *)buff, length));
  for (int i = 0; i < 3; i++) {
    char *c = strchr(buff1, length[i]);
    if (c != NULL) {
      if (length[i] == 'L' || (length[i] == 'h' && c < strchr(buff1, 'l')) ||
          (length[i] == 'l' && strchr(c, length[i]) == NULL &&
           spec->length[0] != 'h')) {
        spec->length[k++] = length[i];
      } else if (length[i] == 'l' && strchr(c, length[i]) != NULL &&
                 spec->length[0] != 'h') {
        spec->length[k++] = length[i];
        spec->length[k++] = length[i];
      }
    }
  }
  spec->length[k] = '\0';
  free(buff1);
}

void numbers_parsing(char *str, char *buff) {
  size_t length = strspn((const char *)buff, (const char *)"1234567890");
  if (*buff == '*' && length == 0) length = 1;
  memcpy(str, buff, length);
}

void pointer_shift(size_t *length, char *buff, char *buff1, const char *str) {
  *length = strspn((const char *)buff, str);
  memcpy(buff1, buff, *length);
  buff += *length;
}

void vararg_init(char type, va_list *ap) {
  if (type == 'c') {
    va_arg(*ap, int);
  } else if (type == 'd' || type == 'i') {
    va_arg(*ap, int);
  } else if (type == 'e' || type == 'E' || type == 'f' || type == 'g' ||
             type == 'G') {
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

void specifier_init(struct specifier *spec) {
  spec->flag[0] = '\0';
  spec->width[0] = '\0';
  spec->precision[0] = '\0';
  spec->length[0] = '\0';
  spec->type = 0;
}

int read_d(char *str, va_list *ap, struct specifier *spec, int *j, char c)
{
  int success = 0;
  int i = 0;
  while (str[*j + i] != '\0' && str[*j + i] != c && str[*j + i] != '%') {
    i++;
  }
  char *copy = malloc(i + 1);
  strncpy(copy, str + *j, i);
  copy[i] = '\0';
    if (strcmp(spec->length, "l") == 0) {
      long int *d = va_arg(*ap, long int *);
      *d = atol(copy);
    }
    else if (strcmp(spec->length, "ll") == 0){
      long long *d = va_arg(*ap, long long *);
      *d = atoll(copy);
    }
    else if (strcmp(spec->length,"h") == 0) {
      short *d = va_arg(*ap, short *);
      *d = atoi(copy);
    }
    else {
      int *d = va_arg(*ap, int *);
      *d = atoi(copy);
    }
    if (atol(copy) || atof(copy) || atoll(copy) || atoi(copy) || (copy[0] == '0'))
      success = 1;
  free(copy);
  *j += i;
  return success;
}

int s21_isspace(char c) {
  return (c == ' ' || c == '\n' || c == '\t' || c == '\r');
}

int read_s(char *str, va_list *ap, struct specifier *spec, int *j)
{
  int success = 0;
  int i = 0;
  while (str[*j + i] != '\0' && str[*j + i] != '%' && !s21_isspace(str[*j + i])) {
    i++;
  }
  if (atoi(spec->width) < i && atoi(spec->width) != 0) {
    i = atoi(spec->width);
  }
  if (i > 0 && spec->width[0] != '*') {
    char *copy = malloc(i + 1);
    strncpy(copy, str + *j, i);
    copy[i] = '\0';

    char *new_str = va_arg(*ap, char *);
    strcpy(new_str, copy);
    if (new_str)
      success++;
    free(copy);
  }
  *j += i;
  return success;
}

int match_str_and_format(char *str, struct specifier *spec, va_list *ap, int *j, char c) {
  int success = 0;
  switch (spec->type) {
    case 'd': ;
      success = read_d(str, ap, spec, j, c);
      break;
    case 'c': ;
      char *c = va_arg(*ap, char *);
      *c = str[0];
      break;
    case 'i': ;
      /* 	An integer. Hexadecimal if the input string begins with "0x" or
      "0X", octal if the string begins with "0", otherwise decimal. */
      int *i = va_arg(*ap, int *);
      if (str[0] != '0') {
        *i = atoi(str);
        break;
      } else {
        if (str[1] == 'x') {
          *i = strtol(str, (char **)NULL, 16);
          break;
        } else {
          *i = strtol(str, (char **)NULL, 8);
          break;
        }
      }
      break;
    case 'e': ;
      break;
    case 'E': ;
      /* code */
      break;
    case 'f': ;
      float *f = va_arg(*ap, float *);
      *f = atof(str);
      //printf("atof: %f\n", atof("1234.1234"));
      // sueta
      break;
    case 'g': ;
      /* code */
      break;
    case 'G': ;
      break;
    case 'o': ;
      int *o = va_arg(*ap, int *);
      *o = strtol(str, (char **)NULL, 8);
      break;
    case 's': ;
      success = read_s(str, ap, spec, j);
      break;
    case 'u': ;
      unsigned int *u = va_arg(*ap, unsigned int *);
      *u = atoi(str);
      // undefined behaviour when the number is negative?
      break;
    case 'x': ;
      int *x = va_arg(*ap, int *);
      *x = strtol(str, (char **)NULL, 16);
      break;
    case 'X': ;
      int *X = va_arg(*ap, int *);
      *X = strtol(str, (char **)NULL, 16);
      break;
    case 'p': ;
      break;
    case 'n': ;
      int *n = va_arg(*ap, int *);
      *n = 0;
      break;
  }
  return success;
}

// int main() {
//   char str1[30];
//   char str2[30];
//   char str3[30];
//   char str4[40];
//   char str5[30];
//   char str6[30];
//   char str7[30];
//   char str8[40];
//   char format[] = "%*s%*s%*s%*s";
//   char str[] = "gcc -Wall -Wextra -Werror -std=c11 -fsanitize=address";
//   s21_sscanf(str, format, str1, str2, str3, str4);
//   printf("str1: %s\n str2: %s\n  str3: %s\n  str4:  %s\n", str1, str2, str3, str4);
//   sscanf(str, format, str5, str6, str7, str8);
//   printf("str1: %s\n str2: %s\n  str3: %s\n  str4:  %s\n", str5, str6, str7, str8);

//   // char fstr[] = "%d.%d %*d%d";
//   // char str[] = "  12321.999  -111   \n 77777";
//   // int d1, d2, d3, d4;
//   // s21_sscanf(str, fstr, &d1, &d2, &d3, &d4);
//   // printf("s21: %d\n", s21_sscanf(str, fstr, &d1, &d2, &d3, &d4));
//   // printf("d1 %d  d2 %d  d3 %d  d4 %d\n", d1, d2, d3, d4);
//   // sscanf(str, fstr, &d1, &d2, &d3, &d4);
//   // printf("ss: %d\n", sscanf(str, fstr, &d1, &d2, &d3, &d4));
//   // printf("d1 %d  d2 %d  d3 %d  d4 %d\n", d1, d2, d3, d4);
// }
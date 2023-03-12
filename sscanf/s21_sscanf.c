#include "s21_sscanf.h"
#include "../standard_functions/s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  const char *types = "cdieEfgGosuxXpn%%";
  va_list ap;
  va_start(ap, format);
  struct specif spec;
  char *string = malloc((s21_strlen(str) + 1) * sizeof(char));
  s21_strcpy(string, str);
  int success = 0;
  int count_successes = 0;
  if ((string[0] == '\0' || s21_empty_str(string)) && format[0] != '\0')
    count_successes = -1;
  int j = 0;
  char c = '\0';

  if (!s21_empty_str(string) && string[0] != '\0') {
    for (size_t i = 0; i < s21_strlen(format) && (size_t)j < s21_strlen(string); i++) {
      scanf_specif_init(&spec);
      if (format[i] && s21_isspace(format[i])) {
        while (s21_isspace(string[j]) && string[i]) {
          j++;
        }
      }
      while (format[i] && s21_isspace(format[i])) {
        i++;
      }
      if (format[i] != '%' && (format[i] == string[j])) {
      } else if (format[i] != '%' && (format[i] != string[j]) &&
                 !s21_isspace(string[j])) {
        break;
      } else if (format[i] == '%' && format[i + 1] == '%') {
        i++;
      } else if (format[i] == '%' && string[j] == '%') {
        i++;
        j++;
      } else if (format[i] && string[j] && format[i] == '%' && string[j]) {
        scanf_specifier_parse((char *)&format[i + 1], &spec);
        i += s21_strcspn(&format[i + 1], types) + 1;
        while (s21_isspace(string[j]) && spec.type != 'c') {
          j++;
        }
        if (format[i]) {
          c = format[i + 1];
        }
        success = match_str_and_format(string, &spec, &ap, &j, c);
        if (success) {
          count_successes++;
          if (spec.width[0] == '*') {
            count_successes--;
          }
        } else if (!success &&
                   (spec.type == 'i' || spec.type == 'd' || spec.type == 'u' ||
                    spec.type == 'o' || spec.type == 'x' || spec.type == 'X')) {
          break;
        }
        j--;
      }
      j++;
    }
  }
  if (string) free(string);
  return count_successes;
}

void scanf_specifier_parse(char *str, struct specif *spec) {
  char *buff = str;
  char *buff1 = malloc(1024);
  char *buff2 = buff1;
  int k = 0;
  const char *flags = "-+ #0";
  const char *numbers = "1234567890*";
  const char *length = "hlL";
  const char *types = "cdieEfgGosuxXpn%%";
  spec->type = str[s21_strcspn(str, types)];
  scanf_pointer_shift(&buff, buff1, flags);
  for (int i = 0; i < 5; i++) {
    if (s21_strchr(buff1, flags[i]) != S21_NULL &&
        ((flags[i] == ' ' && s21_strchr(buff1, '+') == S21_NULL) ||
         (flags[i] == '0' && s21_strchr(buff1, '-') == S21_NULL) || flags[i] == '-' ||
         flags[i] == '+' || flags[i] == '#'))
      spec->flag[k++] = flags[i];
  }
  spec->flag[k] = '\0';
  k = 0;
  scanf_pointer_shift(&buff, buff1, numbers);
  scanf_numbers_parse(spec->width, buff1);
  if (*buff == '.') {
    buff++;
    scanf_pointer_shift(&buff, buff1, numbers);
    if (*buff1 == '\0')
      s21_strcpy(spec->precision, "0");
    else
      scanf_numbers_parse(spec->precision, buff1);
  }
  s21_memcpy(buff1, buff, s21_strspn((const char *)buff, length));
  for (int i = 0; i < 3; i++) {
    char *c = s21_strchr(buff1, length[i]);
    if (c != S21_NULL) {
      if (length[i] == 'L' ||
          (length[i] == 'h' &&
           (c < s21_strchr(buff1, 'l') || s21_strchr(buff1, 'l') == S21_NULL)) ||
          (length[i] == 'l' && s21_strchr(c + 1, length[i]) == S21_NULL &&
           spec->length[0] != 'h')) {
        spec->length[k++] = length[i];
      } else if (length[i] == 'l' && s21_strchr(c + 1, length[i]) != S21_NULL &&
                 spec->length[0] != 'h') {
        spec->length[k++] = length[i];
        spec->length[k++] = length[i];
      }
    }
  }
  spec->length[k] = '\0';
  free(buff2);
}

void scanf_numbers_parse(char *str, char *buff) {
  size_t length = s21_strspn((const char *)buff, "1234567890");
  if (*buff == '*' && length == 0) length = 1;
  s21_strcpy(str, buff);
  buff[length + 1] = '\0';
}

void scanf_pointer_shift(char **buff, char *buff1, const char *str) {
  size_t length = s21_strspn((const char *)*buff, str);
  s21_strncpy(buff1, *buff, length);
  buff1[length] = '\0';
  *buff += length;
}

void scanf_specif_init(struct specif *spec) {
  spec->flag[0] = '\0';
  spec->width[0] = '\0';
  spec->precision[0] = '\0';
  spec->length[0] = '\0';
  spec->type = 0;
}

int read_d(char *str, va_list *ap, struct specif *spec, int *j, char c) {
  int success = 0;
  int i = 0;
  while (str[*j + i] != '\0' && !s21_isspace(str[*j + i]) && str[*j + i] != c &&
         str[*j + i] != '%' && s21_isdigit(str[*j + i])) {
    if (i > 0 && (str[*j + i] == '-' || str[*j + i] == '+')) {
      break;
    }
    i++;
  }
  if (s21_atoi(spec->width) != 0 && s21_atoi(spec->width) < i) {
    i = s21_atoi(spec->width);
  }
  char *copy = malloc(i + 1);
  s21_strncpy(copy, str + *j, i);
  copy[i] = '\0';
  if (spec->width[0] != '*') {
    if (s21_strcmp(spec->length, "l") == 0) {
      long int *d = va_arg(*ap, long int *);
      *d = s21_atol(copy);
    } else if (s21_strcmp(spec->length, "ll") == 0) {
      long long *d = va_arg(*ap, long long *);
      *d = s21_atoll(copy);
    } else if (s21_strcmp(spec->length, "h") == 0) {
      short *d = va_arg(*ap, short *);
      *d = s21_atoi(copy);
    } else {
      int *d = va_arg(*ap, int *);
      *d = s21_atoi(copy);
    }
    if ((copy) && (s21_atol(copy) || s21_atoll(copy) || s21_atoi(copy) ||
                   ((s21_strcmp(copy, "0") == 0 || s21_strcmp(copy, "-0") == 0 ||
                     s21_strcmp(copy, "+0") == 0) &&
                    s21_atoi(copy) == 0)))
      success = 1;
  } else if (copy) {
    success = 1;
  }
  free(copy);
  *j += i;
  return success;
}

int read_s(char *str, va_list *ap, struct specif *spec, int *j) {
  int success = 0;
  int i = 0;
  while (str[*j + i] != '\0' && !s21_isspace(str[*j + i])) {
    i++;
  }
  if (s21_atoi(spec->width) < i && s21_atoi(spec->width) != 0) {
    i = s21_atoi(spec->width);
  }
  if (i > 0 && spec->width[0] != '*') {
    char *copy = malloc(i + 1);
    s21_strncpy(copy, str + *j, i);
    copy[i] = '\0';

    char *new_str = va_arg(*ap, char *);
    s21_strcpy(new_str, copy);
    if (new_str) success++;
    free(copy);
  }
  *j += i;
  return success;
}

int read_c(char *str, va_list *ap, struct specif *spec, int *j) {
  int success = 0;
  if (spec->width[0] != '*') {
    char *c = va_arg(*ap, char *);
    *c = str[*j];
    if (c) success = 1;
  }
  (*j)++;
  return success;
}

int read_u(char *str, va_list *ap, struct specif *spec, int *j, char c) {
  char *end = S21_NULL;
  int success = 0;
  int i = 0;
  while (str[*j + i] != '\0' && !s21_isspace(str[*j + i]) && str[*j + i] != c &&
         str[*j + i] != '%' && s21_isdigit(str[*j + i])) {
    if (i > 0 && (str[*j + i] == '-' || str[*j + i] == '+')) {
      break;
    }
    i++;
  }
  if (s21_atoi(spec->width) && s21_atoi(spec->width) < i) {
    i = s21_atoi(spec->width);
  }
  if (spec->width[0] != '*') {
    char *copy = malloc(i + 1);
    s21_strncpy(copy, str + *j, i);
    copy[i] = '\0';
    if (s21_strcmp(spec->length, "l") == 0) {
      unsigned long int *u = va_arg(*ap, unsigned long int *);
      *u = s21_strtoul(copy, &end, 10);
    } else if (s21_strcmp(spec->length, "ll") == 0) {
      unsigned long long int *u = va_arg(*ap, unsigned long long int *);
      *u = s21_strtoull(copy, &end, 10);
    } else {
      unsigned int *u = va_arg(*ap, unsigned int *);
      *u = s21_strtoul(copy, &end, 10);
    }
    if (s21_strtoul(copy, &end, 10) || s21_strcmp(copy, "0") == 0) {
      success = 1;
    }
    free(copy);
  }
  *j += i;
  return success;
}

int read_o(char *str, va_list *ap, struct specif *spec, int *j, char c) {
  int i = 0;
  int success = 0;
  while (str[*j] == '0') (*j)++;
  while (str[*j + i] != '\0' && !s21_isspace(str[*j + i]) && str[*j + i] != c &&
         str[*j + i] != '%' && s21_isoctal(str[*j + i])) {
    i++;
  }
  if (s21_atoi(spec->width) && s21_atoi(spec->width) < i) {
    i = s21_atoi(spec->width);
  }
  if (spec->width[0] != '*') {
    if (str[*j - 1] == '0' && i == 0) {
      // i = 1;
      success++;
    }
    char *copy = malloc(i + 1);
    s21_strncpy(copy, str + *j, i);
    copy[i] = '\0';
    if (s21_strcmp(spec->length, "l") == 0) {
      long int *d = va_arg(*ap, long int *);
      *d = s21_strtol(copy, (char **)S21_NULL, 8);
    } else if (s21_strcmp(spec->length, "ll") == 0) {
      long long *d = va_arg(*ap, long long *);
      *d = s21_strtoll(copy, (char **)S21_NULL, 8);
    } else if (s21_strcmp(spec->length, "h") == 0) {
      short *d = va_arg(*ap, short *);
      *d = s21_strtol(copy, (char **)S21_NULL, 8);
    } else {
      int *d = va_arg(*ap, int *);
      *d = s21_strtol(copy, (char **)S21_NULL, 8);
    }
    if (s21_strtol(copy, (char **)S21_NULL, 8) || (copy[0] == '0')) success = 1;
    free(copy);
  }
  *j += i;
  return success;
}

int read_xX(char *str, va_list *ap, struct specif *spec, int *j, char c) {
  int i = 0;
  int success = 0;
  while (str[*j + i] != '\0' && !s21_isspace(str[*j + i]) && str[*j + i] != c &&
         str[*j + i] != '%' && s21_ishex(str[*j + i])) {
    i++;
  }
  if (s21_atoi(spec->width) && s21_atoi(spec->width) < i) {
    i = s21_atoi(spec->width);
  }
  if (spec->width[0] != '*') {
    char *copy = malloc(i + 1);
    s21_strncpy(copy, str + *j, i);
    copy[i] = '\0';

    if (s21_strcmp(spec->length, "l") == 0) {
      unsigned long int *x = va_arg(*ap, unsigned long int *);
      *x = s21_strtol(copy, (char **)S21_NULL, 16);
    } else if (s21_strcmp(spec->length, "ll") == 0) {
      unsigned long long int *x = va_arg(*ap, unsigned long long int *);
      *x = s21_strtol(copy, (char **)S21_NULL, 16);
    } else {
      unsigned int *x = va_arg(*ap, unsigned int *);
      *x = s21_strtol(copy, (char **)S21_NULL, 16);
    }
    // if X?????how to make upper case
    if (s21_strtol(copy, (char **)S21_NULL, 16) || (copy[0] == '0')) success = 1;
    free(copy);
  }
  *j += i;
  return success;
}

int read_f(char *str, va_list *ap, struct specif *spec, int *j, char c) {
  int i = 0;
  int success = 0;
  while (str[*j + i] != '\0' && !s21_isspace(str[*j + i]) && str[*j + i] != c &&
         str[*j + i] != '%') {
    i++;
  }
  if (s21_atoi(spec->width) && s21_atoi(spec->width) < i) {
    i = s21_atoi(spec->width);
  }
  if (spec->width[0] != '*') {
    char *copy = malloc(i + 1);
    s21_strncpy(copy, str + *j, i);
    copy[i] = '\0';
    if (s21_strcmp(spec->length, "L") == 0) {
      long double *f = va_arg(*ap, long double *);
      *f = s21_atold(copy);
    } else if (s21_strcmp(spec->length, "l") == 0) {
      double *f = va_arg(*ap, double *);
      *f = s21_atold(copy);
    } else {
      float *f = va_arg(*ap, float *);
      *f = s21_atold(copy);
    }
    if (s21_atold(copy) || (copy[0] == '0')) success = 1;
    free(copy);
  }
  *j += i;
  return success;
}

int read_g(char *str, va_list *ap, struct specif *spec, int *j, char c) {
  return read_f(str, ap, spec, j, c);
}

int read_e(char *str, va_list *ap, struct specif *spec, int *j, char c) {
  return read_f(str, ap, spec, j, c);
}

int read_i(char *str, va_list *ap, struct specif *spec, int *j, char c) {
  int i = 0;
  int success = 0;
  while (str[*j + i] != '\0' && !s21_isspace(str[*j + i]) && str[*j + i] != c &&
         str[*j + i] != '%') {
    i++;
  }
  if (s21_atoi(spec->width) && s21_atoi(spec->width) < i) {
    i = s21_atoi(spec->width);
  }
  if (spec->width[0] != '*') {
    char *copy = malloc(i + 1);
    s21_strncpy(copy, str + *j, i);
    copy[i] = '\0';
    int sign = 0;
    if (copy[0] == '-') {
      sign = 1;
    }
    if (copy[sign] != '0') {
      success = read_d(str, ap, spec, j, c);
    } else {
      if (copy[1 + sign] == 'x' || copy[1 + sign] == 'X') {
        success = read_xX(str, ap, spec, j, c);
      } else {
        success = read_o(str, ap, spec, j, c);
      }
    }
    if (s21_atoll(copy) || s21_strtol(copy, (char **)S21_NULL, 16) ||
        s21_strtol(copy, (char **)S21_NULL, 8) || (copy[0] == '0'))
      success = 1;
    free(copy);
  }
  return success;
}

int match_str_and_format(char *str, struct specif *spec, va_list *ap, int *j,
                         char c) {
  int success = 0;
  switch (spec->type) {
    case 'd':;
      success = read_d(str, ap, spec, j, c);
      break;
    case 'c':;
      success = read_c(str, ap, spec, j);
      break;
    case 'i':;
      success = read_i(str, ap, spec, j, c);
      break;
    case 'e':
      success = read_e(str, ap, spec, j, c);
      break;
    case 'E':;
      success = read_e(str, ap, spec, j, c);
      break;
    case 'f':;
      success = read_f(str, ap, spec, j, c);
      break;
    case 'g':
      success = read_g(str, ap, spec, j, c);
      break;
    case 'G':;
      success = read_g(str, ap, spec, j, c);
      break;
    case 'o':
      success = read_o(str, ap, spec, j, c);
      break;
    case 's':;
      success = read_s(str, ap, spec, j);
      break;
    case 'u':;
      success = read_u(str, ap, spec, j, c);
      break;
    case 'x':;
      success = read_xX(str, ap, spec, j, c);
      break;
    case 'X':;
      success = read_xX(str, ap, spec, j, c);
      break;
    case 'p':;
      break;
    case 'n':;
      int *n = va_arg(*ap, int *);
      *n = *j;
      break;
  }
  return success;
}

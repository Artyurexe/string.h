#include "s21_sscanf2.h"

void s21_sscanf(char *str, const char *format, ...) {
  const char *types = "cdieEfgGosuxXpn%%";
  va_list ap;
  va_start(ap, format);
  struct specifier spec;

  char *string = malloc((strlen(str) + 1) * sizeof(char));
  strcpy(string, str);

  //здесь должна просиходить проверка на корректность форматной строки
  //если находится ошибка, следующий код не должен выполняться
  char *string_token = strtok(string, " \n\t\r");
  for (size_t i = 0; i < strlen(format); i++) {
    specifier_init(&spec);
    if (format[i] == '%') {
      specifier_parsing((char *)&format[i + 1], &spec);
      match_str_and_format(string_token, spec, &ap);
      i += strcspn(&format[i + 1], types) + 1;
      string_token = strtok(NULL, " \n\t\r");
    }
  }

  free(string);
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

void match_str_and_format(char *str, struct specifier spec, va_list *ap) {
  switch (spec.type) {
    case 'd':
      int *d = va_arg(*ap, int *);
      *d = atoi(str);
      break;
    case 'c':
      char *c = va_arg(*ap, char *);
      *c = str[0];
      break;
    case 'i':
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
    case 'e':
      break;
    case 'E':
      /* code */
      break;
    case 'f':
      float *f = va_arg(*ap, float *);
      *f = atof(str);
      printf("atof: %f\n", atof("1234.1234"));
      // sueta
      break;
    case 'g':
      /* code */
      break;
    case 'G':
      break;
    case 'o':
      int *o = va_arg(*ap, int *);
      *o = strtol(str, (char **)NULL, 8);
      break;
    case 's':
      char *new_str = va_arg(*ap, char *);
      strcpy(new_str, str);
      break;
    case 'u':
      unsigned int *u = va_arg(*ap, unsigned int *);
      *u = atoi(str);
      // undefined behaviour when the number is negative?
      break;
    case 'x':
      int *x = va_arg(*ap, int *);
      *x = strtol(str, (char **)NULL, 16);
      break;
    case 'X':
      int *X = va_arg(*ap, int *);
      *X = strtol(str, (char **)NULL, 16);
      break;
    case 'p':
      break;
    case 'n':
      /* code */
      break;
  }
}

int main() {
  char str[100];
  int d;
  char c;
  float f;
  unsigned int u;
  int i;
  int x;
  int X;
  int o;
  s21_sscanf("1 hey -10", "%d%s", &d, str, &u);
  s21_sscanf("hey 1234.1234", "%c%f", &c, &f);
  s21_sscanf("0x1a2 0xA12 0xa123 12", "%i%x%X%o", &i, &x, &X, &o);

  sscanf("-10 hey 0x1A2 0xA12 12", "%u%s%i%x%o", &u, str, &i, &x, &o);
  printf("u: %u\n", u);
  printf("f: %f\n", f);
  printf("str: %s\n", str);
  printf("c: %c\n", c);
  printf("d: %d\n", d);
  printf("i: %i\n", i);
  printf("x: %x\n", x);
  printf("X: %X\n", X);
  printf("o: %o\n", o);
}
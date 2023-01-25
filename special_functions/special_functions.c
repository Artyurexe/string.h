#include <stdlib.h>

void *s21_to_upper(const char *str) {
  char* buff = calloc(strlen(str), sizeof(char));
  for (size_t i = 0; i < s21_strlen(str); i++) {
    if (str[i] > 96 && str[i] < 123)
      buff[i] = str[i] - 32;
    else 
      buff[i] = str[i];
  }
  return buff;
}

void *s21_to_lower(const char *str) {
  char* buff = calloc(s21_strlen(str), sizeof(char));
  for (size_t i = 0; i < s21_strlen(str); i++) {
    if (str[i] > 64 && str[i] < 91)
      buff[i] = str[i] + 32;
    else 
      buff[i] = str[i];
  }
  return buff;
}

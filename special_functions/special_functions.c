#include <stdlib.h>

void *s21_to_upper(const char *str) {
  char* buff = calloc(s21_strlen(str), sizeof(char));
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    if (str[i] > 96 && str[i] < 123)
      buff[i] = str[i] - 32;
    else 
      buff[i] = str[i];
  }
  return buff;
}

void *s21_to_lower(const char *str) {
  char* buff = calloc(s21_strlen(str), sizeof(char));
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    if (str[i] > 64 && str[i] < 91)
      buff[i] = str[i] + 32;
    else 
      buff[i] = str[i];
  }
  return buff;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (start_index > s21_strlen(src))
    return NULL;
  char* buff = calloc(s21_strlen(str), sizeof(char));
  s21_size_t k = 0;
  for (s21_size_t i = 0; i < s21_strlen(src) + s21_strlen(str); i++) {
    if (i < start_index) {
      buff[i] = src[i];
    } else if (i >= start_index && i < start_index + s21_strlen(str)) {
      buff[i] = str[k];
      k++;
    } else 
      buff[i] = src[i - s21_strlen(str)];
  }
  return buff;
}

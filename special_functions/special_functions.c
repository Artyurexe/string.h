#include <stdlib.h>
#include <string.h>
#include "../standard_functions/s21_string.h"
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


void *s21_trim(const char *src, const char *trim_chars) {
    if (s21_strlen(src) == 0)
        return S21_NULL;
    s21_size_t from_start = 0, from_end = 0;
    int flag = 0, other_flag = 0, i = 0;
    /*
    while (!flag) {
        for (int j = 0; j < s21_strlen(trim_chars) && !other_flag; j++)
            if (s21_strchr(src + from_start, trim_chars[j]) == src + from_start) {
                from_start++;
                other_flag = 1;
            }
        if (!other_flag)
            flag = 1;
    }*/
    flag = 0, other_flag = 0;
    /*while (!flag) {
        i = s21_strlen(src) - 2;
        for (int j = s21_strlen(trim_chars) - 1; j >= 0 && !other_flag; j--)
            if (strchr(src + i - from_end, trim_chars[j]) == src + i - from_end) {
                from_end++;
                other_flag = 1;
            }
        if (!other_flag)
            flag = 1;
    }*/
    if (from_end + from_start >= s21_strlen(src))
        return S21_NULL;
    char *res = malloc(sizeof(char) * (s21_strlen(src) - from_end - from_start));
    res = s21_strncpy(res, src + from_start, (s21_strlen(src) - from_end - from_start));
    return res;
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

int main () {
    char charsToTrim[] = " *";
    char* banner = "*** Much Ado About Nothing ***";
    char* result = s21_trim(banner, charsToTrim);
    printf("%s", result);
}